all: hello

hello: testGauthier.o UdpSocketPort.o TcpSocketPort.o POrbMavlink.o
	g++ -g -pthread testGauthier.o UdpSocketPort.o TcpSocketPort.o POrbMavlink.cpp -o hello -std=c++11

testGauthier.o: testGauthier.cpp
	g++ -c -std=c++11 testGauthier.cpp

UdpSocketPort.o: UdpSocketPort.cpp
	g++ -c -std=c++11 UdpSocketPort.cpp

TcpSocketPort.o: TcpSocketPort.cpp
	g++ -c -std=c++11 TcpSocketPort.cpp

POrbMavlink.o: POrbMavlink.cpp
	g++ -c -std=c++11 POrbMavlink.cpp

clean:
	rm *o hello

