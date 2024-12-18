/******************************************************************************

Задание: (5*28)                                 Ограничения: [-6.5; 6.5]
5) -9804x^32 + 4423,3x^16 - 8,7654x^8
            = ((-9804x^{16} + 4423.3)x^8 - 8.7654) x^8
28) 9,09x^9 - 9,09x^3 + 9,09x
            = (x^6 - 1) x^2 + 1) 9.09x

Автор: Егор Даричев (гр. 4352)                  Версия: 1.1.14
Даты: начало: 04.09.2024                        конец: завтра

*******************************************************************************/

#include <iostream>
#include <iomanip>
#include<fstream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    float x, P1, P2;
    const float a1 = -9804, b1 = 4423.3, c1 = -8.7654, a2 = 9.09;
    cout << "Задание: P1(x) = -9804x^32 + 4423,3x^16 - 8,7654x^8\n"
    << "P2(x) = 9,09x^9 - 9,09x^3 + 9,09x\n" << "P1(x) * P2(x)\n"
    << "Версия: 1.1.14\n"
    << "Автор: Егор Даричев (гр. 4352)\n" << "Введите x [-6.5; 6.5]: ";
    cin >> x;
    const float x2 = x * x;
    const float x4 = x2 * x2;
    const float x8 = x4 * x4;


    P1 = a1*x8*x8 + b1;
    cout << "Промежуточное вычисление 1 для P1:";
    cout << setw(20) << setprecision(10) << P1 << endl;
    P1 = P1 * x8 + c1;
    cout << "Промежуточное вычисление 2 для P1:";
    cout << setw(20) << setprecision(10) << P1 << endl;
    P1 = P1 * x8;
    cout << "P1 =";
    cout << setw(20) << setprecision(10) << P1 << endl;

    P2 = x4*x2 - 1;
    cout << "Промежуточное вычисление 1 для P2:";
    cout << setw(20) << setprecision(10) << P2 << endl;
    P2 = P2*x2 + 1;
    cout << "Промежуточное вычисление 2 для P2:";
    cout << setw(20) << setprecision(10) << P2 << endl;
    P2 = P2*x*a2;
    cout << "P2 =";
    cout << setw(20) << setprecision(10) << P2 << endl;

    cout << "Для x = " << setprecision(10) << x << ", P1*P2 равно:" << endl;
    cout << setw(20) << setprecision(10) << P1*P2 << endl;

    return 0;
}