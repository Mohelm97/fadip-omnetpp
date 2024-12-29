//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package fadip;
import inet.networklayer.contract.INetworkLayer;

module FadipNetworkLayer like INetworkLayer
{
    parameters:
        @display("i=block/fork;bgb=381,190");
    gates:
        input transportIn;
        output transportOut;
        input ifIn;
        output ifOut;
    submodules:
        np: FadipNetworkProtocol {
            parameters:
                @display("p=191,105;q=queue");
        }
    connections:
        transportIn --> { @display("m=n"); } --> np.transportIn;
        np.transportOut --> { @display("m=n"); } --> transportOut;
        
        ifIn --> np.queueIn;
        np.queueOut --> ifOut;
        
        
}