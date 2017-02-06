/****************************************************************************
*																			*
*	File:		Team.h														*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Purpose:	This file defines the Team class.							*
*																			*
****************************************************************************/

#ifndef TEAM_H
#define TEAM_H

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "TaskType.h"
#include "Agent.h"

using namespace std;
using boost::property_tree::ptree;

/****************************************************************************
*																			*
*	Definition of Team class		     						        	*
*																			*
****************************************************************************/

//  Notes
//  - Shared task to op with current lowest priority
//  - Add fatigue for just human operators

class Team
{
//  Friend class

 //   	friend class Agent;

//	Public member functions

	public:

	//	Constructor

		Team(const ptree& xmlData);
		// Team(string name, vector<Agent> agents, vector<TaskTypes> taskTypes);

	// 	Inspector

    //     // int getQueueSize() const {return ops[0].getQueueSize();}
    //     Task getNextTask();
    //     float getNextDeptTime();
    //     bool isBusy() const;
	// 	// float getUtil(int i, int j) {return ops[i].getUtil(j);}
	//
    // // 	Mutators
	//
	// 	void createTasks()
	// 	{
	// 		for (const auto& agent : agents)
	// 		{
	//
	// 		}
	// 	}
	//
    //     void arrive(Task* task);
	// 	void depart(Task* task);
    //     void reset() {for (const auto& agent : agents) agent.reset();};
    //     void endRep();
	//
    // //  Other member functions
	//
    //     void output();
        void output(ostream& out) const;

//	Data members

	private:
//      Params& params;
        // Statistics stats;
		string name;
        vector<Agent> agents;
		vector<TaskType> taskTypes;
		// vector<Phase> phases;
		// Team supervisor;
};

ostream& operator<<(ostream& out, const Team& t) {t.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Team														*
*																			*
*	Purpose:	To construct a new team										*
*																			*
****************************************************************************/

Team::Team(const ptree& xmlData)
{
	name = xmlData.get<string>("name");

	for (const auto& task : xmlData.get_child("tasks"))
	{
		if (task.first == "task")
		{
			taskTypes.push_back(TaskType(task.second));
		}
	}

	for (const auto& agent : xmlData.get_child("agents"))
	{
		if (agent.first == "agent")
		{
			agents.push_back(Agent(agent.second, taskTypes));
			// agents.push_back(Agent(*this, agent.second));
		}
	}

	// for (int i = 0; i < num_tasks; i++)
	// {
	// 	TaskType task(xmlData.get_child("tasks.task" + to_string(i)));
	// 	cout << task << endl;
	// }
	// 	// dists.push_back(Distribution(type, parameters));
	// priority = util::toVector<int>(xmlData.get<string>("priority"));
}

//Team::Team(string name, vector<Agent> agents) : name(name), agents(agents), taskTypes(taskTypes) //stats(), ops()

// /****************************************************************************
// *																			*
// *	Function:	getNextDepature												*
// *																			*
// *	Purpose:	To get the task with the soonest depature					*
// *																			*
// ****************************************************************************/
//
// Task Team::getNextDepature()
// {
// //	Initialize variables
//
//     float currDepTime;
//     float minTime = ops[0].getDepTime();
//     int minIndex = 0;
//
// //  Get depature time and index of soonest depature
//
//     for (int i = 0; i < ops.size(); i++)
//     {
//     //  Get depature time
//
//         currDepTime = ops[i].getDepTime();
//
//     //  Check for new minimum
//
//         if (currDepTime < minTime)
//         {
//             minTime = currDepTime;
//             minIndex = i;
//         }
//     }
//
// //  Return task with minimum depature time
//
//     return ops[minIndex].getCurrTask();
// }
//
// /****************************************************************************
// *																			*
// *	Function:	getNextDeptTime                                             *
// *																			*
// *	Purpose:	To get the depature time for the next task 					*
// *																			*
// ****************************************************************************/
//
// float Team::getNextDeptTime()
// {
// //  Get next departing task
//
//     Task* task = getNextDepature();
//
// //  Get depature time
//
//     if (task != NULL)
//         return task->getDepTime();
//     else
//         return INFINITY;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	isBusy                                                      *
// *																			*
// *	Purpose:	To determine if at least one agent is busy               	*
// *																			*
// ****************************************************************************/
//
// bool Team::isBusy() const
// {
//     for (const auto& agent : agents)
//         if (agent.isBusy())
//             return true;
//
//     return false;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	procArr                                                     *
// *																			*
// *	Purpose:	To process a task arrival								 	*
// *																			*
// ****************************************************************************/
//
// void Team::procArr(Task* task)
// {
// //	Get task attributes
//
// 	float currTime = task->getArrTime();
//     vector<int> opNums = task->getOpNums();
// //	int type = task->getType();
//     if (DEBUG_ON) cout << "\t Task arriving at " << currTime << endl;
//
// //	Add task to the appropriate queue
//
// //    if (opNum > ops.size())
// //    {
// //        cerr << "Error: Incompatible operator ID. Exiting..." << opNum << endl;
// //        exit(1);
// //    }
//
// //	vector<int> opNums;
// //	for (int i = 0; i < ops.size(); i++)
// //	{
// //		vector<int> op_tasks = ops[i].getTaskNums();
// //		if (find(op_tasks.begin(), op_tasks.end(), type) != op_tasks.end())
// //			opNums.push_back(i);
// //	}
//
// 	ops[0].procArr(task);
//
// //	if (opNums.size() == 0)
// //	{
// //		cerr << "Error: Task has no associated assistants. Exiting..." << endl;
// //		exit(1);
// //	}
// //    else if (opNums.size() == 1)
// //        ops[opNums[0]].procArr(task);
// //    else
// //    {
// //    //  Find shortest queue (include current task)
// //
// ////        cout << "SHARED TASK ARRIVING" << endl;
// ////
// ////        for (int i = 0; i < ops.size(); i++)
// ////        {
// ////            if (ops[i].isBusy())
// ////                cout << ops[i].getName() << " is busy with " << 1+ops[i].getQueueSize() << " tasks including " << *(ops[i].getCurrTask()) << endl;
// ////            else
// ////                cout << ops[i].getName() << " is idle." << endl;
// ////        }
// //
// //        int queueSize;
// //        int minSize = ops[0].getQueueSize() + ops[0].isBusy();
// //        int minIndex = 0;
// //
// //        int end = (int)opNums.size() - 1;
// //        int j = 0;
// //
// //        for (int i = opNums[0]; i <= opNums[end]; i++)
// //        {
// //        //  Get queue size
// //
// //            if (find(OPS.begin(), OPS.end(), i) != OPS.end())
// //            {
// //                queueSize = ops[j].getQueueSize() + ops[j].isBusy();
// //
// //            //  Check for new minimum
// //
// //                if (queueSize < minSize)
// //                {
// //                    minSize = queueSize;
// //                    minIndex = j;
// //                }
// //                j++;
// //            }
// //        }
// //
// ////        cout << "Operator size = " << ops.size() << endl;
// ////        cout << "Index = " << minIndex << endl;
// ////        cout << "Going to " << ops[minIndex].getName() << endl;
// //
// //        ops[minIndex].procArr(task);
// //    }
//
// //  Update stat
//
//     int type = task->getType();
//     int timeInt = currTime/INT_SIZE;
// 	stats.incNumTasksIn(type, timeInt, 1);
//
// 	return;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	procDep                                                     *
// *																			*
// *	Purpose:	To process the task depature                                *
// *																			*
// ****************************************************************************/
//
// void Team::procDep(Task* task, bool stop)
// {
// //  Process depature from appropriate operator
//
//     bool taskFound = false;
//
//     for (int i = 0; i < ops.size(); i++)
//         if (task == ops[i].getCurrTask())
//         {
//             taskFound = true;
//             ops[i].procDep(task, stop);
//         }
//
// //  If task was not found, output error
//
//     if (!taskFound)
//     {
//         cerr << "Error: Could not process task depature. Exiting..." << endl;
//         exit(1);
//     }
//
// //  Update stats
//
//     int timeInt = task->getDepTime()/INT_SIZE;
//     stats.incNumTasksOut(task->getType(), timeInt, 1);
//
// 	return;
// }
//
// /****************************************************************************
// *																			*
// *	Function:	endRep                                                      *
// *																			*
// *	Purpose:	To end the replication                                      *
// *																			*
// ****************************************************************************/
//
// void Team::endRep()
// {
// //  Update stats
//
//     stats.endRep();
//
// //  Clear operators
//
//     for (int i = 0; i < ops.size(); i++)
//         ops[i].endRep();
//
//     return;
// }
//
/****************************************************************************
*																			*
*	Function:	output                                                      *
*																			*
*	Purpose:	To output a team                                            *
*																			*
****************************************************************************/

void Team::output(ostream& out) const
{
	out << "Name: " << name << endl;
	out << "Task types: " << taskTypes << endl;
	out << "Agents: ";

	for (const auto& agent : agents)
		out << agent.name << ", ";
	// vector<TaskTypes> taskTypes;
}
//
// /****************************************************************************
// *																			*
// *	Function:	output                                                      *
// *																			*
// *	Purpose:	To output...                                                *
// *																			*
// ****************************************************************************/
//
// void Team::output()
// {
// //  Output global stats
//
//     string file = OUTPUT_PATH + "/stats_total.csv";
//     ofstream fout(file);
//     if (!fout)
//     {
//         cout << "Error: Cannot open " << file << ". Exiting..." << endl;
//         cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
//         exit(1);
//     }
//
//     fout << stats;
//
// //  Output operators
//
//     for (int i = 0; i < ops.size(); i++)
//         ops[i].output();
//
//     return;
// }

#endif
