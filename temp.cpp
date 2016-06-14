// Priority queue testing

#include <string>
#include <queue>
#include <iostream>
#include "Task.h"

using namespace std; 

bool compare(Task* t1, Task* t2) 
	{return t1->getPriority() < t2->getPriority();}

int main()
{
	priority_queue<Task*,vector<Task*>,decltype(&compare)> pq(&compare); 
	Task* A = new Task('A',0,1); pq.push(A);
	Task* B = new Task('B',0,1); pq.push(B);
	Task* C = new Task('C',0,1); pq.push(C);
	Task* A2 = new Task('A',0,2); pq.push(A2);

	while (!pq.empty()) 
	{
	   cout << *pq.top() << endl;
	   pq.pop();
	}

	return 0;
}