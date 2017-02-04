/****************************************************************************
*																			*
*	File:		Phase.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 9, 2016													*
*																			*
*	Purpose:	This file defines the Phase class.							*
*																			*
****************************************************************************/

#ifndef PHASE_H
#define PHASE_H

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include "Task.h"

using namespace std;

/****************************************************************************
*																			*
*	Definition of Phase class												*
*																			*
****************************************************************************/

class Phase
{
//	Public member functions

	public:

	//	Constructor

        Phase(string type, vector<TaskTypes> taskTypes) : //, Statistics& sts) :
            type(type),
			taskTypes(taskTypes),
            currTask(),
            taskQueue(&cmpPrty),
            // sharedStats(sts),
            // stats()
			{}

	//	Inspectors

        string getType() const {return type;}
        bool isIdle() const {return !busy;}
		bool isBusy() const {return busy;}
        int getQueueSize() const {return (int)taskQueue.size();}
		Task& getCurrTask() const {return currTask;}
        float getDepTime() const;
        // bool needToIntrp(Queue& queue);
		// float getUtil(int i) {return stats.getUtil(i);}

	//	Mutators

// 		void procArr(Task* task);
// 		void procIntrp(float currTime);
// 		void procDep(Task* task, bool stop);
//         void servNextTask(float currTime);
//         void clear();
//         void endRep() {stats.endRep(); clear();}
//
// 	//	Other member functions
//
//         void output();
//         void output(ostream& out) const {out << stats << endl;}
//
// //  Private member functions
//
//     private:
//         float getFatigueFactor(float time) {return 1 + (time/60 * 0.01);}
//         bool currTaskExp();
//         void procExp(float currTime);
//         void updateUtil(Task* task, float currTime);

//	Data members

	private:
        string type;
		vector<TaskTypes> taskTypes;	// tasks to handle
		Queue taskQueue;           		// task queue
		Task currTask;             		// current task
		bool busy;
		// Statistics& sharedStats;		// shared stats
        // Statistics stats;          	 	// local stats
};

//	Operators

// ostream& operator<<(ostream& out, const Operator& op) {op.output(out); return out;}
//
/****************************************************************************
*																			*
*	Function:	getDepTime													*
*																			*
*	Purpose:	To get the depature time of the current task				*
*																			*
****************************************************************************/

float Phase::getDepTime()
{
	if (busy)
		return currTask.getDepTime();
	else
		return INFINITY;
}

#endif
