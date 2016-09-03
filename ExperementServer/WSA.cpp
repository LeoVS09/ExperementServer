#include"WSA.h"
#include"lol.h"

WSA::WSA(){
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result) throw lol().error("WSAStartup failed: ", result);
}

int WSA::getLastError()const{
	return WSAGetLastError();
}


WSA::~WSA(){
	WSACleanup();
}