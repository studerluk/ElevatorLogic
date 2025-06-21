#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
#include <vector>
#include <stdbool.h>
#include <unistd.h>
#include <cmath>

#include "Request.h"
#include "Elevator.h"


using namespace std;

class Queue {

public:
	Queue(vector<Elevator *>);
	~Queue(void);

	void print(void);

	void addElevator(Elevator*);
	void addRequest(Request*);

	void mainLoop(void);

private:
	vector<Request *> requests;
	vector<Elevator *> elevators;
};

#endif
