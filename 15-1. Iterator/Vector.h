#pragma once

#include <cassert>

template <typename T>
class CVector
{
private:
	T* pDataArray;			// Vector가 데이터를 담기 위한 배열을 동적할당 할 주소값.
	unsigned int m_size;		// Vector 동적 배열에 들어가 있는 데이터 수
	unsigned int m_capacity;	// Vector 동적 배열에 들어갈 수 있는 허용량

public:
	CVector();
	virtual ~CVector();

	void push_back(const T& data);	// Vector의 끝에 데이터 추가
	void pop_back();				// Vector의 끝에 데이터 삭제
	int size();						// Vector에 저장되어 있는 데이터 수
	void resize(unsigned int resize);	// Vector 동적배열의 크기를 재조정
	bool empty();					// Vector가 비어 있을 경우 true 반환
	void clear();					// Vector에 있는 모든 데이터 제거

	T& operator[](unsigned int index);	// Vector의 index번째 데이터 접근

	// 여기부터 iterator 기능들
	class iterator
	{
		friend CVector;
	private:
		CVector*	m_pVec;
		T*			m_pVecData;
		int			m_index;

	public:
		iterator();
		iterator(CVector* pVec, T* pDataArray, int index);
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
CVector<T>::CVector()
{
	pDataArray = new T[5];
	m_size = 0;
	m_capacity = 5;
}

template <typename T>
CVector<T>::~CVector()
{
	delete[] pDataArray;
}

template <typename T>
void CVector<T>::resize(unsigned int resize)
{
	T* newArray = new T[resize];
	for (int i = 0; i < m_size; i++)
	{
		newArray[i] = pDataArray[i];
	}

	m_capacity = resize;
	delete[] pDataArray;
	pDataArray = newArray;
}

template<typename T>
void CVector<T>::push_back(const T& data)
{
	// 데이터를 추가로 넣기 전에 이미 꽉 차 있었던 상황이라면
	if (m_size >= m_capacity)
	{
		resize(m_capacity + 5);
	}

	pDataArray[m_size] = data;
	m_size++;
}

template<typename T>
void CVector<T>::pop_back()
{
	if (!empty())
	{
		// 데이터를 제거 전에 이미 빈공간이 너무 많은 상황이라면
		if (m_size < m_capacity / 4)
		{
			resize(m_capacity / 2);
		}
		m_size--;
	}
}

template<typename T>
int CVector<T>::size()
{
	return m_size;
}

template<typename T>
bool CVector<T>::empty()
{
	return m_size == 0;
}

template<typename T>
void CVector<T>::clear()
{
	delete[] pDataArray;

	pDataArray = new T[5];
	m_size = 0;
	m_capacity = 5;
}

template<typename T>
T& CVector<T>::operator[](unsigned int index)
{
	if (index >= m_size)
	{
		assert(0);
	}
	return pDataArray[index];
}

template<typename T>
typename CVector<T>::iterator CVector<T>::begin()
{
	return iterator(this, pDataArray, 0);
}

template<typename T>
typename CVector<T>::iterator CVector<T>::end()
{
	return iterator(this, pDataArray, -1);
}

template<typename T>
typename CVector<T>::iterator CVector<T>::insert(CVector<T>::iterator iter, const T& value)
{
	// 이터레이터가 유효하지 않은 요소를 추가하려고 한다면
	// 1. 백터에 있는 데이터 범위 외의 요소를 추가하려고 할 때
	if (iter.m_index >= m_size || iter.m_index < -1)
	{
		assert(0);
	}
	// 2. 가리키는 대상이 다른 백터의 요소를 지우려고 할 때
	else if (iter.m_pVec != this || iter.m_pVecData != this->pDataArray)
	{
		assert(0);
	}
	// 3. end() 에 추가하려고 할 때
	else if (iter.m_index == -1)
	{
		push_back(value);
		return iterator(this, pDataArray, m_size);
	}
	
	int index = iter.m_index;
	push_back(0);

	for (int i = m_size - 1; i > index; i--)
	{
		pDataArray[i] = pDataArray[i - 1];
	}
	pDataArray[index] = value;

	return iterator(this, pDataArray, index);
}

template<typename T>
typename CVector<T>::iterator CVector<T>::erase(CVector<T>::iterator iter)
{
	// 이터레이터가 유효하지 않은 요소를 지우려고 한다면
	// 1. 백터에 있는 데이터범위 외의 요소를 지우려고 할 때
	if (iter.m_index >= m_size || iter.m_index < 0)
	{
		assert(0);
	}
	// 2. 가리키는 대상이 다른 백터의 요소를 지우려고 할 때
	else if (iter.m_pVec != this || iter.m_pVecData != this->pDataArray)
	{
		assert(0);
	}

	// 배열의 인덱스를 이용한 복사
	int index = iter.m_index;
	for (int i = index; i < m_size - 1; i++)
	{
		pDataArray[i] = pDataArray[i + 1];
	}

	// 이터레이터를 이용한 복사
	//iterator curIter = iter;
	//iterator nextIter = curIter;
	//nextIter++;
	//for (; nextIter != end(); curIter++, nextIter++)
	//{
	//	*curIter = *nextIter;
	//}

	pop_back();

	if (index < m_size)
	{
		return iterator(this, pDataArray, index);
	}
	else
	{
		return end();
	}
}

template<typename T>
CVector<T>::iterator::iterator()
{
	m_pVec = nullptr;
	m_pVecData = nullptr;
	m_index = -1;
}

template<typename T>
inline CVector<T>::iterator::iterator(CVector* pVec, T* pDataArray, int index)
{
	m_pVec = pVec;
	m_pVecData = pDataArray;
	m_index = index;
}

template<typename T>
CVector<T>::iterator::~iterator()
{
}

template<typename T>
T& CVector<T>::iterator::operator*()
{
	// 1. 이 iterator가 end() 였을 때
	if (m_index < 0)
		assert(0);

	return m_pVecData[m_index];
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator++()
{
	// 1. 백터의 데이터가 추가&삭제 되어서 배열의 위치가 변경된 경우
	if (m_pVec->pDataArray != m_pVecData)
	{
		assert(0);
	}
	// 2. iterator가 마지막 데이터를 가리키고 있는 경우
	else if (m_index == m_pVec->size() - 1)
	{
		m_index = -1;
	}
	// 3. iterator가 end()였을 때
	else if (-1 == m_index)
	{
		assert(0);
	}
	// 4. 그 외에는 다음 데이터를 가리키게 한다.
	else
	{
		++m_index;
	}
	return *this; // 나를 가리키는 포인터 변수를 따라갔을 때 있는거 == 원본
}

template<typename T>
typename CVector<T>::iterator CVector<T>::iterator::operator++(int)
{
	iterator tempIter = *this;
	++(*this);	// 전위 ++ 연산자
	return tempIter;
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator--()
{
	// 1. 백터의 데이터가 추가&삭제 되어서 배열의 위치가 변경된 경우
	if (m_pVec->pDataArray != m_pVecData)
	{
		assert(0);
	}
	// 2. iterator가 첫번째 데이터를 가리키고 있는 경우
	else if (0 == m_index)
	{
		assert(0);
	}
	// 3. iterator가 end()였을 때
	else if (-1 == m_index)
	{
		m_index = m_pVec->size() - 1;
	}
	// 4. 그 외에는 이전 데이터를 가리키게 한다.
	else
	{
		--m_index;
	}

	return *this;
}

template<typename T>
typename CVector<T>::iterator CVector<T>::iterator::operator--(int)
{
	iterator tempIter = *this;
	--(*this);	// 전위 -- 연산자
	return tempIter;
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator+=(int count)
{
	for (int i = 0; i < count; i++)
		++(*this);
	return *this;
}

template<typename T>
typename CVector<T>::iterator& CVector<T>::iterator::operator-=(int count)
{
	for (int i = 0; i < count; i++)
		--(*this);
	return *this;
}

template<typename T>
bool CVector<T>::iterator::operator==(const iterator& other)
{
	// 1. 같은 백터 소속이고
	// 2. 같은 배열 가리키며
	// 3. 같은 인덱스 가지고 있으면
	if (this->m_pVec		== other.m_pVec		&&
		this->m_pVecData	== other.m_pVecData	&&
		this->m_index		== other.m_index		)
		return true;
	else
		return false;
}

template<typename T>
bool CVector<T>::iterator::operator!=(const iterator& other)
{
	return !(*this == other);
}
