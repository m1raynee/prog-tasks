#pragma once

template<typename V, typename SpecT>
list<V, SpecT>::Node::Node()
    : value{new V()}, next(nullptr) {}

template<typename V, typename SpecT>
list<V, SpecT>::Node::Node(V* v)
    : value(v), next(nullptr) {}

template<typename V, typename SpecT>
list<V, SpecT>::Node*
list<V, SpecT>::Node::replicate() {
    return new Node(value);
}

template<typename V, typename SpecT>
list<V, SpecT>::list(bool is_v)
    : is_virtual(is_v), first(nullptr), last(nullptr),
    spec_bytes(0) {}

template<typename V, typename SpecT>
const SpecT list<V, SpecT>::spec() const {
    return *reinterpret_cast<const SpecT*>(spec_bytes);
}

template<typename V, typename SpecT>
void list<V, SpecT>::set_spec(SpecT* v) {
    *reinterpret_cast<SpecT*>(spec_bytes) = *v;
}

template<typename V, typename SpecT>
[[noreturn]] bool list<V, SpecT>::operator<(
    const list<V, SpecT>& other
) { throw std::logic_error("Not implemented"); }

template<typename V, typename SpecT>
bool list<V, SpecT>::is_empty() {
    return first == nullptr;
}

template<typename V, typename SpecT>
void list<V, SpecT>::push_back(
    list<V, SpecT>::Node* node
) {
    if (is_empty()) {
        first = last = node;
        return;
    }
    last->next = node;
    last = node;
}

template<typename V, typename SpecT>
void list<V, SpecT>::push_back(V* value) {
    push_back(new Node(value));
}

template<typename V, typename SpecT>
void list<V, SpecT>::print(ostream& out) {
    Node* p = first;
    while (p) {
        p->value->print(out);
        out << p->value->sep;
        p = p->next;
    }
    out << first->value->end;
}

template<typename V, typename SpecT>
void list<V, SpecT>::destroy() {
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
