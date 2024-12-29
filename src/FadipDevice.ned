package fadip;
import inet.node.inet.AdhocHost;
module FadipDevice extends AdhocHost
{
    parameters:
        @display("i=device/laptop");
        hasIpv4 = false;
        hasUdp = false;
        hasTcp = false;
        generic.typename = "FadipNetworkLayer";
        hasGn = true;
    
}

