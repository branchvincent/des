#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;

int main() 
{
	Simulation sim(100);		// 43200						
	sim.run();
	sim.outputData("/Users/Branch/Desktop/run1.csv");
	
	return 0;
}