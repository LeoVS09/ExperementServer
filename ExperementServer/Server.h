#pragma once
#include"main.h"


class WSA {
	WSADATA wsaData;
public:
	WSA();
	int getLastError();
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
class Server{
	WSA wsa;
	AddrInfo addr;
	static const int max_client_buffer_size = 1024;
	char buf[max_client_buffer_size];
	Socket listen_socket;
public:
	Server(string ip, string port);
	void start();
	~Server();
};

