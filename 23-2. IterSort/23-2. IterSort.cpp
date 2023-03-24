#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <utility>
#include <random>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;

template <typename Iter, typename Compare>
void iterSort(Iter begin, Iter end, Compare comp)
{
	while (begin != end)
	{
		Iter iter_minimum = begin;
		Iter iter_loop = begin;
		while (iter_loop != end)
		{
			if (comp(*iter_loop, *iter_minimum))
				iter_minimum = iter_loop;
			iter_loop++;
		}
		swap(*begin, *iter_minimum);

		begin++;
	}
}

template <typename T>
void printVec(vector<T> vecData)
{
	for (int i = 0; i < vecData.size(); i++)
	{
		cout << " " << vecData[i] << " ";
	}
	cout << endl;
}

template <typename T>
void printDeq(deque<T> deque)
{
	for (int i = 0; i < deque.size(); i++)
	{
		cout << " " << deque[i] << " ";
	}
	cout << endl;
}

template <typename T>
void printList(list<T> listData)
{
	for (list<int>::iterator iter = listData.begin(); iter != listData.end(); iter++)
	{
		cout << " " << *iter << " ";
	}
	cout << endl;
}

int main()
{
	srand((unsigned int)time(NULL));

	vector<int> intVec;
	deque<int> intDeq;
	list<int> intList;

	for (int i = 0; i < 20; i++)
	{
		int random = rand() % 100;
		cout << random << " ";

		intVec.push_back(random);
		intDeq.push_back(random);
		intList.push_back(random);
	}
	cout << endl;

	cout << "양방향 iterator를 이용한 less 정렬" << endl;
	iterSort(intVec.begin(), intVec.end(), less<>());
	printVec(intVec);
	iterSort(intDeq.begin(), intDeq.end(), less<>());
	printDeq(intDeq);
	iterSort(intList.begin(), intList.end(), less<>());
	printList(intList);

	cout << "양방향 iterator를 이용한 greater 정렬" << endl;
	iterSort(intVec.begin(), intVec.end(), greater<>());
	printVec(intVec);
	iterSort(intDeq.begin(), intDeq.end(), greater<>());
	printDeq(intDeq);
	iterSort(intList.begin(), intList.end(), greater<>());
	printList(intList);

	cout << "알고리즘 STL을 이용한 less 정렬" << endl;
	sort(intVec.begin(), intVec.end(), less<>());
	printVec(intVec);
	intList.sort(less<>());
	printList(intList);
}