#include "Request.h"


using namespace std;

Request::Request(int source, int destination) {
	this->source = source;
	this->destination = destination;
}

void Request::print(void) {
	cout << "Level " << this->source << \
		" wants to go to " << this->destination << "\n";
}

int Request::getDirection(void) {
	if (this->source < this->destination)
		return D_UP;
	else 
		return D_DOWN;
}
