#include "strL.hpp"

strL::strL() : chars(NULL), chars_c(0), offset(-1) {}
strL::strL(char* t, unsigned l) : chars(new char[l]{}), chars_c(l), offset(-1)
{
    for (unsigned i = 0; i < l; ++i) {
        chars[i] = t[i];
    }
}
strL::strL(char* t, unsigned l, int o) : strL(t, l) { offset=o; }
strL::~strL() { if (chars != NULL) delete [] chars; }
strL::strL(const strL& other) : strL(other.chars, other.chars_c, other.offset) {}
strL& strL::operator=(const strL& other)
{
    strL temp(other);
    std::swap(chars, temp.chars);
    std::swap(chars_c, temp.chars_c);
    std::swap(offset, temp.offset);
    return *this;
}
void strL::print(std::ostream& o)
{
    for (unsigned i = 0; i < chars_c; ++i)
    o << chars[i];
}
char& strL::set_char(char ch, unsigned i)
{
    return chars[i] = ch;
}
unsigned strL::get_chc() { return chars_c; } 
int strL::get_offset() { return offset; } 
char strL::get_char(unsigned i) { return chars[i]; }