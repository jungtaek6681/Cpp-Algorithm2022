#pragma once
#include <deque>

template <typename T, typename Container = std::deque<T>>
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

template <typename T, typename Container = std::deque<T>>
class CQueue
{
private:
	Container container;

public:
	void push(const T& data)
	{
		container.push_back(data);
	}
	T& front()
	{
		return container.front();
	}
	void pop()
	{
		container.pop_front();
	}
};