#pragma once
#include <vector>
#include <deque>
#include <list>
#include <cassert>

template <typename T>
class CArrayStack
{
private:
	T* arrayData;
	int capacity;
	int topIndex;

public:
	CArrayStack(int size = 10);
	virtual ~CArrayStack();

	bool empty();
	void pop();
	void push(const T& data);
	int size();
	T& top();
	bool isFull();
};

template <typename T>
class CVectorStack
{
private:
	std::vector<T> vecData;

public:
	void push(const T& data)
	{
		vecData.push_back(data);
	}
	T& top()
	{
		return vecData.back();
	}
	void pop()
	{
		vecData.pop_back();
	}
};

template <typename T>
class CDequeStack
{
private:
	std::deque<T> dequeData;

public:
	void push(const T& data)
	{
		dequeData.push_back(data);
	}
	T& top()
	{
		return dequeData.back();
	}
	void pop()
	{
		dequeData.pop_back();
	}
};

template <typename T>
class CListStack
{
private:
	std::list<T> listData;

public:
	void push(const T& data)
	{
		listData.push_back(data);
	}
	T& top()
	{
		return listData.back();
	}
	void pop()
	{
		listData.pop_back();
	}
};

template<typename T>
CArrayStack<T>::CArrayStack(int size)
{
	arrayData = new T[size];
	capacity = size;
	topIndex = -1;
}

template<typename T>
CArrayStack<T>::~CArrayStack()
{
	delete[] arrayData;
}

template<typename T>
bool CArrayStack<T>::empty()
{
	return size() == 0;
}

template<typename T>
void CArrayStack<T>::pop()
{
	if (empty())
		return;

	topIndex--;
}

template<typename T>
void CArrayStack<T>::push(const T& data)
{
	if (isFull())
		return;

	topIndex++;
	arrayData[topIndex] = data;
}

template<typename T>
int CArrayStack<T>::size()
{
	return topIndex + 1;
}

template<typename T>
T& CArrayStack<T>::top()
{
	if (empty())
		assert(0);

	return arrayData[topIndex];
}

template<typename T>
bool CArrayStack<T>::isFull()
{
	return topIndex + 1 >= capacity;
}

template <typename T, typename Container>
class CStack
{
private:
	Container container;

public:
	void push(const T& data)
	{
		container.push_back(data);
	}
	T& top()
	{
		return container.back();
	}
	void pop()
	{
		container.pop_back();
	}
};