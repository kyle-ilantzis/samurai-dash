#include "StopWatch.h"


StopWatch::StopWatch() {
	restart = true;
	run = false;
	startTime = 0;
	endTime = 0;
}


void StopWatch::start() {
	if (!run) {
		if (restart)
			startTime = (unsigned long)clock();
		else
			startTime -= endTime - (unsigned long)clock();
		run = true;
		restart = false;
	}
}


void StopWatch::stop() {
	if (run) {
		endTime = (unsigned long)clock();
		run = false;
	}
}


void StopWatch::reset() {
	bool wereRunning = run;
	if (wereRunning)
		stop();
	restart = true;
	startTime = 0;
	endTime = 0;
	if (wereRunning)
		start();
}

unsigned long StopWatch::getTime() {
	if (run)
		return ((unsigned long)clock() - startTime) / CLOCKS_PER_SEC;
	else
		return endTime - startTime;
}

StopWatch::~StopWatch(){

}