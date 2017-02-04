/****************************************************************************
*																			*
*	File:		Agent.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 9, 2016													*
*																			*
*	Purpose:	This file defines the Agent class.							*
*																			*
****************************************************************************/

#ifndef AGENT_H
#define AGENT_H

#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include "Task.h"
// #include "Statistics.h"

using namespace std;

//	Functions and definitions

typedef priority_queue<Task,list<Task>> Queue;

/****************************************************************************
*																			*
*	Definition of Agent class												*
*																			*
****************************************************************************/

class Agent
{
//	Public member functions

	public:

	//	Constructor

        Agent(string type, vector<TaskTypes> taskTypes) : //, Statistics& sts) :
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

float Agent::getDepTime()
{
	if (busy)
		return currTask.getDepTime();
	else
		return INFINITY;
}

/****************************************************************************
*																			*
*	Function:	needToIntrp                                                 *
*																			*
*	Purpose:	To determine if the current task needs to be interrupted by *
*               by the specified task                                       *
*																			*
****************************************************************************/

bool Agent::needToIntrp(Queue& queue)
{
    if (busy && queue.size() > 1)
        return currTask < queue.top();
    else
        return false;
}
//
// /****************************************************************************
// *																			*
// *	Function:	procArr                                                     *
// *																			*
// *	Purpose:	To enqueue the specified task								*
// *																			*
// ****************************************************************************/
//
void Agent::procArr(Task& task)
{
//	Enqueue task

    taskQueue.push(task);

    // if (DEBUG_ON) cout << name << ": Adding " << *task << " of " << taskQueue.size() << endl;

//  Get task attributes

    float currTime = task->getArrTime();
    int type = task->getType();
    int timeInt = currTime/INT_SIZE;
    task->setQueTime(currTime);

//  Update stats

    stats.incNumTasksIn(type, timeInt, 1);

//	Service next task, if idle

    if (!busy)
        servNextTask(currTime);

//  Interrupt current task, if applicable

    else if (needToIntrp(taskQueue))
        procIntrp(currTime);

	return;
}

/****************************************************************************
*																			*
*	Function:	processIntrp												*
*																			*
*	Purpose:	To process an interruption of the current task              *
*																			*
****************************************************************************/

void Agent::procIntrp(float currTime)
{
//  Check that the Agent is busy

    if (!busy)
    {
        cerr << "Error: Cannot process task interruption. Exiting..." << endl;
        exit(1);
    }

    if (DEBUG_ON) cout << "\t\t " << name << ": Task interrupted at " << currTime << endl;

//	Update stats

    updateUtil(currTask, currTime);
    float depTime = currTask->getDepTime();
    currTask->setSerLeft(depTime - currTime);
    currTask->setDepTime(INFINITY);
    currTask->setQueTime(currTime);

//	Add current task to queue and service next task

    taskQueue.push(currTask);
    currTask = NULL;
    servNextTask(currTime);

    return;
}
//
// /****************************************************************************
// *																			*
// *	Function:	procDep                                                     *
// *																			*
// *	Purpose:	To process a task depature								 	*
// *																			*
// ****************************************************************************/
//
// void Agent::procDep(Task* task, bool stop)
// {
// //	Get task attributes
//
//     float depTime = task->getDepTime();
//     float begTime = task->getBegTime();
//     int type = task->getType();
//     int timeInt = begTime/INT_SIZE;
//
// //	Update stats
//
//     if (DEBUG_ON) cout << "\t " << name << ": Task departing at " << depTime << " and busy for " << depTime - begTime << endl;
//     updateUtil(task, depTime);
//     stats.incNumTasksOut(type, timeInt, 1);
//
// //  Start next task, if applicable
//
//     currTask = NULL;
//
// 	if (!stop)
// 		servNextTask(depTime);
//
//     return;
// }
//
/****************************************************************************
*																			*
*	Function:	clear														*
*																			*
*	Purpose:	To clear the Agent                                       	*
*																			*
****************************************************************************/

void Agent::clear()
{
//  Clear current task

	busy = false;
	currTask = Task();

//  Clear queue

    while (!taskQueue.empty())
        taskQueue.pop();

    return;
}
//
// /****************************************************************************
// *																			*
// *	Function:	output														*
// *																			*
// *	Purpose:	To output an Agent										*
// *																			*
// ****************************************************************************/
//
// //void Agent::output(ostream& out) const
// //{
// ////  Output Agent's status and number of enqueued tasks
// //
// //    if (currTask != NULL)
// //        cout << "Agent is busy until " << currTask->getDepTime();
// //    else
// //        cout << "Agent is not busy";
// //
// //    cout << " and has " << taskQueue.size() << " tasks in queue." << endl;
// //
// ////  Output queue
// //
// //    cout << "Queue = {" << endl;
// //
// //    Queue tmpQ = taskQueue;
// //
// //    while (!tmpQ.empty())
// //    {
// //        cout << *tmpQ.top() << endl;
// //        tmpQ.pop();
// //    }
// //
// //    cout << "}" << endl;
// //
// //    return;
// //}
//
// /****************************************************************************
// *																			*
// *	Function:	servNextTask												*
// *																			*
// *	Purpose:	To service the next task in the queue, if applicable		*
// *																			*
// ****************************************************************************/
//
// // Bug here?
//
// void Agent::servNextTask(float currTime)
// {
// //  Check that a task can be serviced
//
// 	if (!taskQueue.empty())
// 	{
// 	//	Get next task
//
//         if (DEBUG_ON) cout << "\t " << name << ": Task starting at " << currTime;
//
//         currTask = taskQueue.top();
//         taskQueue.pop();
//         currTask->setBegTime(currTime);
//
//         if (DEBUG_ON) cout << " " << *currTask << endl;
//
// 	//	Account for fatigue, if applicable
//
// 		float serTime = currTask->getSerLeft();
//
// 		if (FATIGUE_ON)
// 		{
// 			serTime *= getFatigueFactor(currTime);
//             currTask->setSerLeft(serTime);
//             serTime = currTask->getSerLeft();
// 		}
//
//     //  Set depature time
//
//         float depTime = currTime + serTime;
//         currTask->setDepTime(depTime);
//
//     //  Update stats
//
//         int timeInt = currTime/INT_SIZE;
//         int type = currTask->getType();
//         float waitTime = currTime - currTask->getQueTime();
//         stats.incWaitTime(type, timeInt, waitTime);
//         sharedStats.incWaitTime(type, timeInt, waitTime);
//
//     //	Check to see if task expired
//
//         if (currTaskExp())
//             procExp(currTime);
//     }
//
// 	return;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	currTaskExp                                                 *
// *																			*
// *	Purpose:	To check if the current task has expired                    *
// *																			*
// ****************************************************************************/
//
// bool Agent::currTaskExp()
// {
// //  Get task attributes
//
//     float depTime = currTask->getDepTime();
//     float expTime = currTask->getExpTime();
//
// //  Check if depature time has been set
//
//     if (isinf(depTime))
//     {
//         cerr << "Error: Current task has not started. Exiting..." << endl;
//         exit(1);
//     }
//
// //  Check for expiration
//
//     if (expTime < depTime)
//         return true;
//     else
//         return false;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	procExp                                                     *
// *																			*
// *	Purpose:	To process a task expiration                                *
// *																			*
// ****************************************************************************/
//
// void Agent::procExp(float currTime)
// {
//     if (DEBUG_ON) cout << "\t\t Task expired at " << currTime << endl;
//
// //  Get task attributes and update stats
//
//     int type = currTask->getType();
//     int timeInt = currTime/INT_SIZE;
//     stats.incNumTasksExp(type, timeInt, 1);
//     sharedStats.incNumTasksExp(type, timeInt, 1);
//
// //  Start next task
//
//     currTask = NULL;
//     servNextTask(currTime);
//
//     return;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	updateUtil													*
// *																			*
// *	Purpose:	To update the utilization									*
// *																			*
// ****************************************************************************/
//
// //  Fix wait time
// //  change to updatestat and seed each array here (or implement in stats class)
//
// void Agent::updateUtil(Task* task, float currTime)
// {
// //	Get task attributes
//
//     float begTime = task->getBegTime();
//     int type = task->getType();
//
// //	Get interval times and update time
//
//     int timeInt = begTime/INT_SIZE;
// 	float beginInt = timeInt * INT_SIZE;
// 	float endInt = beginInt + INT_SIZE;
// 	float timeBusy = 0;
// 	float percBusy = 0;
//
// //	Record utilization
//
// 	while (currTime > endInt)
// 	{
// 		timeBusy = endInt - max(begTime, beginInt);
// 		percBusy = timeBusy/INT_SIZE;
// 		stats.incUtil(type, timeInt, percBusy);
// 		stats.incSerTime(type, timeInt, timeBusy);
//         sharedStats.incSerTime(type, timeInt++, timeBusy);
//
//         if (timeBusy < 0)
//         {
//             cout << "WARNING: timeBusy = " << timeBusy << endl;
//             cout << "\t task = " << *task << endl;
//         }
//
//         beginInt = endInt;
// 		endInt += INT_SIZE;
// 	}
//
// 	timeBusy = currTime - max(begTime, beginInt);
// 	percBusy = timeBusy/INT_SIZE;
// 	stats.incUtil(type, timeInt, percBusy);
// 	stats.incSerTime(type, timeInt, timeBusy);
//     sharedStats.incSerTime(type, timeInt, timeBusy);
//
//     if (timeBusy < 0)
//     {
//         cout << "WARNING: timeBusy = " << timeBusy << endl;
//         cout << "\t task = " << *task << endl;
//     }
//
// 	return;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	output                                                      *
// *																			*
// *	Purpose:	To output...                                                *
// *																			*
// ****************************************************************************/
//
// void Agent::output()
// {
// //  Output stats
//
// 	// string file_name = name;
// 	// transform(file_name.begin(), file_name.end(), file_name.begin(), ::tolower);
// 	// replace(file_name.begin(), file_name.end(), ' ', '_');
//     // string file = OUTPUT_PATH + "/stats_" + file_name + to_string(trainNum) + ".csv";
//     // ofstream fout(file);
//     // if (!fout)
//     // {
//     //     cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
//     //     exit(1);
//     // }
// 	//
//     // fout << stats;
//
//     return;
// }

#endif
