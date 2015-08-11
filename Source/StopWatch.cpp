#include "StopWatch.h"


StopWatch::StopWatch()
{
	time = 0;
	pauseTime = 0;
	running = false;
}

void StopWatch::start(){
	if (!running)
		time = clock();

	else{
		running = running - pauseTime + (unsigned long)clock();
		running = true;
	}

}

unsigned long StopWatch::getTime(){
	return (unsigned long)(time + pauseTime) / CLOCKS_PER_SEC;;
}

void StopWatch::stop(){
	running = false;
	pauseTime = clock();
}

bool StopWatch::isRunning(){
	return running;
}



StopWatch::~StopWatch()
{
}
