// CppProject.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

int main()
{
    int value = 10;
    // ※ 포인터 변수는 항상 0 또는 NULL로 초기화 하고 사용할때는 항상 0 또는 NULL인지를 확인한다.
    //    - 0으로 초기화 하지 않는다면 쓰레기 값을 가지게 되고 
    //      만약 쓰레기 값이 다른 중요한 정보를 접근할 경우 
    //      심각한 문제가 발생할 여지가 있다.
    int* pointer = NULL;

    // 1. pointer는 포인터형 변수 이므로 value의 주소값만 받을 수 있다.
    // value 앞에 &(Ampersand)를 붙여주면 주소값이 된다.
    pointer = &value;
    // [Error]
    //pointer = value;

    // 2. pointer가 가리키고 있는 값을 출력할때는 앞에 *를 붙여야 한다.
    cout << "Ex2." << endl;
    cout << "ADDRESS : " << pointer << endl;
    cout << "VALUE : " << *pointer << endl;
    cout << endl;

    // 3. 포인터변수에 주소를 지정할때는 동일한 자료형의 주소만 받을 수 있다.
    float* pointer_float;
    float temp = (float)value;
    pointer_float = &temp;
    cout << "Ex3-1." << endl;
    cout << "VALUE : " << *pointer_float << endl;
    cout << endl;
    // [Error] : 다른 자료형의 포인트 변수라면 형변환을 해주면 에러가 나지는 않지만 쓰레기 값이 출력된다.
    // - 이는 정수타입의 메모리를 실수타입으로 분석해버려서 이다.
    float* pointer_temp;
    pointer_temp = (float*)&value;
    cout << "Ex3-2." << endl;
    cout << "VALUE : " << *pointer_temp << endl;
    cout << endl;
    // [Error] : 메모리에는 변수의 값만 저장하기 때문에 자료형을 알 수가 없기때문에 규칙위반이다.
    //pointer_temp = &value;

    // 4. 포인터변수 크기는 시스템의 기본연산단위를 사용한다. 자료형별 차이는 없다.
    // (16bit=>2byte, 32=>4byte, 64=>8byte)
    cout << "Ex5." << endl;
    cout << "char* \t\t: " << sizeof(char*) << " bytes" << endl;
    cout << "int* \t\t: " << sizeof(int*) << " bytes" << endl;
    cout << "float* \t\t: " << sizeof(float*) << " bytes" << endl;
    cout << "double* \t: " << sizeof(double*) << " bytes" << endl;
    cout << endl;
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
