// 10-2. DynamicAllocate.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

int main()
{
    int* pointer = new int[100];

    pointer[10] = 100;

    cout << "pointer Address : " << &pointer << endl;
    cout << "new Address : " << pointer << endl;
    cout << "value Address : " << pointer[10] << endl;

    delete[] pointer;
    // 동적으로 할당한 int[100]은 해제하였더라도
    // 정적으로 할당된 pointer는 쓰레기 값을 가지게 되므로 NULL로 초기화해 안전하게 하자.
    // ※ 해제한 메모리를 또 해제할 경우 에러가 발생해 프로그램동작이 멈추게 된다.
    pointer = NULL;
    cout << "init Address : " << pointer << endl;

    // pointer를 NULL로 초기화(메모리 주소값이 NULL일경우 아무일도 하지 않는다)
    // 했기 때문에 실수로 다시 해제를 하였더라도 문제가 없다.
    delete[] pointer;

    // new => delete, new[] => delete[] 로 쌍을 맞춰서 사용한다.
    // - 쌍을 맞추기 않을 경우 일부만 해제되는 등의 문제가 발생할 수 있다.
    int* onePointer = new int;
    *onePointer = 100;
    delete onePointer;

    string* str = new string;
    *str = "aaa";
    cout << *str << endl;
    delete str;

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
