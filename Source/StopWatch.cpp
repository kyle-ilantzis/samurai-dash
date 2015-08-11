#include "StopWatch.h"


StopWatch::StopWatch() {
	resetted = true;
	running = false;
	startTime = 0;
	endTime = 0;
}


void StopWatch::start() {
	if (!running) {
		if (resetted)
			startTime = (unsigned long)clock();
		else
			startTime -= endTime - (unsigned long)clock();
		running = true;
		resetted = false;
	}
}


void StopWatch::stop() {
	if (running) {
		endTime = (unsigned long)clock();
		running = false;
	}
}


void StopWatch::reset() {
	bool wereRunning = running;
	if (wereRunning)
		stop();
	resetted = true;
	startTime = 0;
	endTime = 0;
	if (wereRunning)
		start();
}

unsigned long StopWatch::getTime() {
	if (running)
		return ((unsigned long)clock() - startTime) / CLOCKS_PER_SEC;
	else
		return endTime - startTime;
}

StopWatch::~StopWatch(){

}

