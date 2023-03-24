#include <iostream>
#include <queue>
#include <random>
#include <ctime>
#include <utility>
#include "PriorityQueue.h"

using namespace std;

int main()
{
	priority_queue<int> pq;
	// CPriorityQueue<int, vector<int>, CAbsoluteLess<int>> pq;

	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int random = rand() % 200 - 100;
		pq.push(random);
		cout << random << " ";
	}

	cout << endl << endl;

	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
}