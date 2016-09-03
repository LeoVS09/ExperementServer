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






