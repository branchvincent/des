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

#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;
using namespace cnsts;

// Function prototypes

void setTrafficLevels(vector<float>& traffic, bool randRun);
void outputStats(Simulation& sim, string outputFile);

/****************************************************************************
*																			*
*	Function:	main														*
*																			*
****************************************************************************/

//  Notes:
//  - Not using RAND_RUN
//  - OUTPUT_ON used once
//  - sim.run(NUM_RUNS):  NUM_RUNS has already set stat size

int main() 
{
//	Set folder path

//	string filePath = "/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/Data/";
    string outputFile = "/Users/Branch/Desktop/DES/DES/Output/runData.csv";
		
//	Initialize variables

    bool randRun = false;
	vector<float> traffic(NUM_HOURS, 0);
    setTrafficLevels(traffic, randRun);
    
//  Run sim and output data
    
    Simulation sim(randRun, END_TIME, traffic);
	sim.run(NUM_RUNS);
    outputStats(sim, outputFile);

	return 0;
}

/****************************************************************************
*																			*
*	Function:	setTrafficLevels											*
*																			*
*	Purpose:	To set the traffic levels for the simulation				*
*																			*
****************************************************************************/

void setTrafficLevels(vector<float>& traffic, bool randRun)
{
//	Set random traffic, if applicable

    srand((unsigned int) time(0));
	float levels[] = {0.5, 1, 2};
	
	if (randRun)
		for (int i = 0; i < traffic.size(); i++)
			traffic[i] = levels[rand() % 3];
	
//	Otherwise, set specific traffic

	else
		for (int i = 0; i < traffic.size(); i++)
			traffic[i] = levels[i % 3];
	
	return;
}

/****************************************************************************
*																			*
*	Function:	outputStats                                                 *
*																			*
*	Purpose:	To output the statistical data from the simulation			*
*																			*
****************************************************************************/

void outputStats(Simulation& sim, string outputFile)
{
//  Check for output
    
    if (OUTPUT_ON)
    {
    //  Open file
        
        ofstream fout(outputFile);
        if (!fout)
        {
            cerr << "Error: Cannot open file. Exiting..." << endl;
            exit(1);
        }
        
    //  Output stats
        
        fout << sim << endl;
    }
            
    return;
}