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
#include <boost/property_tree/ptree.hpp>
#include "Task.h"
#include "Distribution.h"
#include "Util.h"

using namespace std;
using boost::property_tree::ptree;

/****************************************************************************
*																			*
*	Definition of TaskType class											*
*																			*
****************************************************************************/

class TaskType
{
//	Public member functions

	public:

	//	Constructors

		TaskType(ptree& xmlData);
		TaskType(string name, vector<int> priority, vector<bool> isAffectedByTraffic,
			vector<Distribution> interarrival, vector<Distribution> service,
			vector<Distribution> expiration);

	//	Inspectors

		string getName() const {return name;}
		vector<int> getPriority() const {return priority;}
		vector<bool> getIsAffectedByTraffic() const {return isAffectedByTraffic;}
		vector<Distribution> getInterarrival() const {return interarrival;}
		vector<Distribution> getService() const {return service;}
		vector<Distribution> getExpiration() const {return expiration;}

		int getPriority(int phase) const
			{checkIndex(priority, phase); return priority[phase];}
		bool getIsAffectedByTraffic(int phase) const
			{checkIndex(isAffectedByTraffic, phase); return isAffectedByTraffic[phase];}
		float randInterarrival(int phase = 0)
			{checkIndex(interarrival, phase); return interarrival[phase].rand();}
		float randService(int phase = 0)
			{checkIndex(service, phase); return service[phase].rand();}
		float randExpiration(int phase = 0)
			{checkIndex(expiration, phase); return expiration[phase].rand();}

	//	Mutators

	//	Other member functions

		Task genTask(int phase);

//	Private member functions

	private:
		template <typename T> void checkIndex(const vector<T>& vec, int index) const
			{ASSERT(index >= 0 && index < vec.size(), "Invalid array index");}
		void readDistributionFromXML(vector<Distribution>& dists, ptree& xmlData);
		float genArrivalTime(int phase);
		float genServiceTime();
		float genExpirationTime(float arrivalTime, float serviceTime, int phase);

//	Data members

	private:
		string name;
		vector<int> priority;
		vector<bool> isAffectedByTraffic;
		vector<Distribution> interarrival;
		vector<Distribution> service;
		vector<Distribution> expiration;
		float lastArrivalTime;
};

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

TaskType::TaskType(ptree& xmlData) : lastArrivalTime(0)
{
	name = xmlData.get<string>("name");
	priority = util::stringToVector<int>(xmlData.get<string>("priority"));
	isAffectedByTraffic = util::stringToVector<bool>(xmlData.get<string>("isAffectedByTraffic"));
	readDistributionFromXML(interarrival, xmlData.get_child("interarrival"));
	readDistributionFromXML(service, xmlData.get_child("service"));
	readDistributionFromXML(expiration, xmlData.get_child("expiration"));
}

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

TaskType::TaskType(string name, vector<int> priority, vector<bool> isAffectedByTraffic,
	vector<Distribution> interarrival, vector<Distribution> service,
	vector<Distribution> expiration) :
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

	float interarrivalTime = interarrival[phase].rand();

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

/****************************************************************************
*																			*
*	Function:	readDistributionArray										*
*																			*
*	Purpose:	To return a random number									*
*																			*
****************************************************************************/

void TaskType::readDistributionFromXML(vector<Distribution>& dists, ptree& xmlData)
{
	string type = util::toLower(xmlData.get<string>("<xmlattr>.type"));
	bool byPhase = xmlData.get<bool>("<xmlattr>.byPhase", false);

	if (byPhase)
	{
		int num_phases = 3;
		for (int i = 0; i < num_phases; i++)
		{
			vector<float> parameters = util::stringToVector<float>(xmlData.get<string>("phase" + to_string(i)));
			dists.push_back(Distribution(type, parameters));
		}
	}
	else
	{
		vector<float> parameters = util::stringToVector<float>(xmlData.get<string>(""));
		dists.push_back(Distribution(type, parameters));
	}

	return;
}

#endif
