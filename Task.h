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
		
		Task(int tp, float prevArrTime, int seed, int phase, float traffLevel);

	//	Inspectors

		int getType() const {return type;}
		int& getType() {return type;}
		int getPriority() const {return priority;}
		int& getPriority() {return priority;}
		float getArrTime() const {return arrTime;}
		float& getArrTime() {return arrTime;}
		float getSerTime() const {return serTime;}
		float& getSerTime() {return serTime;}
		float getDepTime() const {return depTime;}
		float& getDepTime() {return depTime;}

	//	Mutators
	
		void setArrTime(float t) {arrTime = t;}
		void setSerTime(float t) {serTime = t;}
		void setDepTime(float t) {depTime = t;}

	//	Other member functions

		int getPriority(int phase);
		float genArrTime(float prevArrTime, int seed, int phase, float traffLevel);
		float genSerTime(int seed, int phase);
		void output(ostream& out) const 
			{cout << "(" << type << ", " << arrTime << ", " << serTime <<  ")";}

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

Task::Task(int tp, float prevArrTime, int seed, int phase, float traffLevel)
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
		exit(1):
	}
	
//	Set task attributes

	type = tp;
	priority = getPriority(phase);
	arrTime = genArrTime(prevArrTime, seed, phase, traffLevel);
	serTime = genSerTime(seed, phase);
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
	int prty[9][3] = {	{2, 3, 2},	// Communicating
						{1, 2, 1}, 	// Exception handling
						{3, 6, 4},	// Paperwork
						{6, 1, 6},	// Maintenance of way
						{6, 1, 6},	// Temp speed restriction
						{6, 1, 6},	// Signal response management
						{4, 4, 5},	// Monitoring inside
						{5, 5, 3},	// Monitoring outisde
						{6, 1, 6}	// Planning ahead
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

float Task::genArrTime(float prevArrTime, int seed, int phase, traffLevel)
{	
//	Distribution parameters

	float lambda[9][3] = {	{1/3., 0.2, 1/3.},		// Communicating
							{0, 0.1/30, 0.1/30}, 	// Exception handling				change 0 to determinisitic
							{1/3., 1/30., 1/3.},	// Paperwork
							{0, 0.05/30, 0.5/30},	// Maintenance of way
							{0, 1/30., 0},			// Temp speed restriction
							{1/30., 0.1, 1/15.},	// Signal response management
							{1/15., 0.1, 0},		// Monitoring inside
							{0.1, 0.2, 0.1},		// Monitoring outisde
							{1/30., 1/15., 1/30.}	// Planning ahead
					 	 };	
		
//	Tasks affected by traffic level

	bool affByTraff[9][3] = {	{0, 1, 0},	// Communicating
								{0, 1, 0}, 	// Exception handling
								{0, 1, 1},	// Paperwork
								{0, 1, 0},	// Maintenance of way
								{0, 1, 0},	// Temp speed restriction
								{0, 1, 0},	// Signal response management
								{0, 0, 0},	// Monitoring inside
								{0, 1, 0},	// Monitoring outisde
								{0, 1, 0}	// Planning ahead
					 		 };	

//	Generated random interarrival time

	default_random_engine gen(seed);
	exponential_distribution<float> dist(lambda[type][phase]);
	float interTime = dist(gen);
	
//	Multiply by traffic level, if applicable 

	if (affByTraff[type][phase])
		interTime *= traffLevel;
		
//	Return arrival time

	return prevArrTime + dist(gen);
}

/****************************************************************************
*																			*
*	Function:	genSerTime													*
*																			*
*	Purpose:	To generate a service time based on the specified task type	* 
*				and distribution seed										*
*																			*
****************************************************************************/

float Task::genSerTime(int seed, int phase)
{
	default_random_engine gen(seed);
	
	switch (type)
	{
		
	//	Communicating
		
		case 0: 
		{
			float min = 0.033;
			float mode = 0.133;
			float max = 0.2167;
			lognormal_distribution<double> dist(mode, max);				// change to triangular
			return dist(gen);
		}
		
	//	Exception Handling
	
		case 1: 
		{	
			int mean = 0;
			int sigma = 1;
			lognormal_distribution<float> dist(mean, sigma);			// changed parameters
			return dist(gen);
		}
		
	//	Paperwork
		
		case 2: 
		{
			float min = 0.05;
			float max = 2;
			uniform_real_distribution<float> dist(min, max);
			return dist(gen);
		}
		
	//	Maintenance of Way
		
		case 3: 
		{
			float min = 0.167;
			float max = 1;
			uniform_real_distribution<float> dist(min, max);
			return dist(gen);
		}
		
	//	Temp Speed Restriction
			
		case 4: 
		{
			float min = 0.1;
			float max = 0.5;
			uniform_real_distribution<float> dist(min, max);
			return dist(gen);
		}
		
	//	Signal Response Management
	
		case 5: 
		{
			float min = 0.1;
			float max = 0.5;
			uniform_real_distribution<float> dist(min, max);
			return dist(gen);
		}
		
	//	Monitoring Inside
		
		case 6: 
		{
			float lambda = 0.1;
			exponential_distribution<float> dist(lambda);
			return dist(gen);
		}
		
	//	Monitoring Outside
		
		case 7: 
		{
			float lambda = 0.133;
			exponential_distribution<float> dist(lambda);
			return dist(gen);
		}	
			
	//	Planning Ahead
		
		case 8: 
		{
			float lambda = 0.33;
			exponential_distribution<float> dist(lambda);
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