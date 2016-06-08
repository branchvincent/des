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
#include <string>
#include <queue>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Task.h"

using namespace std;

// Global variables

double Lambda = 0.1;
int Mean = 1;
int Sigma = 1;

/****************************************************************************
*																			*
*	Definition of Simulation class											*
*																			*
****************************************************************************/

class Simulation
{
//	Public member functions

	public:

	//	Inspectors

//		int getArr() const {return arrTime;}
//		int& getArr() {return arrTime;}
//		int getSer() const {return serTime;}
//		int& getSer() {return serTime;}

	//	Other member functions

		void setup();
		void run();
		int genArrTime(double lambda);
		int genSerTime(int mean, int sigma);
		
//	Private member functions

	//private:
	
	//	Constructors
	
		Simulation(int t) : simTime(0), taskQueue() {endTime = t;}

//	Data members

	private:
		int simTime;
		int endTime;
		queue<Task*> taskQueue;
		
};

/****************************************************************************
*																			*
*	Function:	setup														*
*																			*
*	Purpose:	To setup a simulation by adding tasks to the queue			*
*																			*
****************************************************************************/

void Simulation::setup()
{
	srand(time(0));
	int arrTime = 0;
	int serTime = genSerTime(Mean, Sigma);
	Task* initTask = new Task(arrTime, serTime);
	taskQueue.push(initTask);
	cout << "Task arriving at " << arrTime << endl;
	
	arrTime += genArrTime(Lambda);
	serTime = genSerTime(Mean, Sigma);
	
	while (arrTime < endTime)
	{
		Task* task = new Task(arrTime, serTime);
		taskQueue.push(task);
		cout << "Task arriving at " << arrTime << endl;
		arrTime += genArrTime(Lambda);
		serTime = genSerTime(Mean, Sigma);

	}
			
	return;
}

/****************************************************************************
*																			*
*	Function:	run															*
*																			*
*	Purpose:	To run the simulation by completing tasks in the queue		*
*																			*
****************************************************************************/

void Simulation::run()
{
	setup();
	
	while(!taskQueue.empty() && simTime < endTime) 
	{
		Task* nextTask = taskQueue.front();
		taskQueue.pop();
		int arrTime = nextTask->getArr();
		int serTime = nextTask->getSer();
		simTime = max(simTime, arrTime);
		cout << "Tasking starting at " << simTime << endl;
		simTime += serTime;
		cout << "Tasking leaving at " << simTime << endl;
		delete nextTask;
	}
}

/****************************************************************************
*																			*
*	Function:	genArrTime													*
*																			*
*	Purpose:	To generate an arrival time based on the specified 			*
*				distribution							 					*
*																			*
****************************************************************************/

int Simulation::genArrTime(double lambda)
{
	default_random_engine generator(rand());
	exponential_distribution<double> dist(lambda); 
	return dist(generator);
}

/****************************************************************************
*																			*
*	Function:	genSerTime													*
*																			*
*	Purpose:	To generate a service time based on the specified			* 
*				distribution 												*
*																			*
****************************************************************************/

int Simulation::genSerTime(int mean, int sigma)
{
	default_random_engine generator(rand());
	lognormal_distribution<double> dist(mean,sigma);
	return dist(generator);
}

#endif