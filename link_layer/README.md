# Link Layer Protocol
a simple, link layer protocol, without MAC stuff.
the data link layer serves the network layer, it provides it with a point to point connection
between adjacent nodes in the network, it's responsible for reliably transmitting data from a 
node to the next, thus it's mainly about error detection and correction, some sort of acknowledgement 
mechanism and rudimentary flow control [not swamping the reciever with fast data].

## features of my program:
1. basic error detection using checksums.
2. a record of all sent and received frames, for purposes of performance assesment.
3. sending and receiving frames, as well as acknowledgements.
4. flow control [maybe].

