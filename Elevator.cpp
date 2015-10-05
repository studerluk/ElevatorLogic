#include "Elevator.h"


using namespace std;

Elevator::Elevator(int id, int startPos) {
	this->pos = startPos;
	this->id = id;
	this->state = S_STOPED;
}

Elevator::~Elevator(void) {

}

void Elevator::print(void) {
	cout << "Elevator " << to_string(this->id) << \
		" is " << to_string(this->state) << \
		" at pos " << to_string(this->pos) << \
		" heading " << to_string(this->heading) << "[";

	for (auto val : this->lors)
		cout << val << ", ";

	cout << "]\n";
}

int Elevator::getPos(void) {
	return this->pos;
}

void Elevator::setState(int state) {
	this->state = state;
}

bool Elevator::matches(Request *request) {
	if (this->state == S_STOPED)
		return false;

	if (this->heading == D_STOPED)
		return true;

	if (this->heading == request->getDirection()) {
		if (this->heading == D_UP && request->source >= this->pos)
			return true;
		else if (this->heading == D_DOWN && request->source <= this->pos)
			return true;
	}

	return false;
}

void Elevator::addRequest(Request *request) {
	if (this->heading == D_STOPED) {
		if (request->source >= this->pos)
			this->heading = D_UP;
		else if (request->source <= this->pos)
			this->heading = D_DOWN;
	}
	
	this->lors.push_back(request->source);
	this->lors.push_back(request->destination);
	this->sortRequests();
}

void Elevator::sortRequests(void) {
	sort(begin(this->lors), end(this->lors));
	if (this->heading == D_DOWN) {
		reverse(begin(this->lors), end(this->lors));
	}
}

void Elevator::go(void) {
	if (this->lors.size() > 0) {
		bool searching = true;
		int i = 0;
		for (auto level : this->lors) {
			if ((this->heading == D_UP && level >= this->pos) || \
				(this->heading == D_DOWN && this->lors.at(i) <= this->pos))
				searching = false;
			else
				i++;

			if (!searching) break;
		}

		if (!searching) {
			this->pos = this->lors.at(i);
			this->lors.erase(this->lors.begin()+i);
		} else {
			this->heading *= -1;
		}
	} else {
		this->heading = D_STOPED;
	}
}

void Elevator::mainLoop(void) {
	this->state = S_RUNNING;
	while (true) {
		if (this->heading != D_STOPED && this->state != S_STOPED) this->go();
		usleep(1000000);
	}
	this->state = S_STOPED;
}
