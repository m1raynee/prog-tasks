/*
Задание: определить, входит ли точка (x,y) в параметрически заданную фигуру ниже.
Присутствует диогональная периодичность.
^
|
a         , - ~  - - - - - - - - - - - - - - - - - - - - - - - - - - - , - ~  -             
|     , '                                                          , '                      
|   ,                                                            ,                          
|  ,                                                            ,                           
| ,                                                            ,                            
| ,                                                            ,                            
| ,                                                            ,                            
|  ,                                                            ,                           
|   ,                                                            ,                          
|     ,                                                            ,                        
|       ' - , -  ~ - ,                                               ' - , -  ~ - ,         
|                       ' ,                                                          ' ,    
|                           ,                                                            ,  
|                            ,                                                            , 
|                             ,                                                            ,
|                             ,                                                            ,
|                             ,                                                            ,
|                            ,                                                            , 
|                           ,                                                            ,  
|                        , '                                                          , '   
|               _ _ , _' _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ , _'       
|——————————————————————————————————————————————————————————————————————————————————————————b—————>

Ограничения: 2|b|>=|a|, 

Автор: Егор Даричев (гр. 4352)                  Версия: 2.1.134

Даты: начало: 24.09.2024                        конец: когда рак на горе свистнет
*/

#include <iostream>
#include <cmath>

int main()
{
    std::cout << "Задание: определить, входит ли точка "<<
    "(x,y) в параметрически заданную фигуру ниже." << std::endl;
    
    std::cout << "^" << std::endl;
    std::cout << "|" << std::endl;
    std::cout << "a         , - ~  - - - - - - - - - - - - - - - - - - - - - - - - - - - , - ~  -                   " << std::endl;
    std::cout << "|     , '                                                          , '                            " << std::endl;
    std::cout << "|   ,                                                            ,                                " << std::endl;
    std::cout << "|  ,                                                            ,                                 " << std::endl;
    std::cout << "| ,                                                            ,                                  " << std::endl;
    std::cout << "| ,                                                            ,                                  " << std::endl;
    std::cout << "| ,                                                            ,                                  " << std::endl;
    std::cout << "|  ,                                                            ,                                 " << std::endl;
    std::cout << "|   ,                                                            ,                                " << std::endl;
    std::cout << "|     ,                                                            ,                              " << std::endl;
    std::cout << "|       ' - , -  ~ - ,                                               ' - , -  ~ - ,               " << std::endl;
    std::cout << "|                       ' ,                                                          ' ,          " << std::endl;
    std::cout << "|                           ,                                                            ,        " << std::endl;
    std::cout << "|                            ,                                                            ,       " << std::endl;
    std::cout << "|                             ,                                                            ,      " << std::endl;
    std::cout << "|                             ,                                                            ,      " << std::endl;
    std::cout << "|                             ,                                                            ,      " << std::endl;
    std::cout << "|                            ,                                                            ,       " << std::endl;
    std::cout << "|                           ,                                                            ,        " << std::endl;
    std::cout << "|                        , '                                                          , '         " << std::endl;
    std::cout << "|               _ _ , _' _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ , _'             " << std::endl;
    std::cout << "|——————————————————————————————————————————————————————————————————————————————————————————b—————>" << std::endl;

    std::cout << "Автор: Егор Даричев (гр. 4352) Версия: 2.1.134" << std::endl;

    double a,b,x,y;
    std::cout << "Введите а: ";
    std::cin >> a;
    std::cout << "Введите b: ";
    std::cin >> b;
    std::cout << "Введите x: ";
    std::cin >> x;
    std::cout << "Введите y: ";
    std::cin >> y;

    if (a == 0 and b == 0) {
        if (x == 0 and y == 0) {std::cout << "Входит" << std::endl;}
        else {std::cout << "Не входит" << std::endl;}
        return 0;
    }

    if (a == 0) {
        if (x == 0) {std::cout << "Входит" << std::endl;}
        else {std::cout << "Не входит" << std::endl;}
        return 0;
    }
    if (b == 0) {
        if (y == 0) {std::cout << "Входит" << std::endl;}
        else {std::cout << "Не входит" << std::endl;}
        return 0;
    }


    if (2*abs(b) < abs(a)) {
        std::cout << "2*abs(b) must be greater or equal than abs(a)";
        return -1;
    }

    const int k_x = floor(1-x/b);
    const int k_y = floor(1-y/a);

    x += b*k_x;
    y += a*k_y;

    if (abs(k_x) != abs(k_y)) {
        std::cout << "Не входит (период)";
        return 0;
    }


    int res = -1;

    int sign_b = (b > 0) - (b < 0);

    if (2*abs(b) == abs(a)) {
        res = 10;
        if (
            pow(x-sign_b*abs(a/4), 2)
            + pow(y - a/4, 2)
            == pow(a/4, 2)
        ) {res = -1;}
        else if (
            pow(x-sign_b*abs(a/4), 2)
            + pow(y - 3*a/4, 2)
            == pow(a/4, 2)
        ) {res = -1;}
    }

    else if (y <= abs(a/2))
    {
        if (abs(a/4) > sign_b*x) {res=0;}
        else if (
            pow(x-sign_b*abs(a/4), 2)
            + pow(y - a/4, 2)
            < pow(a/4, 2)
        ) {res = 1;}
        else if (
            pow(x-b+sign_b*abs(a/4), 2)
            + pow(y - a/4, 2)
            > pow(a/4, 2)
            and sign_b*b - abs(a/4) <= sign_b*x
        ) {res=2;}
    }
    else
    {
        if (sign_b*b - abs(a/4) < sign_b*x) {res=3;}
        else if (
            pow(x-sign_b*abs(a/4), 2)
            + pow(y - 3*a/4, 2)
            > pow(a/4, 2)
            and sign_b*x<=abs(a/4)
        ) {res=4;}
        else if (
            pow(x-b+sign_b*abs(a/4), 2)
            + pow(y - 3*a/4, 2)
            < pow(a/4, 2)
        ) {res=5;}
    }

    std::cout << "\nОтсечение: " << res << std::endl;
    std::cout << "X: " << x << " Y: " << y << std::endl;
    if (res == -1) {std::cout << "Входит" << std::endl;}
    else {std::cout << "Не входит" << std::endl;}

    return 0;
}
