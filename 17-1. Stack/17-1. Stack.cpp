#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <deque>
#include <list>
#include "Stack.h"
#include "Vector.h"
#include "LinkedList.h"

using namespace std;

int main()
{
	CStack<int, vector<int>> vecStack;
	CStack<int, deque<int>> dequeStack;
	CStack<int, list<int>> listStack;
	CStack<int, CVector<int>> myVectorStack;
	CStack<int, CLinkedList<int>> myListStack;

	queue<int, CLinkedList<int>> myListQueue;
}
