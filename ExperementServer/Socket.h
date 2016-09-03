#pragma once
#include"main.h"
#include"AddrInfo.h"

class Socket {
	
	AddrInfo *addr;
	SOCKET soc;
public:
	Socket();
	Socket(SOCKET);
	Socket * listenit(AddrInfo &);
	Socket * acceptit();
	int reciv(char *buf, int size, int flag = 0);
	void sendit(string, int flag = 0);
	~Socket();
private:
	void createSocket();
	void bindit();
};
