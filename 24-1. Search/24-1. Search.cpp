#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

using namespace std;

template <typename T, typename Iter>
Iter iterFind(Iter first, Iter last, const T& value)
{
	for (Iter iter = first; iter != last; iter++)
	{
		if (value == *iter)
		{
			return iter;
		}
	}

	return last;
}

int main()
{
	vector<int> intVec;
	list<int> intList;
	set<int> intSet;

	intVec.push_back(10);
	intList.push_back(20);
	intSet.insert(30);

	vector<int>::iterator vecIter = find(intVec.begin(), intVec.end(), 10);
	list<int>::iterator listIter = find(intList.begin(), intList.end(), 10);
	set<int>::iterator setIter = find(intSet.begin(), intSet.end(), 10);
	intSet.find(10);

	if (vecIter != intVec.end())
	{
		cout << "백터 안에 10이 있다" << endl;
	}
	else
	{
		cout << "백터 안에 10이 없다" << endl;
	}

	if (listIter != intList.end())
	{
		cout << "리스트 안에 10이 있다." << endl;
	}
	else
	{
		cout << "리스트 안에 10이 없다." << endl;
	}
}