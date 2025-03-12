#include "modules/strL.H"

int main()
{
    strL s = strL((char[3]){'0', '0', '0'}, 3);
    s.print(std::cout);
    return 0;
}
