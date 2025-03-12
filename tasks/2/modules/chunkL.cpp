#include "chunkL.hpp"
#include "strL.hpp"

chunkL::chunkL() : textv(NULL), textc(0) {}
chunkL::chunkL(strL* strv, unsigned strc) : textv(new strL[strc]{}), textc(strc)
{
    for (unsigned i = 0; i < strc; ++i) textv[i] = strv[i];
}
chunkL::~chunkL() { if (textv != NULL) delete [] textv; }
chunkL::chunkL(const chunkL& other) : chunkL(other.textv, other.textc) {}
chunkL& chunkL::operator=(const chunkL& other)
{
    chunkL temp(other);
    std::swap(textc, temp.textc);
    std::swap(textv, temp.textv);
    return *this;
}
void chunkL::print(std::ostream& o)
{
    for (unsigned i = 0; i < textc; ++i)
    textv[i].print(o);
}
