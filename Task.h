/****************************************************************************
*																			*
*	File:		Task.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file defines the Task class.							*
*																			*
****************************************************************************/

#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <random>

using namespace std;

// Global distribution variables (placeholders)

double arrA = 0.1;
int serA[2] = {1,1};
int arrB[2] = {5,3};
int serB[2] = {3,2};

/****************************************************************************
*																			*
*	Definition of Task class												*
*																			*
****************************************************************************/

class Task
{
//	Public member functions

	public:

	//	Constructor
		
		Task(char type, int currTime, int seed);

	//	Inspectors

		int getArrTime() const {return arrTime;}
		int& getArrTime() {return arrTime;}
		int getSerTime() const {return serTime;}
		int& getSerTime() {return serTime;}
		
	//	Mutators
	
		void setArrTime(int t) {arrTime = t;}
		void setSerTime(int t) {serTime = t;}

	//	Other member functions

		int genArrTime(char type, int prevArrTime, int seed);
		int genSerTime(char type, int seed);
		void output(ostream& out) const 
			{cout << "(" << arrTime << ", " << serTime <<  ")" << endl;}

//	Data members

	private:
		int arrTime;		// arrival time
		int serTime; 		// service time
};

//	Operators

ostream& operator<<(ostream& out, const Task t) {t.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Task														*
*																			*
*	Purpose:	To construct a task of the specified type using the 		*
*				specified previous arrival time and distribution seed		*
*																			*
****************************************************************************/

Task::Task(char type, int prevArrTime, int seed)
{
	arrTime = genArrTime(type, prevArrTime, seed);
	serTime = genSerTime(type, seed);
	return;
}

/****************************************************************************
*																			*
*	Function:	genArrTime													*
*																			*
*	Purpose:	To generate an arrival time based on the specified task		*
*				type, previous arrival time, and distribution seed			*
*																			*
****************************************************************************/

int Task::genArrTime(char type, int prevArrTime, int seed)
{
	default_random_engine gen(seed);
	
	switch (type)
	{
	//	Type A
	
		case 'A': 
		{
			double lambda = arrA;
			exponential_distribution<double> dist(arrA);
			return dist(gen) + prevArrTime;
		}
	//	Type B
	
		case 'B': 
		{
			int mean = arrB[0];
			int sigma = arrB[1];
			normal_distribution<double> dist(mean, sigma);
			return dist(gen) + prevArrTime;
		}
	//	Error message
	
		default:
		{
			cerr << "Error:  Incompatible task type. Exiting..." << endl;
			exit(1);
		}
	} 
}

/****************************************************************************
*																			*
*	Function:	genSerTime													*
*																			*
*	Purpose:	To generate a service time based on the specified task type	* 
*				and distribution seed										*
*																			*
****************************************************************************/

int Task::genSerTime(char type, int seed)
{
	default_random_engine gen(seed);
	
	switch (type)
	{
	//	Type A
	
		case 'A': 
		{
			int mean = serA[0]; 
			int sigma = serA[1];
			lognormal_distribution<double> dist(mean, sigma);
			return dist(gen);
		}
	//	Type B
	
		case 'B':
		{
			int mean = serB[0];
			int sigma = serB[1];
			normal_distribution<double> dist(mean, sigma);
			return dist(gen);
		}
	//	Error message
	
		default:
		{
			cerr << "Error:  Incompatible task type. Exiting..." << endl;
			exit(1);
		}
	}
}

#endif