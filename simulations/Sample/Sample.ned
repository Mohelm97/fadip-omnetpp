package fadip.simulations.Sample;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.AdhocHost;
import inet.physicallayer.wireless.unitdisk.UnitDiskRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import fadip.FadipDevice;
import fadip.apps.FadipSink;
network Sample
{
    parameters:
        int numHosts;
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
        host[numHosts]: FadipDevice {
            parameters:
                @display("r=,,#707070;p=300,200");
        }
}
