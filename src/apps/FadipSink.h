#ifndef __FADIP_FADIPSINK_H_
#define __FADIP_FADIPSINK_H_

#include "../packets/PublishMessage_m.h"
#include "../packets/SubscribeMessage_m.h"
#include "inet/applications/base/ApplicationBase.h"

class FadipSink : public inet::ApplicationBase
{
  protected:
    int recivedMessages = 0;
    const char* topic;
    std::vector<int> recivedMessagesV;
    virtual void initialize(int stage) override;
    virtual void handleMessage(inet::cMessage *msg) override;
    virtual void handleStartOperation(inet::LifecycleOperation *operation) override;
    virtual void handleStopOperation(inet::LifecycleOperation *operation) override;
    virtual void handleCrashOperation(inet::LifecycleOperation *operation) override;
    virtual void handleMessageWhenUp(inet::cMessage *msg) override;
    virtual void finish() override;
};

#endif
