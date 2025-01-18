#include "FadipNetworkProtocol.h"
#include "inet/common/stlutils.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
using inet::endl;
Define_Module(FadipNetworkProtocol);
FadipNetworkProtocol::FadipNetworkProtocol() {
}

FadipNetworkProtocol::~FadipNetworkProtocol() {
}

void FadipNetworkProtocol::initialize(int stage)
    {
    NetworkProtocolBase::initialize(stage);
    if (stage == inet::INITSTAGE_LOCAL) {
        FadipNetworkProtocol::numberOfBroadcasts = 0;
        FadipNetworkProtocol::numberOfSubBroadcasts = 0;
        FadipNetworkProtocol::numberOfPubBroadcasts = 0;
        FadipNetworkProtocol::nonceCounter = 0;
        FadipNetworkProtocol::totalSentMessages = 0;
        FadipNetworkProtocol::totalSentMessagesToSubs = 0;
        FadipNetworkProtocol::totalReceivedMessages = 0;
        FadipNetworkProtocol::topicSubscripers.clear();
        if (inet::ProtocolGroup::getEthertypeProtocolGroup()->findProtocol(0xBBBB) == nullptr) {
            // Add Protocol assume that it's dynamic, and fuck it :)
            inet::ProtocolGroup::getEthertypeProtocolGroup()->addProtocol(getProtocol().getId(), &getProtocol());
        }
        hcMaxSubscribe = par("hcMaxSubscribe");
        hcMaxPublish = par("hcMaxPublish");
        name = getParentModule()->getParentModule()->getFullName();
        WATCH_VECTOR(myTopics);
        WATCH_MAP(topicSubscripers);
        WATCH(FadipNetworkProtocol::numberOfBroadcasts);
        WATCH(FadipNetworkProtocol::numberOfSubBroadcasts);
        WATCH(FadipNetworkProtocol::numberOfPubBroadcasts);
        WATCH(FadipNetworkProtocol::nonceCounter);
    }
}
void FadipNetworkProtocol::handleMessage(inet::cMessage *msg)
{
    if (isUpperMessage(msg)) {
        auto packet = dynamic_cast<inet::Packet *>(msg);
        if (packet->peekAtFront<PubSubMessage>()->getType() == PubSubMessageType::Publication) {
            auto pubChunk = inet::makeShared<PublishMessage>(*packet->popAtFront<PublishMessage>());
            pubChunk->setNodeName(name);
            pubChunk->setNonce(FadipNetworkProtocol::nonceCounter++);
            packet->insertAtFront(pubChunk);
        } else {
            auto subChunk = inet::makeShared<SubscribeMessage>(*packet->popAtFront<SubscribeMessage>());
            subChunk->setNodeName(name);
            subChunk->setNonce(FadipNetworkProtocol::nonceCounter++);
            packet->insertAtFront(subChunk);
        }
    }
    auto packet = dynamic_cast<inet::Packet *>(msg);
    auto pubSubChunk = packet->peekAtFront<PubSubMessage>();
    if (inet::contains(seenMessages, pubSubChunk->getNonce())) {
        delete msg;
        return;
    }
    seenMessages.emplace_back(pubSubChunk->getNonce());
    if (pubSubChunk->getType() == PubSubMessageType::Subscription) {
        handleSubscription(packet);
    }
    if (pubSubChunk->getType() == PubSubMessageType::Publication) {
        handlePublication(packet);
    }
    EV_INFO << "Handling message: " << msg->getName() << " from " << msg->getSenderModule()->getFullName() << endl;
    delete msg;
}

void FadipNetworkProtocol::addSubscription(inet::Packet *packet, inet::Ptr<const SubscribeMessage> subMessage) {

    std::string topic = subMessage->getTopic();
    std::string nodeName = subMessage->getNodeName();
    if (isUpperMessage(packet)) {
        myTopics.push_back(topic);
        EV_INFO << "Adding my own subscription: Topic=" << topic << ", Node=" << nodeName << endl;
        return;
    }
    if (!inet::contains(knownTopics, topic)) {
        knownTopics.push_back(topic);
    }
    inet::MacAddress nextHopMac = packet->getTag<inet::MacAddressInd>()->getSrcAddress();
    auto& subscribers = subscriptionTable[topic]; // Get or create the list of subscribers for the topic

    // Check if the subscription already exists
    for (const auto& entry : subscribers) {
        if (entry.nodeName == nodeName && entry.nextHopMac == nextHopMac) {
            EV_INFO << "Subscription already exists: Topic=" << topic << ", Node=" << nodeName << ", NextHopMAC=" << nextHopMac << endl;
            return; // Do nothing if already subscribed
        }
    }

    // Add the new subscription
    EV_INFO << "Adding subscription: Topic=" << topic << ", Node=" << nodeName << ", NextHopMAC=" << nextHopMac << endl;
    subscribers.emplace_back(topic, nodeName, nextHopMac);
}

void FadipNetworkProtocol::handleSubscription(inet::Packet *packet) {
    auto subChunk = packet->peekAtFront<SubscribeMessage>();
    addSubscription(packet, subChunk);

    if (subChunk->getHopCount() + 1 < hcMaxSubscribe) {
        FadipNetworkProtocol::numberOfSubBroadcasts++;
        broadcastMessage(packet);
    } else {
        inet::PacketDropDetails details;
        details.setReason(inet::PacketDropReason::HOP_LIMIT_REACHED);
        emit(inet::packetDroppedSignal, packet, &details);
    }
}

void FadipNetworkProtocol::handlePublication(inet::Packet *packet) {
    auto pubChunk = packet->peekAtFront<PublishMessage>();
    bool sentUp = false;
    if (isLowerMessage(packet)) {
        if (inet::contains(myTopics, pubChunk->getTopic())){
            auto packetDup = packet->dup();
            packetDup->clearTags();
            packetDup->addTagIfAbsent<inet::DispatchProtocolReq>()->setProtocol(&getDataProtocol());
            packetDup->addTagIfAbsent<inet::PacketProtocolTag>()->setProtocol(&getDataProtocol());
            packetDup->addTagIfAbsent<inet::L3AddressInd>(); // Just add L3Address because sendUp requires it!
            sendUp(packetDup);
            sentUp = true;
        }
    }
    int compareTo = hcMaxPublish;
    if (inet::contains(knownTopics, pubChunk->getTopic())) {
        compareTo += hcMaxSubscribe - 1;
    }
    if (pubChunk->getHopCount() < compareTo) {
        FadipNetworkProtocol::numberOfPubBroadcasts++;
        broadcastMessage(packet);
    } else if (!sentUp) {
        inet::PacketDropDetails details;
        details.setReason(inet::PacketDropReason::HOP_LIMIT_REACHED);
        emit(inet::packetDroppedSignal, packet, &details);
    }
}
void FadipNetworkProtocol::broadcastMessage(inet::Packet *packet) {
    inet::Packet *newPacket = new inet::Packet(packet->getName());
    if (packet->peekAtFront<PubSubMessage>()->getType() == PubSubMessageType::Publication) {
        auto pubChunk = inet::makeShared<PublishMessage>(*packet->popAtFront<PublishMessage>());
        pubChunk->setHopCount(pubChunk->getHopCount() + 1);
        newPacket->insertAtFront(pubChunk);
    } else {
        auto subChunk = inet::makeShared<SubscribeMessage>(*packet->popAtFront<SubscribeMessage>());
        subChunk->setHopCount(subChunk->getHopCount() + 1);
        newPacket->insertAtFront(subChunk);
    }

    auto& tags = newPacket->getTags();
    tags.addTagIfAbsent<inet::MacAddressReq>()->setDestAddress(inet::MacAddress::BROADCAST_ADDRESS);
    tags.addTagIfAbsent<inet::PacketProtocolTag>()->setProtocol(&getProtocol());
    sendDown(newPacket);
    FadipNetworkProtocol::numberOfBroadcasts++;
}
void FadipNetworkProtocol::handleStartOperation(inet::LifecycleOperation *operation) {}
void FadipNetworkProtocol::handleStopOperation(inet::LifecycleOperation *operation) {}
void FadipNetworkProtocol::handleCrashOperation(inet::LifecycleOperation *operation) {}

void FadipNetworkProtocol::finish() {
    if (numberOfBroadcasts == 0)
        return;
    EV_INFO << "FadipNetwork Broadcasts:\n" << "  Total: " << numberOfBroadcasts << "\n    Pub: " << numberOfPubBroadcasts << "\n    Sub: " << numberOfSubBroadcasts << endl;
    EV_INFO << "Total Sent Messages: " << totalSentMessages << "\nTotal Send*Subs: " << totalSentMessagesToSubs << "\nTotal Received Messages: " << totalReceivedMessages
                << "\nDelivery Rate: " << (totalReceivedMessages*100/totalSentMessagesToSubs) << endl;
    EV_INFO << "EXCEL ROW: " << numberOfBroadcasts << "\t" << numberOfSubBroadcasts << "\t" <<  numberOfPubBroadcasts << "\t" << totalReceivedMessages << "\t" << totalSentMessagesToSubs << endl;
    numberOfBroadcasts = 0;
}

const inet::Protocol FadipNetworkProtocol::pubsupProtocol = inet::Protocol("subpub", "Sub/Pub", inet::Protocol::NetworkLayer);
const inet::Protocol FadipNetworkProtocol::pubsupDataProtocol = inet::Protocol("subpubdata", "Sub/Pub Data", inet::Protocol::TransportLayer);
int FadipNetworkProtocol::numberOfBroadcasts = 0;
int FadipNetworkProtocol::numberOfSubBroadcasts = 0;
int FadipNetworkProtocol::numberOfPubBroadcasts = 0;
int FadipNetworkProtocol::nonceCounter = 0;
int FadipNetworkProtocol::totalSentMessages = 0;
int FadipNetworkProtocol::totalSentMessagesToSubs = 0;
int FadipNetworkProtocol::totalReceivedMessages = 0;
std::map<std::string, int> FadipNetworkProtocol::topicSubscripers;

const inet::Protocol& FadipNetworkProtocol::getProtocol() const {
    return pubsupProtocol;
}
const inet::Protocol& FadipNetworkProtocol::getDataProtocol() const {
    return pubsupDataProtocol;
}
