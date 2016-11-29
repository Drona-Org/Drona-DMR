#define WIN32_LEAN_AND_MEAN

//#include <windows.h>
//http://www.cplusplus.com/forum/general/12785/
//http://www.linuxhowtos.org/C_C++/socket.htm
////#include <winsock2.h>
////#include <ws2tcpip.h>

#include "UdpSocketPort.h"
#include <stdio.h>
//Added for Linux
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <iostream>
#include <unistd.h>

#include <cstdint>
#include <cstring>
 
 #define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

HRESULT UdpSocketPort::Initialize()
{
	/*int s;

	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    return s;*/

	////WSADATA wsaData;
	// Initialize Winsock
	////int rc = WSAStartup(MAKEWORD(2, 2), (LPWSADATA)&wsaData);
	////if (rc != 0) {
	////	printf("### WSAStartup failed with error: %d\n", rc);
	////	return rc;
	////}
	return 0;
}

//struct sockaddr_in {
//	short sin_family;
//	u_short sin_port;
//	struct in_addr sin_addr;
//	char sin_zero[8];
//}

//struct sockaddr {ad

//	u_short sa_family;
//	char sa_data[14];
//}

//struct in_addr {
//	u_long s_addr;
//}

// Bind the udp socket to the given local port, and set it up so we only listen
// to UDP packets from the given serverIp address.
HRESULT UdpSocketPort::Connect(const char* serverIp, int localPort, int serverPort)
{
	//int sock = socket(AF_INET, SOCK_DGRAM, 0);
	//printf("SUCCESS");
	//CHANGE THAT
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	//printf("FAILURE");
	//printf(AF_INET);
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(localPort);
	this->serverport = serverPort;

	struct addrinfo hints;
	bzero(&hints, sizeof(hints));
	//ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	struct addrinfo *result = NULL;
	int rc = getaddrinfo(serverIp, "0", &hints, &result);
	if (rc != 0) {
		printf("getaddrinfo failed with error: %d\n", rc);
		return 1;
	}
	for (struct addrinfo *ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	{
		if (ptr->ai_family == AF_INET && ptr->ai_socktype == SOCK_DGRAM && ptr->ai_protocol == IPPROTO_UDP)
		{
			// found it!
			sockaddr_in* sptr = (sockaddr_in*)ptr->ai_addr;
			serveraddr.sin_family = sptr->sin_family;
			serveraddr.sin_addr.s_addr = sptr->sin_addr.s_addr;
			serveraddr.sin_port = 0; // don't know yet.
			break;
		}
	}

	freeaddrinfo(result);

	// bind socket to a local port.
	rc = bind(sock, (sockaddr*)&local, addrlen);
	//printf("GAUTHIER: %d", rc);
	if (rc < 0)
	{
		//int hr = WSAGetLastError();
		handle_error("bind");
		//printf("connect bind failed with error: %d\n", hr);
		printf("connect bind failed with error.\n");
		//return hr;
	}
	return 0;
}

// write to the serial port
HRESULT UdpSocketPort::Write(const BYTE* ptr, int count)
{
	if (sendSocket == 0)
	{
		if (serverport == -1)
		{
			printf("cannot send until we've received something first so we can find out what the server port is.\n");
			return 0;
		}
	}

	serveraddr.sin_port = htons(serverport);
	int hr = sendto(sock, (const char*)ptr, count, 0, (sockaddr*)&serveraddr, addrlen);
	if (hr == -1)
	{
		printf("#### send failed with error.\n");
	}

	return hr;
}

// read a given number of bytes from the port.
HRESULT UdpSocketPort::Read(BYTE* buffer, int bytesToRead, int* bytesRead)
{
	// Receive until the peer closes the connection
	if (pos == size)
	{
		while (true)
		{
			pos = 0;
			size = 0;
			*bytesRead = 0;
			//printf("%d\n", listen(sock, 256));
			int rc = recvfrom(sock, (char*)&this->buffer, 255, 0, (struct sockaddr*)&other, &addrlen);
			//printf("%d --", rc);
			//printf("Ip Address: %d", other.sin_addr.s_addr);
			//printf("Addr: %d", serveraddr.sin_addr.s_addr);
			//printf("Serverport: %d", serverport);
			//printf("Sinport: %d", ntohs(other.sin_port));
			if (rc < 0)
			{
				//int hr = WSAGetLastError();
				handle_error("recvfrom");
				//printf("connect bind failed with error: %d\n", hr);
				printf("connect bind failed with error.\n");
				//return hr;
			}

			if (other.sin_addr.s_addr != serveraddr.sin_addr.s_addr)
			{
				// this is from a different PX4 then, one that we are not interested in.
				continue;
			}
			else if (serverport == -1)
			{
				// we now have it.
				serverport = ntohs(other.sin_port);
			}
			if (serverport != ntohs(other.sin_port))
			{
				// this is from a different mavlink node then, one that we are not interested in.
				continue;
			}
			//printf("HI: %d", rc);
			if (rc == 0)
			{
				printf("Connection closed\n");
			}
			////else if (rc < 0)
			////{
			////	int hr = WSAGetLastError();
			////	if (hr == WSAEMSGSIZE)
			////	{
			////		// skip this, probably noise, try again
			////	}
			////	else if (hr == WSAECONNRESET || hr == ERROR_IO_PENDING)
			////	{
			////		// try again - this can happen if server recreates the socket on their side.
			////	}
			////	else
			////	{
			////		printf("#### recv failed with error: %d\n", hr);
			////		return hr;
			////	}
			////}
			else
			{
				size = rc;
				break;
			}
		}
	}


	int len = size - pos;
	if (len > bytesToRead)
	{
		len = bytesToRead;
	}
	std::memcpy(buffer, this->buffer + pos, len);
	pos += len;

	*bytesRead = len;
	return 0;
}

// close the port.
void UdpSocketPort::Close()
{
	close(sock);
	//closesocket(sock);
}

HRESULT UdpSocketPort::GetLocalAddress(char* buffer, int bufferSize)
{
	/*if (bufferSize == 0)
	{
		return E_NOT_SUFFICIENT_BUFFER;
	}*/
	buffer[0] = 0;

	int rc = gethostname(buffer, bufferSize);
	////if (rc != 0) {
	////	return WSAGetLastError();
	////}

	struct hostent *phe = gethostbyname(buffer);
	////if (phe == 0) {
	////	WSAGetLastError();
	////}

	if (phe->h_addrtype == AF_INET) {

		for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
			struct in6_addr *addr;
			//addr.S_un.S_addr = *(u_long *)phe->h_addr_list[i];
			addr = &((struct sockaddr_in6 *)phe->h_addr_list[i])->sin6_addr;
			inet_ntop(AF_INET, &addr, buffer, bufferSize);
			break;
		}
	}

	return 0;

}