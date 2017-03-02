/****************************************************************************
*																			*
*	File:		Timer.h                                                 	*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Timer class.							*
*																			*
****************************************************************************/

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>

using namespace std;

/****************************************************************************
*																			*
*	Definition of Timer class												*
*																			*
****************************************************************************/

class Timer
{
	public:
       	Timer() : start_t(clock()) {}
		void start(clock_t t) {start_t = t;}
		float elapsed() {return float(clock() - start_t)/CLOCKS_PER_SEC;}
	private:
       float start_t;
};

#endif
