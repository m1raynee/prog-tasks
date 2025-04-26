#pragma once
#include "abstracts.hpp"

template<typename V, typename SpecV>
list<V, SpecV>::Node::Node()
    : value{}, next(nullptr) {}

template<typename V, typename SpecV>
list<V, SpecV>::Node::Node(V* v)
    : value(v), next(nullptr) {}

template<typename V, typename SpecV>
list<V, SpecV>::Node*
list<V, SpecV>::Node::replicate() {
    return new Node(value);
}

template<typename V, typename SpecV>
list<V, SpecV>::list(bool is_v)
    : first(nullptr), last(nullptr),
      is_virtual(is_v), spec(nullptr) {}

template<typename V, typename SpecV>
bool list<V, SpecV>::operator<(
    const list<V, SpecV>& other
) { throw std::logic_error("Not implemented"); }

template<typename V, typename SpecV>
bool list<V, SpecV>::is_empty() {
    return first == nullptr;
}

template<typename V, typename SpecV>
void list<V, SpecV>::push_back(
    list<V, SpecV>::Node* node
) {
    if (is_empty()) {
        first = last = node;
        return;
    }
    last->next = node;
    last = node;
}

template<typename V, typename SpecV>
void list<V, SpecV>::push_back(Node** node) {
    push_back((*node)->replicate());
}

template<typename V, typename SpecV>
void list<V, SpecV>::push_back(const V* value) {
    push_back(new Node(value));
}

template<typename V, typename SpecV>
void list<V, SpecV>::print(ostream& out) {
    Node* p = first;
    while (p) {
        p->value->print(out);
        out << p->value->sep;
        p = p->next;
    }
    out << p->value->end;
}

template<typename V, typename SpecV>
void list<V, SpecV>::destroy() {
    while (!is_empty()) {
        Node* p = first;
        first = p->next;

        if (not is_virtual) {
            p->value->destroy();
            delete p->value;
        }
        delete p;
    }
}
