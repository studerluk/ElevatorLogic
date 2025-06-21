#include <thread>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Request.h"
#include "Elevator.h"
#include "Queue.h"
#include "Button.h"


using namespace std;

void queueMainLoop(Queue *queue) {
	queue->mainLoop();
}

void elevatorMainLoop(Elevator *elevator) {
	elevator->mainLoop();
}

void someRandomBtnPushing(vector<Button *> btns) {
	int n = btns.size();
	while (true) {
		int btn = rand() % n;
		int dest = rand() % n;
		int delay = rand() % 1000000;

		btns.at(btn)->go2(dest);
		usleep(delay);
	}
}

int main(int argc, char *argv[]) {
	srand (time(NULL));

	vector<Elevator *> elevators;
	elevators.push_back(new Elevator(0, 0));
	elevators.push_back(new Elevator(1, 3));
	elevators.push_back(new Elevator(2, 5));
	elevators.push_back(new Elevator(3, 5));
	elevators.push_back(new Elevator(4, 5));

	thread te0(elevatorMainLoop, elevators.at(0));
	thread te1(elevatorMainLoop, elevators.at(1));
	thread te2(elevatorMainLoop, elevators.at(2));
	thread te3(elevatorMainLoop, elevators.at(3));
	thread te4(elevatorMainLoop, elevators.at(4));

	Queue *queue = new Queue(elevators);

	// populate buttons
	vector<Button *> buttons;
	for (int i = 0; i < 10; i++) {
		Button *btn = new Button(queue, i);
		buttons.push_back(btn);
	}

	thread t(queueMainLoop, queue);

	thread t1(someRandomBtnPushing, buttons);

	while (true) ;
	return 0;
}
