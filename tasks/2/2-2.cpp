/*
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
*/



#include <iostream>
#include <iomanip>
#include <math.h>

int main()
{
    float a,b,x,y;
    std::cin >> a >> b >> x >> y;

    if (2*abs(b) < abs(a)) {
        std::cout << "2*abs(b) must be greater or equal than abs(a)";
        return -1;
    }

    const int k_x = x/b, k_y = y/a;
    if (abs(k_x) != abs(k_y)) {
        std::cout << "not in the shape. out of periodic";
        return 0;
    }


    const int sign_a = (a > 0) - (a < 0);
    const int sign_b = (b > 0) - (b < 0);

    x = fmod(x, abs(b));
    y = fmod(y, abs(a));

    bool res = true;

    if (abs(y) <= abs(a/2))
    {
        if (abs(a/4) > sign_b*x) {res=false;}
        else if (
            pow(x-sign_b*abs(a/4), 2)
            + pow(y - a/4, 2)
            < pow(a/4, 2)
        ) {res = false;}
        else if (
            pow(x-b+sign_b*abs(a/4), 2)
            + pow(y - a/4, 2)
            > pow(a/4, 2)
            and sign_b*b - abs(a/4) <= sign_b*x
        ) {res=false;}
    }
    else
    {
        if (sign_b*b - abs(a/4) < sign_b*x) {res=false;}
        else if (
            pow(x-sign_b*abs(a/4), 2)
            + pow(y - 3*a/4, 2)
            < pow(a/4, 2)
            and sign_b*x<=abs(a/4)
        ) {res=false;}
        else if (
            pow(x-b+sign_b*abs(a/4), 2)
            + pow(y - 3*a/4, 2)
            > pow(a/4, 2)
        ) {res=false;}
    }

    std::cout << res;

    return 0;
}
