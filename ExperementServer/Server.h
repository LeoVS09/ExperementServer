#pragma once
#include"main.h"


class WSA {
	WSADATA wsaData;
public:
	WSA();
	~WSA();
};

class AddrInfo {
	struct addrinfo* addr = NULL;
	struct addrinfo hints;
	string ip;
	string port;
public:
	AddrInfo(string,string);
	int getFamily();
	int getSockType();
	int getProtocol();
	int getAddrlen();
	sockaddr * getAddr();
	~AddrInfo();
};
class Server{
	WSA wsa;
	AddrInfo addr;
	static const int max_client_buffer_size = 1024;
	char buf[max_client_buffer_size];
	int client_socket = INVALID_SOCKET;
	int listen_socket;
public:
	Server();
	void start();
	~Server();
};

