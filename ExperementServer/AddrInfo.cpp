#include"AddrInfo.h"
#include"lol.h"

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