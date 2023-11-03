#include "Clock.h"
#include <stdio.h>
#define NOMINMAX
#include <Windows.h>
namespace df {
	Clock::Clock(){
		SYSTEMTIME before;
		GetSystemTime(&before);
		m_previous_time = (before.wMinute * 60 * 1000000) + (before.wSecond * 1000000) + (before.wMilliseconds * 1000);
	}
	long int Clock::delta(){
		SYSTEMTIME after;
		GetSystemTime(&after);
		long int a = (after.wMinute * 60 * 1000000) + (after.wSecond * 1000000) + (after.wMilliseconds * 1000);
		long int ret = a - m_previous_time;
		m_previous_time = a;
		return ret;
	}
	long int Clock::split() const{
		SYSTEMTIME after;
		GetSystemTime(&after);
		long int a = (after.wMinute * 60 * 1000000) + (after.wSecond * 1000000) + (after.wMilliseconds * 1000);
		long int ret = a - m_previous_time;
		return ret;
	}
}

