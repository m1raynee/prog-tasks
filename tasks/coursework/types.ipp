#pragma once

template<>
inline bool str::operator<(const str& other) {
    Node* p = first;
    Node* q = other.first;
    unsigned size = STR_CHUNK_LENGTH;

    while (p and q) {
        if (!(p or q)) {
            if (spec() != other.spec())
                return spec() < other.spec();
            size = spec();
        }
        // return true if other is longer <=> another q exists
        if (bool(p) ^ bool(q)) return bool(q);
        for (unsigned i = 0; i < size; ++i) {
            auto getval = [i](Node* node){
                return node->value->s[i];
            };
            if (getval(p) != getval(q))
                return getval(p) < getval(q);
        }

        p = p->next;
        q = q->next;
    }
    return true;
}

template<>
inline void str::print(ostream& out) {
    Node* p = first;
    while (p) {
        if (!p->next) p->value->print(out, spec());
        p->value->print(out);
        out << p->value->sep;
        p = p->next;
    }
    out << first->value->end;
}

template<typename V, typename SpecT>
istream& operator>>(istream& is, list<V, SpecT>& obj) {
    V* value;
    while (!is.eof()) {
        value = new V();
        is >> *value;
        obj.push_back(value);
    }
    return is;
}