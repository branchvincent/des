/****************************************************************************
*																			*
*	File:		Agent.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Agent class.							*
*																			*
****************************************************************************/

#include <iostream>
#include <string>
#include "Agent.h"
#include "Team.h"
#include "Event.h"
#include "Shift.h"

using namespace std;

/****************************************************************************
*																			*
*	Function:	Agent														*
*																			*
*	Purpose:	To construct an agent										*
*																			*
****************************************************************************/

Agent::Agent(Team& team, const ptree& xmlData) : team(team), taskTypes(), queue(), currTask(NULL)
{
	name = xmlData.get<string>("name");
	// shift = Shift(util::toVector<string>(xmlData.get<string>("shift")));

	for (const auto& i : util::toVector<int>(xmlData.get<string>("tasks")))
	{
		util::checkIndex(team.taskTypes, i);
		taskTypes.push_back(team.taskTypes[i]);
	}
}

optional<Event> Agent::getNextEvent() const
{
    if (currTask)
    {
		optional<Event> nextEvent = currTask->getEvent();
		// for (const Task& task : queue)
		// {
		// 	if (task.getNextEvent() < nextTask)
		// 		nextTask = task.getNextEvent();
		// }
		if (nextEvent)
        	return nextEvent;
    }
	return optional<Event>();
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output an agent											*
*																			*
****************************************************************************/

void Agent::output(ostream& out) const
{
	out << "Name: " << name << endl;
	// out << "Shift: " << shift << endl;
	out << "Tasks: " << taskTypes;
}


// /****************************************************************************
// *																			*
// *	Function:	Agent														*
// *																			*
// *	Purpose:	To construct an agent										*
// *																			*
// ****************************************************************************/
// Agent(string name, vector<TaskTypes> taskTypes) : //, Statistics& sts) :
//    name(name),
//    taskTypes(taskTypes),
//    currTask(),
//    taskQueue(), //&cmpPrty),
//    // sharedStats(sts),
//    // stats()
// {}
//
// /****************************************************************************
// *																			*
// *	Function:	getNextEvent												*
// *																			*
// *	Purpose:	To get the time of the next event							*
// *																			*
// ****************************************************************************/
//
// float Agent::getNextEvent()
// {
// 	if (busy)
// 		return currTask.getNextEvent();
// 	else
// 		return INFINITY;
// }
//
// // /****************************************************************************
// // *																			*
// // *	Function:	procArr                                                     *
// // *																			*
// // *	Purpose:	To enqueue the specified task								*
// // *																			*
// // ****************************************************************************/
// //
// void Agent::arrival(Task& task, float time)
// {
// //	Enqueue task
//
// 	task.start(time);
//     queue.push(task);
//
//     // if (DEBUG_ON) cout << name << ": Adding " << *task << " of " << taskQueue.size() << endl;
//
// //  Get task attributes
//
//     // float currTime = task->getArrTime();
//     // int type = task->getType();
//     // int timeInt = currTime/INT_SIZE;
//     // task->setQueTime(currTime);
//
// //  Update stats
//
//     // stats.incNumTasksIn(type, timeInt, 1);
//
// //	Service next task, if idle
//
//     if (!busy)
//         servNextTask(currTime);
//
// //  Interrupt current task, if applicable
//
//     else if (needToInterrupt())
//         interrupt(currTime);
//
// 	return;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	processIntrp												*
// *																			*
// *	Purpose:	To process an interruption of the current task              *
// *																			*
// ****************************************************************************/
//
// void Agent::interrupt(float currTime)
// {
// //  Check that the Agent is busy
//
// 	ASSERT(not busy, "Cannot interrupt idle agent");
//
//     // if (DEBUG_ON) cout << "\t\t " << name << ": Task interrupted at " << currTime << endl;
//
// //	Update stats
//
//     // updateUtil(currTask, currTime);
//     // float depTime = currTask->getDepTime();
//     // currTask->setSerLeft(depTime - currTime);
//     // currTask->setDepTime(INFINITY);
//     // currTask->setQueTime(currTime);
//
// //	Add current task to queue and service next task
//
//     queue.push(currTask);
//     busy = false;
//     servNextTask(currTime);
//
//     return;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	procDep                                                     *
// *																			*
// *	Purpose:	To process a task depature								 	*
// *																			*
// ****************************************************************************/
//
// void Agent::depart(Task& task)
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
// /****************************************************************************
// *																			*
// *	Function:	needToIntrp                                                 *
// *																			*
// *	Purpose:	To determine if the current task needs to be interrupted by *
// *               by the specified task                                       *
// *																			*
// ****************************************************************************/
//
// bool Agent::needToInterrupt()
// {
//     if (busy and queue.size() >= 1)
//         return currTask < queue.top();
//     else
//         return false;
// }
//
// //
// /****************************************************************************
// *																			*
// *	Function:	reset														*
// *																			*
// *	Purpose:	To reset the Agent                                       	*
// *																			*
// ****************************************************************************/
//
// void Agent::reset()
// {
// 	busy = false;
// 	currTask = Task();
//     while (!taskQueue.empty()) taskQueue.pop();
// }
// //
//    if (currTask != NULL)
//        cout << "Agent is busy until " << currTask->getDepTime();
//    else
//        cout << "Agent is not busy";
//
//    cout << " and has " << taskQueue.size() << " tasks in queue." << endl;
//
// //  Output queue
//
//    cout << "Queue = {" << endl;
//
//    Queue tmpQ = taskQueue;
//
//    while (!tmpQ.empty())
//    {
//        cout << *tmpQ.top() << endl;
//        tmpQ.pop();
//    }
//
//    cout << "}" << endl;
//}
// //
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

//	Operators

ostream& operator<<(ostream& out, const Agent& a) {a.output(out); return out;}
