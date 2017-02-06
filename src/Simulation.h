/****************************************************************************
*																			*
*	File:		Simulation.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file defines the Simulation class.						*
*																			*
****************************************************************************/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <time.h>
#include <algorithm>
// #include "Train.h"
#include "Task.h"
// #include "params/Parameters.h"
#include <stdio.h>

using namespace std;
using namespace params;

// Helper functions and definitions

bool cmpTaskArrs(Task t1, Task t2) {return t1.arrivesSooner(t2);}

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

//  Notes
//  - Add utilization count for tasks cut off at end of phase (processAllDepts)
//  - Add destructor
//  - Think about keeping a single taskList for all phases

class Simulation
{
//	Public member functions

	public:

	//	Constructors

        Simulation(string paramFile);
//		~Simulation() {del Task*;}

	//	Other member functions

        void run();
		void output(ostream& out) const {for (int i = 0; i < trains.size(); i++) out << trains[i] << endl;}

//  Private member functions

    private:

    //  Used by run

        void runRep();
        void runPhase(int phase);
        void genTasks(int type, int phase, int trainNum);
        void procAllArrs();
        void procAllDepts();
        void procArr(Task* task, Train& train) {train.procArr(task);}
        void procDep(Task* task, bool stop, Train& train) {train.procDep(task, stop);}
        void outputTaskList();
		int getNextDepature(float& time);


//	Data members

	private:
		vector<BatchedTeam> batches;
		Flags flags;
		Parameters parameters;
		list<Event> events;
// //      Params pms;				// run parameters
// //		Operator dispatch;		// dispactcher
//         vector<Team> teams;	// trains
// 		vector<int> endTimes;   // phase end times
// 		list<Task> taskList;	// task list
// 		float currTime;
};

//	Operators

ostream& operator<<(ostream& out, const Simulation& sim) {sim.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Simulation													*
*																			*
*	Purpose:	To construct a new simulation								*
*																			*
****************************************************************************/

Simulation::Simulation(string paramFile) :
//	dispatch("Dispatch", DP_TASKS, Statistics(), 0),
    endTimes{30, END_TIME - 30, END_TIME},
    taskList(),
	currTime(0)
{
//	Get run parameters

//	Check duration of simulation

	ASSERT(END_TIME < 90 || END_TIME % 10 != 0, "Invalid simulation time");
	ASSERT(TRAFFIC.size() != NUM_HOURS, "Invalid traffic array");

//  Initialize srand

    if (RAND_RUN_ON)
        srand((unsigned int) time(0));
    else
        srand(0);

//  Output run parameters

    cout << "Simulation Parameters" << endl;
    cout << "Output path = " << OUTPUT_PATH << endl;
    cout << "Number of hours = " << NUM_HOURS << endl;
    cout << "Number of replications = " << NUM_REPS << endl;
    cout << "Traffic levels = ";
    for (int i = 0; i < TRAFFIC.size(); i++)
        cout << TRAFFIC[i] << ", ";
    cout << endl;

//	Output each operator

    for (int i = 0; i < OP_TASKS.size(); i++)
	{
		cout << OP_NAMES[i] << " = ";
		for (int j = 0; j < OP_TASKS[i].size(); j++)
			cout << OP_TASKS[i][j] << ", ";
		cout << endl;
	}

//	Output tasks for each operator

//	for (int i = 0; i < OP_NUMS.size(); i++)
//	{
//		for (int j = 0; j < OP_NUMS[i].size(); j++)
//			cout << OP_NUMS[i][j] << ", ";
//		cout << endl;
//	}
//    cout << endl << endl;
}

/****************************************************************************
*																			*
*	Function:	run                                                         *
*																			*
*	Purpose:	To run the simulation for the specified number of           *
*               replications                                                *
*																			*
****************************************************************************/

void Simulation::run()
{
//  Run simulation the specified number of times

//	string file = OUTPUT_PATH + "/des_status";
//	ofstream fout(file);
//	if (!fout)
//	{
//		cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
//		exit(1);
//	}

	for (int i = 0; i < NUM_REPS; i++)
	{
		if (DEBUG_ON) cout << "Rep " << i << endl;
		runRep();
//        cout << (float)(i + 1)/NUM_REPS * 100 << "% Completed" << endl;
		cout << (float)(i + 1)/NUM_REPS << endl;
//		fout << (float)(i + 1)/NUM_REPS << endl;
//		fout.flush();
	}

//  Output data, if applicable

    if (OUTPUT_ON)
    {
		for (int i = 0; i < trains.size(); i++)
		{
			trains[i].output();
//			trains[i].plot();
		}
    }

    return;
}

/****************************************************************************
*																			*
*	Function:	runRep														*
*																			*
*	Purpose:	To complete one replication of the simulation               *
*																			*
****************************************************************************/

void Simulation::runRep()
{
	if (DEBUG_ON) cout << "Beginning simulation..." << endl;

//	Run all phases

	currTime = 0;
	for (int i = 0; i < NUM_PHASES; i++)
		runPhase(i);

//	End replication

	for (int i = 0; i < trains.size(); i++)
		trains[i].endRep();

    if (DEBUG_ON) cout << "Simulation completed." << endl;

	return;
}

/****************************************************************************
*																			*
*	Function:	runPhase													*
*																			*
*	Purpose:	To run the specified phase of the simulation				*
*																			*
****************************************************************************/

void Simulation::runPhase(int phase)
{
    if (DEBUG_ON) cout << "Beginning Phase " << phase << "." << endl;

//	Generate all task types

	for (int i = 0; i < NUM_TASK_TYPES; i++)
	{
		if (find(DP_TASKS[0].begin(), DP_TASKS[0].end(), i) != DP_TASKS[0].end())
			genTasks(i, phase, 0);
		else
		{
			for (int j = 1; j < NUM_TRAINS; j++)
				genTasks(i, phase, j);
		}
	}

//	Process all events

    if (DEBUG_ON) outputTaskList();

    procAllArrs();
    procAllDepts();

//  Clear task list

    taskList.clear();

	if (DEBUG_ON) cout << "Phase " << phase << " completed." << endl << endl;

	return;
}

/****************************************************************************
*																			*
*	Function:	genTasks													*
*																			*
*	Purpose:	To generate tasks of the specified type						*
*																			*
****************************************************************************/

void Simulation::genTasks(int type, int phase, int trainNum)
{
	if (TASK_NAMES[type].find("Relay") != string::npos)
	{
		return;
	}
	if (TASK_NAMES[type].find("Dependent") != string::npos)
	{
		return;
	}

//  Calculate current time

	if (find(DP_TASKS[0].begin(), DP_TASKS[0].end(), type) != DP_TASKS[0].end())
		if (trainNum != 0)
			cout << "ERROR: Dispatcher task sent to train" << endl;

//	cout << "Generating task " << type << " for train " << trainNum << endl;

	if (phase == 0)
		currTime = 0;
	else
		currTime = max(currTime, (float)endTimes[phase - 1]);

//	Create temporary list and first task

    list<Task*> tmpList;
    Task* task = new Task(type, currTime, phase, trainNum);
    float arrTime = task->getArrTime();
    float serTime = task->getSerTime();

//	Add tasks to list while time is left

    while (arrTime < endTimes[phase])
    {
    //	Add current task

        tmpList.push_back(task);

	//	Add additional task, if necessary

		if (TASK_NAMES[type].find("Trigger") != string::npos)
		{
			if (trainNum == 0)
			{
			//	Relay

				int t = 0;
				for (int i = 0; i < NUM_TASK_TYPES; i++)
				{
					if (TASK_NAMES[i].find("Relay") != string::npos)
					{
//						cout << TASK_NAMES[i] << " found at " << i << endl;
						t = i;
					}
				}
				task = new Task(t, currTime, phase, trainNum, arrTime);
				tmpList.push_back(task);
//				cout << "Adding " << *task << endl;

				int tmp_train = rand() % (NUM_TRAINS);
				if (tmp_train == 0) tmp_train++;
				task = new Task(t, currTime, phase, tmp_train, arrTime);
				tmpList.push_back(task);
//				cout << "Adding " << *task << endl;
//				cout << "Adding relay: " << t << endl;

			//	Dependent

				string name = TASK_NAMES[type];
				name.replace(name.end()-7,name.end(),"Dependent");
//					cout << "Searching for " << name << endl;
				for (int i = type + 2; i < NUM_TASK_TYPES; i++)
				{
//					cout << TASK_NAMES[i] << endl;
					if (TASK_NAMES[i].find(name) != string::npos)
					{
//						cout << TASK_NAMES[i] << " found at " << i << endl;
						t = i;
					}
				}
				task = new Task(t, currTime, phase, tmp_train, arrTime);
				tmpList.push_back(task);
//				cout << "Adding " << *task << " to train " << tmp_train << endl;
			}
			else
			{
			//	Relay

				int t = 0;
				for (int i = 0; i < NUM_TASK_TYPES; i++)
				{
					if (TASK_NAMES[i].find("Relay") != string::npos)
					{
//						cout << TASK_NAMES[i] << " found at " << i << endl;
						t = i;
					}
				}
				task = new Task(t, currTime, phase, trainNum, arrTime);
				tmpList.push_back(task);

				int dispatch = 0;
				task = new Task(t, currTime, phase, dispatch, arrTime);
				tmpList.push_back(task);

			//	Dependent

				string name = TASK_NAMES[type];
				name.replace(name.end()-7,name.end(),"Dependent");
//					cout << "Searching for " << name << endl;
				for (int i = 0; i < NUM_TASK_TYPES/2; i++)
				{
					if (TASK_NAMES[i].find(name) != string::npos)
					{
//						cout << TASK_NAMES[i] << " found at " << i << endl;
						t = i;
					}
				}
				task = new Task(t, currTime, phase, dispatch, arrTime);
				tmpList.push_back(task);
//				cout << "Adding " << *task << " to train " << dispatch << endl;
			}
		}
			//	create new task

////			int tmp_type = rand() % NUM_TASK_TYPES;
//			int tmp_type = 1;
//			int tmp_train = rand() % (NUM_TRAINS);
//			if (tmp_train == trainNum) tmp_train = (tmp_train + 1) % (NUM_TRAINS);
//			if (trainNum != 0) tmp_train = 0;
//			task = new Task(tmp_type, arrTime, phase, tmp_train);
//			task->setArrTime(arrTime);
//			tmpList.push_back(task);
//		}

    //	Get next task

        task = new Task(type, arrTime, phase, trainNum);
        arrTime = task->getArrTime();
        serTime = task->getSerTime();
    }

//	Merge temporary list with task list

//	for (list<Task*>::iterator it = tmpList.begin(); it != tmpList.end(); it++)
//		cout << "Task:  " << **it << endl;

	tmpList.sort(cmpTaskArrs);
    taskList.merge(tmpList, cmpTaskArrs);

//	outputTaskList();

    return;
}

/****************************************************************************
*																			*
*	Function:	procAllArrs                                                 *
*																			*
*	Purpose:	To process all tasks arrivals in the task list				*
*																			*
****************************************************************************/

void Simulation::procAllArrs()
{
//  Initialize variables

    list<Task*>::iterator it = taskList.begin();
    Task *arrTask, *depTask;
    float arrTime, depTime;
	Train arrTrain, depTrain;

	int arrNum, depNum;

//  Process events in the list

    while(it != taskList.end())
    {
    //	Get next arrival and depature

        arrTask = *it;
        arrTime = arrTask->getArrTime();
		arrNum = arrTask->getTrainNum();
//		arrTrain = trains[arrTask->getTrainNum()];
        depNum = getNextDepature(depTime);
		depTask = trains[depNum].getNextDepature();

    //	Process next event

        if (arrTime <= depTime)
        {
//			cout << "Task " << arrTask->getType() << " going to " << arrNum << endl;
            procArr(arrTask, trains[arrNum]);
            it++;
        }
		else
		{
            procDep(depTask, false, trains[depNum]);
			delete depTask;
		}
	}

    return;
}

int Simulation::getNextDepature(float& time) {

	vector<Task*> depTasks;
	vector<float> depTimes;

	for (int i = 0; i < trains.size(); i++)
	{
		depTasks.push_back(trains[i].getNextDepature());
		depTimes.push_back(trains[i].getNextDeptTime());
	}

//	Initialize variables

	float currDepTime;
	float minTime = depTimes[0];
	int minIndex = 0;

	for (int i = 0; i < NUM_TRAINS; i++)
	{
		//  Get depature time

		currDepTime = depTimes[i];

		//  Check for new minimum

		if (currDepTime < minTime)
		{
			minTime = currDepTime;
			minIndex = i;
		}
	}

//	train = trains[minIndex];
	time = minTime;

	return minIndex; //depTasks[minIndex];
}

/****************************************************************************
*																			*
*	Function:	procAllDepts                                                *
*																			*
*	Purpose:    To process all the task depatures that remain after all     *
*               tasks have arrived                                          *
*																			*
****************************************************************************/

void Simulation::procAllDepts()
{
//  Get next depature

	float depTime;
	Train depTrain;
	int depNum = getNextDepature(depTime);
	Task* depTask =trains[depNum].getNextDepature();

//  Process depatures while tasks left and time left

    while (depTrain.isBusy() && depTime <= endTimes[2])
    {
    //  Process depature

		currTime = depTime;
        procDep(depTask, false, depTrain);
		delete depTask;

//		int time = depTime/INT_SIZE;
//		cout << "Util(" << time << ") = " << trains.getUtil(0, time) << endl;

    //  Get next depature

		depNum = getNextDepature(depTime);
		depTask = trains[depNum].getNextDepature();
    }

//    if (!trains.isBusy())
//        cout << "Operators are idle. Finishing Phase..." << endl;
//    else
//        cout << "Depature Time exceeded end time." << endl;

//  Depart any current tasks

	if (depTrain.isBusy())
	{
		while (depTrain.isBusy())
		{
		//	Process Depature

			currTime = endTimes[2];
			depTask->setDepTime(currTime);
			procDep(depTask, true, depTrain);
			delete depTask;

		//  Get next depature

			depNum = getNextDepature(depTime);
			depTask = trains[depNum].getNextDepature();

//			int time = currTime/INT_SIZE;
//			cout << "Util(" << time << ") = " << trains.getUtil(0, time) << endl;
		}
		for (int i = 0; i < trains.size(); i++)
			trains[i].clear();
	}

    return;
}

/****************************************************************************
*																			*
*	Function:	outputTaskList												*
*																			*
*	Purpose:	To output the task list                                     *
*																			*
****************************************************************************/

void Simulation::outputTaskList()
{
    cout << "Task List" << endl;

    int i = 0;
    for (list<Task*>::iterator it = taskList.begin(); it != taskList.end(); it++)
        cout << "Task " << i++ << ":  " << **it << endl;
    cout << endl;

    return;
}

#endif
