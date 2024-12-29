package fadip.apps;

import inet.applications.contract.IApp;
simple FadipSink like IApp
{
    parameters:
        string topic;
    gates:
        input socketIn;
        output socketOut;
}
