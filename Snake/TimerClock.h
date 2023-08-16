#define _CRT_SECURE_NO_WARNINGS  1
#pragma once
#include <chrono>
class TimerClock;
class TimerClock
{
public:
	TimerClock() {
		update();
	}

	~TimerClock() {
	}

	void update() {
		_start = std::chrono::high_resolution_clock::now();
	}
	//��ȡ��
	double getSecond() {
		return getMicroSec() * 0.000001;
	}
	//��ȡ����
	double getMilliSec() {
		return getMicroSec() * 0.001;
	}
	//��ȡ΢��
	long long getMicroSec() {
		//��ǰʱ�Ӽ�ȥ��ʼʱ�ӵ�count
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - _start).count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock>_start;
};