#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <iostream>
#include <string>
#include <stdbool.h>
#include <vector>
#include <unistd.h>
#include <algorithm>

#include "Request.h"
#include "main.h"


using namespace std;

class Elevator {

public:
	Elevator(int, int);
	~Elevator(void);

	void print(void);
	bool matches(Request *);
	void addRequest(Request *);
	void mainLoop(void);
	int getPos(void);
	void setState(int);

private:
	void sortRequests(void);
	void go(void);

	int pos;
	int id;
	int heading;
	int state;
	vector<int> lors;
};

#endif
