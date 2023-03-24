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