#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <utility>
#include <algorithm>

using namespace std;

void selectionSort(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		int index_minimum = i;
		for (int j = i + 1; j < vec.size(); j++)
		{
			if (vec[j] < vec[index_minimum]) index_minimum = j;
		}
		swap(vec[i], vec[index_minimum]);
	}
}

void insertionSort(vector<int>& vec)
{
	for (int i = 1; i < vec.size(); i++)
	{
		int key = vec[i];
		int j;
		for (j = i - 1; j >= 0 && key < vec[j]; j--)
		{
			swap(vec[j], vec[j + 1]);
		}
		vec[j + 1] = key;
	}
}

void bubbleSort(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 1; j < vec.size(); j++)
		{
			if (vec[j - 1] > vec[j])
				swap(vec[j - 1], vec[j]);
		}
	}
}

void merge(vector<int>& vec, int left, int mid, int right)
{
	vector<int> sorted;
	int index_left = left;
	int index_right = mid + 1;

	// 분할 정렬된 Vector를 병합
	while (index_left <= mid && index_right <= right)
	{
		if (vec[index_left] < vec[index_right])
			sorted.push_back(vec[index_left++]);
		else
			sorted.push_back(vec[index_right++]);
	}

	if (index_left > mid)	// 왼쪽 배열이 먼저 소진 됐을 경우
	{
		// 오른쪽 배열을 모두 복사
		for (int i = index_right; i <= right; i++)
		{
			sorted.push_back(vec[i]);
		}
	}
	else // 오른쪽 배열이 먼저 소진 됐을 경우
	{
		// 왼쪽 배열을 모두 복사
		for (int i = index_left; i <= mid; i++)
		{
			sorted.push_back(vec[i]);
		}
	}

	// 정렬된 배열 sorted를 vec 배열로 재복사
	for (int i = left; i <= right; i++)
	{
		vec[i] = sorted[i - left];
	}
}

void mergeSort(vector<int>& vec, int left, int right)
{
	if (left == right) return;

	int mid = (left + right) / 2;
	mergeSort(vec, left, mid);
	mergeSort(vec, mid + 1, right);
	merge(vec, left, mid, right);
}

void quickSort(vector<int>& vec, int start, int end)
{
	if (start >= end) return;

	int index_quick = start;
	int index_left = index_quick + 1;
	int index_right = end;

	while (index_left <= index_right) // 엇갈릴때까지 반복
	{
		// quick보다 큰 값을 만날때까지
		while (vec[index_left] <= vec[index_quick] && index_left < end)
			index_left++;
		// quick보다 작은 값을 만날때까지
		while (vec[index_right] >= vec[index_quick] && index_right > start)
			index_right--;
		// 엇갈리지 않았다면
		if (index_left < index_right)
			swap(vec[index_left], vec[index_right]);
		// 엇갈렸다면
		else
			swap(vec[index_quick], vec[index_right]);
	}

	quickSort(vec, start, index_right - 1);
	quickSort(vec, index_right + 1, end);
}

void printVector(vector<int>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
}

int main()
{
	srand((unsigned int)time(NULL));

	vector<int> selectionVector;	// 선택정렬 : 가장 왼쪽부터 제일 작은 자료를 넣기
	vector<int> insertionVector;	// 삽입정렬 : 가장 왼쪽부터 배열을 늘려가면서(중간에 끼워넣으면서)
	vector<int> bubbleVector;		// 버블정렬 : 인접한 두 요소 중 큰 값을 오른쪽으로 교환해서
	vector<int> mergeVector;		// 병합정렬 : 배열을 2분할(1가 될때까지), 합치면서 정렬 / 분할정복
	vector<int> quickVector;		// 퀵정렬 : 기준(퀵)으로 작은 것은 왼쪽, 큰 것은 오른쪽

	for (int i = 0; i < 20; i++)
	{
		int random = rand() % 100;

		cout << random << " ";

		selectionVector.push_back(random);
		insertionVector.push_back(random);
		bubbleVector.push_back(random);
		mergeVector.push_back(random);
		quickVector.push_back(random);
	}
	cout << endl;

	// 선형 정렬
	// 1개의 요소를 재위치시키기 위해 전체를 훑어야 하는 정렬
	// n개의 요소를 재위치시키기 위해서는 n개를 훑어야 하는 정렬
	// O(N^2)
	cout << "선택 정렬 후 데이터" << endl;
	selectionSort(selectionVector);
	printVector(selectionVector);

	cout << "삽입 정렬 후 데이터" << endl;
	insertionSort(insertionVector);
	printVector(insertionVector);

	cout << "버블 정렬 후 데이터" << endl;
	bubbleSort(bubbleVector);
	printVector(bubbleVector);

	// 분할정복 정렬
	// 1개의 요소를 재위치시키기 위해 전체의 1/2를 훑어야 하는 정렬
	// n개의 요소를 재위치시키기 위해서는 n/2개를 훑어야 하는 정렬
	// O(NlogN);
	cout << "병합 정렬 후 데이터" << endl;
	mergeSort(mergeVector, 0, mergeVector.size() - 1);
	printVector(mergeVector);

	cout << "퀵 정렬 후 데이터" << endl;
	quickSort(quickVector, 0, quickVector.size() - 1);
	printVector(quickVector);
}