#pragma once
#include "const.hpp"
#include <iostream>


enum State { nothing, name, open_bracket, close_bracket, second_brackets };
struct lineState {
    State state = nothing;
    int name_start = -1;
    int name_end = -1;
    int opened_bracket = -1;
    int closed_bracket = -1;

    lineState();
    void print(std::ostream& out, bool is_short);
    void print(std::ostream& out, std::istream& in);
};

struct readState { lineState l[CHUNK_H]{}; };

class resultStates {
    public:
        resultStates();
        resultStates(lineState* stv, unsigned stc, readState mc);
        ~resultStates();
        resultStates(const resultStates& other);
        resultStates& operator=(const resultStates& other);
        void append_state(lineState state, std::ostream& log, std::istream& in);
        readState set_mid_chunk(readState mc);
        readState get_mid_chunk();
    private:
        lineState* states;
        unsigned states_c;
        readState mid_chunk;
};