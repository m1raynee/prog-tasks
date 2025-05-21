#include "file.hpp"

istream& operator>>(istream& is, str& obj) {
    int ch; unsigned i = 0; str::Node* p;
    while ((ch = is.get()) != -1 and ch != '|' and ch != '\n') {
        if (i % STR_CHUNK_LENGTH == 0) {
            p = new str::Node();
            obj.push_back(p);
        }
        p->value->s[i++ % STR_CHUNK_LENGTH] = (char)ch;
    }
    if (obj.is_empty()) obj.push_back(new str::Node());
    obj.set_spec(new unsigned(
        (i % STR_CHUNK_LENGTH) ? i % STR_CHUNK_LENGTH : (
            (i) ? STR_CHUNK_LENGTH : i
        )
    ));
    return is;
}

istream& operator>>(istream& is, Executor& obj) {
    is >> obj.service_number;
    if (is.get() != '|') return is;
    is >> obj.name >> obj.address;

    file::protocol() << "Считан исполнитель:\n";
    obj.print(file::protocol());
    file::protocol() << '\n';

    return is;
}

istream& operator>>(istream& is, Task& obj) {
    is >> obj.name >> obj.rate;
    if (is.get() != '|') return is;
    is >> obj.fee;
    if (is.get() == '$') { is.get(); }
    else {
        is >> obj.scope;
        if (is.get() != '|') return is;
        unsigned y; short unsigned m, d;
        is >> y >> m >> d;
        obj.completion_date = date(y, m, d);
    }

    if (is.get() != '|') return is;
    is >> obj._executors_positions;

    file::protocol() << "Считана задача:\n";
    obj.print(file::protocol());
    file::protocol() << "\tС исполнителями: ";
    obj._executors_positions.print(file::protocol());
    file::protocol() << std::endl;

    return is;
}

istream& operator>>(istream& is, list<_Id>& obj) {
    int ch; unsigned id;
    do {
        is >> id;
        obj.push_back(new _Id{.id = id});
    } while ((ch = is.get()) != -1 and ch == ' ' and ch != '\n');
    return is;
}

istream& operator>>(istream& is, date& obj) {
    unsigned y; short unsigned m, d;
    is >> y >> m >> d;
    date some(y, m, d);
    obj.bytes[0] = some.bytes[0];
    obj.bytes[1] = some.bytes[1];
    obj.bytes[2] = some.bytes[2];
    return is;
}