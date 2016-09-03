#include"Socket.h"
#include"AddrInfo.h"
#include"lol.h"

Socket::Socket(){
}

Socket::Socket(SOCKET s):soc(s){
	if (s == INVALID_SOCKET)
		throw lol().error("accept failed: ");
}

Socket * Socket::listenit(AddrInfo &a){
	addr = &a;
	createSocket();
	bindit();
	if (listen(soc, SOMAXCONN) == SOCKET_ERROR)
		throw lol().error("listen failed with error: ");
	return this;
}

Socket * Socket::acceptit(){
	return new Socket(accept(soc, NULL, NULL));
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
		lol().log(lol().error("send failed: "));
	}
}

Socket::~Socket(){
	closesocket(soc);
}

void Socket::createSocket(){
	soc = socket(addr->getFamily(), addr->getSockType(), addr->getProtocol());
	if(soc == INVALID_SOCKET)
		throw lol().error("Error at socket: ");
}

void Socket::bindit(){
	if (bind(soc, addr->getAddr(), addr->getAddrlen()) == SOCKET_ERROR)
		throw lol().error("bind failed with error: ");
}