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

using namespace std;
using namespace cnsts;

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
	
		Statistics(int nRows, int nCols, int val) : 
			util(nRows + 1, vector<float>(nCols + 1, val)), 
			avgServiceTime(nRows + 1, vector<float>(nCols + 1, val)), 
			avgWaitTime(nRows + 1, vector<float>(nCols + 1, val)), 
			numTasksIn(nRows + 1, vector<float>(nCols + 1, val)),
			numTasksOut(nRows + 1, vector<float>(nCols + 1, val))  
		{
			numRows = nRows + 1;
			numCols = nCols + 1;
			interval[0] = 0;
			for (int i = 1; i < NUM_INTS; i++)
				interval[i] = interval[i-1] + INT_SIZE; 
		}
		
	//	Inspectors
	
		void getSums(Matrix2D& sum, int run);
	
		int getInterval(int i) {return interval[i];}
		float& getUtil(int i, int j) {return util[i][j];} 
		float& getAvgServiceTime(int i, int j) {return avgServiceTime[i][j];} 
		float& getAvgWaitTime(int i, int j) {return avgWaitTime[i][j];} 
		float& getNumTasksIn(int i, int j) {return numTasksIn[i][j];} 
		float& getNumTasksOut(int i, int j) {return numTasksOut[i][j];} 
		
		void incArray(Matrix2D& arr, int i, int j, float val);
		void incUtil(int i, int j, float val) {incArray(util, i, j, val);}
		void incAvgServiceTime(int i, int j, float val) {incArray(avgServiceTime, i, j, val);}
		void incAvgWaitTime(int i, int j, float val) {incArray(avgWaitTime, i, j, val);}
		void incNumTasksIn(int i, int j, float val) {incArray(numTasksIn, i, j, val);}
		void incNumTasksOut(int i, int j, float val) {incArray(numTasksOut, i, j, val);}
		
	//	Mutators
	
		void updateUtil(const int& i, const int& j, const int& val) {util[i][j] = val;}
		void updateSerTime(const int& i, const int& j, const int& val) {avgServiceTime[i][j] = val;}
		void updateWaitTime(const int& i, const int& j, const int& val) {avgWaitTime[i][j] = val;}
		void updateNumTasksIn(const int& i, const int& j, const int& val) {numTasksIn[i][j] = val;}
		void updateNumTasksOut(const int& i, const int& j, const int& val) {numTasksOut[i][j] = val;}
				
	//	Other member functions

		void output(ostream& out) const;
		void outputArr(ostream& out, const Matrix2D& arr) const;

//	Data members

	private:
		int numRows;				// number of rows
		int numCols;				// number of columns
		int interval[NUM_INTS];		// time interval
		Matrix2D util;				// utilization
		Matrix2D avgServiceTime;	// average service time
		Matrix2D avgWaitTime;		// average wait time in queue
		Matrix2D numTasksIn;		// number of tasks in
		Matrix2D numTasksOut;		// number of tasks out
};

//	Operators

ostream& operator<<(ostream& out, const Statistics stats) {stats.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	getSums														*
*																			*
*	Purpose:	To return a the sums of the stats							*
*																			*
****************************************************************************/

void Statistics::getSums(Matrix2D& sum, int run)
{
	if (sum.size() != NUM_STATS * NUM_TASK_TYPES || sum[0].size() != NUM_RUNS + 2)
	{
		cerr << "Incompatible matrix size. Exiting..." << endl;
		exit(1);
	}
	
	for (int i = 0; i < numRows - 1; i++)
	{
		sum[i][run] = util[i][numCols - 1];
		sum[i + NUM_TASK_TYPES][run] = avgServiceTime[i][numCols - 1];
		sum[i + 2 * NUM_TASK_TYPES][run] = avgWaitTime[i][numCols - 1];
		sum[i + 3 * NUM_TASK_TYPES][run] = numTasksIn[i][numCols - 1];
		sum[i + 4 * NUM_TASK_TYPES][run] = numTasksOut[i][numCols - 1];
	}
	
	return;
}

/****************************************************************************
*																			*
*	Function:	incArray													*
*																			*
*	Purpose:	To increment the specified array based on the specified 	*
*				index and value 											*
*																			*
****************************************************************************/

void Statistics::incArray(Matrix2D& arr, int i, int j, float val) 
{
	arr[i][j] += val;						// increment value
	arr[numRows - 1][j] += val;				// increment row sum
	arr[i][numCols - 1] += val;				// increment column sum
	arr[numRows - 1][numCols - 1] += val; 	// increment total sum
	
	return;
}

/****************************************************************************
*																			*
*	Function:	output														*
*																			*
*	Purpose:	To output the stats											*
*																			*
****************************************************************************/

void Statistics::output(ostream& out) const 
{
//	Output header

	out << "Statistic Type, Task Type, ";
	
	for (int i = 0; i < numCols - 1; i++)
		out << i * INT_SIZE << " min, ";
	out << "Sum, Std Dev" << endl;
	
//	Output utilization

	out << "Utilization";
	outputArr(out, util);
	out << endl << endl;

//	Output avg service times

	out << "Avg Service Time";
	outputArr(out, avgServiceTime);
	out << endl << endl;

//	Output avg wait times

	out << "Avg Wait Time";
	outputArr(out, avgWaitTime);
	out << endl << endl;

//	Output number of tasks in

	out << "Number In";
	outputArr(out, numTasksIn);
	out << endl << endl;

//	Output number of tasks out

	out << "Number Out";
	outputArr(out, numTasksOut);

	return;
}

/****************************************************************************
*																			*
*	Function:	outputArr													*
*																			*
*	Purpose:	To output the specified array								*
*																			*
****************************************************************************/

void Statistics::outputArr(ostream& out, const Matrix2D& arr) const 
{
	for (int i = 0; i < numRows; i++)
	{	
		if (i != numRows - 1)
			out << ", " << i << ", ";
		else
			out << ", Sum, ";
					
		for (int j = 0; j < numCols; j++)
			out << arr[i][j] << ", ";	
		 out << endl;
	}	
	
	return;
}

#endif