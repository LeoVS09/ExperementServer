#pragma once
#include"main.h"
#include"AddrInfo.h"
#include"Socket.h"


class Server{
	AddrInfo addr;
	static const int max_client_buffer_size = 1024;
	char buf[max_client_buffer_size];
	Socket listen_socket;
public:
	Server(string ip, string port);
	void start();
	~Server();
};

