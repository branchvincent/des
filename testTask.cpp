#include <iostream>
#include <string>
#include "Task.h"
#include <random>

using namespace std;
char TYPE[] = {'A','B','C','D','E','F','G','H','I'};
int SEED = 1;

int main() 
{
	srand(SEED);

//	random_device rnd_dev;
//	std::mt19937 gen(rnd_dev());
//	
	for (int i = 0; i < 20; i++)
	{
		default_random_engine gen(rand());
		lognormal_distribution<float> dist(1, 1);
		cout << "Dist: " << dist(gen) << endl;
	}
		
//	for (int i = 0; i < 9; i++)
//	{
//		Task task(TYPE[i],0,rand());
//		cout << "Task " << i << ": " << task << endl;
//	}

	return 0;
}