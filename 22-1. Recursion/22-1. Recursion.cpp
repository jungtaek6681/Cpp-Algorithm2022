#include <iostream>
#include <vector>

// 재귀 함수 : 자기 자신을 호출하는 함수
void wrongRecursion()
{
	// 함수가 계속해서 호출되어 호출 스택이 가득참.
	// 그 결과 더이상 스택영역에 사용할 공간이 없어짐.
	// 스택 오버플로우 : 스택영역에 더 이상 사용할 공간이 없어서 프로그램이 종료됨.
	wrongRecursion();
}

// Factorial : 
// x! = x * (x-1)!;
// 1! = 1;
int factorial(int x)
{
	// 재귀 함수는 함수의 종료 조건이 있어야 한다.
	if (x == 1)
		return 1;
	else
		return x * factorial(x - 1);
	// 오버 헤드 : 어떤 처리를 하기위해 들어가는 간접적인 처리 시간, 메모리 등을 말한다.
}

// 재귀 함수의 사용 좋은 상황 : 분할정복
// 분할정복 : 전체의 큰 문제를 같은 유형의 하위 작업으로 분할하여(분할)
//			 작은 문제부터 해결한 결과를 다시 합치는 방법(정복)
// ex : 폴더내에 전체 파일 복사&출력&삭제, 회사-부서-팀-사원 순의 하위 분류 작업
//		이진트리의 순회, 등

// 재귀 함수의 사용이 좋은 상황 1
// 소스의 재사용으로 코드의 가독성이 높아지는 경우
// 반복으로는 간단하게 표현이 어려운 경우

//void printNode(Node* node)
//{
//	if (nullptr == node)
//		return;
//
//	printNode(node->pLeft);
//	std::cout << node->data;
//	printNode(node->pRight);
//}

// 재귀 함수의 사용이 좋은 상황 2
// 작은 단위의 작업이 큰 작업의 작업효율을 늘려줌
// ex : 거듭제곱, 병합정렬, 등
double pow(double x, int n)
{
	// x^n = x*x* ... *x (n번)
	// x^n = (x * x)^(n/2)

	if (n == 0)
		return 1;
	else if (n % 2 == 0)
		return pow(x * x, n / 2);
	else
		return x * pow(x * x, (n - 1) / 2);
}

// 재귀 함수의 사용이 좋지 않은 상황 1
// 반복과 같은 작업인 경우, 오버헤드가 있어서 비효율적
int sigma(int x)
{
	// 1. 재귀를 통한 구현
	// 함수의 오버헤드가 있기 때문에 반복보다 비효율적 : 시간복잡도 O(n) + 오버헤드
	if (x == 1)
		return 1;
	else
		return x + sigma(x - 1);

	// 2. 반복을 통한 구현
	// 함수의 오버헤드가 없기 때문에 효율적 : 시간복잡도 O(n)
	int result = 0;
	for (int i = 1; i <= x; i++)
		result += i;
	return result;

	// +A. 수식을 통한 구현
	// 반복 또한 필요 없는 가장 효율적인 방법(기출문제) : 시간복잡도 O(1)
	return x * (x + 1) * 0.5f;
}

// 재귀 함수의 사용이 좋지 않은 상황 2
// 분할정복을 통해 오히려 작업이 추가되는 경우
// fibonacci : 1 1 2 3 5 8 13 21 34 55 ...
// fibonacci(n) = fibonacci(n - 1) + fibonacci(n - 2);
// fibonacci(1) == 1, fibonacci(2) == 1
int fibonacci(int n)
{
	// 1. 재귀를 통한 구현
	// 소스의 재사용으로 의미는 분명. 하지만 시간 효율이 최악 : 시간복잡도 O(2^n)
	if (n == 1 || n == 2)
		return 1;
	else
		return fibonacci(n - 2) + fibonacci(n - 1);

	// 2. 반복을 통한 구현
	// n번째 요소를 확인하기 위해 n번 반복 : 시간복잡도 O(n)
	int n1 = 1;
	int n2 = 1;
	int result = 1;
	for (int i = 2; i <= n; i++)
	{
		n1 = n2;
		n2 = result;
		result = n1 + n2;
	}
	return result;
}

int main()
{
	wrongRecursion();
}
