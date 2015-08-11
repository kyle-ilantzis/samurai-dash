#pragma once
#include <conio.h>
#include <time.h>

class StopWatch
{
public:
	StopWatch();

	~StopWatch();

	void           start();
	void           stop();
	void           reset();
	unsigned long  getTime();


private:
	bool           resetted;
	bool           running;
	unsigned long pauseTime;
	unsigned long time;
	unsigned long  current;
	unsigned long  startTime;
	unsigned long  endTime;
};

