#include "Server.h"
#include "lol.h"


Server::Server(string ip,string port):wsa(),addr(ip,port),listen_socket(){

	listen_socket.listenit(wsa,addr);

}

void Server::start(){
	while (true) {
		Socket * client_socket = listen_socket.acceptit();
		stringstream response;
		stringstream response_body;
		int result = client_socket->reciv(buf, max_client_buffer_size);
		
		if (result > 0) {
			buf[result] = '\0';
			response_body << "<title>Test C++ HTTP Server</title>\n"
				<< "<h1>Test page</h1>\n"
				<< "<p>This is body of the test page...</p>\n"
				<< "<h2>Request headers</h2>\n"
				<< "<pre>" << buf << "</pre>\n"
				<< "<em><small>Test C++ Http Server</small></em>\n";
			response << "HTTP/1.1 200 OK\r\n"
				<< "Version: HTTP/1.1\r\n"
				<< "Content-Type: text/html; charset=utf-8\r\n"
				<< "Content-Length: " << response_body.str().length()
				<< "\r\n\r\n"
				<< response_body.str();
			client_socket->sendit(response.str());
			delete client_socket;
		}
	}
}


Server::~Server(){
	listen_socket;
	addr.~AddrInfo();
	wsa.~WSA();
}

WSA::WSA(){
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result) throw lol().error("WSAStartup failed: ", result);
}

int WSA::getLastError(){
	return WSAGetLastError();
}


WSA::~WSA(){
	WSACleanup();
}

AddrInfo::AddrInfo(string Ip, string Port):ip(Ip),port(Port){
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	int result = getaddrinfo(ip.c_str(), port.c_str(), &hints, &addr);
	if (result) throw lol().error("getaddrinfo failed: ", result);
}

int AddrInfo::getFamily(){
	return addr->ai_family;
}

int AddrInfo::getSockType(){
	return addr->ai_socktype;
}

int AddrInfo::getProtocol(){
	return addr->ai_protocol;
}

int AddrInfo::getAddrlen(){
	return (int)addr->ai_addrlen;
}

sockaddr * AddrInfo::getAddr(){
	return addr->ai_addr;
}

AddrInfo::~AddrInfo(){
	freeaddrinfo(addr);
}

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
