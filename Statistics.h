/****************************************************************************
*																			*
*	File:		Statistics.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 28, 2016												*
*																			*
*	Purpose:	This file defines the Statistics class.						*
*																			*
****************************************************************************/

#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <fstream>
#include <string>
#include "Statistic.h"
//#include "PyPlot.h"

using namespace std;
using namespace params;

/****************************************************************************
*																			*
*	Definition of Statistics class											*
*																			*
****************************************************************************/

class Statistics
{
//	Public member functions

	public:
		
	//	Constructor
	
		Statistics(int xDim = NUM_TASK_TYPES,
                   int yDim = NUM_INTS,
                   int zDim = NUM_REPS);
		
	//	Inspectors

//		int getInterval(int i) {return interval[i];}
//		float& getUtil(int i, int j) {return util[i][j];}
//		float& getserTime(int i, int j) {return serTime[currRep][i][j];} 
//		float& getwaitTime(int i, int j) {return waitTime[i][j];}
//		float& getNumTasksIn(int i, int j) {return numTasksIn[currRep][i][j];} 
//		float& getNumTasksOut(int i, int j) {return numTasksOut[i][j];}

	//	Mutators

        void incUtil(int i, int j, float val) {util.incData(i, j, currRep, val);}
        void incSerTime(int i, int j, float val) {serTime.incData(i, j, currRep, val);}
		void incWaitTime(int i, int j, float val) {waitTime.incData(i, j, currRep, val);}
		void incNumTasksIn(int i, int j, float val) {numTasksIn.incData(i, j, currRep, val);}
		void incNumTasksOut(int i, int j, float val) {numTasksOut.incData(i, j, currRep, val);}
		void incNumTasksExp(int i, int j, float val) {numTasksExp.incData(i, j, currRep, val);}
		void endRep();

//		void setUtil(const int& i, const int& j, const int& val) {util[i][j] = val;}
//		void setSerTime(const int& i, const int& j, const int& val) {serTime[i][j] = val;}
//		void setWaitTime(const int& i, const int& j, const int& val) {waitTime[i][j] = val;}
//		void setNumTasksIn(const int& i, const int& j, const int& val) {numTasksIn[i][j] = val;}
//		void setNumTasksOut(const int& i, const int& j, const int& val) {numTasksOut[i][j] = val;}
				
	//	Other member functions

//        void plot(string opName);
        void output(ostream& out) const {outputSim(out); return;}

//	Private member functions

	private:
        void outputRep(ostream& out, int rep) const;
        void outputSim(ostream& out) const;
        void endSim();

//	Data members

	private:
		int currRep;			// current run counter
		vector<int> interval;	// time interval
		Statistic util;			// utilization
		Statistic serTime;      // average service time
		Statistic waitTime;		// average wait time in queue
		Statistic numTasksIn;	// number of tasks in
		Statistic numTasksOut;	// number of tasks out
		Statistic numTasksExp;	// number of tasks expired
};

//	Operators

ostream& operator<<(ostream& out, const Statistics& stats) {stats.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	Statistics													*
*																			*
*	Purpose:	To construct a new Statistics								*
*																			*
****************************************************************************/

Statistics::Statistics(int xDim, int yDim, int zDim) :
    currRep(0),
    interval(yDim),
	util("Utilization", xDim, yDim, zDim),
	serTime("Service Time", xDim, yDim, zDim),
	waitTime("Wait Time", xDim, yDim, zDim),
	numTasksIn("Number In", xDim, yDim, zDim),
	numTasksOut("Number Out", xDim, yDim, zDim),
	numTasksExp("Number Expired", xDim, yDim, zDim)
{
//  Set time intervals
    
	for (int i = 1; i < interval.size(); i++)
		interval[i] = interval[i-1] + INT_SIZE;
}

/****************************************************************************
*																			*
*	Function:	endRep														*
*																			*
*	Purpose:	To output the stats for the current replication and move to *
*               the next replication                                        *
*																			*
****************************************************************************/

void Statistics::endRep()
{
//  Output statistics for current replication
    
    if (false) //DEBUG_ON)
    {
        string file = OUTPUT_PATH + "/rep" + to_string(currRep) + ".csv";
        ofstream fout(file);
        if (!fout)
        {
            cerr << "Error: Cannot open " << file << ". Exiting..." << endl;
            exit(1);
        }
        outputRep(fout, currRep);
    }

//	Move to next replication and end simulation, if applicable
    
    if (++currRep == NUM_REPS) endSim();
}

/****************************************************************************
*																			*
*	Function:	outputRep													*
*																			*
*	Purpose:	To output the stats for the specified replication			*
*																			*
****************************************************************************/

void Statistics::outputRep(ostream& out, int rep) const
{
//	Output header
    
    out << "Statistic, Task, ";
    
    for (int i = 0; i < interval.size(); i++)
        out << interval[i] << " min, ";
    out << "Sum" << endl;
    
//	Output stats
    
    util.outputRep(out, rep);
    serTime.outputRep(out, rep);
    waitTime.outputRep(out, rep);
    numTasksIn.outputRep(out, rep);
    numTasksOut.outputRep(out, rep);
    numTasksExp.outputRep(out, rep);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	outputSim													*
*																			*
*	Purpose:	To output the stats averaged across all replications        *
*																			*
****************************************************************************/

void Statistics::outputSim(ostream& out) const
{
//	Output header
    
    out << "Statistic, Task";
    
    for (int i = 0; i < interval.size(); i++)
        out << ", " << interval[i] << " min";
    out << "," << endl;
//    out << ", Sum" << endl;
    
//  Output arrays
    
    util.outputSim(out);
    serTime.outputSim(out);
    waitTime.outputSim(out);
    numTasksIn.outputSim(out);
    numTasksOut.outputSim(out);
    numTasksExp.outputSim(out);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	endSim														*
*																			*
*	Purpose:	To average the stats across all replications                *
*																			*
****************************************************************************/

void Statistics::endSim()
{
//	Calculate mean and std dev across all replications
    
    util.avgData();
    serTime.avgData();
    waitTime.avgData();
    numTasksIn.avgData();
    numTasksOut.avgData();
    numTasksExp.avgData();
    
    return;
}

/****************************************************************************
*																			*
*	Function:	plot                                                        *
*																			*
*	Purpose:	To plot the utilization										*
*																			*
****************************************************************************/

//void Statistics::plot(string opName)
//{
//    int lastRow = util[0].size() - 1;
//    int lastCol = util[0][0].size() - 1;
//
//    vector<float> time;
//    vector<float> util;
//    vector<float> err;
//
//    for (int i = 0; i < interval.size(); i++)
//    {
//        time.push_back(interval[i] + INT_SIZE/2);
//        util.push_back(stats[i][NUM_REPS]);
//        err.push_back(stats[i][NUM_REPS + 1]);
//    }
//
////  Plot using matplotlib
//
//    PyPlot plt;
//    plt.set_title(opName + " Utilization for " + to_string(NUM_REPS) + " Reps");
//    plt.set_xlabel("Time (min)");
//    plt.set_ylabel("Utilization");
//    plt.set_xlim(0, END_TIME);
//    plt.set_ylim(0, 1.1);
//    plt.set_axis();
//    plt.plot_bar(time, util, err);
//    for (int i = 0; i < NUM_HOURS; i++)
//    {
//        string hr = to_string(60 * (i + 1));
//        plt.run_cmd("plt.plot((" + hr + ", " + hr + "), (0, 1.10), 'm--')");
//    }
//    plt.save_fig(OUTPUT_PATH + "/" + opName + "_Util.pdf");
//
//    return;
//}

#endif