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
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=100,100;is=s");
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
}
