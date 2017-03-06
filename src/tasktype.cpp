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
#include "tasktype.h"
#include "task.h"
#include "team.h"
#include "datetime.h"
#include "distribution.h"
#include "utility.h"
#include "pugixml.h"
#include "easylogging++.h"

using namespace std;
using pugi::xml_node;

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

TaskType::TaskType(Team& team, const xml_node& data) : _team(team), _agentIds{}, _lastArrival(0)
{
	LOG(DEBUG) << "Initializing tasktype at " << this;

//	Get attributes

	_name = data.attribute("name").value();
	string id = data.attribute("id").value();
	string priority = data.child_value("priority");
	string traffic = data.child_value("isAffectedByTraffic");

	LOG_IF(_name == "", FATAL) << "XML Error: Could not read task attribute 'name'";
	LOG_IF(id == "", FATAL) << "XML Error: Could not read task attribute 'id'";
	LOG_IF(priority == "", FATAL) << "XML Error: Could not read task attribute 'priority'";
	LOG_IF(traffic == "", FATAL) << "XML Error: Could not read task attribute 'traffic'";

	_id = atoi(id.c_str());
	_priority = atoi(priority.c_str());
	_isAffectedByTraffic = atoi(traffic.c_str());

	//TODO: Fixup
	for (const xml_node& child : data)
	{
		if ((string)child.name() == "interarrival")
		{
			readDistributionFromXML(_interarrival, child);
		}
		if ((string)child.name() == "service")
		{
			readDistributionFromXML(_service, child);
		}
		else if ((string)child.name() == "expiration")
		{
			readDistributionFromXML(_expiration, child);
		}
	}

	LOG(DEBUG) << "Initialized task type\n" << *this;
}

vector<Agent> TaskType::agents() const {return util::subset(_team._agents, _agentIds);}

// TaskType::TaskType() :
// 	// team(NULL),
// 	name("DefaultTaskType"),
// 	priority(2),
// 	isAffectedByTraffic(true),
// 	interarrival(Distribution()),
// 	service(Distribution("uniform", 600, 6000)),
// 	expiration(Distribution()),
// 	lastArrival(0)
// {}
//
//
// TaskType::TaskType(string name, int priority, bool isAffectedByTraffic,
// 	Distribution interarrival, Distribution service, Distribution expiration, Team* team) :
// 	// team(team),
// 	name(name),
// 	priority(priority),
// 	isAffectedByTraffic(isAffectedByTraffic),
// 	interarrival(interarrival),
// 	service(service),
// 	expiration(expiration),
// 	lastArrival(0)
// {}

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

// TaskType::TaskType(Team& team, const ptree& xmlData) : team(team), lastArrival(0)
// {
// 	name = xmlData.get<string>("name");
// 	priority = util::toVector<int>(xmlData.get<string>("priority"));
// 	isAffectedByTraffic = util::toVector<bool>(xmlData.get<string>("isAffectedByTraffic"));
// 	readDistributionFromXML(interarrival, xmlData.get_child("interarrival"));
// 	readDistributionFromXML(service, xmlData.get_child("service"));
// 	readDistributionFromXML(expiration, xmlData.get_child("expiration"));
// }

/****************************************************************************
*																			*
*	Function:	TaskType													*
*																			*
*	Purpose:	To construct a task type									*
*																			*
****************************************************************************/

// TaskType::TaskType(string name, vector<int> priority, vector<bool> isAffectedByTraffic,
// 	vector<Distribution> interarrival, vector<Distribution> service, vector<Distribution> expiration) :
// 	name(name),
// 	priority(priority),
// 	isAffectedByTraffic(isAffectedByTraffic),
// 	interarrival(interarrival),
// 	service(service),
// 	expiration(expiration),
// 	lastArrival(0)
// {}

// float TaskType::randInterarrival() {return _interarrival.rand();}
// float TaskType::randService() {return _service.rand();}
// float TaskType::randExpiration() {return _expiration.rand();}

/****************************************************************************
*																			*
*	Function:	genTask														*
*																			*
*	Purpose:	To generate a new task										*
*																			*
****************************************************************************/

Task TaskType::genTask()
{
	 float arrivalTime = genArrivalTime();
	 float serviceTime = genServiceTime();
	 float expirationTime = genExpirationTime(arrivalTime, serviceTime);
	 _lastArrival = arrivalTime;
	 DateTime arrivalDate = getAbsTime(arrivalTime);
	 DateTime expirationDate = getAbsTime(expirationTime);
	 // cout << "Start " << startDate << endl;
	 // cout << "Arrival " << arrivalDate << endl;
	 // cout << "Expiration " << expirationDate << endl;
	 return Task(_priority, arrivalDate, serviceTime, expirationDate, *this);
}

void TaskType::addAgentId(int id)
{
	_agentIds.push_back(id);
}

/****************************************************************************
*																			*
*	Function:	validate													*
*																			*
*	Purpose:	To validate a task type										*
*																			*
****************************************************************************/

void TaskType::validate() const
{
//	for (const Agent* agent : _agents)
//	{
//		LOG_IF(agent == NULL, FATAL) << "Task Type not valid: agent is null";
//		// LOG_IF(not util::contains(agent->taskTypes, this), FATAL) << "Task Type not valid: agent does not contain self";
//	}
}

void TaskType::reset()
{
	_lastArrival = 0;
}

DateTime TaskType::getAbsTime(float relativeTime)
{
	DateTime startDate = Shift().getStart(); //team.shift.getStart();	TODO
	if (isinf(relativeTime))
		return DateTime(MAX_TIME);
	else
		return startDate + util::minToSec(relativeTime);
}

/****************************************************************************
*																			*
*	Function:	genArrival													*
*																			*
*	Purpose:	To generate a new arrival time								*
*																			*
****************************************************************************/

float TaskType::genArrivalTime()
{
//	Generate random interarrival time

	float interarrivalTime = _interarrival.rand();

//  Adjust for arrival time for traffic, if applicable

    float arrivalTime = _lastArrival + interarrivalTime;

    // if (isAffectedByTraffic and !isinf(arrivalTime))
    // {
    //     float budget = interarrivalTime;
    //     float currTime = lastArrival;
    //     int currHour = currTime/60;
	//
	// 	assert(currHour >= 0 && currHour < util::TRAFFIC.size());		// TODO
    //     float trafficLevel = util::TRAFFIC[currHour];
    //     float timeToAdj = (currHour + 1) * 60 - currTime;
    //     float adjTime = timeToAdj * trafficLevel;
	//
    // //  If time is left in budget, proceed
	//
    //     while (budget > adjTime)
    //     {
    //     //  Decrement budget
	//
    //         budget -= adjTime;
	//
    //     //	Calculate new values
	//
    //         currTime += timeToAdj;
    //         currHour++;
	//
    //         if (currHour >= util::TRAFFIC.size())
	// 			trafficLevel = 1;
	// 		else
    //         	trafficLevel = util::TRAFFIC[currHour];
    //         timeToAdj = (currHour + 1) * 60 - currTime;
    //         adjTime = timeToAdj * trafficLevel;
    //     }
	//
    //     arrivalTime = currTime + budget/trafficLevel;
    // }

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

float TaskType::genExpirationTime(float arrivalTime, float serviceTime)
{
	float relativeExpTime = randExpiration();
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

void TaskType::readDistributionFromXML(Distribution& dist, const xml_node& data)
{
	string type = util::toLower(data.attribute("type").value());
	vector<float> params;

	if (type == "exponential")
	{
		params.push_back(data.attribute("lambda").as_float());
	}
	else if (type == "lognormal")
	{
		params.push_back(data.attribute("mean").as_float());
		params.push_back(data.attribute("stddev").as_float());
	}
	else if (type == "uniform")
	{
		params.push_back(data.attribute("min").as_float());
		params.push_back(data.attribute("max").as_float());
	}

	dist = Distribution(type, params);
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
	out << "Task " << _name << endl;
	out << "Priority: " << _priority << endl;
	out << "Traffic effect: " << _isAffectedByTraffic << endl;
	out << "Interarrival: " << _interarrival << endl;
	out << "Service: " << _service << endl;
	out << "Expiration: " << _expiration;
}

// void TaskType::copy(const TaskType& t)
// {
// 	team = t.team;
// 	name = t.name;
// 	priority = t.priority;
// 	isAffectedByTraffic = t.isAffectedByTraffic;
// 	interarrival = t.interarrival;
// 	service = t.service;
// 	expiration = t.expiration;
// 	lastArrival = t.lastArrival;
// }

//	Operators

ostream& operator<<(ostream& out, const TaskType& t) {t.output(out); return out;}
