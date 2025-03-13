#include "strL.hpp"

strL::strL() : chv(NULL), chc(0) {}
strL::strL(char* t, unsigned l) : chv(new char[l]{}), chc(l)
{
    for (unsigned i = 0; i < l; ++i) {
        chv[i] = t[i];
    }
}
strL::~strL() { if (chv != NULL) delete [] chv; }
strL::strL(const strL& other) : strL(other.chv, other.chc) {}
strL& strL::operator=(const strL& other)
{
    strL temp(other);
    std::swap(chv, temp.chv);
    std::swap(chc, temp.chc);
    return *this;
}
void strL::print(std::ostream& o)
{
    for (unsigned i = 0; i < chc; ++i)
    o << chv[i];
    o << '\n';
}
char& strL::set_char(char ch, unsigned i)
{
    return chv[i] = ch;
}