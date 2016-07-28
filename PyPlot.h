/****************************************************************************
*																			*
*	File:		PyPlot.cpp													*
*																			*
*	Author:		Branch Vincent												*
*																			*
*	Date:		Jul 27, 2016												*
*																			*
*	Purpose:	This file is a wrapper for calling matplotlib in Python 	*
*																			*
****************************************************************************/

#ifndef PYPLOT_H
#define PYPLOT_H

#include <iostream>
#include <string>
#include "Python.h"

using namespace std;
using namespace cnsts;

class PyPlot
{
//  Public member functions
    
    public:
    
    //  Constructor
    
        PyPlot()
        {
            _pythoncmd = "";
//            Py_Initialize(); // Might already have been called?
            run("import matplotlib.pyplot as plt");
            run("plt.clf()");
        }
    
    //  Destructor
        
        ~PyPlot()
        {
//            Py_Finalize();
            cout << "- Python plot command:\n";
            cout << _pythoncmd;
        }

    //  Mutators
    
        void set_title(string title) {run("plt.title('" + title + "')");}
        void set_xlabel(string xlabel) {run("plt.xlabel('" + xlabel + "')");}
        void set_ylabel(string ylabel) {run("plt.ylabel('" + ylabel + "')");}
        void set_xlim(float min, float max) {run("plt.xlim(" + to_string(min) + ", " + to_string(max) + ")");}
        void set_ylim(float min, float max) {run("plt.ylim(" + to_string(min) + ", " + to_string(max) + ")");}
        void set_axis() {run("ax = plt.gca()");}
//        void set_legend() {}
        
        void save_fig(string outputFile) {run("plt.savefig('" + outputFile + "')");}
    
        void plot_bar(vector<float> x, vector<float> y, vector<float> yerr)
        {
            string xPts;
            string yPts;
            string yerrPts;
            
            for (int i = 0; i < x.size(); i++)
            {
            //  Insert comma
                
                if (i != 0)
                {
                    xPts += ",";
                    yPts += ",";
                    yerrPts += ",";
                }
            
            //  Add to list
                
                xPts += to_string(x[i]);
                yPts += to_string(y[i]);
                yerrPts += to_string(yerr[i]);
            }
            
            run("plt.bar([" + xPts + "], "
                         "[" + yPts + "], "
                         "width = " + to_string(INT_SIZE/2) + ", "
                         "color = 'r', "
//                         "bottom = np.sum(), "
                         "linewidth = 0.1, "
                         "align = 'center', "
                         "yerr = [" + yerrPts + "])");
        }


        void run_cmd(string command) {run(command);}
    
    private:
        string _pythoncmd;
        void run(string cmdString) {PyRun_SimpleString(cmdString.c_str());_pythoncmd += "\n" + cmdString;}
};

#endif