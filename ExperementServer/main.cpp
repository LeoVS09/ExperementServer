#include "main.h"
#include "Server.h"
#include "lol.h"
int main() {
	cout << "lol" << endl;
	try {
		Server server;
		server.start();
	}
	catch (int e) {
		return e;
	}
	catch (Error err) {
		lol().log(err);
		return err.num;
	}
	catch (...) {
		cerr << "Unknow error";
		throw;
	}
	return 0;
}
