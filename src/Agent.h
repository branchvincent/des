///****************************************************************************
//*																			*
//*	File:		Agent.h														*
//*																			*
//*	Author:		Branch Vincent												*
//*																			*
//*	Purpose:	This file defines the Agent class.							*
//*																			*
//****************************************************************************/
//
//#ifndef AGENT_H
//#define AGENT_H
//
//#include <iostream>
//#include <string>
//#include <queue>
//#include <algorithm>
//#include <list>
//#include <boost/property_tree/ptree.hpp>
//#include "Task.h"
//#include "Shift.h"
//#include "TaskType.h"
//#include "Utility.h"
//// #include "Statistics.h"
//
//using namespace std;
//using boost::property_tree::ptree;
//
//class Event;
//
///****************************************************************************
//*																			*
//*	Definition of Agent class												*
//*																			*
//****************************************************************************/
//
//class Agent
//{
////	Friend class
//
//	friend class Team;
//
////	Public member functions
//
//	public:
//
//	//	Constructor
//
//		Agent(Team& team, const ptree& xmlData);
//		// Agent(Team& team, const ptree& xmlData);
//        // Agent(string name, vector<TaskTypes> taskTypes);
//
//	//	Inspectors
//
//        // string getType() const {return type;}
//        // bool isIdle() const {return !busy;}
//		// bool isBusy() const {return busy;}
//        // int getQueueSize() const {return (int)taskQueue.size();}
//		// Task& getCurrTask() const {return currTask;}
//        // float getDepTime() const;
//        // bool needToIntrp(Queue& queue);
//		// float getUtil(int i) {return stats.getUtil(i);}
//
//	//	Mutators
//
//		// void arrive(Task& task, float time);
//		// void interrupt(float time);
//		// void depart(Task& task, float time);
//		// void service(Task& task, float time);
//
////         void servNextTask(float currTime);
////         void clear();
////         void endRep() {stats.endRep(); clear();}
////
//// 	//	Other member functions
//
////		Event getNextEvent();
////         void output();
//        void output(ostream& out) const;
//
//// //  Private member functions
////
////     private:
////         float getFatigueFactor(float time) {return 1 + (time/60 * 0.01);}
////         bool currTaskExp();
////         void procExp(float currTime);
////         void updateUtil(Task* task, float currTime);
//
////	Data members
//
//	private:
//		Team& team;
//        string name;
//		Shift shift;
//		vector<TaskType> taskTypes;		// types of tasks
//		priority_queue<Task> queue; 	// task queue
//		list<Task> arrivingTasks;
//		// Task& currTask;             		// current task
//		bool busy;						// busy
//		// Team& team;
//		// Statistics& sharedStats;		// shared stats
//        // Statistics stats;          	 	// local stats
//};
//
////	Operators
//
//ostream& operator<<(ostream& out, const Agent& a);
//
//#endif
