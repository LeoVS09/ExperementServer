#include"Socket.h"
#include"WSA.h"
#include"AddrInfo.h"
#include"lol.h"

Socket::Socket(){
}

Socket::Socket(SOCKET s, WSA *w):soc(s){
	wsa = w;
	if (s == INVALID_SOCKET)
		throw lol().error("accept failed: ", wsa->getLastError());
}

Socket * Socket::listenit(WSA &w, AddrInfo &a){
	wsa = &w;
	addr = &a;
	createSocket();
	bindit();
	if (listen(soc, SOMAXCONN) == SOCKET_ERROR)
		throw lol().error("listen failed with error: ", wsa->getLastError());
	return this;
}

Socket * Socket::acceptit(){
	return new Socket(accept(soc, NULL, NULL),wsa);
}

int Socket::reciv(char * buf, int size, int flag){
	int result = recv(soc, buf, size, flag);
	if (result == SOCKET_ERROR)
		lol().log(lol().error("recv failed: ", result));
	else if (!result) 
		lol().log("connection closed...");
	return result;
}

void Socket::sendit(string response, int flag){
	int result = send(soc, response.c_str(),response.length(), flag);
	if (result == SOCKET_ERROR) {
		lol().log(lol().error("send failed: ", wsa->getLastError()));
	}
}

Socket::~Socket(){
	closesocket(soc);
}

void Socket::createSocket(){
	soc = socket(addr->getFamily(), addr->getSockType(), addr->getProtocol());
	if(soc == INVALID_SOCKET)
		throw lol().error("Error at socket: ", wsa->getLastError());
}

void Socket::bindit(){
	if (bind(soc, addr->getAddr(), addr->getAddrlen()) == SOCKET_ERROR)
		throw lol().error("bind failed with error: ", wsa->getLastError());
}