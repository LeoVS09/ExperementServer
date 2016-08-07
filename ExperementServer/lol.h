#pragma once
#include"main.h"
struct Error {
	long num;
	string text;
};
class lol{
public:
	lol();
	static Error error(string, long);
	static void log(Error);
	static void log(string);
	~lol();
};
void log(string);