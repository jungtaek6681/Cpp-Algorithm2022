#include <iostream>
#include <list>
#include <cmath>
#include <algorithm>
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
	bool active;		// 활성화 여부 (탐색된 여부)
	ASNode* connect;	// 이 정점을 탐색한 정점의 주소값
	Point point;		// 현재 좌표

	int F;				// 예상 최단거리(G + H)
	int G;				// 지금까지 온 거리
	int H;				// 예상 거리(장애물 X)

	ASNode(bool active, ASNode* connect, Point point, int G, int H)
	{
		this->active = active;
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

// 정점 리스트 중 다음으로 탐색해야할 F가 가장 낮은 정점 찾기
list<ASNode>::iterator findMinFNode(list<ASNode>& nodeList)
{
	list<ASNode>::iterator minFIter = nodeList.end();
	int minF = INF;
	int minH = INF;

	for (list<ASNode>::iterator iter = nodeList.begin();
		iter != nodeList.end();
		iter++)
	{
		if (true == iter->active && // 활성화 됐으면서
			(iter->F < minF ||		// F가 가장 낮은 정점
			iter->F == minF && iter->H < minH))	// F가 똑같다면, H가 작은 정점
		{
			minFIter = iter;
			minF = iter->F;
			minH = iter->H;
		}
	}

	return minFIter;
}

// 정점 리스트 중 좌표에 해당하는 정점 찾기
list<ASNode>::iterator findNode(list<ASNode>& nodeList, Point point)
{
	list<ASNode>::iterator findIter = nodeList.end();
	for (list<ASNode>::iterator iter = nodeList.begin();
		iter != nodeList.end();
		iter++)
	{
		if (iter->point == point)
			findIter = iter;
	}
	return findIter;
}

						//  상  하  좌  우 우상 좌상 우하 좌하
const int directionX[8] = { 0,  0, -1, +1, +1, -1, +1, -1};
const int directionY[8] = {+1, -1,  0,  0, +1, +1, -1, -1};

list<Point> astar(bool map[GRAPH_SIZE][GRAPH_SIZE], Point start, Point end)
{
	list<ASNode> nodeList;	// 탐색해야 할 노드들을 보관할 자료구조
	
	ASNode startNode(true, nullptr, start, 0, getH(start, end));
	nodeList.push_back(startNode);

	while (true)
	{
		// 1. 다음으로 탐색할 정점을 선정
		// 다음으로 탐색할 정점 : F가 가장 낮은 정점
		// F가 같은 정점끼리 비교 : H가 낮은 정점
		list<ASNode>::iterator minFIter = findMinFNode(nodeList);

		// 2. 더이상 탐색할 정점이 없는 경우
		// 경로가 없다고 판단하여 종료
		if (minFIter == nodeList.end())
		{
			break;
		}

		// 3. 다음으로 탐색할 정점이 도착지인 경우
		// 도착했다고 판단해서 경로 return;
		if (minFIter != nodeList.end() && minFIter->point == end)
		{
			ASNode endNode = *minFIter;
			ASNode* pPathNode = &endNode;

			list<Point> path;
			while (pPathNode != nullptr)
			{
				path.push_front(pPathNode->point);
				pPathNode = pPathNode->connect;
			}
			return path;
		}

		// 4. AStar 탐색을 진행
		// 상하좌우 대각선
		for (int i = 0; i < 8; i++)
		{
			int x = minFIter->point.x + directionX[i];
			int y = minFIter->point.y + directionY[i];

			list<ASNode>::iterator nodeIter = findNode(nodeList, Point(x, y));

			// 4-0. 탐색하면 안되는 경우
			// 맵을 벗어났을 경우
			if (x < 0 || x >= GRAPH_SIZE || y < 0 || y >= GRAPH_SIZE)
				continue;
			// 벽일 경우
			else if (false == graphMap[y][x])
				continue;
			// 이미 탐색된 정점일 경우
			else if (nodeIter != nodeList.end() && false == nodeIter->active)
				continue;

			// 정점의 F, G ,H
			int G;
			if (minFIter->point.x == x || minFIter->point.y == y)
				G = minFIter->G + 10;
			else
				G = minFIter->G + 14;
			int H = getH(Point(x, y), end);
			int F = G + H;

			// 4-1. 정점리스트에 이미 해당 정점이 있는 경우
			// F가 작으면 덮어씌우기, F가 같고 H가 작으면 덮어씌우기
			if (nodeIter != nodeList.end() && // 탐색하려고 했던 정점이 리스트에 있었을 경우
				nodeIter->F > F)			// 이전의 F값이 새로운 F보다 큰 경우
			{
				nodeIter->F = F;
				nodeIter->H = H;
				nodeIter->G = G;
				nodeIter->connect = &(*minFIter);
			}

			// 4-2. 정점리스트에 해당 정점이 없는 경우
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