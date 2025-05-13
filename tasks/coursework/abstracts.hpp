#pragma once
#include <iostream>

using std::ostream, std::istream;

template<typename V, typename SpecT = void>
struct list {
    struct Node {
        V* value;
        Node* next;

        Node();
        Node(V* value);
        Node* replicate();
    };

    bool is_virtual;
    Node* first, * last;

    char spec_bytes[sizeof(SpecT)];
    const SpecT spec() const;
    void set_spec(SpecT* value);

    list(bool is_virtual = false);
    [[noreturn]] bool operator<(const list& other);

    bool is_empty();
    void push_back(Node* node);
    void push_back(V* value);
    void print(ostream& out);
    void destroy();
};

#include "abstracts.ipp"