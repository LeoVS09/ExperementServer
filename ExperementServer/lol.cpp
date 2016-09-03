#include "lol.h"


WSA lol::wsa;

lol::lol(){
}

Error lol::error(string text, long num){
	Error err;
	err.text = text;
	err.num = num;
	return err;
}


lol::~lol(){
}

void lol::log(Error err){
	if (!err.num) err.num = wsa.getLastError();
	cout << err.text << err.num << endl;
	cerr << err.text << err.num << endl;
}
void lol::log(string error) {
	cout << error << endl;
	cerr << error << endl;
}
void log(string line) {
	cout << line << endl;
}
