/****************************************************************************
*																			*
*	File:		OpStatistics.h												*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jun 28, 2016												*
*																			*
*	Purpose:	This file defines the OpStatistics class.					*
*																			*
****************************************************************************/

#ifndef OPSTATISTICS_H
#define OPSTATISTICS_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace cnsts;

typedef vector<vector<float> > Matrix2D;
typedef vector<Matrix2D> Matrix3D;

/****************************************************************************
*																			*
*	Definition of OpStatistics class										*
*																			*
****************************************************************************/

class OpStatistics
{
//	Public member functions
    
    public:
    
//	Constructor
    
    OpStatistics(int xDim = NUM_TASK_TYPES + 1,
               int yDim = NUM_INTS + 1,
               int zDim = NUM_REPS, int val = 0);
    
//	Inspectors
    
    float& getUtil(int i, int j) {return util[i][j];}
    float& getAvgServiceTime(int i, int j) {return avgServiceTime[currRep][i][j];}
//		float& getAvgWaitTime(int i, int j) {return avgWaitTime[i][j];}
    float& getNumTasksIn(int i, int j) {return numTasksIn[currRep][i][j];}
//		float& getNumTasksOut(int i, int j) {return numTasksOut[i][j];}
//		void getColSums(Matrix2D& sum, int run);
//		void getRowSums(Matrix2D& sum, int run);
    
//	Mutators
    
    void incUtil(int i, int j, float val) {incStat(util[currRep], i, j, val);}
    void incAvgServiceTime(int i, int j, float val) {incStat(avgServiceTime[currRep], i, j, val);}
    void incAvgWaitTime(int i, int j, float val) {incStat(avgWaitTime[currRep], i, j, val);}
    void incNumTasksIn(int i, int j, float val) {incStat(numTasksIn[currRep], i, j, val);}
    void incNumTasksOut(int i, int j, float val) {incStat(numTasksOut[currRep], i, j, val);}
    void incNumTasksExp(int i, int j, float val) {incStat(numTasksExp[currRep], i, j, val);}
    void endRep();
    void endSim();
    void getMeanAndStdDev(vector<float>& data);
 
//	Other member functions
    
    void output(ostream& out) const;
    void outputArr(ostream& out, string arrName, int statNum) const;
    void outputRun(ostream& out, int run) const;
    void outputRunArr(ostream& out, string arrName, const Matrix2D& arr) const;
    
//	Private member functions
    
    private:
        void incStat(Matrix2D& stat, int i, int j, float val);
    
//	Data members
    
    private:
        int currRep;                    // current run counter
        int cmpStatsIndex[NUM_STATS];   // index in cmpStats
        int interval[NUM_INTS];         // time interval
        Matrix3D util;                  // utilization
        Matrix3D avgServiceTime;        // average service time
        Matrix3D avgWaitTime;           // average wait time in queue
        Matrix3D numTasksIn;            // number of tasks in
        Matrix3D numTasksOut;           // number of tasks out
        Matrix3D numTasksExp;           // number of tasks expired
        Matrix2D cmpStats;              // compiled stats
};

//	Operators

ostream& operator<<(ostream& out, const OpStatistics& stats) {stats.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	OpStatistics												*
*																			*
*	Purpose:	To construct a new OpStatistics								*
*																			*
****************************************************************************/

OpStatistics::OpStatistics(int xDim, int yDim, int zDim, int val) :
    currRep(0),
    cmpStatsIndex(),
    interval(),
    util(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
    avgServiceTime(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
    avgWaitTime(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
    numTasksIn(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
    numTasksOut(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
    numTasksExp(zDim, Matrix2D(xDim, vector<float>(yDim, val))),
    cmpStats(5 * (xDim-1) + yDim-1, vector<float>(zDim + 2, val))
{
    for (int i = 1; i < NUM_INTS; i++)
        interval[i] = interval[i-1] + INT_SIZE;
    
    for (int i = 1; i < NUM_STATS; i++)
        cmpStatsIndex[i] = NUM_INTS + i * NUM_TASK_TYPES;
}

/****************************************************************************
*																			*
*	Function:	incStat														*
*																			*
*	Purpose:	To increment the specified statistic based on the specified *
*				index and value 											*
*																			*
****************************************************************************/

void OpStatistics::incStat(Matrix2D& stat, int i, int j, float val)
{
//	Calculate indices for the last row/column
    
    int lastRow = util[0].size() - 1;
    int lastCol = util[0][0].size() - 1;
    
//	Increment stat values for the current run
    
    stat[i][j] += val;					// increment value
    stat[lastRow][j] += val;			// increment row sum
    stat[i][lastCol] += val;			// increment column sum
    stat[lastRow][lastCol] += val; 		// increment total sum
    
    return;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output the stats											*
*																			*
****************************************************************************/

void OpStatistics::output(ostream& out) const
{
//	Output header
    
    out << "Statistic Type, Time (min), ";
    
    for (int i = 0; i < currRep; i++)
        out << "Rep " << i << ", ";
    out << "Mean, Std Dev" << endl;
    
//	Output statistical data
    
    out << "Utilization";
    
    for (int i = 0; i < NUM_INTS; i++)
    {
        out << ", " << i * INT_SIZE << ", ";
        
        for (int j = 0; j < NUM_REPS + 2; j++)
            out << cmpStats[i][j] << ", ";
        out << endl;
    }
    
    out << endl << endl;
    
    outputArr(out, "Avg Service Time", 0);
    outputArr(out, "Avg Wait Time", 1);
    outputArr(out, "Number In", 2);
    outputArr(out, "Number Out", 3);
    outputArr(out, "Number Expired", 4);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	outputRunArr												*
*																			*
*	Purpose:	To output the specified array								*
*																			*
****************************************************************************/

void OpStatistics::outputArr(ostream& out, string arrName, int statNum) const
{
//	Output stat name
    
    out << arrName;
    
//	Output stat
    
    for (int i = NUM_INTS + statNum * NUM_TASK_TYPES; i < NUM_INTS + (statNum + 1) * NUM_TASK_TYPES; i++)
    {
    //	Output task type
        
        out << ", " << (i - NUM_INTS) % NUM_TASK_TYPES << ", ";
        
    //	Output stat data
        
        for (int j = 0; j < NUM_REPS + 2; j++)
            out << cmpStats[i][j] << ", ";
        out << endl;
    }
    
    out << endl << endl;
    
    return;
}

/****************************************************************************
*																			*
*	Function:	endRep														*
*																			*
*	Purpose:	To update the compiled stats at the end of a replication	*
*																			*
****************************************************************************/

void OpStatistics::endRep()
{
//	Calculate indices for the last row/column
    
    int lastRow = util[0].size() - 1;
    int lastCol = util[0][0].size() - 1;

//	Copy totals from stats
    
    for (int i = 0; i < lastCol; i++)
        cmpStats[i][currRep] = util[currRep][lastRow][i];
    
    for (int i = 0; i < lastRow; i++)
    {
        cmpStats[i + NUM_INTS][currRep] = avgServiceTime[currRep][i][lastCol];
        cmpStats[i + NUM_INTS + NUM_TASK_TYPES][currRep] = avgWaitTime[currRep][i][lastCol];
        cmpStats[i + NUM_INTS + 2*NUM_TASK_TYPES][currRep] = numTasksIn[currRep][i][lastCol];
        cmpStats[i + NUM_INTS + 3*NUM_TASK_TYPES][currRep] = numTasksOut[currRep][i][lastCol];
        cmpStats[i + NUM_INTS + 4*NUM_TASK_TYPES][currRep] = numTasksExp[currRep][i][lastCol];
    }
    
//	Increment current run
    
    currRep++;
    
    if (currRep == NUM_REPS)
        endSim();
}

/****************************************************************************
*																			*
*	Function:	endSim														*
*																			*
*	Purpose:	To update the compiled stats at the end of all runs			*
*																			*
****************************************************************************/

void OpStatistics::endSim()
{
//	Calculate mean and standard deviation
    
    for (int i = 0; i < cmpStats.size(); i++)
        getMeanAndStdDev(cmpStats[i]);
    
    return;
}

/****************************************************************************
*																			*
*	Function:	getMeanAndStdDev											*
*																			*
*	Purpose:	To calculate the mean and standard deviation for the 		*
*				specified array												*
*																			*
****************************************************************************/

void OpStatistics::getMeanAndStdDev(vector<float>& data)
{
//	Initialize variables
    
    int N = data.size() - 2;
    float mean = 0;
    float devSum = 0;
    
//	Calculate mean
    
    for (int i = 0; i < N; i++)
        mean += data[i];
    mean /= N;
    data[N] = mean;
    
//	Calculate standard deviation
    
    for (int i = 0; i < N; i++)
        devSum += (data[i] - mean) * (data[i] - mean);
    data[N + 1] = sqrt(devSum/(N-1));
    
    return;           
}

#endif