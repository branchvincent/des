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
#include "Cab.h"
#include "Task.h"
#include "Constants.h"
#include "Statistics.h"

using namespace std;
using namespace cnsts;

// Helper functions and definitions

typedef vector<vector<float> > Matrix2D;
typedef vector<Matrix2D> Matrix3D;
bool compareTasks(Task* t1, Task* t2) 
	{return t1->getArrTime() < t2->getArrTime();}

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

//  Notes
//  - See no need for simTime (delete)
//  - Intialize stats at constructor or run(numRuns)?
//  - Add utilization count for tasks cut off at end of phase
//  - Add destructor

class Simulation
{
//	Public member functions

	public:
		
	//	Constructors
	
		Simulation(bool randRun, int t, vector<float> trafficLevels);
//		~Simulation() {del Task*;}

	//	Other member functions
    
        void run(int numRuns);
		void output(ostream& out) const {out << *stats << endl;}

//  Private member functions
    
    private:
    
    //  Used by run(int)
    
        void run();
        void runPhase(int phase);
        void genTasks(int type, int phase);
        void outputTaskList();
        void processArrival(Task* task) {cab.processArrival(task);}
        void processDepature(Task* task) {cab.processDepature(task);}

//	Data members

	private:
//		float simTime;				// simulation time
		int endTimes[NUM_PHASES];	// phase end times
		list<Task*> taskList;		// task list
		Statistics* stats;			// simulation statistics
		Cab cab;                    // cab of operators
		vector<float> traffic; 		// traffic levels
};

//	Operators

ostream& operator<<(ostream& out, const Simulation sim) {sim.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Simulation													*
*																			*
*	Purpose:	To construct a new simulation								*
*																			*
****************************************************************************/

Simulation::Simulation(bool randRun, int t, vector<float> trafficLevels) :
//    simTime(0),
    endTimes{30, t-30, t},
    taskList(),
    stats(new Statistics(NUM_TASK_TYPES + 1, NUM_INTS + 1, NUM_RUNS)),
//    stats(NULL),
    cab(stats),
    traffic(trafficLevels)
{
//	Check duration of simulation

	if (t < 90 || t%10 != 0) 
	{
		cerr << "Error: Invalid simulation time. Exiting..." << endl;
		exit(1);
	}
	
//	Check traffic array
	
	if (trafficLevels.size() != NUM_HOURS) 
	{
		cerr << "Error: Invalid traffic array. Exiting..." << endl;
		exit(1);
	}

//  Initialize srand
    
    if (randRun)
        srand((unsigned int) time(0));
    else
        srand(0);
}

/****************************************************************************
*																			*
*	Function:	run                                                         *
*																			*
*	Purpose:	To run the simulation the specified number of times			*
*																			*
****************************************************************************/

void Simulation::run(int numRuns)
{
//  Initialize stats
    
//    stats = new Statistics(NUM_TASK_TYPES + 1, NUM_INTS + 1, numRuns);
    
//  Run simulation the specified number of times
    
	for (int i = 0; i < numRuns; i++)
	{
//        simTime = 0;
		cout << "Run " << i << endl;
		run();
	}
    
    return;
}

/****************************************************************************
*																			*
*	Function:	run															*
*																			*
*	Purpose:	To complete one run of the simulation                       *
*																			*
****************************************************************************/

void Simulation::run()
{
	cout << "Beginning simulation..." << endl;

//	Run all phases 
	
	for (int i = 0; i < NUM_PHASES; i++)
		runPhase(i);
		
//	End statistics counter and clear cab

	stats->endRun();
    cab.clear();
    
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
//	Generate all task types
	
	for (int i = 0; i < NUM_TASK_TYPES; i++)
		genTasks(i, phase);
    
    if (DEBUG_ON) outputTaskList();

//	Initiliaze variables

	list<Task*>::iterator it = taskList.begin();
	Task *arrTask, *depTask;
	float arrTime, depTime;
	
//	Process all events in the task list
	
	cout << "Beginning Phase " << phase << "." << endl;

	while(it != taskList.end())
	{
	//	Get next arrival and depature
        
		arrTask = *it;
		arrTime = arrTask->getArrTime();
		depTask = cab.getNextDepature();
		depTime = cab.getNextDeptTime();
        
	//	Process next event

		if (arrTime < depTime || depTime == -1)
        {
			processArrival(arrTask);
            it++;
        }
        else
			processDepature(depTask);
    }
			
//	Process remaining tasks in the queue
	
	depTask = cab.getNextDepature();
	depTime = cab.getNextDeptTime();
		
	while (cab.isBusy() && depTime <= endTimes[2])
	{
		processDepature(depTask);
		depTask = cab.getNextDepature();
		depTime = cab.getNextDeptTime();
	}
	
//	if (op.isBusy())
//	{
//		float serTime = depTask->getSerLeft();
//		int type = depTask->getType();
//		processDepature(depTask, uIndex);
//		stats->getAvgServiceTime(type, uIndex) -= serTime;
//		stats->getNumTasksIn(type, uIndex)--;
//	}

//	Clear task list for next phase
	
    taskList.clear();
	cout << "Phase " << phase++ << " completed." << endl << endl;

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
//    currTime = simTime;
    
//	Create first task and temporary list
    
    list<Task*> tmpList;
    Task* task = new Task(type, currTime, rand(), phase, traffic);
    float arrTime = task->getArrTime();
    float serTime = task->getSerTime();
    
//	Add tasks to list while time is left
    
    while (arrTime < endTimes[phase])
    {
    //	Add current task
        
        tmpList.push_back(task);
        
    //	Get next task
        
        task = new Task(type, arrTime, rand(), phase, traffic);
        arrTime = task->getArrTime();
        serTime = task->getSerTime();
    }
    
//	Merge new list with task list
    
    taskList.merge(tmpList, compareTasks);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	processArrival												*
*																			*
*	Purpose:	To process a task arrival								 	*
*																			*
****************************************************************************/

//void Simulation::processArrival(Task* task)
//{	
//	cab.processArrival(task);
////	simTime = task->getArrTime();
//	return;
//}

/****************************************************************************
*																			*
*	Function:	processDepature												*
*																			*
*	Purpose:	To process a task depature								 	*
*																			*
****************************************************************************/

//void Simulation::processDepature(Task* task)
//{
//	cab.processDepature(task);
////	simTime = task->getDepTime();
//	return;
//}

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