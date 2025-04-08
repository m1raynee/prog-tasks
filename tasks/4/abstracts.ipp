#pragma once
#include "abstracts.hpp"

template<Printable ValueT, typename AT>
list<ValueT, AT>::Node::Node()
: value{}, next(nullptr) {}

template<Printable ValueT, typename AT>
list<ValueT, AT>::Node::Node(ValueT val)
: value(val), next(nullptr) {}

template<Printable ValueT, typename AT>
list<ValueT, AT>::list()
: first(nullptr), cur(nullptr), last(nullptr) {}

template<Printable ValueT, typename AT>
bool list<ValueT, AT>::is_empty() {
    return first == nullptr;
}

template<Printable ValueT, typename AT>
bool list<ValueT, AT>::operator==(
    const list<ValueT, AT>& other
) {
    Node *p = first, *q = other.first;
    while (p and q) {
        if (p->value != q->value) return false;
        p = p->next;
        q = q->next;
    }
    if (!(p or q)) return true;
    return false;
}
template<Printable ValueT, typename AT>
bool list<ValueT, AT>::operator!=(
    const list<ValueT, AT>& other
) { return !(*this == other); }

template<Printable ValueT, typename AT>
bool list<ValueT, AT>::Node::operator>>=(
    const Node& other
) {
    Node *p = this;
    while (p) {
        if (p->value == other.value) return true;
        p = p->next;
    }
    return false;
}

template<Printable ValueT, typename AT>
void list<ValueT, AT>::push_back(
    const ValueT& value
) {
    Node* p = new Node(value);
    push_back(p);
}

template<Printable ValueT, typename AT>
void list<ValueT, AT>::push_back(Node* node) {
    if (is_empty()) {
        first = last = node;
        return;
    }
    last->next = node;
    last = node;
}

template<Printable ValueT, typename AT>
void list<ValueT, AT>::print(ostream& out) {
    Node *p = first;
    while (p) {
        if (p->next) p->value.print(out);
        else p->value.print(out, A.last);
        out << A.arrow;
        p = p->next;
    }
    if (p == first) out << A.arrow;
    out << "nullptr" << std::endl;
}

template<Printable ValueT, typename AT>
void list<ValueT, AT>::print(ostream& out, int) {
    print(out);
}

template<Printable ValueT, typename AT>
void list<ValueT, AT>::list::destroy() {
    if (is_empty()) return;
    while (!is_empty()) {
        Node *p = first;
        first = p->next;
        delete p;
    }
}