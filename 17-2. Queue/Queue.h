#pragma once
#include <vector>
#include <deque>
#include <list>
#include <cassert>

template <typename T>
class CArrayQueue
{
private:
	T* arrayData;
	int capacity;
	int amount;

public:
	CArrayQueue(int size = 10);
	virtual ~CArrayQueue();

	T& back();
	bool empty();
	T& front();
	void pop();
	void push(const T& data);
	int size();
	bool isFull();
};

template <typename T>
class CCircularQueue
{
private:
	T* arrayData;
	int capacity;
	int frontIndex;
	int rearIndex;

public:
	CCircularQueue(int size = 10);
	virtual ~CCircularQueue();

	T& back();
	bool empty();
	T& front();
	void pop();
	void push(const T& data);
	int size();
	bool isFull();
};

template <typename T>
class CVectorQueue
{
private:
	std::vector<int> vecData;
public:
	void push(const T& data)
	{
		vecData.push_back(data);
	}
	T& front()
	{
		return vecData.front();
	}
	void pop()
	{
		vecData.erase(vecData.begin());
	}
};

template <typename T>
class CDeqequeQueue
{
private:
	std::deque<int> dequeData;
public:
	void push(const T& data)
	{
		dequeData.push_back(data);
	}
	T& front()
	{
		return dequeData.front();
	}
	void pop()
	{
		dequeData.pop_front();
	}
};

template <typename T>
class CListQueue
{
private:
	std::list<int> listData;
public:
	void push(const T& data)
	{
		listData.push_back(data);
	}
	T& front()
	{
		return listData.front();
	}
	void pop()
	{
		listData.pop_front();
	}
};

template<typename T>
CArrayQueue<T>::CArrayQueue(int size)
{
	arrayData = new T[size];
	capacity = size;
	amount = 0;
}

template<typename T>
CArrayQueue<T>::~CArrayQueue()
{
	delete[] arrayData;
}

template<typename T>
T& CArrayQueue<T>::back()
{
	if (empty())
		assert(0);

	return arrayData[amount - 1];
}

template<typename T>
bool CArrayQueue<T>::empty()
{
	return size() == 0;
}

template<typename T>
T& CArrayQueue<T>::front()
{
	if (empty())
		assert(0);

	return arrayData[0];
}

template<typename T>
void CArrayQueue<T>::pop()
{
	if (empty())
		return;

	for (int i = 1; i < amount; i++)
	{
		arrayData[i - 1] = arrayData[i];
	}
	amount--;
}

template<typename T>
void CArrayQueue<T>::push(const T& data)
{
	if (isFull())
		return;

	arrayData[amount] = data;
	amount++;
}

template<typename T>
int CArrayQueue<T>::size()
{
	return amount;
}

template<typename T>
bool CArrayQueue<T>::isFull()
{
	return amount == capacity;
}

template<typename T>
CCircularQueue<T>::CCircularQueue(int size)
{
	arrayData = new T[size + 1];
	capacity = size;
	frontIndex = 0;
	rearIndex = 0;
}

template<typename T>
CCircularQueue<T>::~CCircularQueue()
{
	delete[] arrayData;
}

template<typename T>
T& CCircularQueue<T>::back()
{
	if (empty())
		assert(0);

	if (rearIndex == 0)
		return arrayData[capacity];
	else
		return arrayData[rearIndex - 1];
}

template<typename T>
bool CCircularQueue<T>::empty()
{
	return frontIndex == rearIndex;
}

template<typename T>
T& CCircularQueue<T>::front()
{
	if (empty())
		assert(0);

	return arrayData[frontIndex];
}

template<typename T>
void CCircularQueue<T>::pop()
{
	if (empty())
		return;

	if (frontIndex < capacity)
		frontIndex++;
	else
		frontIndex = 0;
}

template<typename T>
void CCircularQueue<T>::push(const T& data)
{
	if (isFull())
		return;

	arrayData[rearIndex] = data;
	if (rearIndex < capacity)
		rearIndex++;
	else
		rearIndex = 0;
}

template<typename T>
int CCircularQueue<T>::size()
{
	if (frontIndex < rearIndex)
		return rearIndex - frontIndex;
	else
		return rearIndex + (capacity + 1 - frontIndex);
}

template<typename T>
bool CCircularQueue<T>::isFull()
{
	return size() == capacity;
}
