#include <iostream>
#include "CQueue.h"
#include "CCircleQueue.h"

using namespace std;

int main()
{
	CQueueList<int> Q;

	cout << "*****List Queue*****" << endl << endl;

	for (int i = 0; i < 10; i++)
	{
		Q.push(i);
	}
	Q.printQueue();

	cout << "Queue Pop [ ";
	for (int i = 0; i < 10; i++)
	{
		cout << Q.pop() << " ";
	}
	cout << "]" << endl << endl;
	Q.printQueue();

	cout << "*****Circle Queue*****" << endl << endl;

	CCircleQueue<int, 10> C_Q;

	for (int j = 0; j < 10; j++)
	{
		C_Q.push(j);
	}
	C_Q.printQueue();

	cout << endl << "Pop [ ";
	for (int j = 0; j < 5; j++)
	{
		cout << C_Q.pop() << " ";
	}
	cout << "]" << endl << endl;

	C_Q.printQueue();

	cout << "Push [ 10 11 12 13 14]" << endl << endl;
	for (int j = 10; j < 15; j++)
	{
		C_Q.push(j);
	}
	C_Q.printQueue();

	return 0;
}