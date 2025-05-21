#pragma once

template <typename V, typename SpecT>
istream& operator>>(istream& is, list<V, SpecT>& obj) {
  V* value;
  while (!is.eof()) {
    value = new V();
    is >> *value;
    obj.push_back(value);
  }
  return is;
}