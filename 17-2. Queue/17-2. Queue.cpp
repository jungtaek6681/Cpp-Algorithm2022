#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <deque>
#include <list>

using namespace std;

int main()
{
	stack<int> testStack;
	testStack.push(0);	// 0
	testStack.push(1);	// 0, 1
	testStack.pop();	// 0
	testStack.push(2);	// 0, 2
	testStack.pop();	// 0

	queue<int> testQueue;
	testQueue.push(0);	// 0
	testQueue.push(1);	// 0, 1
	testQueue.pop();	// 1
	testQueue.push(2);	// 1, 2
	testQueue.pop();	// 2

	stack<int, vector<int>> vecStack;
	stack<int, deque<int>> deqStack;
	stack<int, list<int>> listStack;

	queue<int, deque<int>> deqQueue;
	queue<int, list<int>> listQueue;
}
