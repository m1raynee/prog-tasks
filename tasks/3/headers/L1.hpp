#pragma once
#include "../headers/strL.hpp"
#include <iostream>
using std::ostream;

struct L1 {
    strL val;
    L1 *next;
    L1(strL _val);
};

struct list {
    L1 *first;
    L1 *last;

    L1 *first_prev;
    L1 *cur_prev;

    void init_list();
    void destroy_list();

    bool is_empty();
    void push_back(strL _val);
    void print(ostream& out);
    int count_elem(strL str);

    L1 *find_prev(strL _val);
    void remove_next(L1 *node);

    L1 *next();
    L1 *begin();
};
void process(list &l, list q, int count);
