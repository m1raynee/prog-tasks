#include "readState.hpp"

lineState::lineState() {
    state = nothing;
    name_start = -1;
    name_end = -1;
    opened_bracket = -1;
    closed_bracket = -1;
}
void lineState::print(std::ostream& o, bool is_short)
{
    o << "[статус: ";
    switch (state)
    {
    case nothing: o << "ничего"; break;
    case name: o << "имя"; break;
    case open_bracket: o << "открытие скобки"; break;
    case close_bracket: o << "закрытие скобки"; break;
    case second_brackets: o << "повторные скобки"; break;
    case eol: o << "конец строки"; break;
    default: break;
    }

    if (!is_short) {
        o << ' ' << name_start << ';';
        o << ' ' << name_end << ';';
        o << ' ' << opened_bracket << ';';
        o << ' ' << closed_bracket;
    }
    o << ']';
}
resultStates::resultStates() : states(NULL), states_c(0), mid_chunk(readState{}) {}
resultStates::resultStates(lineState* stv, unsigned stc, readState mc)
: states(new lineState[stc]), states_c(stc), mid_chunk(mc)
{
    for (unsigned i = 0; i < states_c; ++i) states[i] = stv[i];
}
resultStates::~resultStates() { if (states != NULL) delete [] states; }
resultStates::resultStates(const resultStates& other) : resultStates(other.states, other.states_c, other.mid_chunk) {}
resultStates& resultStates::operator=(const resultStates& other)
{
    resultStates temp(other);
    std::swap(states_c, temp.states_c);
    std::swap(states, temp.states);
    return *this;
}
void resultStates::append_state(lineState state, std::ostream& log)
{
    lineState* temp = new lineState[states_c++]{};
    log << "{новый ответ: ";
    state.print(log, false);
    log << '}';
    for (unsigned i = 0; i < states_c-1; ++i) temp[i] = states[i];
    temp[states_c] = state;
    delete [] states;
    states = temp;
}
readState resultStates::set_mid_chunk(readState mc) { return mid_chunk = mc; }
readState resultStates::get_mid_chunk() { return mid_chunk; }