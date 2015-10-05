#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <string>

#include "Request.h"
#include "Queue.h"


using namespace std;

class Button {

public:
	Button(Queue*, int);
	~Button(void);

	void go2(int);

private:
	Queue *queue;
	int source;
};

#endif
