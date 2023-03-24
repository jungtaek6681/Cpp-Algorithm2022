#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <cmath>
#include <utility>

using namespace std;

#define INF	999999
#define GRAPH_SIZE	9

struct Point
{
	int x;
	int y;

	Point()
	{
		x = -1;
		y = -1;
	}

	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(const Point& other)
	{
		return this->x == other.x && this->y == other.y;
	}

	bool operator!=(const Point& other)
	{
		return !(*this == other);
	}
};

struct ASNode
{
	ASNode* connect;	// 이 정점을 탐색한 정점의 주소값
	Point point;		// 현재 좌표
	list<Point> path;	// 정점까지의 경로

	int F;				// 예상 최단거리(G + H)
	int G;				// 지금까지 온 거리
	int H;				// 예상 거리(장애물 X)

	ASNode(ASNode* connect, Point point, int G, int H)
	{
		this->connect = connect;
		this->point = point;
		this->G = G;
		this->H = H;
		this->F = G + H;
	}
};

// [y][x]
bool graphMap[GRAPH_SIZE][GRAPH_SIZE] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 1, 1, 1, 0,
	0, 1, 0, 0, 0, 1, 0, 1, 0,
	0, 1, 0, 0, 0, 1, 0, 1, 0,
	0, 1, 1, 1, 1, 1, 0, 1, 0,
	0, 1, 0, 1, 0, 0, 0, 1, 0,
	0, 1, 0, 1, 0, 0, 0, 1, 0,
	0, 1, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0
};

int getH(Point start, Point end)
{
	// 대각선으로 최대한 이동 후 남은 직선을 가주면 가장 작은 H

	int xSize = abs(start.x - end.x);	// 가로로 가야하는 횟수
	int ySize = abs(start.y - end.y);	// 세로로 가야하는 횟수

	int straight;	// 직선으로 가야하는 횟수
	int diagonal;	// 대각선으로 가야하는 횟수

	if (xSize > ySize)
	{
		diagonal = ySize;
		straight = xSize - diagonal;
	}
	else
	{
		diagonal = xSize;
		straight = ySize - diagonal;
	}

	return 10 * straight + 14 * diagonal;
}

//  상  하  좌  우 우상 좌상 우하 좌하
const int directionX[8] = { 0,  0, -1, +1, +1, -1, +1, -1 };
const int directionY[8] = { +1, -1,  0,  0, +1, +1, -1, -1 };

struct ASNodeCompare
{
	bool operator()(const ASNode& left, const ASNode& right)
	{
		if (left.F == right.F)
			return (left.H < right.H) ? true : false;
		else
			return (left.F < right.F) ? true : false;
	}
};

list<Point> astar(bool map[GRAPH_SIZE][GRAPH_SIZE], Point start, Point end)
{
	priority_queue<ASNode, vector<ASNode>, ASNodeCompare()> pq;
	bool visited[GRAPH_SIZE][GRAPH_SIZE] = { false };

	ASNode startNode(nullptr, start, 0, getH(start, end));
	pq.push(startNode);

	while (!pq.empty())
	{
		// 1. 다음으로 탐색할 정점을 선정
		// 다음으로 탐색할 정점 : F가 가장 낮은 정점
		// F가 같은 정점끼리 비교 : H가 낮은 정점
		ASNode nextNode = pq.top();
		pq.pop();

		// 2. 다음으로 탐색할 정점이 도착지인 경우
		// 도착했다고 판단해서 경로 return;
		if (nextNode.point == end)
			return nextNode.path;

		// 3. AStar 탐색을 진행
		// 상하좌우 대각선
		for (int i = 0; i < 8; i++)
		{
			int x = nextNode.point.x + directionX[i];
			int y = nextNode.point.y + directionY[i];

			// 3-0. 탐색하면 안되는 경우
			// 맵을 벗어났을 경우
			if (x < 0 || x >= GRAPH_SIZE || y < 0 || y >= GRAPH_SIZE)
				continue;
			// 벽일 경우
			else if (false == graphMap[y][x])
				continue;
			// 이미 탐색된 정점일 경우
			else if (visited[y][x])
				continue;

			// 정점의 F, G ,H
			int G;
			if (nextNode.point.x == x || nextNode.point.y == y)
				G = nextNode.G + 10;
			else
				G = nextNode.G + 14;
			int H = getH(Point(x, y), end);
			int F = G + H;

			ASNode node = ASNode(&nextNode, Point(x, y), G, H);

			// 3-1. 정점리스트에 이미 해당 정점이 있는 경우
			// F가 작으면 덮어씌우기, F가 같고 H가 작으면 덮어씌우기
			if (nodeIter != nodeList.end() && // 탐색하려고 했던 정점이 리스트에 있었을 경우
				nodeIter->F > F)			// 이전의 F값이 새로운 F보다 큰 경우
			{
				nodeIter->F = F;
				nodeIter->H = H;
				nodeIter->G = G;
				nodeIter->connect = &(*minFIter);
			}

			// 3-2. 정점리스트에 해당 정점이 없는 경우
			// 정점리스트에 해당 정점을 추가
			else if (nodeIter == nodeList.end())
			{
				nodeList.push_back(ASNode(true, &(*minFIter), Point(x, y), G, H));
			}
		}

		// 5. 탐색을 완료한 정점은 비활성화
		minFIter->active = false;
	}

	// 도착할 수 없는 경우, 비어 있는 리스트를 return
	// 경로가 비어 있을 경우는 도착할 수 없다라고 판단할 수 있다.
	return list<Point>();
}

void printMap(const bool graph[GRAPH_SIZE][GRAPH_SIZE])
{
	for (int i = 0; i < GRAPH_SIZE; i++)
	{
		for (int j = 0; j < GRAPH_SIZE; j++)
		{
			cout << graph[i][j] << " ";
		}
		cout << endl;
	}
}

void printPathMap(const bool graph[GRAPH_SIZE][GRAPH_SIZE], list<Point> path)
{
	char pathMap[GRAPH_SIZE][GRAPH_SIZE];
	for (int i = 0; i < GRAPH_SIZE; i++)
	{
		for (int j = 0; j < GRAPH_SIZE; j++)
		{
			if (graph[i][j] == 0)
				pathMap[i][j] = '#';
			else if (graph[i][j] == 1)
				pathMap[i][j] = ' ';
		}
	}

	for (list<Point>::iterator iter = path.begin(); iter != path.end(); iter++)
	{
		pathMap[iter->y][iter->x] = '*';
	}
	Point start = path.front();
	Point end = path.back();
	pathMap[start.y][start.x] = 'S';
	pathMap[end.y][end.x] = 'E';

	for (int i = 0; i < GRAPH_SIZE + 2; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < GRAPH_SIZE; i++)
	{
		cout << "#";
		for (int j = 0; j < GRAPH_SIZE; j++)
		{
			cout << pathMap[i][j];
		}
		cout << "#" << endl;
	}
	for (int i = 0; i < GRAPH_SIZE + 2; i++)
		cout << "#";
	cout << endl;
}

int main()
{
	list<Point> path = astar(graphMap, Point(1, 1), Point(7, 7));

	if (path.size() == 0)
		cout << "경로를 찾지 못했습니다." << endl;
	else
		printPathMap(graphMap, path);
}