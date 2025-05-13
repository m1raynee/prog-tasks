#pragma once
#include "types.hpp"
#include <iostream>

using std::ifstream, std::ofstream;
istream& operator>>(istream& is, list<_Id>& obj);