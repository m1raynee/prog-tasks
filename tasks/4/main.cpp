#include "file.hpp"
#include "abstracts.hpp"
#include <fstream>

int main() {
    std::ifstream in1, in2;
    std::ofstream out;
    in1.open("in.txt");
    in2.open("in copy.txt");
    out.open("out.txt");
    strings l1 = readfile(in1);
    strings l2 = readfile(in2);
    l1.print(out);
    bar(out);
    l2.print(out);
    bar(out);

    strings::Node *p = l2.first, *q = l2.first->next;
    while (p) {
        if (!l2.cur) {
            l2.cur = p;
            p->next = nullptr;
        }
        else if (!(*l2.cur >>= *p)) {
            p->next = l2.cur;
            l2.cur = p;
        }
        p = q;
        if (q) q = q->next;
    }
    l1.last->next = l2.cur;
    l1.print(out);
    return 0;
}