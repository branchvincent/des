#include <iostream>
#include <string>
#include "Task.h"

using namespace std;

int main() 
{
	Task t('B',1);
	cout << t << endl;
	t.setSerTime(200);
	cout << t << endl;

	return 0;
}