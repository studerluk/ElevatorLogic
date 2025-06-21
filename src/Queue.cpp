#include "Queue.h"


using namespace std;

Queue::Queue(vector<Elevator *> elevators) {
	for (auto elevator : elevators) {
		this->elevators.push_back(elevator);
	}
}

Queue::~Queue(void) {

}

void Queue::print(void) {
	cout << "Queue";
}

void Queue::addElevator(Elevator *elevator) {
	this->elevators.push_back(elevator);
}

void Queue::addRequest(Request *request) {
	this->requests.push_back(request);
}

void Queue::mainLoop(void) {
	while (true) {
		vector<Request *> tmpReq;
		for (auto request : this->requests) {  
			bool rMatched = false;
			vector<Elevator *> matched_elevators;

			for (auto elevator : this->elevators){
				if (elevator->matches(request)) {
					matched_elevators.push_back(elevator);
					rMatched = true;
				}
			}

			if (rMatched) {
				int t_dist = this->elevators.size() +2;
				Elevator *closest_elevator;

				for (auto elevator : matched_elevators) {	
					int tt_dist = abs(elevator->getPos() - request->source);
					if (tt_dist < t_dist) {
						t_dist = tt_dist;
						closest_elevator = elevator;
					}
				}
				closest_elevator->addRequest(request);

			} else {
				tmpReq.push_back(request);
			}

		}
		this->requests = tmpReq;

		cout << "------------------------------------\n";
		for (auto elevator : this->elevators)
			elevator->print();
		cout << "------------------------------------\n";
		usleep(1000000);
	}
}
