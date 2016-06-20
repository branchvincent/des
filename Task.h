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
		
		Task(int tp, float prevArrTime, int seed, int phase);

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

		float genArrTime(float prevArrTime, int seed, int phase);
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

Task::Task(int tp, float prevArrTime, int seed, int phase)
{
	type = tp;
	arrTime = genArrTime(prevArrTime, seed, phase);
	serTime = genSerTime(seed, phase);
	depTime = -1;
}

/****************************************************************************
*																			*
*	Function:	genArrTime													*
*																			*
*	Purpose:	To generate an arrival time based on the specified task		*
*				type, previous arrival time, and distribution seed			*
*																			*
****************************************************************************/

float Task::genArrTime(float prevArrTime, int seed, int phase)
{
	default_random_engine gen(seed);
	
	switch (type)
	{
	//	Communicating
	
		case 0: 
		{
			int prty[3] = {2, 3, 2}; 
			priority = prty[phase];
			float lambda = 10/30.;
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}
		
	//	Exception Handling
	
		case 1: 
		{
			int prty[3] = {1, 2, 1}; 
			priority = prty[phase];
			float lambda = 1/3.;									//	Placeholder (change to deterministic)
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}
		
	//	Paperwork
		
		case 2: 
		{
			int prty[3] = {3, 6, 4}; 
			priority = prty[phase];
			float lambda = 10/30.;
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}
		
	//	Maintenance of Way
		
		case 3: 
		{
			int prty[3] = {6, 1, 6}; 
			priority = prty[phase];
			float lambda = 0.1;													// No startup distribution
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}
		
	//	Temp Speed Restriction
			
		case 4: 
		{
			int prty[3] = {6, 1, 6}; 
			priority = prty[phase];
			float lambda = 0.1;													// No startup
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}
		
	//	Signal Response Management
	
		case 5: 
		{
			int prty[3] = {6, 1, 6}; 
			priority = prty[phase];
			float lambda = 15/30.;
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}
		
	//	Monitoring Inside
		
		case 6: 
		{
			int prty[3] = {4, 4, 5}; 
			priority = prty[phase];
			float lambda = 2/30.;
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}
		
	//	Monitoring Outside
		
		case 7: 
		{
			int prty[3] = {5, 5, 3}; 
			priority = prty[phase];
			float lambda = 3/30.;
			exponential_distribution<float> dist(lambda);
			return dist(gen) + prevArrTime;
		}	
			
	//	Planning Ahead
		
		case 8: 
		{
			int prty[3] = {6, 1, 6}; 
			priority = prty[phase];
			float lambda = 15/30.;
			exponential_distribution<float> dist(lambda);
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