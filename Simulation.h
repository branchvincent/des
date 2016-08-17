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
#include "Supervisor.h"
#include "Task.h"
#include "Parameters/Parameters.h"
#include "Parameters/NewParams.h"
#include "Statistics.h"

using namespace std;
using namespace params;

// Helper functions and definitions

bool cmpTaskArrs(Task* t1, Task* t2)
	{return t1->getArrTime() < t2->getArrTime();}

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

//  Notes
//  - Add utilization count for tasks cut off at end of phase (processAllDepts)
//  - Add destructor
//  - Add feature to plot timeline of events
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
        void output(ostream& out) const {out << spv << endl;}

//  Private member functions
    
    private:
    
    //  Used by run
    
        void runRep();
        void runPhase(int phase);
        void genTasks(int type, int phase);
        void procAllArrs();
        void procAllDepts();
        void procArr(Task* task) {spv.procArr(task);}
        void procDep(Task* task) {spv.procDep(task);}
        void outputTaskList();

//	Data members

	private:
//        NewParams params;       // run parameters
        Supervisor spv;         // operator supervisor
		vector<int> endTimes;   // phase end times
		list<Task*> taskList;	// task list
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
//    params(paramFile),
//    spv(params),
    spv(),
    endTimes{30, END_TIME - 30, END_TIME},
    taskList()
{
//	Check duration of simulation

	if (END_TIME < 90 || END_TIME % 10 != 0)
    {
		cerr << "Error: Invalid simulation time. Exiting..." << endl;
		exit(1);
	}
	
//	Check traffic array
	
	if (TRAFFIC.size() != NUM_HOURS)
	{
		cerr << "Error: Invalid traffic array. Exiting..." << endl;
		exit(1);
	}

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
    cout << endl << "Operators = ";
    for (int i = 0; i < OPS.size(); i++)
        cout << OPS[i] << ", ";
    cout << endl << endl;
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
    
	for (int i = 0; i < NUM_REPS; i++)
	{
		if (DEBUG_ON) cout << "Rep " << i << endl;
		runRep();
        cout << (float)(i + 1)/NUM_REPS * 100 << "% Completed" << endl;
	}
    
//  Output data, if applicable
    
    if (OUTPUT_ON)
    {
        spv.output();
//        spv.plot();
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
	
	for (int i = 0; i < NUM_PHASES; i++)
		runPhase(i);
		
//	End replication

    spv.endRep();
    
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
//    cout << "Queue size = " << spv.getQueueSize() << endl;

//	Generate all task types
	
	for (int i = 0; i < NUM_TASK_TYPES; i++)
		genTasks(i, phase);
    
//	Process all events
	
    if (DEBUG_ON) outputTaskList();
    
    procAllArrs();
    procAllDepts();
    
//  Clear task list
    
//    for (list<Task*>::iterator it = taskList.begin(); it != taskList.end(); it++)
//    {
//        cout << "Deleting " << **it << endl;
//        delete *it;
//    }
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

void Simulation::genTasks(int type, int phase)
{
//  Calculate current time
    
    float currTime = 0;
    if (phase != 0)
        currTime = endTimes[phase - 1];
    
//	Create temporary list and first task
    
    list<Task*> tmpList;
    Task* task = new Task(type, currTime, phase);
    float arrTime = task->getArrTime();
    float serTime = task->getSerTime();
    
//	Add tasks to list while time is left
    
    while (arrTime < endTimes[phase])
    {
    //	Add current task
        
        tmpList.push_back(task);
        
    //	Get next task
        
        task = new Task(type, arrTime, phase);
        arrTime = task->getArrTime();
        serTime = task->getSerTime();
    }
    
//	Merge temporary list with task list
    
    taskList.merge(tmpList, cmpTaskArrs);
    
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

//  Process events in the list
    
    while(it != taskList.end())
    {
    //	Get next arrival and depature
        
        arrTask = *it;
        arrTime = arrTask->getArrTime();
        depTask = spv.getNextDepature();
        depTime = spv.getNextDeptTime();
                
    //	Process next event
        
        if (arrTime <= depTime)
        {
            procArr(arrTask);
            it++;
        }
        else
            procDep(depTask);
    }

    return;
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
    
    Task* depTask = spv.getNextDepature();
    float depTime = spv.getNextDeptTime();
    
//  Process depatures while tasks left and time left
    
    while (spv.isBusy() && depTime <= endTimes[2])
    {
    //  Process depature
        
        procDep(depTask);
        
    //  Get next depature
        
        depTask = spv.getNextDepature();
        depTime = spv.getNextDeptTime();
    }
    
//    if (!spv.isBusy())
//        cout << "Operators are idle. Finishing Phase..." << endl;
//    else
//        cout << "Depature Time exceeded end time." << endl;
    
//  Depart any current tasks
    
//	if (spv.isBusy())
//	{
//        depTask->setDepTime(endTimes[2]);
//		procDep(depTask);
//        spv.clear();
//	}

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