#pragma once
#include "types.hpp"
#include <fstream>

using std::ifstream, std::ofstream;
istream& operator>>(istream& is, list<_Id>& obj);
istream& operator>>(istream& is, date& obj);

#include "file.ipp"