#pragma once
#include <cassert>

template <typename T>
struct BinaryNode
{
	T data;
	BinaryNode* pParent;
	BinaryNode* pLeft;
	BinaryNode* pRight;

	bool isRootNode()
	{
		return nullptr == pParent;
	}
	bool isLeftChild()
	{
		if (nullptr != pParent && pParent->pLeft == this)
			return true;
		else
			return false;
	}
	bool isRightChild()
	{
		if (nullptr != pParent && pParent->pRight == this)
			return true;
		else
			return false;
	}

	bool hasNoChild()
	{
		return nullptr == pLeft && nullptr == pRight;
	}
	bool hasLeftChild()
	{
		return nullptr != pLeft && nullptr == pRight;
	}
	bool hasRightChild()
	{
		return nullptr == pLeft && nullptr != pRight;
	}
	bool hasBothChild()
	{
		return nullptr != pLeft && nullptr != pRight;
	}
};

template <typename T>
class CBinarySearchTree
{
private:
	BinaryNode<T>* m_pRootNode;
	int m_size;

public:
	CBinarySearchTree();
	virtual ~CBinarySearchTree();
	int size();
	bool empty();
	void clear();

	class iterator
	{
		friend CBinarySearchTree;
	private:
		CBinarySearchTree<T>* m_pBST;
		BinaryNode<T>* m_pBinaryNode;

	public:
		iterator();
		iterator(CBinarySearchTree<T>* pBST, BinaryNode<T>* pNode);
		virtual ~iterator();

		T& operator*();

		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);

		bool operator==(const iterator& _other);
		bool operator!=(const iterator& _other);
	};

	iterator insert(const T& data);
	int erase(const T& data);
	iterator erase(const iterator& iter);
	iterator find(const T& data);

	iterator begin();
	iterator end();
};

template<typename T>
CBinarySearchTree<T>::CBinarySearchTree()
{
	m_pRootNode = nullptr;
	m_size = 0;
}

template<typename T>
CBinarySearchTree<T>::~CBinarySearchTree()
{
	clear();
}

template<typename T>
int CBinarySearchTree<T>::size()
{
	return m_size;
}

template<typename T>
bool CBinarySearchTree<T>::empty()
{
	return 0 == m_size;
}

template<typename T>
void CBinarySearchTree<T>::clear()
{
	while (!empty())
	{
		erase(begin());
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::insert(const T& data)
{
	BinaryNode<T>* pNewNode = new BinaryNode<T>();
	pNewNode->data = data;

	// 1. 데이터가 비어 있었을 때
	if (empty())
	{
		m_pRootNode = pNewNode;
		m_size++;
		return iterator(this, pNewNode);
	}

	BinaryNode<T>* pCurrent = m_pRootNode;
	while (true)
	{
		// 2-1. 추가 하는 데이터가 더 큰 경우
		if (data > pCurrent->data)
		{
			// 3-1. 오른쪽에 노드가 있는 경우, 오른쪽으로 가기.
			if (nullptr != pCurrent->pRight)
			{
				pCurrent = pCurrent->pRight;
			}
			// 3-2. 오른쪽에 노드가 없는 경우, 그 위치에 추가
			else
			{
				pCurrent->pRight = pNewNode;
				pNewNode->pParent = pCurrent;
				break;
			}
		}
		// 2-2. 추가 하는 데이터가 더 작은 경우
		else if (data < pCurrent->data)
		{
			// 3-1. 왼쪽에 노드가 있는 경우, 왼쪽으로 가기.
			if (nullptr != pCurrent->pLeft)
			{
				pCurrent = pCurrent->pLeft;
			}
			// 3-2. 왼쪽에 노드가 없는 경우, 그 위치에 추가.
			else
			{
				pCurrent->pLeft = pNewNode;
				pNewNode->pParent = pCurrent;
				break;
			}
		}
		// 2-3. 추가 하는 데이터가 같은 경우, 무시
		else // (data == pCurrent->data)
		{
			delete pNewNode;
			return iterator(this, pCurrent);
		}
	}

	m_size++;
	return iterator(this, pNewNode);
}

template<typename T>
int CBinarySearchTree<T>::erase(const T& data)
{
	// 1. 데이터가 하나도 없는 경우
	if (empty())
		assert(0);

	iterator findIter = find(data);
	if (findIter != end())
		erase(findIter);

	return size();
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::erase(const iterator& iter)
{
	// 1. 데이터가 하나도 없는 경우
	if (empty())
		assert(0);

	BinaryNode<T>* pCurrent = iter.m_pBinaryNode;

	// 2-1. 자식 노드가 없는 경우, 그냥 노드를 지운다.
	if (pCurrent->hasNoChild())
	{
		iterator next = iter;
		next++;

		if (pCurrent->isLeftChild())
			pCurrent->pParent->pLeft = nullptr;
		else if (pCurrent->isRightChild())
			pCurrent->pParent->pRight = nullptr;
		else //(pCurrent->isRootNode())
			m_pRootNode = nullptr;

		m_size--;
		delete pCurrent;
		return next;
	}
	// 2-2. 자식 노드가 하나인 경우, 자식을 자기 위치로 옮긴다.
	else if (pCurrent->hasLeftChild())
	{
		BinaryNode<T>* parentNode = pCurrent->pParent;
		BinaryNode<T>* childNode = pCurrent->pLeft;

		iterator next = iter;
		next++;
		if (pCurrent->isLeftChild())
		{
			// 부모 노드의 연결을 손자 노드에 연결
			parentNode->pLeft = childNode;
			// 손자 노드의 연결을 부모 노드에 연결
			childNode->pParent = parentNode;
		}
		else if (pCurrent->isRightChild())
		{
			// 부모 노드의 연결을 손자 노드에 연결
			parentNode->pRight = childNode;
			// 손자 노드의 연결을 부모 노드에 연결
			childNode->pParent = parentNode;
		}
		else // (pCurrent->isRootNode())
		{
			// 루트 노드를 손자 노드로 지정
			m_pRootNode = childNode;
			// 손자 노드의 연결을 해제
			childNode->pParent = nullptr;
		}

		m_size--;
		delete pCurrent;
		return next;
	}
	else if (pCurrent->hasRightChild())
	{
		BinaryNode<T>* parentNode = pCurrent->pParent;
		BinaryNode<T>* childNode = pCurrent->pRight;

		iterator next = iter;
		next++;
		if (pCurrent->isLeftChild())
		{
			// 부모 노드의 연결을 손자 노드에 연결
			parentNode->pLeft = childNode;
			// 손자 노드의 연결을 부모 노드에 연결
			childNode->pParent = parentNode;
		}
		else if (pCurrent->isRightChild())
		{
			// 부모 노드의 연결을 손자 노드에 연결
			parentNode->pRight = childNode;
			// 손자 노드의 연결을 부모 노드에 연결
			childNode->pParent = parentNode;
		}
		else // (pCurrent->isRootNode())
		{
			// 루트 노드를 손자 노드로 지정
			m_pRootNode = childNode;
			// 손자 노드의 연결을 해제
			childNode->pParent = nullptr;
		}

		m_size--;
		delete pCurrent;
		return next;
	}
	// 2-3. 자식 노드가 둘인 경우, 중위순회상의 전 노드나 후 노드를 자기 위치로 옮긴다.
	else // (hasBothChild())
	{
		iterator next = iter;
		next++;
		pCurrent->data = next.m_pBinaryNode->data;
		erase(next);

		return iterator(this, pCurrent);
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::find(const T& data)
{
	// 1. 데이터가 하나도 없는 경우
	if (empty())
		return end();

	BinaryNode<T>* pCurrent = m_pRootNode;
	while (nullptr != pCurrent)
	{
		// 2-1. 찾고자 하는 데이터가 더 큰 경우, 오른쪽으로 가기.
		if (data > pCurrent->data)
			pCurrent = pCurrent->pRight;
		// 2-2. 찾고자 하는 데이터가 더 작은 경우, 왼쪽으로 가기.
		else if (data < pCurrent->data)
			pCurrent = pCurrent->pLeft;
		// 2-3. 찾고자 하는 데이터가 같은 경우, 찾은 위치 반환하기.
		else // (data == pCurrent->data)
			return iterator(this, pCurrent);
	}

	return end();
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::begin()
{
	if (0 == m_size)
		return end();

	BinaryNode<T>* pCurrent = m_pRootNode;
	while (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
	}
	return iterator(this, pCurrent);
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
CBinarySearchTree<T>::iterator::iterator()
{
	m_pBST = nullptr;
	m_pBinaryNode = nullptr;
}

template<typename T>
CBinarySearchTree<T>::iterator::iterator(CBinarySearchTree<T>* pBST, BinaryNode<T>* pNode)
{
	m_pBST = pBST;
	m_pBinaryNode = pNode;
}

template<typename T>
CBinarySearchTree<T>::iterator::~iterator()
{
	m_pBST = nullptr;
	m_pBinaryNode = nullptr;
}

template<typename T>
T& CBinarySearchTree<T>::iterator::operator*()
{
	return m_pBinaryNode->data;
}

template<typename T>
typename CBinarySearchTree<T>::iterator& CBinarySearchTree<T>::iterator::operator++()
{
	// 0. 예외처리, 하나도 없었을 때, 이미 end() iterator였을 때
	if (nullptr == this->m_pBST->m_pRootNode || nullptr == m_pBinaryNode)
	{
		assert(nullptr);
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;
	// 1. 오른쪽 자식이 있는 경우, 오른쪽 자식으로 가서 왼쪽 자식이 없을 때까지 내려감
	// 오른쪽 자식의 가장 작은 값이 당연히 다음 노드이다.
	if (nullptr != pCurrent->pRight)
	{
		pCurrent = pCurrent->pRight;
		while (true)
		{
			if (nullptr == pCurrent->pLeft)
				break;
			pCurrent = pCurrent->pLeft;
		}
		this->m_pBinaryNode = pCurrent;
		return *this;
	}
	// 2. 오른쪽 자식이 없는 경우, 부모로 가야하는데 왼쪽 자식일 때까지 위로 감.
	// 나를 가장 먼저 왼쪽으로 보낸 노드가 내 다음노드다.
	else   // nullptr == pCurrent->pRight;
	{
		while (true)
		{
			// 계속 따라 올라갔는데 부모가 없을때까지 올라갔다 == 처음 노드가 가장 큰(마지막) Node였다.
			if (nullptr == pCurrent->pParent)
			{
				this->m_pBinaryNode = nullptr;
				return *this;
			}
			if (pCurrent->isLeftChild())
			{
				// 이때 부모가 자신의 다음 Node
				this->m_pBinaryNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::iterator::operator++(int)
{
	iterator temp(*this);
	++(*this);
	return temp;
}

template<typename T>
typename CBinarySearchTree<T>::iterator& CBinarySearchTree<T>::iterator::operator--()
{
	// 0. 예외처리, 하나도 없었을 때, 이미 begin() iterator였을 때
	if (nullptr == this->m_pMyBST->m_pRootNode || this->m_pMyBST->begin() == this)
	{
		assert(nullptr);
	}

	// 0. end() iterator 였을 때
	if (nullptr == this->m_pBinaryNode)	// this->m_pMYBST->end() == this
	{
		BinaryNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;
		while (true)
		{
			if (nullptr == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		return iterator(this, pCurrent);
	}

	BinaryNode<T>* pCurrent = this->m_pBinaryNode;
	// 1. 왼쪽 자식이 있는 경우, 왼쪽 자식으로 가서 오른쪽 자식이 없을 때까지 내려감
	// 왼쪽 자식의 가장 큰 값이 당연히 이전 노드이다.
	if (nullptr != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
		while (true)
		{
			if (nullptr == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		this->m_pBinaryNode = pCurrent;
		return *this;
	}
	// 2. 왼쪽 자식이 없는 경우, 부모로 가야하는데 오른쪽 자식일 때까지 위로 감.
	// 나를 가장 먼저 오른쪽으로 보낸 노드가 내 이전 노드다.
	else   // nullptr == pCurrent->pRight;
	{
		while (true)
		{
			// 계속 따라 올라갔는데 부모가 없을때까지 올라갔다 == 처음 노드가 가장 작은(처음) Node였다.
			if (nullptr == pCurrent->pParent)
			{
				assert(nullptr);
			}
			if (pCurrent->isRightChild() == pCurrent)
			{
				// 이때 부모가 자신의 다음 Node
				this->m_pBinaryNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CBinarySearchTree<T>::iterator CBinarySearchTree<T>::iterator::operator--(int)
{
	iterator temp(*this);
	--(*this);
	return temp;
}

template<typename T>
bool CBinarySearchTree<T>::iterator::operator==(const iterator& _other)
{
	if (this->m_pBinaryNode == _other.m_pBinaryNode &&
		this->m_pBST == _other.m_pBST)
		return true;
	return false;
}

template<typename T>
bool CBinarySearchTree<T>::iterator::operator!=(const iterator& _other)
{
	return !(*this == _other);
}