package fadip.simulations.NoMobility;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.AdhocHost;
import inet.physicallayer.wireless.unitdisk.UnitDiskRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import fadip.FadipDevice;
import fadip.apps.FadipSink;
network NoMobility
{
    parameters:
        int hcMaxSubscribe;
        int hcMaxPublish;
        **.hcMaxSubscribe = this.hcMaxSubscribe;
        **.hcMaxPublish = this.hcMaxPublish;
    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            parameters:
                @display("p=100,300;is=s");
        }
        radioMedium: UnitDiskRadioMedium {
            parameters:
                @display("p=100,200;is=s");
        }
        host0: FadipDevice {
            parameters:
                @display("p=250,200");
        }
        host1: FadipDevice {
            parameters:
                @display("p=450,200");
        }
        host2: FadipDevice {
            parameters:
                @display("p=650,200");
        }
        host3: FadipDevice {
            parameters:
                @display("p=850,200");
        }
        host4: FadipDevice {
            parameters:
                @display("p=1050,200");
        }
        host5: FadipDevice {
            parameters:
                @display("p=1250,200");
        }
        host6: FadipDevice {
            parameters:
                @display("p=1450,200");
        }
        host7: FadipDevice {
            parameters:
                @display("p=1650,200");
        }
        
        host8: FadipDevice {
            parameters:
                @display("p=250,400");
        }
        host9: FadipDevice {
            parameters:
                @display("p=450,400");
        }
        host10: FadipDevice {
            parameters:
                @display("p=650,400");
        }
        host11: FadipDevice {
            parameters:
                @display("p=850,400");
        }
        host12: FadipDevice {
            parameters:
                @display("p=1050,400");
        }
        host13: FadipDevice {
            parameters:
                @display("p=1250,400");
        }
        host14: FadipDevice {
            parameters:
                @display("p=1450,400");
        }
        host15: FadipDevice {
            parameters:
                @display("p=1650,400");
        }
}
