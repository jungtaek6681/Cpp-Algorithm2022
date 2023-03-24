#include <iostream>
#include <vector>

using namespace std;

int nodeCount = 5;
vector<int> stick[3];

void printHanoi()
{
	for (int i = nodeCount; i >= 0; i--)
	{
		cout << " ";
		for (int j = 0; j < 3; j++)
		{
			if (stick[j].size() >= i + 1)
			{
				cout << stick[j][i] << "  ";
			}
			else
			{
				cout << "   ";
			}
		}
		cout << endl;
	}
	cout << "---------" << endl;
}

void Hanoi(int count, int start, int end)
{
	if (count == 1)
	{
		int node = stick[start].back();
		stick[start].pop_back();
		stick[end].push_back(node);

		cout << start << " 에서 " << end << " 로 " << node << " 를 움직임" << endl;
		printHanoi();
		return;
	}

	int waypoint = 3 - (start + end);
	Hanoi(count - 1, start, waypoint);
	Hanoi(1, start, end);
	Hanoi(count - 1, waypoint, end);
}

int main()
{
	for (int i = nodeCount; i > 0; i--)
	{
		stick[0].push_back(i);
	}

	printHanoi();
	Hanoi(nodeCount, 0, 2);
}
