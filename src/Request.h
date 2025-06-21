#ifndef REQUEST_H
#define REQUEST_H

#include <iostream>

#include "main.h"


using namespace std;

class Request {

public:
	Request(int, int);

	void print(void);
	int getDirection(void);

	int source;
	bool sourceCheck;

	int destination;
	bool destCheck;
};

#endif
