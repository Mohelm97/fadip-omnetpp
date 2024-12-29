#ifndef FADIPNETWORKPROTOCOL_H_
#define FADIPNETWORKPROTOCOL_H_

#include "inet/common/INETDefs.h"
#include "packets/PublishMessage_m.h"
#include "packets/SubscribeMessage_m.h"
#include <omnetpp.h>
#include "inet/networklayer/base/NetworkProtocolBase.cc"
#include "inet/networklayer/common/NetworkInterface.h"
#include "inet/common/packet/tag/SharingTagSet.h"
#include "inet/linklayer/common/MacAddressTag_m.h"

struct SubscriptionEntry {
    std::string topic;
    std::string nodeName;
    inet::MacAddress nextHopMac;

    SubscriptionEntry() : topic(""), nodeName(""), nextHopMac(inet::MacAddress::UNSPECIFIED_ADDRESS) {}
    SubscriptionEntry(const std::string& topic, const std::string& nodeName, const inet::MacAddress& mac)
        : topic(topic), nodeName(nodeName), nextHopMac(mac) {}
};

class FadipNetworkProtocol : public inet::NetworkProtocolBase {
protected:
    int hcMaxSubscribe;
    int hcMaxPublish;
    const char* name;

    std::unordered_map<std::string, std::list<SubscriptionEntry>> subscriptionTable;
    std::vector<std::string> myTopics;
    std::vector<std::string> knownTopics;
    std::vector<uint32_t> seenMessages;

    virtual void initialize(int stage) override;
    void addSubscription(inet::Packet *packet, inet::Ptr<const SubscribeMessage> subMessage);
    virtual void handleMessage(inet::cMessage *msg) override;
    void handleSubscription(inet::Packet *packet);
    void handlePublication(inet::Packet *packet);
    void broadcastMessage(inet::Packet *packet);
    virtual void handleStartOperation(inet::LifecycleOperation *operation) override;
    virtual void handleStopOperation(inet::LifecycleOperation *operation) override;
    virtual void handleCrashOperation(inet::LifecycleOperation *operation) override;
    virtual const inet::Protocol& getProtocol() const override;
    virtual const inet::Protocol& getDataProtocol() const;
    virtual void finish() override;

public:
    static int numberOfBroadcasts;
    static int numberOfSubBroadcasts;
    static int numberOfPubBroadcasts;
    static const inet::Protocol pubsupProtocol;
    static const inet::Protocol pubsupDataProtocol;
    static int nonceCounter;
    FadipNetworkProtocol();
    virtual ~FadipNetworkProtocol();
};


#endif /* FADIPNETWORKPROTOCOL_H_ */
