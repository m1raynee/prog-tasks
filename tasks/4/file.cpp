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
    if (result.is_empty()) result.push_back(new str::Node());
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
            l2->cur = p;
            l2->cur->next = nullptr;
        }
        else {
            strings::Node *e = *l2->cur >>= *p;
            if (!e) {
                p->next = l2->cur;
                l2->cur = p;
            } else {
                strings::Node *e_next = e->next;
                e->next = p;
                p->next = e_next;
            }
        }
        p = q;
        if (q) q = q->next;
    }
    // l1 имеет хотя бы один элемент - пустая строка
    l1->last->next = l2->cur;
}