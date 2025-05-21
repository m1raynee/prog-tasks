#pragma once
#include <fstream>
#include "types.hpp"

using std::ifstream, std::ofstream;

istream& operator>>(istream& is, list<_Id>& obj);
istream& operator>>(istream& is, date& obj);

#include "file.ipp"
