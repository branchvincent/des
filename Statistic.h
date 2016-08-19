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
#include <cmath>

using namespace std;

//  Type definitions

template <typename T>
using Matrix2D = vector<vector<T> >;
template <typename T>
using Matrix3D = vector<Matrix2D<T> >;

/****************************************************************************
*																			*
*	Definition of Statistic class											*
*																			*
****************************************************************************/

// Notes
// - Assert for positive dimensions

class Statistic
{
//	Public member functions

	public:
		
	//	Constructor
	
        Statistic(string nm, int xDim, int yDim, int zDim) :
            name(nm),
            data(xDim + 1, Matrix2D<float>(yDim + 1, vector<float>(zDim, 0))),
            avgs(xDim + 1, vector<float>(yDim + 1, 0)),
            devs(xDim + 1, vector<float>(yDim + 1, 0)) {}

	//	Mutators

        void incData(int i, int j, int k, float val);
        void avgData();

	//	Other member functions

//        void output(ostream& out) const {outputSim(out); return;}
        void outputRep(ostream& out, int rep) const;
        void outputSim(ostream& out) const;

//	Private member functions

//	private:

//	Data members

	private:
        string name;			// stat name
		Matrix3D<float> data;	// stat data
        Matrix2D<float> avgs;	// sim averages
        Matrix2D<float> devs;	// sim std devs
};

//	Operators

//ostream& operator<<(ostream& out, const Statistic& stat) {stat.output(out); return out;}

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
    
    int rowSum = (int)data.size() - 1;
    int colSum = (int)data[i].size() - 1;
    
//  Increment replication sums
    
    data[i][j][k] += val;
    data[rowSum][j][k] += val;			// row sum
    data[i][colSum][k] += val;			// col sum
    data[rowSum][colSum][k] += val;     // row + col sum
    
//  Increment simulation sums
    
//    avg[i][j] += val;
//    avg[rowSum][j] += val;          // avg row sum
//    avg[i][colSum] += val;          // avg col sum
//    avg[rowSum][colSum] += val;     // avg row + col sum
    
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
*	Function:	outputSim                                                   *
*																			*
*	Purpose:	To output the data averaged across all replications         *
*																			*
****************************************************************************/

void Statistic::outputSim(ostream& out) const
{
//	Output stat name
    
    out << name;
    
//	Output data
    
    for (int i = 0; i < avgs.size(); i++)
    {
    //	Output task type
        
        if (i != data.size() - 1)
            out << ", " << i;
        else
            out << ",Sum";
        
    //	Output averages
        
        for (int j = 0; j < avgs[i].size() - 1; j++)
            out << ", " << avgs[i][j];
        out << endl << ", ";
        
    //  Output std devs
        
        for (int j = 0; j < devs[i].size() - 1; j++)
            out << ", " << devs[i][j];
        out << endl;
    }
    
    return;
}

/****************************************************************************
*																			*
*	Function:	avgData                                                     *
*																			*
*	Purpose:	To calculate and store the mean and standard deviation for  *
*				the specified array	across all replications					*
*																			*
****************************************************************************/

void Statistic::avgData()
{
//	Initialize variables
    
    int N = 0;
    float mean = 0;
    float devSum = 0;
    float delta;
    
//  Calculate mean and std dev across all replications
    
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size(); j++)
        {
        //  Reset variables
            
            N = 0;
            mean = 0;
            devSum = 0;
            
        //  Calculate values using Welford's algorithm
            
            for (int k = 0; k < data[i][j].size(); k++)
            {
                N++;
                delta = data[i][j][k] - mean;
                mean += delta/N;
                devSum += delta * (data[i][j][k] - mean);
            }
            
        //  Store values
            
            avgs[i][j] = mean;
            devs[i][j] = sqrt(devSum / (N - 1));
        }
    }
    
    return;           
}

#endif