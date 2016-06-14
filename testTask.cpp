#include <iostream>
#include <string>
#include "Task.h"

using namespace std;

int main() 
{
	Task t('B',0,1);
	cout << t << endl;
	t.setSerTime(200);
	cout << t << endl;
	
	for (int i = 0; i < 4900000; i++)
		Task ('A',0,1);

	return 0;
}