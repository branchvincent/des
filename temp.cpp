// Priority queue testing

#include <string>
#include <queue>
#include <iostream>
#include "Task.h"

using namespace std; 

bool compare(Task* t1, Task* t2) 
	{return t1->getPriority() > t2->getPriority();}

int main()
{
	priority_queue<Task*,vector<Task*>,decltype(&compare)> pq(&compare); 
	Task* A = new Task(0,0,1,0); pq.push(A);
	Task* B = new Task(1,0,1,0); pq.push(B);
	Task* C = new Task(2,0,1,0); pq.push(C);
	Task* A2 = new Task(0,0,2,0); pq.push(A2);

	while (!pq.empty()) 
	{
	   cout << *pq.top() << endl;
	   pq.pop();
	}

	return 0;
}