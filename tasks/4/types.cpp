#include "types.hpp"

void chunk::print(ostream& out) {
    for (int i = 0; i < CHUNK_WIDTH; ++i) out << s[i];
}

bool chunk::operator==(const chunk& other) {
    for (int i = 0; i < CHUNK_WIDTH; ++i)
        if (s[i] != other.s[i]) return false;
    return true;
}

bool chunk::operator!=(const chunk& other) {
    return !(*this == other);
}