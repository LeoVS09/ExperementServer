#include "main.h"
#include "Server.h"

int main() {
	cout << "lol" << endl;
	try {
		Server server;
		server.start();
	}
	catch (int e) {
		return e;
	}
	return 0;
}
