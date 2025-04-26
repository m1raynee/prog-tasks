#include "types.hpp"

bool str::operator<(const str& other) {
    Node* p = first;
    Node* q = other.first;
    unsigned size = STR_CHUNK_LENGTH;

    while (p and q) {
        if (!(p or q)) {
            if (*spec != *other.spec)
                return *spec < *other.spec;
            size = *spec;
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
}

date::date(
    unsigned _year,
    short unsigned _month,
    short unsigned _day
) {
    bytes[0] = _year & 0b11111111;
    bytes[1] = ((_year  >> 8) & 0b00111111)
             | ((_month & 0b00000011) << 6);
    bytes[2] = ((_month >> 2) & 0b00000011)
             | ((_day   & 0b00001111) << 2);
}
unsigned date::year() {
    return bytes[0] | (unsigned)(bytes[1] & 0b00111111) << 8;
}
short unsigned date::month() {
    return ((bytes[1] & 0b11000000) >> 6)
         | ((bytes[2] & 0b00000011) << 2);
}
short unsigned date::day() {
    return (bytes[2] & 0b01111100) >> 2;
}

bool StrChunk::operator==(const StrChunk& other) {
    for (unsigned i = 0; i < STR_CHUNK_LENGTH; ++i)
        if (s[i] != other.s[i]) return false;
    return true;
}

MultiTask tasks_pool{};