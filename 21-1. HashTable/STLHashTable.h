#pragma once
#include <map>
#include <utility>
#include <string>

using namespace std;

template <typename T>
struct Hasher
{
	size_t operator()(T key)
	{
		return 0;
	}
};

template <>
struct Hasher<int>
{
	size_t operator()(int key)
	{
		// ³ª´°¼À ¹ý
		return key;
	}
};

template <>
struct Hasher<string>
{
	size_t operator()(string key)
	{
		// ÀÚ¸´¼ö Á¢±â¹ý
		size_t result = 0;
		const char* data = key.c_str();
		for (size_t i = 0; data[i] != NULL; i++)
		{
			result += data[i];
		}
		return result;
	}
};

template <typename type, typename content, typename hasher = Hasher<type>>
class CHashTable
{
private:
	map<type, content>* m_pMapTable;
	hasher m_hasher;
	size_t m_tableSize;

public:

	CHashTable(size_t tableSize = 101)
	{
		m_pMapTable = new map<type, content>[tableSize]();
		m_tableSize = tableSize;
	}

	virtual ~CHashTable()
	{
		delete[] m_pMapTable;
	}

	void insert(type key, const content& value)
	{
		size_t address = m_hasher(key) % m_tableSize;
		m_pMapTable[address].insert(make_pair(key, value));
	}

	const content& find(type key)
	{
		size_t address = m_hasher(key) % m_tableSize;
		return m_pMapTable[address][key];
	}

	void erase(type key)
	{
		size_t address = m_hasher(key) % m_tableSize;
		m_pMapTable[address].erase(key);
	}

	const content& operator[](type key)
	{
		return find(key);
	}
};