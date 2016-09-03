#pragma once
#include"main.h"

class WSA {
	WSADATA wsaData;
public:
	WSA();
	int getLastError();
	~WSA();
};