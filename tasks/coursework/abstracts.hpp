#pragma once
#include <iostream>

using std::ostream;

template<typename V, typename SpecV = void>
struct list {
    struct Node {
        V* value;
        Node* next;

        Node();
        Node(V* value);
        Node* replicate();
    };

    Node* first, * last;
    SpecV* spec;
    bool is_virtual = false;

    list(bool is_virtual = false);
    bool operator<(const list& other);
    bool is_empty();
    void push_back(Node* node);
    void push_back(Node* *node);
    void push_back(const V* value);
    void print(ostream& out);
    void destroy();
};

#include "abstracts.ipp"