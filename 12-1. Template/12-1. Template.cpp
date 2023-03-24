#include <iostream>

using namespace std;

//int sum(int left, int right) { return left + right; }
//float sum(float left, float right) { return left + right; }
//double sum(double left, double right) { return left + right; }

template <typename T>
T sum(T left, T right) { return left + right; }

int main()
{
    int iValue = sum<int>(10, 20);
    float fValue = sum<float>(3.2f, 1.0f);
    double dValue = sum<double>(1.5376432, 8.295739);
}

