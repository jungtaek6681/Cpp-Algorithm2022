#pragma once

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct RedBlackNode
{
	T data;
	RedBlackNode* pParent;
	RedBlackNode* pLeft;
	RedBlackNode* pRight;

	enum class Color { Red, Black };
	Color color;

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
};

template <typename T>
class CRedBlackTree
{
private:
	RedBlackNode<T>* m_pRootNode;
	int m_size;

	void RotateLeft(RedBlackNode<T>* node);
	void RotateRight(RedBlackNode<T>* node);
	void InsertFixUp(RedBlackNode<T>* node);
	void DeleteFixUp(RedBlackNode<T>* node);
	void printNode(int depth, RedBlackNode<T>* node);

public:
	RedBlackNode<T>* m_pLeafNode;

	CRedBlackTree();
	virtual ~CRedBlackTree();

	int size();
	bool empty();
	void clear();

	class iterator
	{
		friend CRedBlackTree;
	private:
		CRedBlackTree<T>* m_pRedBlackTree;
		RedBlackNode<T>* m_pRedBlackNode;

	public:
		iterator();
		iterator(CRedBlackTree<T>* pBST, RedBlackNode<T>* pNode);
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

	void printAll();
};

template<typename T>
void CRedBlackTree<T>::RotateLeft(RedBlackNode<T>* node)
{
	RedBlackNode<T>* rightChild = node->pRight;
	if (nullptr == rightChild)
		assert(0);

	node->pRight = rightChild->pLeft;
	if (nullptr != rightChild->pLeft)
		rightChild->pLeft->pParent = node;
	rightChild->pParent = node->pParent;

	if (node->isRootNode())
		m_pRootNode = rightChild;
	else if (node->isLeftChild())
		node->pParent->pLeft = rightChild;
	else
		node->pParent->pRight = rightChild;

	node->pParent = rightChild;
	rightChild->pLeft = node;
}

template<typename T>
void CRedBlackTree<T>::RotateRight(RedBlackNode<T>* node)
{
	RedBlackNode<T>* leftChild = node->pLeft;
	if (nullptr == leftChild)
		assert(0);

	node->pLeft = leftChild->pRight;
	if (nullptr != leftChild->pRight)
		leftChild->pRight->pParent = node;
	leftChild->pParent = node->pParent;

	if (node->isRootNode())
		m_pRootNode = leftChild;
	else if (node->isLeftChild())
		node->pParent->pLeft = leftChild;
	else
		node->pParent->pRight = leftChild;

	node->pParent = leftChild;
	leftChild->pRight = node;

}

template<typename T>
void CRedBlackTree<T>::InsertFixUp(RedBlackNode<T>* node)
{
	while (node != m_pRootNode && node->pParent->color == RedBlackNode<T>::Color::Red)
	{
		RedBlackNode<T>* parent = node->pParent;
		RedBlackNode<T>* grandParent = parent->pParent;

		// 부모가 왼쪽 자식인 경우
		if (parent->isLeftChild())
		{
			RedBlackNode<T>* uncle = grandParent->pRight;
			// 1. 삼촌이 빨간색일 경우
			// 조부모를 빨간색으로 삼촌을 검은색으로 변경 후, 조부모를 기준으로 반복
			if (nullptr != uncle && uncle->color == RedBlackNode<T>::Color::Red)
			{
				parent->color = RedBlackNode<T>::Color::Black;
				uncle->color = RedBlackNode<T>::Color::Black;
				grandParent->color = RedBlackNode<T>::Color::Red;
				node = grandParent;
			}
			else
			{
				// 2. 삼촌이 검은색이며 현재 노드가 오른쪽 자식인 경우
				// 부모를 기준으로 왼쪽회전 후, 새로 삽입한 노드를 기준으로 진행
				if (node->isRightChild())
				{
					node = node->pParent;
					RotateLeft(node);
				}

				// 3. 삼촌이 검은색이며 현재 노드가 왼쪽 자식일 때
				// 부모를 검은색으로 조부모를 빨간색으로 변경 후, 조부모를 기준으로 오른쪽으로 회전 후 반복
				node->pParent->color = RedBlackNode<T>::Color::Black;
				node->pParent->pParent->color = RedBlackNode<T>::Color::Red;
				RotateRight(node->pParent->pParent);
			}
		}
		// 부모가 오른쪽 자식인 경우
		else
		{
			RedBlackNode<T>* uncle = grandParent->pLeft;
			// 1. 삼촌이 빨간색일 경우
			// 조부모를 빨간색으로 삼촌을 검은색으로 변경 후, 조부모를 기준으로 반복
			if (nullptr != uncle && uncle->color == RedBlackNode<T>::Color::Red)
			{
				parent->color = RedBlackNode<T>::Color::Black;
				uncle->color = RedBlackNode<T>::Color::Black;
				grandParent->color = RedBlackNode<T>::Color::Red;
				node = grandParent;
			}
			else
			{
				// 2. 삼촌이 검은색이며 현재 노드가 왼쪽 자식일 때
				// 부모를 기준으로 오른쪽회전 후, 새로 삽입한 노드를 기준으로 반복
				if (node->isLeftChild())
				{
					node = node->pParent;
					RotateRight(node);
				}

				// 3. 삼촌이 검은색이며 현재 노드가 오른쪽 자식일 때
				// 부모를 검은색으로 조부모를 빨간색으로 변경 후, 조부모를 기준으로 왼쪽으로 회전 후 반복
				node->pParent->color = RedBlackNode<T>::Color::Black;
				node->pParent->pParent->color = RedBlackNode<T>::Color::Red;
				RotateLeft(node->pParent->pParent);
			}
		}
	}
	m_pRootNode->color = RedBlackNode<T>::Color::Black;
}

template<typename T>
void CRedBlackTree<T>::DeleteFixUp(RedBlackNode<T>* doubleBlackNode)
{
	while (nullptr != doubleBlackNode->pParent && doubleBlackNode->color == RedBlackNode<T>::Color::Black)
	{
		// 노드가 왼쪽 자식인 경우
		if (doubleBlackNode->isLeftChild())
		{
			RedBlackNode<T>* parent = doubleBlackNode->pParent;
			RedBlackNode<T>* brother = parent->pRight;

			// 1. 형제가 빨간색인 경우
			// 부모를 빨간색으로 형제를 검은색으로 변경 후, 부모를 기준으로 왼쪽으로 회전 후 진행
			if (brother->color == RedBlackNode<T>::Color::Red)
			{
				brother->color = RedBlackNode<T>::Color::Black;
				parent->color = RedBlackNode<T>::Color::Red;
				RotateLeft(parent);
				brother = doubleBlackNode->pParent->pRight;
			}

			// 2. 형제가 검은색이며 형제의 양쪽 자식이 모두 검은색인 경우
			// 형제를 빨간색으로 부모가 빨간색이므로 검은색으로 칠한 후 끝난다.
			if (brother->pLeft->color == RedBlackNode<T>::Color::Black &&
				brother->pRight->color == RedBlackNode<T>::Color::Black)
			{
				brother->color = RedBlackNode<T>::Color::Red;
				doubleBlackNode = doubleBlackNode->pParent;
			}
			else
			{
				// 3. 형제가 검은색이며 형제의 오른쪽 자식만 검은색인 경우
				// 형제를 빨간색으로 형제의 왼쪽 자식을 검은색으로 변경 후, 형제를 기준으로 오른쪽으로 회전 후 진행
				if (brother->pRight->color == RedBlackNode<T>::Color::Black)
				{
					brother->pLeft->color = RedBlackNode<T>::Color::Black;
					brother->color = RedBlackNode<T>::Color::Red;
					RotateRight(brother);
					brother = doubleBlackNode->pParent->pRight;
				}

				// 4. 형제가 검은색이며 형제의 왼쪽 자식만 검은색인 경우
				// 형제를 부모색으로 부모와 형제의 오른쪽 자식을 검은색으로 변경 후
				// 부모를 기준으로 좌회전하고 루트노드에 검은색을 준다.(반복 종료)
				brother->color = doubleBlackNode->pParent->color;
				doubleBlackNode->pParent->color = RedBlackNode<T>::Color::Black;
				brother->pRight->color = RedBlackNode<T>::Color::Black;
				RotateLeft(doubleBlackNode->pParent);
				doubleBlackNode = m_pRootNode;
			}
		}
		// 노드가 오른쪽 자식인 경우
		else
		{
			RedBlackNode<T>* parent = doubleBlackNode->pParent;
			RedBlackNode<T>* brother = parent->pLeft;

			// 1. 형제가 빨간색인 경우
			// 부모를 빨간색으로 형제를 검은색으로 변경 후, 부모를 기준으로 오른쪽으로 회전 후 진행
			if (brother->color == RedBlackNode<T>::Color::Red)
			{
				brother->color = RedBlackNode<T>::Color::Black;
				parent->color = RedBlackNode<T>::Color::Red;
				RotateRight(parent);
				brother = doubleBlackNode->pParent->pLeft;
			}
			// 2. 형제가 검은색이며 형제의 양쪽 자식이 모두 검은색인 경우
			// 형제를 빨간색으로 부모가 빨간색이므로 검은색으로 칠한 후 끝난다.
			if (brother->pLeft->color == RedBlackNode<T>::Color::Black &&
				brother->pRight->color == RedBlackNode<T>::Color::Black)
			{
				brother->color = RedBlackNode<T>::Color::Red;
				doubleBlackNode = doubleBlackNode->pParent;
			}
			else
			{
				// 3. 형제가 검은색이며 형제의 왼쪽 자식만 검은색인 경우
				// 형제를 빨간색으로 형제의 오른쪽 자식을 검은색으로 변경 후, 형제를 기준으로 왼쪽으로 회전 후 진행
				if (brother->pRight->color == RedBlackNode<T>::Color::Black)
				{
					brother->pRight->color = RedBlackNode<T>::Color::Black;
					brother->color = RedBlackNode<T>::Color::Red;
					RotateLeft(brother);
					brother = doubleBlackNode->pParent->pLeft;
				}

				// 4. 형제가 검은색이며 형제의 오른쪽 자식만 검은색인 경우
				// 형제를 부모색으로 부모와 형제의 왼쪽 자식을 검은색으로 변경 후
				// 부모를 기준으로 우회전하고 루트노드에 검은색을 준다.(반복 종료)
				brother->color = doubleBlackNode->pParent->color;
				doubleBlackNode->pParent->color = RedBlackNode<T>::Color::Black;
				brother->pLeft->color = RedBlackNode<T>::Color::Black;
				RotateRight(doubleBlackNode->pParent);
				doubleBlackNode = m_pRootNode;
			}
		}
	}
	doubleBlackNode->color = RedBlackNode<T>::Color::Black;
	m_pRootNode->color = RedBlackNode<T>::Color::Black;
}

template<typename T>
CRedBlackTree<T>::CRedBlackTree()
{
	m_pLeafNode = new RedBlackNode<T>();
	m_pLeafNode->color = RedBlackNode<T>::Color::Black;
	m_pRootNode = m_pLeafNode;
	m_size = 0;
}

template<typename T>
CRedBlackTree<T>::~CRedBlackTree()
{
	clear();
	delete m_pLeafNode;
}

template<typename T>
int CRedBlackTree<T>::size()
{
	return m_size;
}

template<typename T>
bool CRedBlackTree<T>::empty()
{
	return 0 == m_size;
}

template<typename T>
void CRedBlackTree<T>::clear()
{
	while (!empty())
	{
		erase(begin());
	}
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::insert(const T& data)
{
	RedBlackNode<T>* pNewNode = new RedBlackNode<T>();
	pNewNode->pParent = nullptr;
	pNewNode->pLeft = m_pLeafNode;
	pNewNode->pRight = m_pLeafNode;
	pNewNode->color = RedBlackNode<T>::Color::Red;
	pNewNode->data = data;

	// 1. 데이터가 비어 있었을 때
	if (empty())
	{
		m_pRootNode = pNewNode;
		InsertFixUp(pNewNode);
		m_size++;
		return iterator(this, pNewNode);
	}

	RedBlackNode<T>* pCurrent = m_pRootNode;
	while (true)
	{
		// 2-1. 추가 하는 데이터가 더 큰 경우
		if (data > pCurrent->data)
		{
			// 3-1. 오른쪽에 노드가 있는 경우, 오른쪽으로 가기.
			if (m_pLeafNode != pCurrent->pRight)
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
			if (m_pLeafNode != pCurrent->pLeft)
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

	InsertFixUp(pNewNode);
	m_size++;
	return iterator(this, pNewNode);
}

template<typename T>
int CRedBlackTree<T>::erase(const T& data)
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
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::erase(const iterator& iter)
{
	// 1. 데이터가 하나도 없는 경우
	if (empty())
		assert(0);

	RedBlackNode<T>* pCurrent = iter.m_pRedBlackNode;
	RedBlackNode<T>* nextNode = m_pLeafNode;
	RedBlackNode<T>* removedNode = m_pLeafNode;
	RedBlackNode<T>* doubleBlackNode = m_pLeafNode;

	typename RedBlackNode<T>::Color color = pCurrent->color;

	if (pCurrent->pLeft == m_pLeafNode || pCurrent->pRight == m_pLeafNode)
	{
		removedNode = pCurrent;
		iterator next = iterator(this, pCurrent);
		next++;
		nextNode = next.m_pRedBlackNode;
	}
	else
	{
		iterator next = iter;
		next++;
		removedNode = next.m_pRedBlackNode;
		pCurrent->data = removedNode->data;
		nextNode = pCurrent;
	}

	if (removedNode->pLeft != m_pLeafNode)
		doubleBlackNode = removedNode->pLeft;
	else
		doubleBlackNode = removedNode->pRight;

	doubleBlackNode->pParent = removedNode->pParent;

	if (nullptr == removedNode->pParent)
		m_pRootNode = doubleBlackNode;
	else
	{
		if (removedNode->isLeftChild())
			removedNode->pParent->pLeft = doubleBlackNode;
		else
			removedNode->pParent->pRight = doubleBlackNode;
	}

	if (removedNode->color == RedBlackNode<T>::Color::Black)
		DeleteFixUp(doubleBlackNode);

	delete removedNode;
	m_size--;
	return iterator(this, nextNode);
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::find(const T& data)
{
	// 1. 데이터가 하나도 없는 경우
	if (empty())
		return end();

	RedBlackNode<T>* pCurrent = m_pRootNode;
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
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::begin()
{
	if (0 == m_size)
		return end();

	RedBlackNode<T>* pCurrent = m_pRootNode;
	while (m_pLeafNode != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
	}
	return iterator(this, pCurrent);
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::end()
{
	return iterator(this, nullptr);
}

template<typename T>
CRedBlackTree<T>::iterator::iterator()
{
	m_pRedBlackTree = nullptr;
	m_pRedBlackNode = nullptr;
}

template<typename T>
CRedBlackTree<T>::iterator::iterator(CRedBlackTree<T>* pRBT, RedBlackNode<T>* pNode)
{
	m_pRedBlackTree = pRBT;
	m_pRedBlackNode = pNode;
}

template<typename T>
CRedBlackTree<T>::iterator::~iterator()
{
	m_pRedBlackTree = nullptr;
	m_pRedBlackNode = nullptr;
}

template<typename T>
T& CRedBlackTree<T>::iterator::operator*()
{
	return m_pRedBlackNode->data;
}

template<typename T>
typename CRedBlackTree<T>::iterator& CRedBlackTree<T>::iterator::operator++()
{
	// 0. 예외처리, 하나도 없었을 때, 이미 end() iterator였을 때
	if (this->m_pRedBlackTree->m_pLeafNode == this->m_pRedBlackTree->m_pRootNode || nullptr == m_pRedBlackNode)
	{
		assert(0);
	}

	RedBlackNode<T>* pCurrent = this->m_pRedBlackNode;
	RedBlackNode<T>* leafNode = this->m_pRedBlackTree->m_pLeafNode;
	// 1. 오른쪽 자식이 있는 경우, 오른쪽 자식으로 가서 왼쪽 자식이 없을 때까지 내려감
	// 오른쪽 자식의 가장 작은 값이 당연히 다음 노드이다.
	if (leafNode != pCurrent->pRight)
	{
		pCurrent = pCurrent->pRight;
		while (true)
		{
			if (leafNode == pCurrent->pLeft)
				break;
			pCurrent = pCurrent->pLeft;
		}
		this->m_pRedBlackNode = pCurrent;
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
				this->m_pRedBlackNode = nullptr;
				return *this;
			}
			if (pCurrent->isLeftChild())
			{
				// 이때 부모가 자신의 다음 Node
				this->m_pRedBlackNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::iterator::operator++(int)
{
	iterator temp(*this);
	++(*this);
	return temp;
}

template<typename T>
typename CRedBlackTree<T>::iterator& CRedBlackTree<T>::iterator::operator--()
{
	// 0. 예외처리, 하나도 없었을 때, 이미 begin() iterator였을 때
	if (nullptr == this->m_pMyBST->m_pRootNode || this->m_pMyBST->begin() == this)
	{
		assert(nullptr);
	}

	RedBlackNode<T>* pCurrent = this->m_pRedBlackNode;
	RedBlackNode<T>* leafNode = this->m_pRedBlackTree->m_pLeafNode;

	// 0. end() iterator 였을 때
	if (nullptr == this->m_pRedBlackNode)   // this->m_pMYBST->end() == this
	{
		RedBlackNode<T>* pCurrent = this->m_pMyBST->m_pRootNode;
		while (true)
		{
			if (leafNode == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		return iterator(this, pCurrent);
	}

	RedBlackNode<T>* pCurrent = this->m_pRedBlackNode;
	// 1. 왼쪽 자식이 있는 경우, 왼쪽 자식으로 가서 오른쪽 자식이 없을 때까지 내려감
	// 왼쪽 자식의 가장 큰 값이 당연히 이전 노드이다.
	if (leafNode != pCurrent->pLeft)
	{
		pCurrent = pCurrent->pLeft;
		while (true)
		{
			if (leafNode == pCurrent->pRight)
				break;
			pCurrent = pCurrent->pRight;
		}
		this->m_pRedBlackNode = pCurrent;
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
				this->m_pRedBlackNode = pCurrent->pParent;
				return *this;
			}
			pCurrent = pCurrent->pParent;
		}
	}
}

template<typename T>
typename CRedBlackTree<T>::iterator CRedBlackTree<T>::iterator::operator--(int)
{
	iterator temp(*this);
	--(*this);
	return temp;
}

template<typename T>
bool CRedBlackTree<T>::iterator::operator==(const iterator& _other)
{
	if (this->m_pRedBlackNode == _other.m_pRedBlackNode &&
		this->m_pRedBlackTree == _other.m_pRedBlackTree)
		return true;
	return false;
}

template<typename T>
bool CRedBlackTree<T>::iterator::operator!=(const iterator& _other)
{
	return !(*this == _other);
}

template <typename T>
void CRedBlackTree<T>::printNode(int depth, RedBlackNode<T>* node)
{
	int i = 0;
	char c = 'X';
	T v = -1;
	string cnt;

	if (nullptr == node || m_pLeafNode == node)
		return;

	if (node->pParent != nullptr)
	{
		v = node->pParent->data;

		if (node->isLeftChild())
			c = 'L';
		else
			c = 'R';
	}

	for (int i = 0; i < depth; i++) cout << "  ";

	cout << node->data << " ";
	if (node->color == RedBlackNode<T>::Color::Red) cout << "Red";
	else cout << "Black";
	cout << " " << c << " " << v << " " << endl;

	printNode(depth + 1, node->pLeft);
	printNode(depth + 1, node->pRight);
}

template <typename T>
void CRedBlackTree<T>::printAll()
{
	printNode(0, m_pRootNode);
	cout << endl << endl;
}