#include <iostream>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
struct GraphNode
{
	T data;
	vector<GraphNode*> pNodes;
};

// 정점의 연결상황을 저장하는 자료구조로 2차원 배열을 사용하는 경우가 많다.
// 각 2차원 배열의 값은 [출발점][도착점]의 연결 여부로 저장한다.
// ex  graph[1][3] : 정점1 에서 정점3 까지의 연결 상황
bool graph[7][7] =
{
	0, 0, 0, 0, 0, 0, 1,
	0, 0, 1, 0, 0, 1, 1,
	0, 1, 0, 1, 0, 0, 0,
	0, 0, 1, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0
};

// 깊이 우선 탐색 : 최대한 깊이 내려간 뒤, 더이상 깊이 갈 곳이 없을 경우 옆을 탐색
// 재귀 & 스택
void dfs(int start, bool visited[])
{
	// 탐색이 진행된 정점을 visited 배열에 표시
	// 탐색이 진행된 정점은 다음 탐색 대상에서 제외
	visited[start] = true;
	cout << start << "을 탐색했다." << endl;
	for (int i = 0; i < 7; i++)
	{
		if (graph[start][i] &&	// 연결이 되어 있는 정점
			!visited[i])		// 탐색하지 않은 정점
		{
			dfs(i, visited);
		}
	}
}

// 너비 우선 탐색 : 최대한 옆부터 탐색한 다음, 다음 깊이로 이동해서 탐색
// 큐
void bfs(int start)
{
	queue<int> bfsQueue;	// 다음 탐색할 정점을 보관할 Queue
	bool visited[7] = { false };

	bfsQueue.push(start);
	while (!bfsQueue.empty())
	{
		int next = bfsQueue.front();
		bfsQueue.pop();
		visited[next] = true;
		cout << next << "을 탐색했다." << endl;

		for (int i = 0; i < 7; i++)
		{
			if (graph[next][i] &&	// 연결이 되어 있는 정점
				!visited[i])		// 탐색하지 않은 정점
			{
				bfsQueue.push(i);	// Queue에 탐색할 정점으로 추가함.
			}
		}
	}
}

int main()
{
	cout << "깊이 우선 탐색" << endl;
	bool visited[7] = { false };
	dfs(2, visited);
	cout << endl;

	cout << "너비 우선 탐색" << endl;
	bfs(2);
	cout << endl;
}