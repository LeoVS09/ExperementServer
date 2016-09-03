#pragma once
#include"main.h"
#include"WSA.h"

struct Error {
	long num;
	string text;
};

class lol{
	static WSA wsa;
public:
	lol();
	static Error error(string text, long num = 0);
	static void log(Error);
	static void log(string);
	~lol();
};
void log(string);