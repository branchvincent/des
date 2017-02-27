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
// #include <boost/property_tree/ptree.hpp>
#include "Distribution.h"
// #include "DateTime.h"

using namespace std;
// using boost::property_tree::ptree;

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

		TaskType();
		// TaskType(Team& team, const ptree& xmlData);
		TaskType(string name, int priority, bool isAffectedByTraffic,
			Distribution interarrival, Distribution service, Distribution expiration, Team* team);
		// TaskType(string name, vector<int> priority, vector<bool> isAffectedByTraffic,
		// 	vector<Distribution> interarrival, vector<Distribution> service,
		// 	vector<Distribution> expiration);

	//	Inspectors

		// const string& getName() const;
		// vector<int> getPriority() const;
		// vector<bool> getIsAffectedByTraffic() const;
		// vector<Distribution> getInterarrival() const;
		// vector<Distribution> getService() const;
		// vector<Distribution> getExpiration() const;

		void addAgent(Agent* agent);
		void setTeam(Team* t) {team = t;}
		// int getPriority(int phase) const;
		// bool getIsAffectedByTraffic(int phase) const;
		// float randInterarrival(int phase);
		// float randService(int phase);
		// float randExpiration(int phase);
		float randInterarrival();
		float randService();
		float randExpiration();

	//	Mutators

	//	Operators

		// TaskType& operator=(const TaskType& t);

	//	Other member functions

		void reset();
		Task genTask();
        void output(ostream& out) const;
		// void copy(const TaskType& t);

//	Private member functions

	private:
		DateTime getAbsTime(float relativeTime);
		float genArrivalTime();
		float genServiceTime();
		float genExpirationTime(float arrivalTime, float serviceTime);
		// void readDistributionFromXML(vector<Distribution>& dists, const ptree& xmlData);

//	Data members

	public:
		Team* team;
		vector<Agent*> agents;
		string name;
		int priority;
		bool isAffectedByTraffic;
		Distribution interarrival;
		Distribution service;
		Distribution expiration;
		// vector<int> priority;
		// vector<bool> isAffectedByTraffic;
		// vector<Distribution> interarrival;
		// vector<Distribution> service;
		// vector<Distribution> expiration;
		float lastArrival;
};

//	Operators

ostream& operator<<(ostream& out, const TaskType& t);

#endif
