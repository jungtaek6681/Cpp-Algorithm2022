#include <iostream>

using namespace std;

template <typename T>
void Bigger(T left, T right)
{
    if (left > right)
    {
        cout << "왼쪽이 더 큽니다." << endl;
    }
    else
    {
        cout << "오른쪽이 더 큽니다." << endl;
    }
}

class Student
{
public:
    Student(string name, int num)
    {
        this->name = name;
        this->num = num;
    }

    string name;
    int num;

    // this > other
    bool operator>(Student other)
    {
        // 학번으로 비교하겠다.
        if (this->num > other.num)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    cout << "2 과 5를 비교" << endl;
    Bigger<int>(2, 5);
    cout << "8.1f 과 1.3f을 비교" << endl;
    Bigger<float>(8.1f, 1.3f);
    cout << "2.0 과 3.0을 비교" << endl;
    Bigger<double>(2.0, 3.0);

    Student student1("홍길동", 10);
    Student student2("김철수", 20);
    cout << "홍길동(10)과 김철수(20)를 비교" << endl;
    Bigger<Student>(student1, student2);
}