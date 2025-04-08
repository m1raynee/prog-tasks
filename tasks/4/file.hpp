#pragma once

#include "types.hpp"
using std::istream, std::ostream;



str readline(istream &in);
strings readfile(istream &in);
void bar(ostream& out);
void process(strings *l1, strings *l2);