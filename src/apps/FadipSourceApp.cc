#include "FadipSourceApp.h"
#include "../FadipNetworkProtocol.h"
#include "inet/common/ProtocolTag_m.h"
Define_Module(FadipSourceApp);

void FadipSourceApp::initialize(int stage)
{
    if (stage == inet::INITSTAGE_LOCAL) {
        topic = par("topic").stringValue();
        operationalState = State::OPERATING;
        const std::string name = getParentModule()->getFullName();
        const std::string messageName = name + "_" + topic;
        auto pubPacket = new inet::Packet(messageName.c_str());
        auto pubChunk = inet::makeShared<PublishMessage>();
        pubChunk->setTopic(topic);
        pubChunk->setType(PubSubMessageType::Publication);
        pubPacket->insertAtFront(pubChunk);
        double delay = par("delay").doubleValue();
        scheduleAt(delay, pubPacket);
    }
}

void FadipSourceApp::handleMessage(inet::cMessage *msg)
{
    inet::ApplicationBase::handleMessage(msg);
}

void FadipSourceApp::handleStartOperation(inet::LifecycleOperation *operation) {}
void FadipSourceApp::handleStopOperation(inet::LifecycleOperation *operation) {}
void FadipSourceApp::handleCrashOperation(inet::LifecycleOperation *operation) {}
void FadipSourceApp::handleMessageWhenUp(inet::cMessage *msg) {
    if (msg->isSelfMessage()){
        // scheduleAfter(0.1, msg->dup());
        auto& tags = check_and_cast<inet::ITaggedObject *>(msg)->getTags();
        tags.addTagIfAbsent<inet::DispatchProtocolReq>()->setProtocol(&FadipNetworkProtocol::pubsupProtocol);
        send(msg, gate("socketOut"));
    } else {
        EV_INFO << "Message Received in FadipSource!" << *msg << inet::endl;
    }
}
