package fadip;

import inet.networklayer.contract.INetworkProtocol;
import inet.networklayer.common.InterfaceTable;
module FadipNetworkProtocol like INetworkProtocol
{
    parameters:
        int hcMaxSubscribe;
        int hcMaxPublish;
        string wlanInterfaceModule = default("^.^.wlan[0]");
        string interfaceTableModule = default(absPath("^.^.interfaceTable"));
        @display("i=block/switch");
        @class(FadipNetworkProtocol);
    gates:
        input transportIn;
        output transportOut;
        input queueIn;
        output queueOut;
}