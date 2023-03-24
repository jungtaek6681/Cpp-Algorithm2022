// 11-1. DataType.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
// 

#include <iostream>

using namespace std;

// 구조체 선언
struct StructSample
{
    char name[10];
    int number;
};

// 공용체 선언
union UnionSample
{
    int number1;
    short number2;
};

// 열거체 선언
enum class Company { GOOGLE, KAKAO, NAVER };

int main()
{
    // 배열 사용
    int array[10] = { 0 };
    cout << array[5] << endl;

    // 구조체 사용
    StructSample structSample = { "struct ", 100 };
    cout << structSample.name << " // " << structSample.number << endl;

    // 공용체 사용
    UnionSample unionSample;
    // - 모든 멤버가 같은 메모리 공간을 차지하고 있어 한개의 값만 바꿔도 모두 변경된다.
    unionSample.number1 = 1;
    cout << unionSample.number1 << " // " << unionSample.number2 << "\n";

    // 열거체 사용
    // - 전역에서 사용되는 상수를 정의하여 사용할 수 있다.
    Company company = Company::KAKAO;

    if (Company::KAKAO != company)
    {

    }
    else if (1 != company)      // 열거체가 아니기에 문제 발생
    {

    }

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
