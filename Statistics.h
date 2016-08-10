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
#include <string>
#include <vector>
//#include "PyPlot.h"

using namespace std;
using namespace params;

typedef vector<vector<float> > Matrix2D;
typedef vector<Matrix2D> Matrix3D;

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
	
		Statistics( //NewParams& pms,
                   int xDim = NUM_TASK_TYPES + 1,
                   int yDim = NUM_INTS + 1,
                   int zDim = NUM_REPS + 2, int val = 0);
		
	//	Inspectors

//		int getInterval(int i) {return interval[i];}
//		float& getUtil(int i, int j) {return util[i][j];}
//		float& getserTime(int i, int j) {return serTime[currRep][i][j];} 
//		float& getwaitTime(int i, int j) {return waitTime[i][j];}
//		float& getNumTasksIn(int i, int j) {return numTasksIn[currRep][i][j];} 
//		float& getNumTasksOut(int i, int j) {return numTasksOut[i][j];}

	//	Mutators

        void incUtil(int i, int j, float val) {incArr(util, i, j, val);}
        void incSerTime(int i, int j, float val) {incArr(serTime, i, j, val);}
		void incWaitTime(int i, int j, float val) {incArr(waitTime, i, j, val);}
		void incNumTasksIn(int i, int j, float val) {incArr(numTasksIn, i, j, val);}
		void incNumTasksOut(int i, int j, float val) {incArr(numTasksOut, i, j, val);}
		void incNumTasksExp(int i, int j, float val) {incArr(numTasksExp, i, j, val);}
		void endRep();

//		void setUtil(const int& i, const int& j, const int& val) {util[i][j] = val;}
//		void setSerTime(const int& i, const int& j, const int& val) {serTime[i][j] = val;}
//		void setWaitTime(const int& i, const int& j, const int& val) {waitTime[i][j] = val;}
//		void setNumTasksIn(const int& i, const int& j, const int& val) {numTasksIn[i][j] = val;}
//		void setNumTasksOut(const int& i, const int& j, const int& val) {numTasksOut[i][j] = val;}
				
	//	Other member functions

//        void plot(string opName);
        void output(ostream& out) const {outputAvg(out); return;}

//	Private member functions

	private:
		void incArr(Matrix3D& arr, int i, int j, float val);
        void outputRep(ostream& out, int rep) const;
        void outputRepArr(ostream& out, string arrName, const Matrix2D& arr) const;
        void outputAvg(ostream& out) const;
        void outputAvgArr(ostream& out, string arrName, const Matrix3D& arr) const;
        void endSim();
        void setMeanAndStdDev(Matrix3D& data);

//	Data members

	private:
//        NewParams pms;            // parameters
		int currRep;			// current run counter
		vector<int> interval;	// time interval
		Matrix3D util;			// utilization
		Matrix3D serTime;       // average service time
		Matrix3D waitTime;		// average wait time in queue
		Matrix3D numTasksIn;	// number of tasks in
		Matrix3D numTasksOut;	// number of tasks out
		Matrix3D numTasksExp;	// number of tasks expired
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

Statistics::Statistics(int xDim, int yDim, int zDim, int val) :
    currRep(0),
    interval(NUM_INTS),
	util(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
	serTime(zDim, Matrix2D(xDim, vector<float>(yDim, val))), 
	waitTime(zDim, Matrix2D(xDim, vector<float>(yDim, val))), 
	numTasksIn(zDim, Matrix2D(xDim, vector<float>(yDim, val))), 
	numTasksOut(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
	numTasksExp(zDim, Matrix2D(xDim, vector<float>(yDim, val)))
{
	for (int i = 1; i < NUM_INTS; i++)
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
    
    if (DEBUG_ON)
    {
        string file = OUTPUT_PATH + "/rep" + to_string(currRep) + ".csv";
        ofstream fout(file);
        outputRep(fout, currRep);
    }

//	Move to next replication and end simulation, if applicable
    
    if (++currRep == NUM_REPS) endSim();
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
//    for (int i = 0; i < NUM_INTS; i++)
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

/****************************************************************************
*																			*
*	Function:	incArr														*
*																			*
*	Purpose:	To increment the specified stat based on the specified      *
*				indices and value 											*
*																			*
****************************************************************************/

void Statistics::incArr(Matrix3D& arr, int i, int j, float val)
{
//	Calculate indices for the last row/column
    
    int lastRow = arr[currRep].size() - 1;
    int lastCol = arr[currRep][0].size() - 1;
    
//	Increment array
    
    arr[currRep][i][j] += val;				// increment value
    arr[currRep][lastRow][j] += val;		// increment row sum
    arr[currRep][i][lastCol] += val;		// increment column sum
    arr[currRep][lastRow][lastCol] += val; 	// increment total sum

    return;
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
    
    for (int i = 0; i < NUM_INTS; i++)
        out << i * INT_SIZE << " min, ";
    out << "Sum" << endl;
    
//	Output stats
    
    outputRepArr(out, "Utilization", util[rep]);
    outputRepArr(out, "Avg Service Time", serTime[rep]);
    outputRepArr(out, "Avg Wait Time", waitTime[rep]);
    outputRepArr(out, "Number In", numTasksIn[rep]);
    outputRepArr(out, "Number Out", numTasksOut[rep]);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	outputRepArr												*
*																			*
*	Purpose:	To output the specified stat for a specified replication	*
*																			*
****************************************************************************/

void Statistics::outputRepArr(ostream& out, string arrName, const Matrix2D& arr) const
{
//	Output array name
    
    out << arrName;
    
//	Output array
    
    for (int i = 0; i < arr.size(); i++)
    {
    //	Output task type
        
        if (i != arr.size() - 1)
            out << ", " << i;
        else
            out << ", Sum";
        
    //	Output data
        
        for (int j = 0; j < arr[i].size(); j++)
            out << ", " << arr[i][j];
        out << endl;
    }	
    
    out << endl << endl;
    
    return;
}

/****************************************************************************
*																			*
*	Function:	outputAvg													*
*																			*
*	Purpose:	To output the stats averaged across all replications        *
*																			*
****************************************************************************/

void Statistics::outputAvg(ostream& out) const
{
//	Output header
    
    out << "Statistic, Task";
    
    for (int i = 0; i < NUM_INTS; i++)
        out << ", " << i * INT_SIZE << " min";
    out << ", Sum" << endl;
    
//  Output arrays
    
    outputAvgArr(out, "Utilization", util);
    outputAvgArr(out, "Service Time", serTime);
    outputAvgArr(out, "Wait Time", waitTime);
    outputAvgArr(out, "Number In", numTasksIn);
    outputAvgArr(out, "Number Out", numTasksOut);
    outputAvgArr(out, "Number Expired", numTasksExp);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	outputAvgArr                                                *
*																			*
*	Purpose:	To output the specified stat averaged across all            *
*               replications                                                *
*																			*
****************************************************************************/

void Statistics::outputAvgArr(ostream& out, string arrName, const Matrix3D& arr) const
{
//	Output stat name
    
    out << arrName;
    
//	Output stat
    
    for (int i = 0; i < arr[0].size(); i++)
    {
    //	Output task type
        
        if (i != arr[0].size() - 1)
            out << ", " << i;
        else
            out << ", Sum";
        
    //	Output averages
        
        for (int j = 0; j < arr[0][0].size(); j++)
            out << ", " << arr[NUM_REPS][i][j];
        out << endl << ", ";
        
    //  Output std devs
        
        for (int j = 0; j < arr[0][0].size(); j++)
            out << ", " << arr[NUM_REPS + 1][i][j];
        out << endl;
    }
    
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
//	Calculate mean and std dev for all arrays
    
    setMeanAndStdDev(util);
    setMeanAndStdDev(serTime);
    setMeanAndStdDev(waitTime);
    setMeanAndStdDev(numTasksIn);
    setMeanAndStdDev(numTasksOut);
    setMeanAndStdDev(numTasksExp);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	setMeanAndStdDev											*
*																			*
*	Purpose:	To calculate and store the mean and standard deviation for  *
*				the specified array	across all replications					*
*																			*
****************************************************************************/

void Statistics::setMeanAndStdDev(Matrix3D& arr)
{
//	Initialize variables
    
    int N = 0;
    float mean = 0;
    float devSum = 0;
    float delta;
    
//  Calculate mean and std dev across all replications
    
    for (int i = 0; i < arr[0].size(); i++)
    {
        for (int j = 0; j < arr[0][0].size(); j++)
        {
        //  Reset variables
            
            N = 0;
            mean = 0;
            devSum = 0;
            
        //  Calculate values using Welford's algorithm
            
            for (int k = 0; k < arr.size() - 2; k++)
            {
                N++;
                delta = arr[k][i][j] - mean;
                mean += delta/N;
                devSum += delta * (arr[k][i][j] - mean);
            }
            
        //  Store values
            
            arr[N][i][j] = mean;
            arr[N + 1][i][j] = sqrt(devSum / (N - 1));
        }
    }
    
    return;           
}

#endif