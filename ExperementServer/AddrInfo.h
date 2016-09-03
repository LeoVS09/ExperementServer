#pragma once
#include"main.h"

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
