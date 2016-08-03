/****************************************************************************
 *																			*
 *	File:		NewParams.h                                                 *
 *																			*
 *	Author:		Branch Vincent												*
 *																			*
 *	Date:		Jul 12, 2016												*
 *																			*
 *	Purpose:	This file defines the NewParams class.                      *
 *																			*
 ****************************************************************************/

#ifndef NEWPARAMS_H
#define NEWPARAMS_H

#include <iostream>
#include <string>

using namespace std;

/****************************************************************************
*																			*
*	Definition of NewParams class                                           *
*																			*
****************************************************************************/

class NewParams
{
//	Public member functions
    
    public:
    
    //	Constructor
    
        NewParams(string paramFile);
    
    //	Inspectors
    
        string getOutPath() {return outPath;}
        int getNumHours() {return numHours;}
        vector<float> getTraffic() {return traffic;}
        int getNumReps() {return numReps;}
    
//	Data members
    
    public:
        string outPath;
        int numHours;
        vector<float> traffic;
        int numReps;
};

/****************************************************************************
*																			*
*	Function:	NewParams                                                   *
*																			*
*	Purpose:	To construct new parameters                                 *
*																			*
****************************************************************************/

NewParams::NewParams(string paramFile) :
    outPath("/Users/Branch/Documents/Academic/Year 1/Summer/DES Code/DES/Input/params.txt"),
    numHours(12),
    traffic(numHours),
    numReps(100)
{
//  Open parameter file
    
    cout << "Input parameter file location: " << paramFile <<endl;
    
    fstream fin(paramFile);
    
    if (!fin)
    {
        cerr << "Error: Cannot open parameter file. Exiting..." << endl;
        exit(1);
    }
    
//	Read in output file path

    string paramName;
    char tab;
    fin >> paramName;
    fin >> tab >> tab;
    cout << "Tab = " << tab << endl;
    getline(cin, outPath);
    
//  Read in number of hours
    
    fin >> paramName >> numHours;
    
//  Read in traffic
    
    char paramChar;
    fin >> paramName;
    
    for (int i = 0; i < numHours; i++)
    {
        fin >> paramChar;
        
        switch (paramChar)
        {
            case 'l': traffic.push_back(0.5); break;
            case 'm': traffic.push_back(1); break;
            case 'h': traffic.push_back(2); break;
            default: break;
        }
    }
    
//	Read in number of replications
    
    cin >> paramName >> numReps;
    
    return;
}

#endif