#pragma once
#include <vector>

template <typename T>
class CLess
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};

template <typename T>
class CGreater
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template <typename T, typename Container = std::vector<T>, typename Compare = CLess<T>>
class CPriorityQueue
{
private:
	Container container;
	Compare comp;

	void swap(T& left, T& right)
	{
		T temp = left;
		left = right;
		right = temp;
	}

	void popHeap()
	{
		// 1. 최 우측의 노드를 최상단 노드와 교체하고 최 우측 노드를 제거
		swap(container.front(), container.back());
		container.pop_back();
		// 2. 자식 노드들과 비교하여 더 작은 값의 자식노드와 비교하고 교체
		int curIndex = 0;

		while (curIndex < container.size())
		{
			int leftChildIndex = curIndex * 2 + 1;
			int rightChildIndex = curIndex * 2 + 2;

			if (leftChildIndex < container.size() && rightChildIndex < container.size())
			{
				// 노드가 둘다 있는 경우
				int lessIndex =
					comp(container[leftChildIndex], container[rightChildIndex]) ?
					leftChildIndex :
					rightChildIndex;

				//if (container[curIndex] > container[lessIndex])
				if (comp(container[lessIndex], container[curIndex]))
				{
					swap(container[curIndex], container[lessIndex]);
					curIndex = lessIndex;
				}
				else
				{
					break;
				}
			}
			else if (leftChildIndex < container.size() && rightChildIndex >= container.size())
			{
				// 왼쪽 자식 노드만 있는 경우
				//if (container[curIndex] > container[leftChildIndex])
				if (comp(container[leftChildIndex], container[curIndex]))
				{
					swap(container[curIndex], container[leftChildIndex]);
					curIndex = leftChildIndex;
				}
				else
				{
					break;
				}
			}
			else
			{
				// 노드가 둘다 없는 경우
				break;
			}
		}
		// 3. 2번 과정을 반복
	}
	void pushHeap(const T& data)
	{
		// 1. 힙의 최 우측에 새 노드를 추가
		container.push_back(data);
		int curIndex = container.size() - 1;
		while (curIndex > 0)
		{
			// 2. 삽입한 노드가 부모랑 비교해서
			int parentIndex = (curIndex - 1) / 2;
			// 2-1. 더 작으면 교체
			//if (container[curIndex] < container[parentIndex])
			if (comp(container[curIndex], container[parentIndex]))
			{
				swap(container[curIndex], container[parentIndex]);
				curIndex = parentIndex;
			}
			// 2-2. 더 크면 끝
			else
			{
				break;
			}
		}
		// 3. 교체한 부모를 기준으로 다시 진행
	}

public:
	CPriorityQueue() {}
	virtual ~CPriorityQueue() {}

	bool empty()
	{
		return container.empty();
	}
	void pop()
	{
		popHeap();
	}
	void push(const T& data)
	{
		pushHeap(data);
	}
	int size()
	{
		return container.size();
	}
	const T& top()
	{
		return container.front();
	}
};