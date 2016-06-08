/****************************************************************************
*																			*
*	File:		Task.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file defines the task class.							*
*																			*
****************************************************************************/

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <queue>
#include <random>

using namespace std;

// Enumerated Type

//enum Type = {exponential, lognormal}

/****************************************************************************
*																			*
*	Definition of Task class												*
*																			*
****************************************************************************/

class Task
{
//	Public member functions

	public:

	//	Inspectors

		int getArr() const {return arrTime;}
		int& getArr() {return arrTime;}
		int getSer() const {return serTime;}
		int& getSer() {return serTime;}
		
	// 
	
//		int exponential(float lambda);
//		int lognormal(float mean, float sigma);

	//	Other member functions

		void output(ostream& out) const 
			{cout << "arr:  " << arrTime << endl << "ser:  " << serTime << endl;};

//	Private member functions

	//private:
	
	//	Constructors
	
		Task(int arr, int ser) {arrTime = arr; serTime = ser;}

//	Data members

	private:
		int arrTime;			// arrival time
		int serTime; 			// service time
};

//	Operators

ostream& operator<<(ostream& out, const Task t) {t.output(out); return out;}

//int Task:exponential(float lambda) 
//{
//	default_random_engine generator(rand());
//	exponential_distribution<float> dist(lambda); 
//	T += dist(generator); 
//	return T;
//}
//
//int Task:lognormal(float mean, float sigma)
//{
//	default_random_engine generator(rand());
//	lognormal_distribution<float> dist(mean,sigma);
//	int t = dist(generator);
//	return t;
//}

#endif