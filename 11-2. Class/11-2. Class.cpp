// 11-2. Class.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

class CCar
{
    // 캡슐화 : 접근제한자를 통해 외부에 공개할 내용과 공개하지 않은 내용을 구분하여 개발자에 맞는 기능만 사용하도록 제한.
    // 접근제한자 private : 클래스 외부에서 이 데이터에 대해 접근할 수 없음.
private:
    string m_owner;

    // 접근제한자 protected : 클래스 외부에서 이 데이터에 대해 접근할 수 없지만, 자식 클래스는 접근이 가능
protected:
    string m_name;
    // 접근제한자 public: 클래스 외부에서도 이 데이터에 대해 접근 가능.
public:
    CCar()      // 기본 생성자 : class를 생성 시킬 때 호출되는 함수로서 반환형이 없이 클래스 이름의 함수로 만듬.
    {
        // 생성자에서는 클래스가 생성되었을 당시에 필요한 작업을 진행한다.
        cout << "CCar 생성자 호출" << endl;

        m_owner = "소유자";
        m_name = "차";
    }
    ~CCar()     // 기본 소멸자 : class를 소멸 시킬 떄 호출되는 함수로서 반환형이 없이 클래스 이름 앞에 ~를 붙여 만듬.
    {
        cout << "CCar 소멸자 호출" << endl;
    }

    // 주의!! : 기본 생성자는 다른 생성자를 만들 경우에 자동으로 만들어지지 않는다.

    string manufacture;
    void showManufacture()
    {
        cout << "이 차의 제조사는 " << manufacture << endl;
    }

    void move()
    {
        cout << "천천히 움직임" << endl;
    }


};

// 상속 : 부모 클래스의 속성을 모두 이어받아 자식에 물려줌.
class CTruck : public CCar      // CCar를 상속받은 클래스, CCar의 모든 속성을 이어 받는다.
{
    void checkStorage();
};

// 정보은닉 : 클래스의 내에 함수를 선언만 존재하고 외부에 그 함수를 구현할 수 있다. 여기서 만약 클래스 정의만을 h(헤더)파일에, 구현을 cpp(소스)파일에 분리하여 구현한다면,
//            내부의 구현방식을 외부에서 확인할 수 없게끔 구현하는 정보은닉을 할 수 있음.
void CTruck::checkStorage()
{
    cout << "저장소 확인" << endl;
}

class CSportCar : public CCar   // CCar를 상속받은 클래스, CCar의 모든 속성을 이어 받는다.
{
public:
    CSportCar()     // 자식 기본생성자
    {
        cout << "CSportCar 생성자 호출" << endl;

        // m_owner = "스포츠카 소유자";         // Error : 부모의 m_onwer의 접근제한자가 private이기 떄문에 수정 불가능
        m_name = "스포츠카";                    // Success : 부모의 m_name의 접근제한자가 public이기 떄문에 수정 가능
        // m_name 맴버변수는 CSportCar에 없지만 부모인 CCar에 있어 모든 속성을 이어 받기에 CSportCar에도 CCar의 m_name 맴버변수를 가지고 있다.
    }
    ~CSportCar()     // 자식 기본소멸자
    {
        cout << "CSportCar 소멸자 호출" << endl;
    }

    void move()         // 부모에 있는 함수와 같은 이름의 함수 생성
    {
        cout << "빠르게 움직임" << endl;
    }
};

int main()
{
    // 클래스 인스턴스 만들기
    // 클래스는 구조 설계와 같고, 그 빵틀을 통해 생성되는 인스턴스와 같다.      -- 클래스(빵틀), 인스턴스(빵)
    // 즉 car1과 car2는 같은 클래스 변수이지만, 같은 데이터를 쓰는 것이 아니다.(구조만 같지 데이터는 서로 생성됐을 당시에 따로 가지고 있다.)
    CCar car1, car2;
    car1.manufacture = "현대자동차";
    car2.manufacture = "기아자동차";
    car1.showManufacture();
    car2.showManufacture();

    CCar        myCar;
    CTruck      myTruck;
    CSportCar   mySportCar;

    // 다형성
    // 모두 같은 move 기능을 수행하지만, myCar와 myTruck은 CCar의 move를 / mySportCar는 CSportCar의 move를 사용한다.
    // 이를 이용하여 같은 함수 이름을 호출하더라도 각기 행동이 다른 "다형성"을 확보할 수 있다.
    // 오버라이딩 : 부모의 함수를 같은 이름의 자식 함수로 덮어쓰는 방식
    myCar.move();           // "천천히 움직임"
    myTruck.move();         // "천천히 움직임"
    mySportCar.move();      // "빠르게 움직임"

    // main 함수의 끝 지역변수로 만든 클래스 인스턴스들이 main 함수의 끝으로 모두 소멸된다.
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