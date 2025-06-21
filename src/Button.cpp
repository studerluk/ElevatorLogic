#include "Button.h"


using namespace std;

Button::Button(Queue *queue, int source) {
	this->queue = queue;
	this->source = source;
}

Button::~Button(void) {

}

void Button::go2(int destination) {
	cout << "Button on level " << to_string(this->source) << \
		" wants to go to " << to_string(destination) << "\n";

	Request *r = (Request*) malloc(sizeof(Request));
	r->source = this->source;
	r->destination = destination;
	this->queue->addRequest(r);
}
