#pragma once
#include"main.h"
#include"WSA.h"
#include"AddrInfo.h"

class Socket {
	WSA *wsa;
	AddrInfo *addr;
	SOCKET soc;
public:
	Socket();
	Socket(SOCKET, WSA *);
	Socket * listenit(WSA &, AddrInfo &);
	Socket * acceptit();
	int reciv(char *buf, int size, int flag = 0);
	void sendit(string, int flag = 0);
	~Socket();
private:
	void createSocket();
	void bindit();
};
