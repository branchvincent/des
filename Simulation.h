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
#include "Constants.h"
#include "Statistics.h"

using namespace std;
using namespace cnsts;

// Helper functions and definitions

typedef vector<vector<float> > Matrix2D;
typedef vector<Matrix2D> Matrix3D;
bool cmpTaskArrs(Task* t1, Task* t2)
	{return t1->getArrTime() < t2->getArrTime();}

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

//  Notes
//  - Intialize stats at constructor or run(numRuns)?
//  - Add utilization count for tasks cut off at end of phase (processAllDepts)
//  - Add destructor
//  - Add feature to plot timeline of events
//  - Think about keeping a single taskList for all phases
//  - change all -1 to inf
//  - create traffic as global variable

class Simulation
{
//	Public member functions

	public:
		
	//	Constructors
	
        Simulation(int t = END_TIME); // , vector<float> trafficLevels);
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
		vector<int> endTimes;       // phase end times
//        int endTimes[NUM_PHASES];   // phase end times
		list<Task*> taskList;		// task list
		Supervisor spv;             // operator supervisor
		vector<float> traffic; 		// traffic levels
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

Simulation::Simulation(int t) : //, vector<float> trafficLevels) :
    endTimes{30, t-30, t},
    taskList(),
    spv(),
    traffic(TRAFFIC)
{
//	Check duration of simulation

	if (t < 90 || t%10 != 0)
    {
		cerr << "Error: Invalid simulation time. Exiting..." << endl;
		exit(1);
	}
	
//	Check traffic array
	
	if (traffic.size() != NUM_HOURS)
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
    cout << "Number of hours = " << NUM_HOURS << endl;
    cout << "Number of replications = " << NUM_REPS << endl;
    
    cout << "Traffic levels = ";
    for (int i = 0; i < TRAFFIC.size(); i++)
        cout << TRAFFIC[i] << ", ";
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
		cout << "Rep " << i << endl;
		runRep();
	}
    
    spv.plot();
    
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
	cout << "Beginning simulation..." << endl;

//	Run all phases 
	
	for (int i = 0; i < NUM_PHASES; i++)
		runPhase(i);
		
//	End replication

    spv.endRep();
    
    cout << "Simulation completed." << endl;
    
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
    cout << "Beginning Phase " << phase << "." << endl;

//	Generate all task types
	
	for (int i = 0; i < NUM_TASK_TYPES; i++)
		genTasks(i, phase);
    
//	Process all events and clear task list
	
    if (DEBUG_ON) outputTaskList();

    procAllArrs();
    procAllDepts();
    taskList.clear();
    
	cout << "Phase " << phase << " completed." << endl << endl;

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
    Task* task = new Task(type, currTime, phase, traffic);
    float arrTime = task->getArrTime();
    float serTime = task->getSerTime();
    
//	Add tasks to list while time is left
    
    while (arrTime < endTimes[phase])
    {
    //	Add current task
        
        tmpList.push_back(task);
        
    //	Get next task
        
        task = new Task(type, arrTime, phase, traffic);
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
        
//        cout << "arrTime = " << arrTime << " and depTime = " << depTime << endl;
        
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
    
//  Depart any current tasks
    
//	if (spv.isBusy())
//	{
//		float serTime = depTask->getSerLeft();
//		int type = depTask->getType();
//		procDep(depTask);
//		stats->getAvgServiceTime(type) -= serTime;
//		stats->getNumTasksIn(type)--;
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