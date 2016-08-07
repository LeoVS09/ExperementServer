#include "Server.h"
#include "lol.h"


Server::Server(){
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result) throw lol().error("WSAStartup failed: ", result);
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	result = getaddrinfo("127.0.0.1", "8000", &hints, &addr);
	if (result) {
		WSACleanup();
		throw lol().error("getaddrinfo failed: ", result);
	}
	listen_socket = socket(addr->ai_family, addr->ai_socktype,
		addr->ai_protocol);
	if (listen_socket == INVALID_SOCKET) {
		freeaddrinfo(addr);
		WSACleanup();
		throw lol().error("Error at socket: ", WSAGetLastError());
	}
	result = bind(listen_socket, addr->ai_addr, (int)addr->ai_addrlen);
	if (result == SOCKET_ERROR) {
		freeaddrinfo(addr);
		closesocket(listen_socket);
		WSACleanup();
		throw lol().error("bind failed with error: ", WSAGetLastError());;
	}
	if (listen(listen_socket, SOMAXCONN) == SOCKET_ERROR) {
		closesocket(listen_socket);
		WSACleanup();
		throw lol().error("listen failed with error: ", WSAGetLastError());;
	}
}

void Server::start(){
	while (true) {
		client_socket = accept(listen_socket, NULL, NULL);
		if (client_socket == INVALID_SOCKET) {
			closesocket(listen_socket);
			WSACleanup();
			throw lol().error("accept failed: ", WSAGetLastError());
		}
		int result = recv(client_socket, buf, max_client_buffer_size, 0);
		stringstream response;
		stringstream response_body;
		if (result == SOCKET_ERROR) {
			lol().log(lol().error("recv failed: ",result));
			closesocket(client_socket);
		}
		else if (!result) {
			lol().log("connection closed...");
		}
		else if (result > 0) {
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
			result = send(client_socket, response.str().c_str(),
				response.str().length(), 0);

			if (result == SOCKET_ERROR) {
				lol().log(lol().error("send failed: ", WSAGetLastError()));
			}
			closesocket(client_socket);
		}
	}
}


Server::~Server(){
	closesocket(listen_socket);
	freeaddrinfo(addr);
	WSACleanup();
}
