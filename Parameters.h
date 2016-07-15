/****************************************************************************
*																			*
*	File:		Parameters.h                                                *
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 12, 2016												*
*																			*
*	Purpose:	This file defines the Parameters class.                     *
*																			*
****************************************************************************/

#ifndef Parameters_H
#define Parameters_H

#include <iostream>
#include <string>

using namespace std;

/****************************************************************************
*																			*
*	Definition of Parameters class                                          *
*																			*
****************************************************************************/

class Parameters
{
//	Public member functions

	public:

	//	Constructor
		
		Parameters(string paramFile);

	//	Inspectors
    
        string getOutFile() {return outFile;}
        vector<float> getTraffic() {return traffic;}
        float getParam(int i) {return params[i];}
	
//	Data members

	public:
        string outFile;
        vector<float> traffic;
        vector<float> params;
};

/****************************************************************************
*																			*
*	Function:	Parameters                                                  *
*																			*
*	Purpose:	To construct new parameters                                 *
*																			*
****************************************************************************/

Parameters::Parameters(string paramFile)
{
//  Open parameter file
    
    fstream fin(paramFile);
    
    if (!fin)
    {
        cerr << "Error: Cannot open parameter file. Exiting..." << endl;
        exit(1);
    }
    
//  Initialize variables
    
    char paramChar;
    float paramVal;
    string paramName;
    
//	Read in output file
    
    fin >> paramName >> outFile;
    
//  Read in number of hours
    
    fin >> paramName >> paramVal;
    params.push_back(paramVal);
    
//  Read in traffic
    
    fin >> paramName;
    for (int i = 0; i < params[0]; i++)
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
    
//	Read in rest of parameters
    
    while (fin >> paramName >> paramVal)
        params.push_back(paramVal);
    
    return;
}

#endif