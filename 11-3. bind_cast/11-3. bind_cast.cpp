// 11-3. bind_cast.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;

// 추상화
class CMonster
{
protected:
	string name;
	int hp;
public:
	CMonster()
	{
		hp = 20;
	}

	virtual ~CMonster()
	{

	}

	virtual void TakeHit(int damage)
	{
		hp -= damage;
		cout << name << "이 데미지 " << damage << "를 받아 체력이 " << hp << "가 되었다." << endl;
	}

	void Die()
	{
		cout << name << "이 쓰러졌다." << endl;
	}
};

class CDragon : public CMonster
{
public:
	CDragon()
	{
		name = "드래곤";
		hp = 50;
	}

	virtual ~CDragon()
	{

	}

	void Breath()
	{
		cout << "불뿜기" << endl;
	}

	virtual void TakeHit(int damage)
	{
		if (hp >= 0)
		{
			cout << "데미지를 받고 분노한다." << endl;
		}
		else
		{
			Die();
		}
	}
};

class CSlime : public CMonster
{
public:
	CSlime()
	{
		name = "슬라임";
	}

	virtual ~CSlime()
	{
	}

	virtual void TakeHit(int damage)
	{
		cout << "슬라임이 꿈틀댄다." << endl;
		if (hp <= 0)
			Split();
	}

	void Split()
	{
		cout << name << "이 분열했다" << endl;
	}
};

class CPlayer
{
private:
	int attackPoint;

public:
	CPlayer()
	{
		attackPoint = 10;
	}

	void Attack(CMonster monster)
	{
		cout << "플레이어가 몬스터를 때린다" << endl;
		monster.TakeHit(attackPoint);
	}

	void Attack(CMonster* pMonster)
	{
		cout << "플레이어가 몬스터를 때린다" << endl;
		pMonster->TakeHit(attackPoint);
	}
};

int main()
{
	// 정적 바인딩 : 컴파일 시점에 이루어지는 바인딩
	// 장점	(1) : 컴파일시 타입에 대한 정보가 결정되기 때문에 속도가 빠름
	//		(2) : 타입 에러로 인한 문제를 소스편집당시에 발견할 수 있음. 안정적.
	// 단점	(1)	: 컴파일시 결정됨으로 동작 중에 변경이 불가능하다.
	CPlayer player;
	CMonster monster;
	CDragon dragon;
	CSlime slime;

	// 다형성이 확보 될 것으로 원했지만 실제로 그렇지 않다.
	cout << "<정적바인딩>" << endl << endl;
	player.Attack(monster);
	cout << endl;
	player.Attack(dragon);
	cout << endl;
	player.Attack(slime);
	cout << endl << endl;

	// 동적바인딩 : 런타임 당시에 바인딩
	// 장점	(1)	: 실행 당시에 필요한 객체의 함수를 호출함으로써 유연성을 갖고 있다.
	// 단점	(1) : 변수의 예상치 못한 타입으로 인해 안정성이 저하.
	cout << "<동적바인딩>" << endl << endl;
	CMonster* pMonster = NULL;
	pMonster = new CSlime();
	//player.Attack(pMonster);

	// 정적 캐스팅 : 형 변환 시점이 컴파일 시점
	cout << "<정적캐스팅>" << endl << endl;
	cout << "정적 캐스팅은 컴파일 시점에 결정됨으로 문제가 있는 경우 사용 불가능 하다." << endl;
	monster = (CMonster)dragon;
	// player = (CPlayer)dragon;	// 정적 캐스팅의 경우 부모클래스가 같지 않은 경우 가능하지 않다.
	// player = static_cast<CPlayer>(dragon);
	cout << "하지만 포인터 변수는 모두 주소값이기 때문에 변환이 가능하다. 위험하니 동적캐스팅을 진행해야 한다." << endl << endl;
	// CPlayer* pPlayer = (CPlayer*)pMonster;	// 굉장히 위험하다. 동적 할당된 객체가 정확한 자료형이 아닐경우

	// 동적 캐스팅 : 형 변환 시점이 런타임 시점
	//				형 변환이 성공적이면 주소값이 반환
	//				형 변환이 실패한다면 NULL이 반환
	cout << "<동적캐스팅>" << endl << endl;
	CDragon* pDragon = dynamic_cast<CDragon*>(pMonster);
	if (pDragon != NULL)
	{
		cout << "드래곤의 동적 캐스팅 성공" << endl;
	}
	else
	{
		cout << "드래곤의 동적 캐스팅 실패" << endl;
	}

	CSlime* pSlime = dynamic_cast<CSlime*>(pMonster);		// pMonster가 런타임 시점에 슬라임이었기 때문에 주소값 반환
	if (pSlime != NULL)
	{
		cout << "슬라임의 동적 캐스팅 성공" << endl;
	}
	else
	{
		cout << "슬라임의 동적 캐스팅 실패" << endl;
	}

	delete pMonster;
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
