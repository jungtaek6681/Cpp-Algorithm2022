#include <iostream>
#include <map>
#include <unordered_map>
#include "HashTable.h"
#include "STLHashTable.h"

using namespace std;

int main()
{
	CHashTable<int, string> intHash;
	CHashTable<string, string> strHash;

	intHash.insert(10, "aaa");
	intHash.insert(20, "bbb");
	intHash.insert(30, "ccc");
	cout << intHash[10] << endl;
	cout << intHash[20] << endl;
	cout << intHash[30] << endl << endl;

	strHash.insert("aaa", "aaa 데이터");
	strHash.insert("bbb", "bbb 데이터");
	strHash.insert("ccc", "ccc 데이터");
	cout << strHash["aaa"] << endl;
	cout << strHash["bbb"] << endl;
	cout << strHash["ccc"] << endl << endl;
}
