/****************************************************************************
*																			*
*	File:		TaskType.h													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the TaskType class.						*
*																			*
****************************************************************************/

#ifndef TASKTYPE_H
#define TASKTYPE_H

#include <iostream>
#include <string>
#include <cassert>
#include "distribution/Distribution.h"
#include "TaskNew.h"
// #include "distribution/ExponentialDistribution.h"
// #include "distribution/ExponentialDistribution.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of TaskType class											*
*																			*
****************************************************************************/

class TaskType
{
//	Public member functions

	public:

	//	Constructor

		TaskType(string name, vector<int> priority, vector<bool> isAffectedByTraffic,
			vector<Distribution*> interarrival, vector<Distribution*> service,
			vector<Distribution*> expiration);

	//	Destructor

		~TaskType();

	//	Inspectors

		string getName() const {return name;}
		vector<int> getPriority() const {return priority;}
		vector<bool> getIsAffectedByTraffic() const {return isAffectedByTraffic;}
		vector<Distribution*> getInterarrival() const {return interarrival;}
		vector<Distribution*> getService() const {return service;}
		vector<Distribution*> getExpiration() const {return expiration;}

		int getPriority(int phase) const
			{assert(phase >= 0 && phase < priority.size());
			return priority[phase];}
		bool getIsAffectedByTraffic(int phase) const
			{assert(phase >= 0 && phase < isAffectedByTraffic.size());
			return isAffectedByTraffic[phase];}
		float randInterarrival(int phase = 0) const
			{assert(phase >= 0 && phase < interarrival.size());
			return interarrival[phase]->rand();}
		float randService(int phase = 0) const
			{assert(phase >= 0 && phase < service.size());
			return service[phase]->rand();}
		float randExpiration(int phase = 0) const
			{assert(phase >= 0 && phase < expiration.size());
			return expiration[phase]->rand();}

	//	Mutators

	//	Other member functions

		Task genTask(int phase);

//	Private member functions

	private:
		float genArrivalTime(int phase);
		float genServiceTime();
		float genExpirationTime(float arrivalTime, float serviceTime, int phase);

//	Data members

	private:
		string name;
		vector<int> priority;
		vector<bool> isAffectedByTraffic;
		vector<Distribution*> interarrival;
		vector<Distribution*> service;
		vector<Distribution*> expiration;
		float lastArrivalTime;
};

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

TaskType::TaskType(string name, vector<int> priority, vector<bool> isAffectedByTraffic,
	vector<Distribution*> interarrival, vector<Distribution*> service,
	vector<Distribution*> expiration) :
	name(name),
	priority(priority),
	isAffectedByTraffic(isAffectedByTraffic),
	interarrival(interarrival),
	service(service),
	expiration(expiration),
	lastArrivalTime(0)
{}

/****************************************************************************
*																			*
*	Function:	~TaskType													*
*																			*
*	Purpose:	To destroy a task type										*
*																			*
****************************************************************************/

TaskType::~TaskType()
{
	// delete interarrival;
	// delete service;
	// delete expiration;
}

/****************************************************************************
*																			*
*	Function:	genTask														*
*																			*
*	Purpose:	To generate a new task										*
*																			*
****************************************************************************/

Task TaskType::genTask(int phase)
{
	float arrivalTime = genArrivalTime(phase);
	float serviceTime = genServiceTime();
	float expirationTime = genExpirationTime(arrivalTime, serviceTime, phase);
	lastArrivalTime = arrivalTime;
	return Task(name, priority[phase], arrivalTime, serviceTime, expirationTime);;
}

/****************************************************************************
*																			*
*	Function:	genArrival													*
*																			*
*	Purpose:	To generate a new arrival time								*
*																			*
****************************************************************************/

float TaskType::genArrivalTime(int phase)
{
//	Generate random interarrival time

	float interarrivalTime = interarrival[phase]->rand();

//  Adjust for arrival time for traffic, if applicable

    float arrivalTime = lastArrivalTime + interarrivalTime;

    if (isAffectedByTraffic[phase] && !isinf(arrivalTime))
    {
        float budget = interarrivalTime;
        float currTime = lastArrivalTime;
        int currHour = currTime/60;

		assert(currHour >= 0 && currHour < util::TRAFFIC.size());
        float trafficLevel = util::TRAFFIC[currHour];
        float timeToAdj = (currHour + 1) * 60 - currTime;
        float adjTime = timeToAdj * trafficLevel;

    //  If time is left in budget, proceed

        while (budget > adjTime)
        {
        //  Decrement budget

            budget -= adjTime;

        //	Calculate new values

            currTime += timeToAdj;
            currHour++;

            if (currHour >= util::TRAFFIC.size())
				trafficLevel = 1;
			else
            	trafficLevel = util::TRAFFIC[currHour];
            timeToAdj = (currHour + 1) * 60 - currTime;
            adjTime = timeToAdj * trafficLevel;
        }

        arrivalTime = currTime + budget/trafficLevel;
    }

	return arrivalTime;
}

/****************************************************************************
*																			*
*	Function:	genServiceTime												*
*																			*
*	Purpose:	To generate a service time									*
*																			*
****************************************************************************/

float TaskType::genServiceTime()
{
    float serviceTime = randService();
    while (isinf(serviceTime))
		serviceTime = randService();
    return serviceTime;
}

/****************************************************************************
*																			*
*	Function:	genExpirationTime											*
*																			*
*	Purpose:	To generate an expiration time                              *
*																			*
****************************************************************************/

float TaskType::genExpirationTime(float arrivalTime, float serviceTime, int phase)
{
	float relativeExpTime = randExpiration(phase);
	while (relativeExpTime <= serviceTime)
		relativeExpTime = randExpiration(phase);
	return arrivalTime + relativeExpTime;
}

#endif
