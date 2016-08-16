/****************************************************************************
*																			*
*	File:		Statistic.h                                                 *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Aug 10, 2016												*
*																			*
*	Purpose:	This file defines the Statistic class.						*
*																			*
****************************************************************************/

#ifndef STATISTIC_H
#define STATISTIC_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef vector<vector<float> > Matrix2D;
typedef vector<Matrix2D> Matrix3D;

/****************************************************************************
*																			*
*	Definition of Statistic class											*
*																			*
****************************************************************************/

class Statistic
{
//	Public member functions

	public:
		
	//	Constructor
	
        Statistic(string nm, int xDim, int yDim, int zDim) :
            name(nm),
            stat(xDim + 1, Matrix2D(yDim + 1, vector<float>(zDim, 0)))
            avgs(xDim + 1, vector<float>(yDim + 1, 0)),
            devs(xDim + 1, vector<float>(yDim + 1, 0)) {}

	//	Mutators

        void incData(int i, int j, int k, float val);
		void endRep();

	//	Other member functions

        void output(ostream& out) const {outputAvg(out); return;}
        void outputRep(ostream& out, int rep) const;
        void outputAvgs(ostream& out) const;

//	Private member functions

	private:
        void endSim(); // necessary?
        void setMeanAndStdDev(Matrix3D& data);

//	Data members

	private:
        string name;    // stat name
		Matrix3D data;	// stat data
        Matrix2D avgs;  // averages
        Matrix2D devs;  // std devs
};

//	Operators

ostream& operator<<(ostream& out, const Statistic& stat) {stat.output(out); return out;}

/****************************************************************************
*																			*
*	Function:	incData														*
*																			*
*	Purpose:	To increment the data based on the specified indices and    *
*               value                                                       *
*																			*
****************************************************************************/

void Statistic::incData(int i, int j, int k, float val)
{
//	Calculate indices for the last row/column
    
    int lastRow = data.size() - 1;
    int lastCol = data[i].size() - 1;
    
//  Increment replication sums
    
    data[i][j][k] += val;
    data[lastRow][j][k] += val;			// row sum
    data[i][lastCol][k] += val;			// col sum
    data[lastRow][lastCol][k] += val; 	// row + col sum
    
//  Increment average sums
    
    avg[i][j] += val;
    avg[lastRow][j] += val;             // avg row sum
    avg[i][lastCol] += val;             // avg col sum
    avg[lastRow][lastCol] += val;       // avg row + col sum
    
    return;
}

/****************************************************************************
*																			*
*	Function:	outputRep                                                   *
*																			*
*	Purpose:	To output the data for the specified replication            *
*																			*
****************************************************************************/

void Statistic::outputRep(ostream& out, int rep) const
{
//	Output name
    
    out << name;
    
//	Output data
    
    for (int i = 0; i < data.size(); i++)
    {
    //	Output task type
        
        if (i != data.size() - 1)
            out << ", " << i;
        else
            out << ", Sum";
        
    //	Output data
        
        for (int j = 0; j < data[i].size(); j++)
            out << ", " << data[i][j][rep];
        out << endl;
    }	
    
    return;
}

/****************************************************************************
*																			*
*	Function:	outputAvgs                                                  *
*																			*
*	Purpose:	To output the data averaged across all replications         *
*																			*
****************************************************************************/

void Statistic::outputAvgs(ostream& out) const
{
//	Output stat name
    
    out << arrName;
    
//	Output stat
    
    for (int i = 0; i < avgs.size(); i++)
    {
    //	Output task type
        
        out << ", " << i;
        
    //	Output averages
        
        for (int j = 0; j < avgs[i].size(); j++)
            out << ", " << avgs[i][j];
        out << endl << ", ";
        
    //  Output std devs
        
        for (int j = 0; j < devs[i].size(); j++)
            out << ", " << devs[i][j];
        out << endl;
    }
    
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

void Statistic::setMeanAndStdDev(Matrix3D& arr)
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