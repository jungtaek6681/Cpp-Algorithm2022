#include <iostream>
#include <random>
#include <ctime>
#include "RedBlackTree.h"
#include "BinarySearchTree.h"

using namespace std;

int main()
{
	CBinarySearchTree<int> myBST;
	CRedBlackTree<int> myRBT;

	for (int i = 0; i < 50; i++)
	{
		myBST.insert(i);
		myRBT.insert(i);
	}

	myBST.printAll();
	myRBT.printAll();

	myBST.clear();
	myRBT.clear();
}
