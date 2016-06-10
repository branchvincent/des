#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;

int main() 
{
	string file = "/Users/Branch/Desktop/run1.csv";
	Simulation sim(200);
	sim.run();
	sim.outputData(file);
	
	return 0;
}