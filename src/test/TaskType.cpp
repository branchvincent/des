/****************************************************************************
*																			*
*	File:		TaskType.cpp												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the TaskType class.						*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include "TaskType.h"
#include "Task.h"
#include "Distribution.h"
#include "Utility.h"

using namespace std;
using boost::property_tree::ptree;

/****************************************************************************
*																			*
*	Definition of TaskType class											*
*																			*
****************************************************************************/

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

TaskType::TaskType() :
	name(""),
	priority(-1),
	isAffectedByTraffic{},
	interarrival{},
	service{},
	expiration{},
	lastArrival(-1)
{}

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

TaskType::TaskType(const ptree& xmlData) //: team(team), lastArrival(0)
{
	name = xmlData.get<string>("name");
	priority = util::toVector<int>(xmlData.get<string>("priority"));
	isAffectedByTraffic = util::toVector<bool>(xmlData.get<string>("isAffectedByTraffic"));
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
	vector<Distribution> interarrival, vector<Distribution> service, vector<Distribution> expiration) :
	name(name),
	priority(priority),
	isAffectedByTraffic(isAffectedByTraffic),
	interarrival(interarrival),
	service(service),
	expiration(expiration),
	lastArrival(0)
{}

const string& TaskType::getName() const {return name;}
vector<int> TaskType::getPriority() const {return priority;}
vector<bool> TaskType::getIsAffectedByTraffic() const {return isAffectedByTraffic;}
vector<Distribution> TaskType::getInterarrival() const {return interarrival;}
vector<Distribution> TaskType::getService() const {return service;}
vector<Distribution> TaskType::getExpiration() const {return expiration;}

int TaskType::getPriority(int phase) const
	{util::checkIndex(priority, phase); return priority[phase];}
bool TaskType::getIsAffectedByTraffic(int phase) const
	{util::checkIndex(isAffectedByTraffic, phase); return isAffectedByTraffic[phase];}
float TaskType::randInterarrival(int phase)
	{util::checkIndex(interarrival, phase); return interarrival[phase].rand();}
float TaskType::randService(int phase)
	{util::checkIndex(service, phase); return service[phase].rand();}
float TaskType::randExpiration(int phase)
	{util::checkIndex(expiration, phase); return expiration[phase].rand();}

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
	float serviceTime = genServiceTime(phase);
	float expirationTime = genExpirationTime(phase, arrivalTime, serviceTime);
	lastArrival = arrivalTime;
	return Task(*this, priority[phase], arrivalTime, serviceTime, expirationTime);
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

    float arrivalTime = lastArrival + interarrivalTime;

    if (isAffectedByTraffic[phase] and !isinf(arrivalTime))
    {
        float budget = interarrivalTime;
        float currTime = lastArrival;
        int currHour = currTime/60;

		assert(currHour >= 0 && currHour < util::TRAFFIC.size());		// TODO
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

float TaskType::genServiceTime(int phase)
{
    float serviceTime = randService(phase);
    // while (isinf(serviceTime))				// TODO
	// 	serviceTime = randService(phase);
    return serviceTime;
}

/****************************************************************************
*																			*
*	Function:	genExpirationTime											*
*																			*
*	Purpose:	To generate an expiration time                              *
*																			*
****************************************************************************/

float TaskType::genExpirationTime(int phase, float arrivalTime, float serviceTime)
{
	float relativeExpTime = randExpiration(phase);
	// while (relativeExpTime <= serviceTime)		// TODO
	// 	relativeExpTime = randExpiration(phase);
	return arrivalTime + serviceTime + relativeExpTime;
}

/****************************************************************************
*																			*
*	Function:	readDistributionFromXML										*
*																			*
*	Purpose:	To return a random number									*
*																			*
****************************************************************************/

void TaskType::readDistributionFromXML(vector<Distribution>& dists, const ptree& xmlData)
{
	string type = util::toLower(xmlData.get<string>("<xmlattr>.type"));
	bool byPhase = xmlData.get<bool>("<xmlattr>.byPhase", false);

	if (byPhase)
	{
		for (const auto& phase : xmlData)
		{
			if (phase.first == "phase")
			{
				vector<float> parameters = util::toVector<float>(phase.second.get<string>(""));
				dists.push_back(Distribution(type, parameters));
			}
		}
	}
	else
	{
		vector<float> parameters = util::toVector<float>(xmlData.get<string>(""));
		dists.push_back(Distribution(type, parameters));
	}

	return;
}

/****************************************************************************
*																			*
*	Function:	output 														*
*																			*
*	Purpose:	To return a random number									*
*																			*
****************************************************************************/

void TaskType::output(ostream& out) const
{
	out << "Name: " << name << endl;
	out << "Priority: " << priority << endl;
	out << "Traffic effect: " << isAffectedByTraffic << endl;
	out << "Interarrival: " << interarrival << endl;
	out << "Service: " << service << endl;
	out << "Expiration: " << expiration;
}

//	Operators

ostream& operator<<(ostream& out, const TaskType& t) {t.output(out); return out;}
