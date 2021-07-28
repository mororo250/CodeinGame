#include "Timer.h"

#include <iostream>


void Timer::start()
{
	begin = std::chrono::steady_clock::now();
}

void Timer::stop()
{
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cerr << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "us" << std::endl; 
}

void Timer::split()
{
	stop();
}
