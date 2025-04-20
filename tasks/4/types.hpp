#pragma once
#include "abstracts.hpp"

struct chunk {
    char s[CHUNK_WIDTH]{};
    void print(ostream& out);
    void print(ostream& out, int len);
    bool operator==(const chunk& other);
    bool operator!=(const chunk& other);
};

struct _foo {
    char arrow[5] = "\\|/\n";
};
struct _bar {
    char arrow[4] = " > ";
    int last = 0;
};

using str = list<chunk, _bar>;
using strings = list<str, _foo>;