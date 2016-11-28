#define WIN32_LEAN_AND_MEAN

////#include <windows.h>
//http://www.cplusplus.com/forum/general/12785/
//http://www.linuxhowtos.org/C_C++/socket.htm
////#include <winsock2.h>
////#include <ws2tcpip.h>

#include "TcpSocketPort.h"
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
//-----------------

HRESULT TcpSocketPort::Initialize()
{
	////WSADATA wsaData;
	// Initialize Winsock
	//https://en.wikibooks.org/wiki/Windows_Programming/Winsock
	////int rc = WSAStartup(MAKEWORD(2, 2), (LPWSADATA)&wsaData);
	////if (rc != 0) {
	////	printf("### WSAStartup failed with error: %d\n", rc);
	////	return rc;
	////}

	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR opening socket");
    }


	return 0;
}

// Bind the udp socket any available local port, and connect to the given 
// server and port.
HRESULT TcpSocketPort::Connect(const char* serverIp, int serverPort)
{
	////sock = socket(AF_INET, SOCK_STREAM, 0);
	////struct sockaddr_in local;
	////local.sin_family = AF_INET;
	////local.sin_addr.s_addr = INADDR_ANY;
	////local.sin_port = htons(serverPort);
	////
	////struct addrinfo hints;
	////ZeroMemory(&hints, sizeof(hints));
	////hints.ai_family = AF_UNSPEC;
	////hints.ai_socktype = SOCK_STREAM;
	////hints.ai_protocol = IPPROTO_TCP;
	////
	////struct addrinfo *result = NULL;
	////int rc = getaddrinfo(serverIp, "0", &hints, &result);
	////if (rc != 0) {
	////	printf("getaddrinfo failed with error: %d\n", rc);
	////	return WSAGetLastError();
	////}
	////bool found = false;
	////for (struct addrinfo *ptr = result; ptr != NULL; ptr = ptr->ai_next) 
	////{
	////	if (ptr->ai_family == AF_INET && ptr->ai_socktype == SOCK_STREAM && ptr->ai_protocol == IPPROTO_TCP)
	////	{
	////		// found it!
	////		sockaddr_in* sptr = (sockaddr_in*)ptr->ai_addr;
	////		serveraddr.sin_family = sptr->sin_family;
	////		serveraddr.sin_addr.s_addr = sptr->sin_addr.s_addr;
	////		serveraddr.sin_port = 0; // don't know yet.
	////		found = true;
	////		break;
	////	}
	////}
	////
	////if (!found) {
    ////return E_FAIL;
	////}
	////
	////freeaddrinfo(result);
	////
	//// bind socket to a local port.
	////rc = bind(sock, (sockaddr*)&local, addrlen);
	////if (rc < 0)
	////{
	////	int hr = WSAGetLastError();
	////	printf("connect bind failed with error: %d\n", hr);
	////	return hr;
	////}
	////
	////rc = connect(sock, (sockaddr*)&serveraddr, addrlen);
	////if (rc != 0) {
	////	printf("connect failed with error: %d\n", rc);
	////	return WSAGetLastError();
	////}

	//Source: http://unix.stackexchange.com/questions/92608/how-can-i-tell-if-a-tcp-port-is-open-or-not
	int sockfd;
	struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("ERROR opening socket");
    }

    server = gethostbyname(serverIp);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(serverPort);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        printf("Port is closed");
    } else {
        printf("Port is active");
    }
	
	return 0;
}

// write to the serial port
HRESULT TcpSocketPort::Write(const BYTE* ptr, int count)
{
	if (sock == 0)
	{
    printf("cannot send until we've connected this socket.\n");
    return 0;
	}

	serveraddr.sin_port = htons(serverport);
	int hr = send(sock, (const char*)ptr, count, 0);
	if (hr == -1)
	{
		printf("#### send failed with error.\n");
	}

	return hr;
}

// read a given number of bytes from the port.
HRESULT TcpSocketPort::Read(BYTE* buffer, int bytesToRead, int* bytesRead)
{
	  int size = 0;
	  int pos = 0;
	  char* buf = (char*)buffer;
		while (pos < bytesToRead)
		{
			pos = 0;
			size = 0;
			*bytesRead = 0;
			int rc = recv(sock, buf, bytesToRead - pos, 0);
			if (rc == 0)
			{
				printf("Connection closed\n");
			}
			////else if (rc < 0)
			////{
			////	// I don't know the equivalent in linux
			////	int hr = WSAGetLastError();
			////	if (hr == WSAEMSGSIZE)
			////	{
			////		// skip this, probably noise, try again
			////	}
			////	else if (hr == WSAECONNRESET || hr == ERROR_IO_PENDING)
			////	{
			////		// try again - this can happen if server recreates the socket on their side.
			////		// so we need to reconnect.
			////		return hr;
			////	}
			////	else
			////	{
			////		printf("#### recv failed with error: %d\n", hr);
			////		return hr;
			////	}
			////}
			else
			{
				pos += rc;
				buf += rc;
			}
	}

	*bytesRead = pos;
	return 0;
}

// close the port.
void TcpSocketPort::Close()
{
	close(sock);
}
