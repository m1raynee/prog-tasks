#pragma once

template <>
inline void str::print(ostream& out) {
  Node* p = first;
  while (p) {
    if (!p->next)
      p->value->print(out, spec());
    else
      p->value->print(out);
    p = p->next;
    if (p)
      out << p->value->sep;
  }
  out << first->value->end;
}
