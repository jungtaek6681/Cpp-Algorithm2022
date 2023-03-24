#include <iostream>
#include "LinkedList.h"

using namespace std;

int main()
{
	CLinkedList<int> myList;
	for (int i = 0; i < 5; i++)
	{
		myList.push_back(i);
	}

	CLinkedList<int>::iterator iter = myList.begin();
	iter++;

	myList.insert(iter, 100);

	for (CLinkedList<int>::iterator iter = myList.begin();
		iter != myList.end(); iter++)
	{
		cout << *iter << " ";
	}

	cout << endl;
	myList.erase(myList.begin());
	for (CLinkedList<int>::iterator iter = myList.begin();
		iter != myList.end(); iter++)
	{
		cout << *iter << " ";
	}
}