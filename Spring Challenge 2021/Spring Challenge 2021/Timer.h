#pragma once

#include <chrono>

class Timer
{
public:
	Timer() = default;

	void start();
	void stop();
	void split();

private:

	std::chrono::steady_clock::time_point begin;
};