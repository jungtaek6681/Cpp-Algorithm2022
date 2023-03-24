#include <iostream>
#include <set>
#include <map>
#include <utility>
#include "BinarySearchTree.h"

using namespace std;

int main()
{
	CBinarySearchTree<int> myTree;

	for (int i = 0; i < 10; i++)
	{
		myTree.insert(i);
		myTree.insert(20 - i);
	}

	myTree.erase(5);
	myTree.erase(11);
	myTree.erase(19);
	myTree.erase(3);

	for (CBinarySearchTree<int>::iterator iter = myTree.begin();
		iter != myTree.end();
		iter++)
	{
		cout << *iter << " ";
	}
}