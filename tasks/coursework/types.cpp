#include "types.hpp"

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