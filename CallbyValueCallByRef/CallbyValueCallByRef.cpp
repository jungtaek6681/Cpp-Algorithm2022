// CallbyValueCallByRef.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

int call_by_value(int a, int b);
int call_by_address(int* a, int* b);
int call_by_reference(int& a, int& b);
int call_by_const(const int* a, const int* b);

int main()
{
    int num1 = 1;
    int num2 = 2;

    cout << "call_by_value" << endl;
    cout << call_by_value(num1, num2) << endl;
    cout << "num1 : " << num1 << ", num2 : " << num2 << endl << endl;

    cout << "call_by_address" << endl;
    cout << call_by_address(&num1, &num2) << endl;
    cout << "num1 : " << num1 << ", num2 : " << num2 << endl << endl;

    cout << "call_by_reference" << endl;
    cout << call_by_reference(num1, num2) << endl;
    cout << "num1 : " << num1 << ", num2 : " << num2 << endl << endl;

    cout << "call_by_const" << endl;
    cout << call_by_const(&num1, &num2) << endl;
    cout << "num1 : " << num1 << ", num2 : " << num2 << endl << endl;
}

// 값에 의한 복사는 복사본의 값이 변경되기 때문에 원본에는 변경이 없다.
int call_by_value(int a, int b)
{
    a = 0;
    b = 0;

    return a + b;
}

// 주소값을 참조한 포인트 변수를 역참조하여 변경할때는 원본이 교체된다.
int call_by_address(int* a, int* b)
{
    *a = 10;
    *b = 10;

    return *a + *b;
}

// 래퍼런스는 마치 변수처럼 사용하지만 원본을 변경한다.
int call_by_reference(int& a, int& b)
{
    a = 20;
    b = 20;

    return a + b;
}

// 내부에서 값을 변경할 수 없다.
int call_by_const(const int* a, const int* b)
{
    //*a = 30;
    //*b = 30;

    return *a + *b;
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
