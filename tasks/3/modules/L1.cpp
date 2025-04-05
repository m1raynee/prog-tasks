#include "../headers/L1.hpp"

L1::L1(strL _val) : val(_val), next(nullptr) {}
void list::init_list() {
    first = last = first_prev = cur_prev = nullptr;
}
void list::destroy_list() {
    if (is_empty()) return;
    while (!is_empty()) remove_next(first_prev);
    delete first_prev;
}
bool list::is_empty() { return first == nullptr; }
void list::push_back(strL _val) {           
    L1 *p = new L1(_val);
    if (is_empty()) {
        first = last = p;
        L1 *q = new L1(strL().init((char *)"", 1));
        q->next = p;
        first_prev = cur_prev = q;
        return;
    }
    last->next = p;
    last = p;
}
void list::print(std::ostream& out) {
    if (!is_empty()) {
        L1 *p = first;
        while (p) {
            p->val.print(out); out << "\n\\|/" << std::endl;
            p = p->next;
        }
    }
    out << "nullptr" << std::endl;
}
int list::count_elem(strL str) {
    int count = 0;
    L1* p = first_prev;
    while (p->next and (p = find_prev(str)) and p->next) ++count;
    return count;
}


L1 *list::find_prev(strL _val) {
    if (is_empty()) return nullptr;
    while (
        cur_prev
        and cur_prev->next
        and cur_prev->next->val != _val
    ) next();
    L1* p = cur_prev;
    next();
    return (p and p->next ? p : nullptr);
}
void list::remove_next(L1 *node) {
    if (is_empty()) return;
    if (!node) return;
    if (node == last) return;
    if (node == first_prev) {
        delete first_prev;
        first_prev = first;
        first = first->next;
        return;
    }
    L1 *p = node->next->next;
    delete node->next;
    node->next = p;
}

L1* list::next() {
    if (cur_prev) {
        cur_prev = cur_prev->next;
    }
    return cur_prev;
}
L1 *list::begin() {
    cur_prev = first_prev;
    return cur_prev;
}
void process(list &l, list q, int count) {
    L1 *p, *p_second, *p_previous, *p_last;
    switch (count) {
    case 1: return;
    case 2:
    p_second = l.find_prev(q.first->val);
    p_previous = l.find_prev(q.first->val);
    break;
    default:
    l.find_prev(q.first->val);
    p_second = l.find_prev(q.first->val); l.begin();
    p_previous = nullptr; p_last = l.first_prev;
    while (p_last) {
        p = p_last; p_last = l.find_prev(q.first->val);
        if (p_last) p_previous = p;
    }
        break;
    }
    if (p_second != p_previous) l.remove_next(p_previous);
    l.remove_next(p_second);
}