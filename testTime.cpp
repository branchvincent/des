#include <iostream>
#include <string>
#include "Time.h"

using namespace std;

int main() 
{
	Time t(3);
	int time = t.get();
	cout << time << endl;
	
	return 0;
}