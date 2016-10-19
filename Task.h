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
#include <cmath>
#include <algorithm>
#include "Parameters/Parameters.h"

using namespace std;
using namespace params;

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
		
		Task(int tp, float prevArrTime, int phase, int tNum);

	//	Inspectors

//		int getType() const {return type;}
		const int& getType() {return type;}
		const int& getPriority() {return priority;}
		const float& getArrTime() {return arrTime;}
		const float& getSerTime() {return serTime;}
		const float& getDepTime() {return depTime;}
		const float& getExpTime() {return expTime;}
        const float& getBegTime() {return begTime;}
        const float& getQueTime() {return queTime;}
        const float& getSerLeft() {return serLeft;}
//        const float getPercLeft() {return serLeft/serTime;}
        const vector<int> getOpNums() {return opNums;}
		const int& getTrainNum() {return trainNum;}

	//	Mutators
	
		void setArrTime(float t) {arrTime = t;}
		void setSerTime(float t) {serTime = t;}
		void setDepTime(float t) {depTime = t;}
        void setSerLeft(float t) {serLeft = t;}
        void setBegTime(float t) {begTime = t;}
        void setQueTime(float t) {queTime = t;}

	//	Other member functions

		void output(ostream& out) const 
			{cout << "(Pr " << priority << ", Tp " << type << ", Arr " << arrTime;
			cout << ", Ser " << serTime <<  ", Dep " << depTime << ", Exp " << expTime << ")";}
			
//	Private member functions

	private:
		
	//	Used by constructor
	
		float genArrTime(float prevArrTime, int phase);
		float genSerTime();
		float genExpTime(int phase);
		float genRandNum(char distType, int seed, float arg1, float arg2 = 0);
	
//	Data members

	private:
		int type;			// type
		int priority;		// priority level
		float arrTime;		// arrival time (min)
		float serTime; 		// service time (min)
		float depTime;		// depature time (min)
		float expTime;		// expiration time (min)
		float begTime;		// begin service time (min)
        float queTime;      // enter queue time (min)
        float serLeft;      // service time left
        vector<int> opNums;  // operator id number
		int trainNum;
};

//	Operators

ostream& operator<<(ostream& out, const Task& t) {t.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Task														*
*																			*
*	Purpose:	To construct a task of the specified type using the 		*
*				specified previous arrival time and distribution seed		*
*																			*
****************************************************************************/

Task::Task(int tp, float prevArrTime, int phase, int tNum) :
    type(tp),
    priority(PRTY[type][phase]),
    arrTime(genArrTime(prevArrTime, phase)),
    serTime(genSerTime()),
    depTime(INFINITY),
    expTime(genExpTime(phase)),
    begTime(0),
    queTime(arrTime),
    serLeft(serTime),
    opNums(OP_NUMS[type]),
	trainNum(tNum)
{
//	Check type
	
	if (tp < 0 || tp >= NUM_TASK_TYPES)
	{
		cerr << "Error:  Incompatible task type . Exiting..." << endl;
		exit(1);
	}
	
//	Check phase

	else if (phase < 0 || phase >= NUM_PHASES)
	{
		cerr << "Error:  Incompatible phase. Exiting..." << endl;
		exit(1);
	}
}

/****************************************************************************
*																			*
*	Function:	genArrTime													*
*																			*
*	Purpose:	To generate an arrival time based on the specified task		*
*				type, previous arrival time, and distribution seed			*
*																			*
****************************************************************************/

float Task::genArrTime(float prevArrTime, int phase)
{
//	Generate random interarrival time

	float interArrTime = genRandNum(ARR_DISTS[type], rand(), ARR_DIST_PARAMS[type][phase]);
    
//  Adjust for arrival time for traffic, if applicable
    
    float newArrTime = prevArrTime + interArrTime;
    if (isinf(newArrTime)) return INFINITY;
    
    if (AFF_BY_TRAFF[type][phase] && TRAFFIC_ON)
    {
        float budget = interArrTime;
        float currTime = prevArrTime;
        int currHour = currTime/60;
        float traffLevel = TRAFFIC[currHour];
        float timeToAdj = (currHour + 1) * 60 - currTime;
        float adjTime = timeToAdj * traffLevel;
        
    //  If time is left in budget, proceed
        
        while (budget > adjTime)
        {
        //  Decrement budget
            
            budget -= adjTime;
            
        //	Calculate new values
            
            currTime += timeToAdj;
            currHour++;
            
            if (currHour >= TRAFFIC.size())
            {
                if (DEBUG_ON) cout << "OVERFLOW" << endl;
                return INFINITY;
            }
            
            traffLevel = TRAFFIC[currHour];
            timeToAdj = (currHour + 1) * 60 - currTime;
            adjTime = timeToAdj * traffLevel;
        }
        
        newArrTime = currTime + budget/traffLevel;
    }
    
	return newArrTime;
}

/****************************************************************************
*																			*
*	Function:	genSerTime													*
*																			*
*	Purpose:	To generate a service time based on the specified task type	* 
*				and distribution seed										*
*																			*
****************************************************************************/

float Task::genSerTime()
{
//	Get service time parameters
    
    char distType = SER_DISTS[type];
    float param1 = SER_DIST_PARAMS[type][0];
    float param2 = SER_DIST_PARAMS[type][1];
    
//  Return random number
    
    float num = genRandNum(distType, rand(), param1, param2);
    
    while (isinf(num))
    {
        if (DEBUG_ON) cout << "ERROR:  " << *this << endl;
        if (DEBUG_ON) cout << distType << " " << param1 << " " << param2 << endl;
        num = genRandNum(distType, rand(), param1, param2);
    }
    
    return num;
}

/****************************************************************************
*																			*
*	Function:	genExpTime													*
*																			*
*	Purpose:	To generate an expiration time based on the specified task	*
*				type                                                        *
*																			*
****************************************************************************/

float Task::genExpTime(int phase)
{
//  Initialize variables
    
	float param;
	float expiration = 0;
	int hour = arrTime/60;
	
//	Set lambda
	
	if (hour >= TRAFFIC.size())
		return arrTime;
	else if (TRAFFIC[hour] == 2)
		param = EXP_DIST_PARAMS_HIGH[type][phase];
	else
		param = EXP_DIST_PARAMS_LOW[type][phase];
	
//	Get random number

    expiration = 2*serTime;
	expiration = 1000000;
//	while (expiration <= serTime)
//		expiration = genRandNum(EXP_DISTS[type], rand(), param);

	return arrTime + expiration;
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