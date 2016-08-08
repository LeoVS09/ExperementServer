#pragma once
#include"main.h"


class WSA {
	WSADATA wsaData;
public:
	WSA();
	~WSA();
};

class Server{
	WSA wsa;
	struct addrinfo* addr = NULL;
	struct addrinfo hints;
	static const int max_client_buffer_size = 1024;
	char buf[max_client_buffer_size];
	int client_socket = INVALID_SOCKET;
	int listen_socket;
public:
	Server();
	void start();
	~Server();
};

