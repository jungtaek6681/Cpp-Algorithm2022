#pragma once

template <typename T>
struct Node
{
	T			m_data;
	Node<T>* pPrev;
	Node<T>* pNext;
};

template <typename T>
class CLinkedList
{
private:
	Node<T>* pHeadNode;
	Node<T>* pTailNode;
	unsigned int m_size;

public:
	CLinkedList();
	virtual ~CLinkedList();

	class iterator
	{

	};

	void push_front(const T& data);
	void pop_front();
	void push_back(const T& data);
	void pop_back();

	int size();
	bool empty();
	void clear();
};

template <typename T>
CLinkedList<T>::CLinkedList()
{
	pHeadNode = nullptr;
	pTailNode = nullptr;
	m_size = 0;
}

template <typename T>
CLinkedList<T>::~CLinkedList()
{
	clear();
}

template <typename T>
void CLinkedList<T>::push_front(const T& data)
{
	if (m_size > 0)
	{
		// 1. 새로운 노드를 만든다.
		Node<T>* newNode = new Node<T>();
		// 2. 노드에 데이터 넣기
		newNode->m_data = data;
		// 3. 새로운 노드의 다음 데이터를 처음 노드로 지정한다.
		newNode->pNext = pHeadNode;
		// 4. 처음 노드의 이전 데이터를 새로운 노드로 지정한다.
		pHeadNode->pPrev = newNode;
		// 5. 처음 노드를 새로운 노드로 지정한다.
		pHeadNode = newNode;
	}
	else
	{
		// 1 .새로운 노드를 만든다.
		Node<T>* newNode = new Node<T>();
		// 2. 노드에 데이터 넣기
		newNode->m_data = data;
		// 3. 처음 노드를 새로운 노드로 지정해준다.
		pHeadNode = newNode;
		// 4. 마지막 노드도 새로운 노드로 지정해준다.
		pTailNode = newNode;
	}

	m_size++;
}

template <typename T>
void CLinkedList<T>::pop_front()
{
	if (0 == m_size)
	{
		// assert(0); // 없는데 빼는 것을 오류라고 판단
		return;	// 없는데 빼는 것을 무시하라고 판단
	}
	else if (1 == m_size)
	{
		// 1. 지우기 전에 지울 노드의 주소를 잠깐 복사
		Node<T>* deleteNode = pHeadNode;
		// 2. 처음노드를 nullptr 지정.
		pHeadNode = nullptr;
		// 3. 마지막노드를 nullptr 지정.
		pTailNode = nullptr;
		// 4. 지울 노드를 삭제
		delete deleteNode;
	}
	else
	{
		// 1. 지우기 전에 지울 노드의 주소를 잠깐 복사
		Node<T>* deleteNode = pHeadNode;
		// 2 .처음노드를 지울 노드의 다음 노드로 지정함
		pHeadNode = deleteNode->pNext;
		// 3. 처음이 될 노드의 이전 데이터를  Nullptr 지정
		pHeadNode->pPrev = nullptr;
		// 4. 지울노드를 삭제
		delete deleteNode;
	}


	m_size--;
}

template <typename T>
void CLinkedList<T>::push_back(const T& data)
{
	if (m_size > 0)
	{
		// 1. 새로운 노드 생성
		Node<T>* newNode = new Node<T>();
		// 2. 새로운 노드에 데이터 저장
		newNode->m_data = data;
		// 3. 새로운 노드의 이전 데이터를 마지막 노드로 지정
		newNode->pPrev = pTailNode;
		// 4. 마지막 노드의 다음 데이터를 새로운 노드로 지정
		pTailNode->pNext = newNode;
		// 5. 마지막 노드를 새로운 노드로 지정
		pTailNode = newNode;
	}
	else
	{
		// 1. 새로운 노드 생성
		Node<T>* newNode = new Node<T>();
		// 2. 새로운 노드에 데이터 저장
		newNode->m_data = data;
		// 3. 처음 노드를 새로운 노드로 지정
		pHeadNode = newNode;
		// 4. 마지막 노드를 새로운 노드로 지정
		pTailNode = newNode;
	}

	m_size++;
}

template <typename T>
void CLinkedList<T>::pop_back()
{
	if (m_size == 0)
	{
		// assert(0);
		return;
	}
	else if (m_size == 1)
	{
		// 1. 지울 노드를 잠시 기억
		Node<T>* deleteNode = pTailNode;
		// 2. 처음 노드를 nullptr 변경
		pHeadNode = nullptr;
		// 3. 마지막 노드를 nullptr 변경
		pTailNode = nullptr;
		// 4. 지울 노드를 삭제
		delete deleteNode;
	}
	else
	{
		// 1. 지울 노드를 잠시 기억
		Node<T>* deleteNode = pTailNode;
		// 2. 마지막 노드를 지울 노드의 이전 데이터로 변경
		pTailNode = deleteNode->pPrev;
		// 3. 마지막의 다음 데이터를 nullptr 변경
		pTailNode->pNext = nullptr;
		// 4. 지울 노드를 삭제
		delete deleteNode;
	}

	m_size--;
}

template <typename T>
int CLinkedList<T>::size()
{
	return m_size;
}

template <typename T>
bool CLinkedList<T>::empty()
{
	return 0 == m_size;
}

template <typename T>
void CLinkedList<T>::clear()
{
	while (!empty())
		pop_back();
}