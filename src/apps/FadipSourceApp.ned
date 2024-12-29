package fadip.apps;

import inet.applications.contract.IApp;
simple FadipSourceApp like IApp
{
    parameters:
        string topic;
        double delay = default(0.1);
    gates:
        input socketIn;
        output socketOut;
}