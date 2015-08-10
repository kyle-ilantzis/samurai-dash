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
	bool           isRunning();
	unsigned long  getTime();
	bool           isOver(unsigned long seconds);

private:
	bool           resetted;
	bool           running;
	unsigned long pauseTime;
	unsigned long time;
	unsigned long  current;
	unsigned long  beg;
	unsigned long  end;
};

