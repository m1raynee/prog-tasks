#include "file.hpp"

istream& operator>>(istream& is, str& obj) {
    int ch; unsigned i; str::Node* p;
    while ((ch = is.get()) > 0 and ch != '|' and ch != '\n') {
        if (i % STR_CHUNK_LENGTH == 0) {
            p = new str::Node();
            obj.push_back(p);
        }
        p->value->s[i++ % STR_CHUNK_LENGTH] = (char)ch;
    }
    if (obj.is_empty()) obj.push_back(new str::Node());
    obj.set_spec(new unsigned(i % STR_CHUNK_LENGTH));
    return is;
}

istream& operator>>(istream& is, Executor& obj) {
    is >> obj.service_number;
    if (is.get() != '|') return is;
    is >> obj.name >> obj.address;
    return is;
}

istream& operator>>(istream& is, Task& obj) {
    is >> obj.name >> obj.rate;
    if (is.get() != '|') return is;
    is >> obj.fee;
    if (is.get() != '|') return is;
    if (is.get() == '|') {
        is.get(); is.get();
    }
    return is;
}
