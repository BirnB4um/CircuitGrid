#pragma once
#include <chrono>

class Timer {
private:
	std::chrono::steady_clock::time_point t;
	std::chrono::duration<double, std::milli> duration;

public:
	//start timer
	void start() { t = std::chrono::high_resolution_clock::now(); }

	//stop timer and get time from timer in millisec
	double stop() {
		duration = std::chrono::high_resolution_clock::now() - t;
		return duration.count();
	}

	//get duration of timer in milliseconds
	double get_duration() { return duration.count(); }

	//get time since betriebszeit in milliseconds
	long long get_time() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}
};