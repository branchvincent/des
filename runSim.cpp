/****************************************************************************
*																			*
*	File:		runSim.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 6, 2016													*
*																			*
*	Purpose:	This file executes the simulation for the specified number	* 
*				of minutes and the specified number of runs. Then, it 		*
*				outputs the results to the specified file.					*
*																			*
****************************************************************************/

// Header files

#include <iostream>
#include <string>
#include "Simulation.h"
#include "Statistics.h"

using namespace std;
using namespace cnsts;

// Function prototypes

void setSeed(int& seed);
void setTrafficLevels(vector<float>& traffic);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

int main() 
{
//	Set folder paths

	const string filePath = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/Data/";
	const string oneRunFile = filePath + "singleRun.csv";
	const string batchRunFile = filePath + "batchRun.csv";
		
//	Initialize variables

	srand((unsigned int) time(0));
	
	int seed = 0;
	vector<float> traffic(NUM_HOURS, 0);
	Statistics* stats = new Statistics(NUM_TASK_TYPES + 1, NUM_INTS + 1, NUM_RUNS);

//	Run simulations for specified times

	for (int i = 0; i < NUM_RUNS; i++)
	{
	//	Set simulation seed and traffic levels
	
		setSeed(seed);
		setTrafficLevels(traffic);
		
	//	Run simulation	
	
		cout << "Run " << i << endl;
		Simulation sim(END_TIME, seed, traffic, stats);	
		sim.run();	
}

//	Output data, if applicable

	if (OUTPUT)	
	{
		ofstream fout(batchRunFile);
		fout << *stats << endl;
	}	

	return 0;
}

/****************************************************************************
*																			*
*	Function:	setSeed														*
*																			*
*	Purpose:	To set the seed for the simulation							*
*																			*
****************************************************************************/

void setSeed(int& seed)
{
//	Set random seed, if applicable

	if (RAND_RUN) 
		seed = rand();

//	Otherwise, set specific seed

	else 
		seed++;
		
	return;
}

/****************************************************************************
*																			*
*	Function:	setTrafficLevels											*
*																			*
*	Purpose:	To set the traffic levels for the simulation				*
*																			*
****************************************************************************/

void setTrafficLevels(vector<float>& traffic)
{
//	Set random traffic, if applicable

	float levels[] = {0.5, 1, 2};
	
	if (RAND_RUN)
		for (int i = 0; i < traffic.size(); i++)
			traffic[i] = levels[rand() % 3];
	
//	Otherwise, set specific traffic

	else
		for (int i = 0; i < traffic.size(); i++)
			traffic[i] = levels[i % 3];
	
	return;
}