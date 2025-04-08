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

void process(strings *l1, strings *l2) {
    strings::Node *p = l2->first, *q = l2->first->next;
    while (p) {
        if (!l2->cur) {
            l2->cur = new strings::Node(*p);
            l2->cur->next = nullptr;
        }
        else if (!(*l2->cur >>= *p)) {
            strings::Node *r = new strings::Node(*p);
            r->next = l2->cur;
            l2->cur = r;
        }
        p = q;
        if (q) q = q->next;
    }
    // l1 имеет хотя бы один элемент - пустая строка
    l1->last->next = l2->cur;
}