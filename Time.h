/****************************************************************************
*																			*
*	File:		Time.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 7, 2016													*
*																			*
*	Purpose:	This file defines the time class.							*
*																			*
****************************************************************************/

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <string>

using namespace std;

// Enumerated type

enum phase {P1, P2, P3};

/****************************************************************************
*																			*
*	Definition of Time class												*
*																			*
****************************************************************************/

class Time
{
//	Public member functions

	public:

	//	Inspectors

		int get() const {return simTime;}
		int& get() {return simTime;}
		
	//	Mutators
	
		void add(int t) {simTime += t;}

//	Private member functions

	//private:
	
	//	Constructors
	
		Time(const int& t = 0) {simTime = t;} 

//	Data members

	private:
		int simTime;		// Simulation time
		phase simPhase;		// Phase
};

#endif