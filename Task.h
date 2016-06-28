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
		
		Task(int tp, float prevArrTime, int seed, int phase, vector<float> traffLevel);

	//	Inspectors

//		int getType() const {return type;}
		const int& getType() {return type;}
		const int& getPriority() {return priority;}
		const float& getArrTime() {return arrTime;}
		const float& getSerTime() {return serTime;}
		const float& getDepTime() {return depTime;}

	//	Mutators
	
		void setArrTime(float t) {arrTime = t;}
		void setSerTime(float t) {serTime = t;}
		void setDepTime(float t) {depTime = t;}

	//	Other member functions
	
		void output(ostream& out) const 
			{cout << "(Pr " << priority << ", Tp " << type << ", Arr " << arrTime;
			cout << ", Ser " << serTime <<  ", Dep " << depTime << ")";}
			
//	Private member functions

	private:
		
	//	Used by constructor
	
		int getPriority(int phase);
		float genArrTime(float prevArrTime, int seed, int phase, vector<float> traffLevel);
		float genSerTime(int seed);
		float genRandNum(char distType, int seed, float arg1, float arg2 = 0);
	
//	Data members

	private:
		int type;			// type
		int priority;		// priority level
		float arrTime;		// arrival time (min)
		float serTime; 		// service time (min)
		float depTime;		// depature time (min)
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

Task::Task(int tp, float prevArrTime, int seed, int phase, vector<float> traffLevel)
{
//	Check type 

	if (tp < 0 || tp > 8)
	{
		cerr << "Error:  Incompatible task type. Exiting..." << endl;
		exit(1);
	}
	
//	Check phase

	else if (phase < 0 || phase > 2)
	{
		cerr << "Error:  Incompatible phase. Exiting..." << endl;
		exit(1);
	}
	
//	Set task attributes

	type = tp;
	priority = getPriority(phase);
	arrTime = genArrTime(prevArrTime, seed, phase, traffLevel);
	serTime = genSerTime(seed);
	depTime = -1;
}

/****************************************************************************
*																			*
*	Function:	getPriority													*
*																			*
*	Purpose:	To return the priority based on the task type and specified *
*				phase			 											*
*																			*
****************************************************************************/

int Task::getPriority(int phase)
{	
//	Priority array (task types vs. phases)

						//	P0,	P1,	P2
	int prty[9][3] = 	{	{4, 3, 	4},		// Communicating
							{5, 4, 	5}, 	// Exception handling
							{3,	0, 	2},		// Paperwork
							{0, 5, 	0},		// Maintenance of way
							{0, 5, 	0},		// Temp speed restriction
							{0, 5, 	0},		// Signal response management
							{2, 2, 	1},		// Monitoring inside
							{1, 1, 	3},		// Monitoring outisde
							{0, 5, 	0}		// Planning ahead
					 	};	
					
	return prty[type][phase];
}

/****************************************************************************
*																			*
*	Function:	genArrTime													*
*																			*
*	Purpose:	To generate an arrival time based on the specified task		*
*				type, previous arrival time, and distribution seed			*
*																			*
****************************************************************************/

float Task::genArrTime(float prevArrTime, int seed, int phase, vector<float> traffLevel)
{	
//	Exponential distribution parameters (task types vs. phases)

							//	P0,		P1,		P2
	float lambda[9][3] = 	{	{1/3., 	0.2, 	1/3.},		// Communicating
								{0, 	.1/30, 	.1/30}, 	// Exception handling		*change 0 to determinisitic
								{1/3., 	1/30., 	1/3.},		// Paperwork
								{0, 	.05/30, .5/30},		// Maintenance of way
								{0, 	1/30., 	0},			// Temp speed restriction
								{1/30., 0.1, 	1/15.},		// Signal response management
								{1/15., 0.1, 	0},			// Monitoring inside
								{0.1, 	0.2, 	0.1},		// Monitoring outisde
								{1/30., 1/15., 1/30.}		// Planning ahead
					 	 	};	
		
//	Tasks affected by traffic level (task types vs. phases)

								//	P0, P1,	P2
	bool affByTraff[9][3] = 	{	{0,	1,	0},		// Communicating
									{0, 1, 	0}, 	// Exception handling
									{0, 1, 	1},		// Paperwork
									{0, 1, 	0},		// Maintenance of way
									{0, 1, 	0},		// Temp speed restriction
									{0, 1, 	0},		// Signal response management
									{0, 0, 	0},		// Monitoring inside
									{0, 1, 	0},		// Monitoring outisde
									{0, 1, 	0}		// Planning ahead
					 		 	};	

//	Generate random interarrival time

	float interArrTime = genRandNum('E', seed, lambda[type][phase]);
	float arrival = prevArrTime + interArrTime; 
	int currHour = (arrival/60. + 0.5);
	
//	Multiply by traffic level, if applicable 												think more about traffic
	
//	if (affByTraff[type][phase]) 
//	{	
//		float newInterArrTime = interArrTime / traffLevel[currHour];
//		float newArrival = prevArrTime + newInterArrTime;
//	 	int newCurrHour = (newArrival/60. + 0.5);
//		if (currHour == newCurrHour)
//			arrival = newArrival;
//	}	
	
//	Return arrival time

	return arrival; //prevArrTime + interArrTime;
}

/****************************************************************************
*																			*
*	Function:	genSerTime													*
*																			*
*	Purpose:	To generate a service time based on the specified task type	* 
*				and distribution seed										*
*																			*
****************************************************************************/

float Task::genSerTime(int seed)
{
//	Generate service time, based on type

	switch (type)
	{
//		case 0:	return genRandNum('L', seed, -1.6670796, 0.74938);	// Communicating
		case 0:	return genRandNum('E', seed, 1/0.133);				// Communicating
		case 1:	return genRandNum('L', seed, 0.980297, 1.389685);	// Exception handling
		case 2: return genRandNum('U', seed, 0.05, 2);				// Paperwork	
		case 3: return genRandNum('U', seed, 0.167, 1);				// Maintenance of way
		case 4:	return genRandNum('U', seed, 0.1, 0.5);				// Temp speed restriction
		case 5:	return genRandNum('U', seed, 0.1, 0.5);				// Signal response management
		case 6:	return genRandNum('E', seed, 1/0.133);				// Monitoring inside
		case 7:	return genRandNum('E', seed, 1/0.1);				// Monitoring outside
		case 8:	return genRandNum('E', seed, 1/0.33);				// Planning ahead
	
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
*	Function:	genRandNum													*
*																			*
*	Purpose:	To generate a random number based on the specified 			*
*				distribution type and seed									*
*																			*
****************************************************************************/

float Task::genRandNum(char distType, int seed, float arg1, float arg2)
{
//	Initialize generator

	default_random_engine gen(seed);
	
//	Return random number, based on distribution type

	switch (distType)
	{
	//	Exponential
	
		case 'E': 
		{
			exponential_distribution<float> dist(arg1);			// args = lambda
			return dist(gen);
		}
		
	//	Lognormal
	
		case 'L': 
		{
			lognormal_distribution<double> dist(arg1, arg2);	// args = mean, stddev
			return dist(gen);
		}
		
	//	Uniform
	
		case 'U': 
		{	
			uniform_real_distribution<float> dist(arg1, arg2);	// args = min, max
			return dist(gen);
		}
		
	//	Error message
	
		default:
		{
			cerr << "Error:  Incompatible distribution type. Exiting..." << endl;
			exit(1);
		}
	}
}

#endif