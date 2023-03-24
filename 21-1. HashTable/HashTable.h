#pragma once
#include <utility>
#include <string>
#include <map>
#include <cassert>

using namespace std;

template <typename T>
class CIntHashTable
{
	struct Node
	{
		int key;
		T value;
	};

private:
	Node* m_pTable;
	size_t m_tableSize;

	size_t Hash(int key)
	{
		// ³ª´°¼À ¹ý
		return key % m_tableSize;
	}

public:
	CIntHashTable(size_t tableSize)
	{
		m_pTable = new Node[tableSize];
		m_tableSize = tableSize;
	}
	virtual ~CIntHashTable()
	{
		delete[] m_pTable;
	}

	void insert(int key, const T& value)
	{
		size_t address = Hash(key);
		m_pTable[address].key = key;
		m_pTable[address].value = value;
	}
	const T& find(int key)
	{
		size_t address = Hash(key);
		return m_pTable[address].value;
	}
};

template <typename T>
class CStrHashTable
{
	struct Node
	{
		string key;
		T value;
	};

private:
	Node* m_pTable;
	size_t m_tableSize;

	size_t Hash(string key)
	{
		// ÀÚ¸´¼ö Á¢±â
		size_t result = 0;
		const char* data = key.c_str();
		for (size_t i = 0; data[i] != NULL; i++)
		{
			result += data[i];
		}
		return result % m_tableSize;
	}

public:
	CStrHashTable(size_t tableSize)
	{
		m_pTable = new Node[tableSize];
		m_tableSize = tableSize;
	}
	virtual ~CStrHashTable()
	{
		delete[] m_pTable;
	}

	void insert(string key, const T& value)
	{
		size_t address = Hash(key);
		m_pTable[address].key = key;
		m_pTable[address].value = value;
	}
	const T& find(string key)
	{
		size_t address = Hash(key);
		return m_pTable[address].value;
	}
};

// 1. ´ÝÈù ÁÖ¼Ò¹ý : Ã¼ÀÌ´×
template <typename T>
class CChaningHashTable
{
private:
	map<string, T>* m_pMapTable;
	size_t m_tableSize;

	size_t Hash(string key)
	{
		// ÀÚ¸´¼ö Á¢±â
		size_t result = 0;
		const char* data = key.c_str();
		for (size_t i = 0; data[i] != NULL; i++)
		{
			result += data[i];
		}
		return result % m_tableSize;
	}

public:
	CChaningHashTable(size_t tableSize)
	{
		m_pMapTable = new map<string, T>[tableSize]();
		m_tableSize = tableSize;
	}

	virtual ~CChaningHashTable()
	{
		delete[] m_pMapTable;
	}

	void insert(string key, const T& value)
	{
		size_t address = Hash(key);
		m_pMapTable[address].insert(make_pair(key, value));
	}

	const T& find(string key)
	{
		size_t address = Hash(key);
		return m_pMapTable[address][key];
	}
};

// 2. ¿­¸° ÁÖ¼Ò¹ý : ¼±Çü Å½»ç
template <typename T>
class COpenAddressingHashTable
{
	struct Node
	{
		string key;
		T value;
		bool status = false;
	};

private:
	Node* m_pTable;
	size_t m_tableSize;

	size_t Hash(string key)
	{
		// ÀÚ¸´¼ö Á¢±â
		size_t result = 0;
		const char* data = key.c_str();
		for (size_t i = 0; data[i] != NULL; i++)
		{
			result += data[i];
		}
		return result % m_tableSize;
	}

public:
	COpenAddressingHashTable(size_t tableSize) {
		m_pTable = new Node[tableSize];
		m_tableSize = tableSize;
	}

	virtual ~COpenAddressingHashTable()
	{
		delete[] m_pTable;
	}

	void insert(string key, const T& value)
	{
		size_t address = Hash(key);
		while (m_pTable[address].status)
		{
			address++;
		}
		m_pTable[address].status = true;
		m_pTable[address].key = key;
		m_pTable[address].value = value;
	}

	const T& find(string key)
	{
		size_t address = Hash(key);
		while (m_pTable[address].key != key)
		{
			if (m_pTable[address].status != true)
				assert(0);
			address++;
		}
		return m_pTable[address].value;
	}
};