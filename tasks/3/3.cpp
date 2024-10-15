/*
Задание: Определить минимальное значение n > 0, для которого очередное слагаемое
по модулю не превышает ε > 0 при нахождении результата согласно следующей формуле:

\sum_{i=1}^n \frac{(-x)^i}{(3i^2)!!}

Автор: Егор Даричев (гр. 4352)                  Версия: 3.1.12887

Даты: начало: 22.10.2024                        конец: надеюсь никогда
*/

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    int i = 0;
    long long int mult; 
    long double eps, xi = 1, si = 0;

    ofstream Logs("latest.log");

    cout << "Задание: Определить минимальное значение n > 0, для которого очередное слагаемое" <<
    "по модулю не превышает ε > 0 при нахождении результата согласно следующей формуле:" << endl;
    Logs << "Задание: Определить минимальное значение n > 0, для которого очередное слагаемое" <<
    "по модулю не превышает ε > 0 при нахождении результата согласно следующей формуле:" << endl;

    cout << "\\sum_{i=1}^n \\frac{(-x)^i}{(3i^2)!!}" << endl;
    cout << "Автор: Егор Даричев (гр. 4352)       Версия: 3.1.12887" << endl;
    
    Logs << "\\sum_{i=1}^n \\frac{(-x)^i}{(3i^2)!!}" << endl;
    Logs << "Автор: Егор Даричев (гр. 4352)       Версия: 3.1.12887" << endl;

    cout << "Введите x: ";
    cin >> mult;
    
    Logs << "Введите x: " << mult << endl;

    do
    {
        if (i > 0) {
            cout << "eps должен быть меньше 10^-7" << endl;
            Logs << "eps должен быть меньше 10^-7" << endl;
        }
        cout << "Введите eps: ";
        cin >> eps;
        Logs << "Введите eps: " << eps << endl;
        i++;
    } while (i < 3 and eps > 1e-7);
    if (i >= 3) {
        cout << "Вы слишком глупый, чтобы пользоваться этой программой" << endl;
        Logs << "Вы слишком глупый, чтобы пользоваться этой программой" << endl;
        return 0;
    }

    i = 0;
    long double xii;
    long long int fac_even = 1;
    long long int fac_odd = 1;

    cout << setw(3) << "i" << "|" << setw(20) << "xi" << "|" << setw(20) << "si" << "|" << endl;
    cout << "----------------------------------------------" << endl;
    Logs << setw(3) << "i" << "|" << setw(20) << "xi" << "|" << setw(20) << "si" << "|" << endl;
    Logs << "----------------------------------------------" << endl;
    do
    {
        i++;
        xii = -mult;
        if (i%2) {
            // fac_odd;
            xii *= fac_even;
            for (int n = (i == 1 ? 1 : 3*(i-2)*(i-2))+2; n<=3*i*i; n+=2) {
                cout << n << " ";
                fac_odd *= n;
            }
            cout << endl;
            xii /= fac_odd;
        }
        else {
            // fac_even;
            xii *= fac_odd;
            for (int n = (i == 2 ? 2 : 3*(i-2)*(i-2))+2; n<=3*i*i; n+=2) {
                cout << n << " ";
                fac_even *= n;
            }
            cout << endl;
            xii /= fac_even;

        }
        xi *= xii;
        si += xi;

        cout << setw(3) << i << "|" << setw(20) << xi << "|" << setw(20) << si << "|" << endl;
        Logs << setw(3) << i << "|" << setw(20) << xi << "|" << setw(20) << si << "|" << endl;

    } while (i < 1000 and abs(xi) > eps);

    cout << "После шага №" << i << " очередной член последовательности меньше eps=" << eps << endl;
    Logs << "После шага №" << i << " очередной член последовательности меньше eps=" << eps << endl;
    return 0;
}