#include "../headers/strL.hpp"

strL &strL::init(char *_chars, int _chars_c) {
    chars = _chars;
    chars_c = _chars_c;
    return *this;
}
void strL::destroy() {
    if (chars != nullptr) delete [] chars;
    chars = nullptr; chars_c = 0;
}
void strL::print(std::ostream &out) {
    for (int i = 0; i < chars_c; ++i) out << chars[i];
}
bool strL::operator==(const strL &other) {
    if (chars_c != other.chars_c) return false;
    for (int i = 0; i < chars_c; ++i)
        if (other.chars[i] != chars[i]) return false;
    return true;
}
bool strL::operator!=(const strL &other) { return !(*this == other); }