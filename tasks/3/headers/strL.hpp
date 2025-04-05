#pragma once
#include <iostream>
using std::ostream;

struct strL {
    char *chars;
    int chars_c;
    strL &init(char *_chars = nullptr, int _chars_c = 0);
    void destroy();
    void print(ostream& out);
    bool operator==(const strL& other);
    bool operator!=(const strL& other);
};
