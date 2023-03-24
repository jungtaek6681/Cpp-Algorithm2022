#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

int main()
{
	vector<int>	intVec;
	list<int>	intList;
	set<int>	intSet;

	for (int i = 0; i < 5; i++)
	{
		intVec.push_back(i);
		intList.push_back(i);
		intSet.insert(i);
	}

	cout << "intVec = ";
	for (vector<int>::iterator iter = intVec.begin();
		iter != intVec.end(); iter++)
	{
		cout << *iter << " ";
	}

	cout << "intList = ";
	for (list<int>::iterator iter = intList.begin();
		iter != intList.end(); iter++)
	{
		cout << *iter << " ";
	}

	cout << "intSet = ";
	for (set<int>::iterator iter = intSet.begin();
		iter != intSet.end(); iter++)
	{
		cout << *iter << " ";
	}
}