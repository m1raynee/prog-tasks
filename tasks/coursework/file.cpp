#include "file.hpp"

istream& operator>>(istream& is, str& obj) {
    int ch; unsigned i = 0; str::Node* p;
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
    if (is.get() == '|') { is.get(); is.get(); }
    else {
        is.seekg(-2, is.cur);
        is >> obj.scope;
        if (is.get() != '|') return is;
        unsigned y; short unsigned m, d;
        is >> y >> m >> d;
        obj.completion_date = date(y, m, d);
    }

    is >> obj._executors_positions;
    return is;
}

istream& operator>>(istream& is, list<_Id>& obj) {
    int ch; unsigned id;
    do {
        is >> id;
        obj.push_back(new _Id{.id = id});
    } while ((ch = is.get()) > 0 and ch == '/' and ch != '\n');
    return is;
}
