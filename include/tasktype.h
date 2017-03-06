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
#include <vector>
#include "distribution.h"
#include "pugixml.h"
// #include "datetime.h"

using namespace std;
using pugi::xml_node;

// class Distribution;
class Agent;
class Team;
class Task;
class DateTime;

/****************************************************************************
*																			*
*	Definition of TaskType class											*
*																			*
****************************************************************************/

class TaskType
{
//	Friends

	friend class Agent;
	friend class Task;
	friend class Team;

//	Public member functions

	public:

	//	Constructors

		// TaskType();
		TaskType(Team& team, const xml_node& data);
		// TaskType(Team* team, const xml_node& data);
		// TaskType(string name, int priority, bool isAffectedByTraffic,
//			Distribution interarrival, Distribution service, Distribution expiration, Team* team);
		// TaskType(string name, vector<int> priority, vector<bool> isAffectedByTraffic,
		// 	vector<Distribution> interarrival, vector<Distribution> service,
		// 	vector<Distribution> expiration);

	//	Inspectors

		string& name() {return _name;}
		int& id() {return _id;}
		// vector<Agent*>& agents() {return _agents;}
		vector<Agent> agents() const;
		int& priority() {return _priority;}
		bool& isAffectedByTraffic() {return _isAffectedByTraffic;}
		Distribution& interarrival() {return _interarrival;}
		Distribution& service() {return _service;}
		Distribution& expiration() {return _expiration;}
		float& lastArrival() {return _lastArrival;}

		//  string& name() const {return _name;}
		//  int& id() const {return _id;}
		//  vector<Agent*>& agents() const {return _agents;}
		//  int& priority() const {return _priority;}
		//  bool& isAffectedByTraffic() const {return _isAffectedByTraffic;}
		//  Distribution& interarrival() {return _interarrival;}
		//  Distribution& service() {return _service;}
		//  Distribution& expiration() {return _expiration;}
		//  float& lastArrival() {return _lastArrival;}

		void addAgentId(int id);
		// void setTeam(Team* t) {team = t;}
		// int getPriority(int phase) const;
		// bool getIsAffectedByTraffic(int phase) const;
		// float randInterarrival(int phase);
		// float randService(int phase);
		// float randExpiration(int phase);
		float randInterarrival() {return _interarrival.rand();}
		float randService() {return _service.rand();}
		float randExpiration() {return _expiration.rand();}

	//	Mutators

	//	Operators

		// TaskType& operator=(const TaskType& t);

	//	Other member functions

		void reset();
		Task genTask();
		void validate() const;
        void output(ostream& out) const;
		// void copy(const TaskType& t);

//	Private member functions

	private:
		DateTime getAbsTime(float relativeTime);
		float genArrivalTime();
		float genServiceTime();
		float genExpirationTime(float arrivalTime, float serviceTime);
		void readDistributionFromXML(Distribution& dist, const xml_node& data);

//	Data members

	private:
		Team& _team;
		string _name;
		int _id;
		vector<int> _agentIds;
		int _priority;
		bool _isAffectedByTraffic;
		Distribution _interarrival;
		Distribution _service;
		Distribution _expiration;
		float _lastArrival;
};

//	Operators

ostream& operator<<(ostream& out, const TaskType& t);

#endif
