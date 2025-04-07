#include "file.hpp"

str readline(istream &in) {
    str result = str();
    int ch = 0;
    int i = 0;
    str::Node* p;
    while ((ch = in.get()) and ch != '\n' and ch != -1) {
        if (i % CHUNK_WIDTH == 0) {
            p = new str::Node();
            result.push_back(p);
        }
        p->value.s[i++ % CHUNK_WIDTH] = (char)ch;
    }
    result.A.last = i % CHUNK_WIDTH;
    return result;
}

strings readfile(istream &in) {
    strings result = strings();
    while (!in.eof()) result.push_back(readline(in));
    return result;
}

void bar(ostream& out) {
    for (int i = 0; i < 20; ++i) out << '_';
    out << "\n\n";
}