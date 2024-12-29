#include "FadipSink.h"
#include "../FadipNetworkProtocol.h"
#include "inet/common/ProtocolTag_m.h"
Define_Module(FadipSink);

void FadipSink::initialize(int stage)
{
    if (stage == inet::INITSTAGE_LOCAL) {
        topic = par("topic").stringValue();
        operationalState = State::OPERATING;
        const std::string name = getParentModule()->getFullName();
        const std::string messageName = name + "_" + topic;
        auto subPacket = new inet::Packet(messageName.c_str());
        auto subChunk = inet::makeShared<SubscribeMessage>();
        subChunk->setTopic(topic);
        subChunk->setType(PubSubMessageType::Subscription);
        subPacket->insertAtFront(subChunk);
        scheduleAt(0, subPacket);
        WATCH(recivedMessages);
        WATCH_VECTOR(recivedMessagesV);
    } else if (stage == inet::INITSTAGE_APPLICATION_LAYER) {
        // inet::registerService(FadipNetworkProtocol::pubsupDataProtocol, gate("socketOut"), gate("socketIn"));
        inet::registerProtocol(FadipNetworkProtocol::pubsupDataProtocol, gate("socketOut"), gate("socketIn"));
    }
}

void FadipSink::handleMessage(inet::cMessage *msg)
{
    inet::ApplicationBase::handleMessage(msg);
}

void FadipSink::handleStartOperation(inet::LifecycleOperation *operation) {}
void FadipSink::handleStopOperation(inet::LifecycleOperation *operation) {}
void FadipSink::handleCrashOperation(inet::LifecycleOperation *operation) {}
void FadipSink::handleMessageWhenUp(inet::cMessage *msg) {
    EV_INFO << "FadipSink::handleMessageWhenUp MESSAGE: " << msg << inet::endl;
    if (msg->isSelfMessage()){
        auto& tags = check_and_cast<inet::ITaggedObject *>(msg)->getTags();
        tags.addTagIfAbsent<inet::DispatchProtocolReq>()->setProtocol(&FadipNetworkProtocol::pubsupProtocol);
        send(msg, gate("socketOut"));
    } else {
        EV_INFO << "RECIVED MESSAGE: " << msg << inet::endl;
        auto packet = dynamic_cast<inet::Packet *>(msg);
        auto pubSubChunk = packet->peekAtFront<PubSubMessage>();
        if (pubSubChunk->getType() == PubSubMessageType::Publication) {
            if (strcmp(topic, pubSubChunk->getTopic()) == 0 && !inet::contains(recivedMessagesV, pubSubChunk->getNonce())){
                recivedMessagesV.emplace_back(pubSubChunk->getNonce());
                recivedMessages++;
                EV_INFO << "RECIVED PUBLISH MESSAGE TOPIC: " << pubSubChunk->getTopic() << " FROM: " << pubSubChunk->getNodeName() << inet::endl;
            }
        }
        delete msg;
    }
}
void FadipSink::finish() {
    EV_INFO << "Number of Recived Messages on " << topic << ": " << recivedMessages << inet::endl;
}
