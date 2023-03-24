
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vec;
	vector<int>::iterator iter;

	for (iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << *iter << ", " << endl;
	}
}

