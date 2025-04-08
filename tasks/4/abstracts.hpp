#pragma once
#include "const.hpp"
#include <concepts>
#include <iostream>

using std::ostream;

template<typename T>
concept Printable = requires(T t, ostream& o) {
    {t.print(o)};
};

template<Printable ValueT, typename AT>
struct list {
    struct Node {
        ValueT value;
        Node *next;

        Node();
        Node(ValueT value);
        Node *operator>>=(const Node& other);
    };

    Node *first, *cur, *last;
    AT A;

    list();
    bool operator==(const list& other);
    bool operator!=(const list& other);

    bool is_empty();
    void push_back(const ValueT& value);
    void push_back(Node* node);
    void print(ostream& out);
    void print(ostream& out, int last);

    void destroy();
};

#include "abstracts.ipp"