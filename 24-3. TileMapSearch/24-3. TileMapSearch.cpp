#include <iostream>
#include <queue>

using namespace std;

// [y][x]
bool graphMap[9][7] =
{
	0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 0,
	0, 1, 0, 1, 0, 0, 0,
	0, 1, 0, 1, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

struct position
{
	int x;
	int y;

	position(int y, int x)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(const position& other)
	{
		return x == other.x && y == other.y;
	}
};

bool visited[9][7] = { false };
void dfs(position pos)
{
	visited[pos.y][pos.x] = true;
	cout << "(" << pos.y << "," << pos.x << ")" << "을 탐색했다." << endl;

	// 상하좌우 탐색
	// 좌
	if (graphMap[pos.y][pos.x - 1] &&	// 갈수 있는 타일이면서
		!visited[pos.y][pos.x - 1])		// 방문하지 않은 경우
	{
		dfs(position(pos.y, pos.x - 1));
	}
	// 우
	if (graphMap[pos.y][pos.x + 1] &&	// 갈수 있는 타일이면서
		!visited[pos.y][pos.x + 1])		// 방문하지 않은 경우
	{
		dfs(position(pos.y, pos.x + 1));
	}
	// 상
	if (graphMap[pos.y - 1][pos.x] &&	// 갈수 있는 타일이면서
		!visited[pos.y - 1][pos.x])		// 방문하지 않은 경우
	{
		dfs(position(pos.y - 1, pos.x));
	}
	// 하
	if (graphMap[pos.y + 1][pos.x] &&	// 갈수 있는 타일이면서
		!visited[pos.y + 1][pos.x])		// 방문하지 않은 경우
	{
		dfs(position(pos.y + 1, pos.x));
	}
}

void bfs(position pos)
{
	queue<position> bfsQueue;	// 다음 탐색할 정점을 보관할 Queue
	bool visited[9][7] = {false};

	bfsQueue.push(pos);
	while (!bfsQueue.empty())
	{
		position next = bfsQueue.front();
		bfsQueue.pop();
		visited[next.y][next.x] = true;
		cout << "(" << next.y << "," << next.x << ")" << "을 탐색했다." << endl;

		// 상하좌우 탐색
		// 좌
		if (graphMap[next.y][next.x - 1] &&		// 갈수 있는 타일이면서
			!visited[next.y][next.x - 1])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y, next.x - 1));
		}
		// 우
		if (graphMap[next.y][next.x + 1] &&		// 갈수 있는 타일이면서
			!visited[next.y][next.x + 1])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y, next.x + 1));
		}
		// 상
		if (graphMap[next.y - 1][next.x] &&		// 갈수 있는 타일이면서
			!visited[next.y - 1][next.x])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y - 1, next.x));
		}
		// 하
		if (graphMap[next.y + 1][next.x] &&		// 갈수 있는 타일이면서
			!visited[next.y + 1][next.x])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y + 1, next.x));
		}
	}
}

bool mazeVisited[9][7] = { false };
bool dfsMazeEscape(position pos, position goal)
{
	mazeVisited[pos.y][pos.x] = true;
	cout << "(" << pos.y << "," << pos.x << ")" << "을 탐색했다." << endl;

	if (pos == goal)
		return true;

	// 상하좌우 탐색
		// 좌
	if (graphMap[pos.y][pos.x - 1] &&	// 갈수 있는 타일이면서
		!mazeVisited[pos.y][pos.x - 1])		// 방문하지 않은 경우
	{
		bool ret = dfsMazeEscape(position(pos.y, pos.x - 1), goal);
		if (ret) return true;
	}
	// 우
	if (graphMap[pos.y][pos.x + 1] &&	// 갈수 있는 타일이면서
		!mazeVisited[pos.y][pos.x + 1])		// 방문하지 않은 경우
	{
		bool ret = dfsMazeEscape(position(pos.y, pos.x + 1), goal);
		if (ret) return true;
	}
	// 상
	if (graphMap[pos.y - 1][pos.x] &&	// 갈수 있는 타일이면서
		!mazeVisited[pos.y - 1][pos.x])		// 방문하지 않은 경우
	{
		bool ret = dfsMazeEscape(position(pos.y - 1, pos.x), goal);
		if (ret) return true;
	}
	// 하
	if (graphMap[pos.y + 1][pos.x] &&	// 갈수 있는 타일이면서
		!mazeVisited[pos.y + 1][pos.x])		// 방문하지 않은 경우
	{
		bool ret = dfsMazeEscape(position(pos.y + 1, pos.x), goal);
		if (ret) return true;
	}
	return false;
}

bool bfsMazeEscape(position pos, position goal)
{
	queue<position> bfsQueue;	// 다음 탐색할 정점을 보관할 Queue
	bool visited[9][7] = { false };

	bfsQueue.push(pos);
	while (!bfsQueue.empty())
	{
		position next = bfsQueue.front();
		bfsQueue.pop();
		visited[next.y][next.x] = true;
		cout << "(" << next.y << "," << next.x << ")" << "을 탐색했다." << endl;

		if (next == goal)
			return true;

		// 상하좌우 탐색
		// 좌
		if (graphMap[next.y][next.x - 1] &&		// 갈수 있는 타일이면서
			!visited[next.y][next.x - 1])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y, next.x - 1));
		}
		// 우
		if (graphMap[next.y][next.x + 1] &&		// 갈수 있는 타일이면서
			!visited[next.y][next.x + 1])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y, next.x + 1));
		}
		// 상
		if (graphMap[next.y - 1][next.x] &&		// 갈수 있는 타일이면서
			!visited[next.y - 1][next.x])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y - 1, next.x));
		}
		// 하
		if (graphMap[next.y + 1][next.x] &&		// 갈수 있는 타일이면서
			!visited[next.y + 1][next.x])		// 방문하지 않은 경우
		{
			bfsQueue.push(position(next.y + 1, next.x));
		}
	}

	return false;
}

int main()
{
	cout << "깊이 우선 탐색" << endl;
	dfs(position(7, 1));
	cout << endl;

	cout << "너비 우선 탐색" << endl;
	bfs(position(7, 1));
	cout << endl;

	cout << "깊이 우선 미로 찾기" << endl;
	if (dfsMazeEscape(position(7, 1), position(1, 5)))
		cout << "탈출했다!" << endl;
	else
		cout << "탈출구가 없다!" << endl;
	cout << endl;

	cout << "너비 우선 미로 찾기" << endl;
	if (bfsMazeEscape(position(7, 1), position(1, 5)))
		cout << "탈출했다!" << endl;
	else
		cout << "탈출구가 없다!" << endl;
}