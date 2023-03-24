#include <iostream>
#include <vector>
#include <queue>
#include <utility>

#define GRAPH_SIZE	9

using namespace std;

#define INF 999999

int graph[GRAPH_SIZE][GRAPH_SIZE] =
{
	  0, INF,   1,   7, INF, INF, INF,   5, INF,
	INF,   0, INF, INF, INF,   4, INF, INF, INF,
	INF, INF,   0, INF, INF, INF, INF, INF, INF,
	  5, INF, INF,   0, INF, INF, INF, INF, INF,
	INF, INF,   9, INF,   0, INF, INF, INF,   2,
	  1, INF, INF, INF, INF,   0, INF,   6, INF,
	  3, INF, INF, INF, INF, INF,   0, INF, INF,
	  1, INF, INF, INF,   4, INF, INF,   0, INF,
	INF, INF, INF,   2, INF, INF, INF, INF,   0
};

void dijkstra(int start, int distance[GRAPH_SIZE])
{
	bool visited[GRAPH_SIZE] = { false };
	for (int i = 0; i < GRAPH_SIZE; i++)
	{
		distance[i] = graph[start][i];
	}
	visited[start] = true;

	for (int i = 0; i < GRAPH_SIZE; i++)
	{
		// 1. 방문하지 않은 정점 중 가장 가까운 정점부터 탐색
		int next = 0;
		int minDistance = INF;
		for (int j = 0; j < GRAPH_SIZE; j++)
		{
			if (!visited[j] &&	// 방문하지 않은 정점
				distance[j] < minDistance)	// 가장 가까운 정점
			{
				next = j;
				minDistance = distance[j];
			}
		}

		// 2. 직접연결된 거리보다 거쳐서 더 짧아진다면 갱신.
		for (int j = 0; j < GRAPH_SIZE; j++)
		{
			// distance[j] : 목적지까지 직접 연결된 거리
			// distance[next] : 탐색중인 정점까지 거리
			// graph[next][j] : 탐색중인 정점부터 목적지의 거리
			if (distance[j] > distance[next] + graph[j][next])
			{
				distance[j] = distance[next] + graph[j][next];
			}
		}
		visited[next] = true;
	}
}

void priority_dijkstra(int start, int distance[GRAPH_SIZE], vector<int> path[GRAPH_SIZE])
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(pair<int, int>(0, start));

	for (int i = 0; i < GRAPH_SIZE; i++)
	{
		distance[i] = INF;
		path[i].push_back(start);
	}
	distance[start] = 0;

	while (!pq.empty())
	{
		// 우선순위 큐에서 꺼낼 경우 다음으로 가장 가까운 정점이 꺼내어진다.
		int next = pq.top().second;
		int cost = pq.top().first;
		pq.pop();

		// 다음 정점보다 더 가중치가 높은 경로는 무시
		if (distance[next] < cost)
			continue;

		for (int i = 0; i < GRAPH_SIZE; i++)
		{
			// distance[i] : 목적지까지 직접 연결된 거리
			// distance[next] : 탐색중인 정점까지 거리
			// graph[next][i] : 탐색중인 정점부터 목적지의 거리
			if (distance[i] > distance[next] + graph[next][i])
			{
				distance[i] = distance[next] + graph[next][i];
				pq.push(pair<int, int>(distance[i], i));

				path[i] = path[next];
				path[i].push_back(i);
			}
		}
	}
}

int main()
{
	int distance[GRAPH_SIZE];

	for (int index = 0; index < GRAPH_SIZE; index++)
	{
		vector<int> path[GRAPH_SIZE];

		cout << index << " 정점부터 탐색" << endl;
		priority_dijkstra(index, distance, path);
		for (int i = 0; i < GRAPH_SIZE; i++)
		{
			cout << index << " -> " << i << " : ";
			cout << distance[i] << endl << " 경로 : ";

			for (int j = 0; j < path[i].size(); j++)
			{
				cout << path[i][j];
				if (j != path[i].size() - 1)
					cout << " -> ";
				else
					cout << endl;
			}
		}
		cout << endl;
	}
}
