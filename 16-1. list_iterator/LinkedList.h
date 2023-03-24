#pragma once

#include <cassert>

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

	void push_front(const T& data);
	void pop_front();
	void push_back(const T& data);
	void pop_back();

	int size();
	bool empty();
	void clear();

	class iterator
	{
		friend CLinkedList;
	private:
		CLinkedList*	m_pLinkedList;
		Node<T>*		m_pNode;

	public:
		iterator();
		iterator(CLinkedList* pLinkedList, Node<T>* pNode);
		virtual ~iterator();

		// 1. 접근 (*) : 반복자가 가르키는 원소의 내용을 가져오기
		T& operator*();

		// 2. 이동 (++, --, +=, -=) : 반복자가 가르키고 있는 원소의 다음 원소나 이전 원소를 가르킴
		iterator& operator++();		// 전위 : ++iter
		iterator  operator++(int);	// 후위 : iter++
		iterator& operator--();		// 전위 : --iter
		iterator  operator--(int);	// 후위 : iter--
		iterator& operator+=(int);
		iterator& operator-=(int);

		// 3. 비교 (==, !=): 반복자가 다른 반복자와 동일한 원소를 가르키고 있는가 아닌가에 대해서 판단
		bool operator==(const iterator& other);
		bool operator!=(const iterator& other);
	};

	// 4. 순회 (begin(), end()): 반복자가 자료구조의 처음부터 끝까지 한바퀴 돌수 있어야 함
	iterator begin();		// 시작 iterator
	iterator end();			// 끝 iterator

	iterator insert(iterator iter, const T& value);
	iterator erase(iterator iter);
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

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::begin()
{
	return iterator(this, pHeadNode);
}

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::insert(iterator iter, const T& value)
{
	// 유효하지 않은 상황에서 insert를 진행하는 경우
	// 1. 리스트가 지정되지 않은 경우
	if (iter.m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator가 end()를 가리키고 있는 경우
	else if (iter.m_pNode == nullptr)
	{
		push_back(value);
		return iterator(this, pTailNode);
	}

	// 새로운 노드 추가 과정
	// 1. 새로운 노드 생성
	Node<T>* newNode = new Node<T>();
	
	// 2. 이전노드와 이후노드를 잠시 보관
	Node<T>* leftNode = iter.m_pNode->pPrev;
	Node<T>* rightNode = iter.m_pNode;
	
	// 3. 새로운 노드에 데이터 추가
	newNode->m_data = value;

	// 4. 노드간의 연결 진행
	newNode->pPrev = leftNode;
	newNode->pNext = rightNode;

	if (leftNode == nullptr)
	{
		pHeadNode = newNode;
	}
	else
	{
		leftNode->pNext = newNode;
	}

	if (rightNode == nullptr)
	{
		// 이경우는 일어나지 않음
	}
	else
	{
		rightNode->pPrev = newNode;
	}
	
	//5. 새로 추가한 노드를 가리키는 이터레이터 반환
	return iterator(this, newNode);
}

template<typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::erase(iterator iter)
{
	// 유효하지 않은 상황에서 삭제
	// 1. 리스트가 지정되지 않은 경우
	if (iter.m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator가 end() 가리키고 있었던 경우
	else if (iter.m_pNode == nullptr)
		assert(0);

	// 노드의 삭제 과정
	// 1. 노드들을 지정
	Node<T>* deleteNode = iter.m_pNode;
	Node<T>* leftNode = iter.m_pNode->pPrev;
	Node<T>* rightNode = iter.m_pNode->pNext;

	// 2. 노드를 삭제
	delete deleteNode;

	// 3. 노드의 연결 구조 변경
	if (leftNode == nullptr)
	{
		pHeadNode = rightNode;
	}
	else
	{
		leftNode->pNext = rightNode;
	}

	if (rightNode == nullptr)
	{
		pTailNode = leftNode;
	}
	else
	{
		rightNode->pPrev = leftNode;
	}

	// 4. 지워진 노드의 다음 노드를 반환
	return iterator(this, rightNode);
}

template <typename T>
CLinkedList<T>::iterator::iterator()
{
	m_pLinkedList = nullptr;
	m_pNode = nullptr;
}

template <typename T>
CLinkedList<T>::iterator::iterator(CLinkedList* pLinkedList, Node<T>* pNode)
{
	this->m_pLinkedList = pLinkedList;
	this->m_pNode = pNode;
}

template <typename T>
CLinkedList<T>::iterator::~iterator()
{
}

template <typename T>
typename T& CLinkedList<T>::iterator::operator*()
{
	// 유효하지 않은 데이터를 접근할 때
	// 1. end() iterator 일 때
	if (m_pNode == nullptr)
		assert(0);
	return m_pNode->m_data;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator++()
{
	// 1. 리스트가 지정되지 않은 경우
	if (m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator가 end() 를 가리키고 있는 경우
	else if (m_pNode == nullptr)
		assert(0);
	
	m_pNode = m_pNode->pNext;
	return *this;
}

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::iterator::operator++(int)
{
	iterator tempIter = *this;
	++(*this);
	return tempIter;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator+=(int count)
{
	for (int i = 0; i < count; i++)
		++(*this);
	return *this;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator--()
{
	// 1. 리스트가 지정되지 않은 경우
	if (m_pLinkedList == nullptr)
		assert(0);
	// 2. iterator가 begin()을 가리키고 있는 경우
	else if (m_pNode == m_pLinkedList->pHeadNode)
		assert(0);
	// 3. iterator가 end()를 가리키고 있는 경우
	else if (m_pNode == nullptr)
	{
		m_pNode = m_pLinkedList->pTailNode;
		return *this;
	}

	m_pNode = m_pNode->pPrev;
	return *this;
}

template <typename T>
typename CLinkedList<T>::iterator CLinkedList<T>::iterator::operator--(int)
{
	iterator tempIter = *this;
	--(*this);
	return tempIter;
}

template <typename T>
typename CLinkedList<T>::iterator& CLinkedList<T>::iterator::operator-=(int count)
{
	for (int i = 0; i < count; i++)
		--(*this);
	return *this;
}

template <typename T>
bool CLinkedList<T>::iterator::operator==(const iterator& other)
{
	if (this->m_pLinkedList == other.m_pLinkedList &&
		this->m_pNode		== other.m_pNode)
		return true;
	else
		return false;
}

template <typename T>
bool CLinkedList<T>::iterator::operator!=(const iterator& other)
{
	return !(*this == other);
}