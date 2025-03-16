#pragma once
#include "const.hpp"
#include <iostream>


enum State { nothing, name, open_bracket, close_bracket, second_brackets, eol };
struct lineState {
    State state = nothing;
    int name_start = -1;
    int name_end = -1;
    int opened_bracket = -1;
    int closed_bracket = -1;

    lineState();

    void print(std::ostream& out, bool is_short);
};

struct readState { lineState l[CHUNK_H]{}; };

class resultStates {
    public:
        // Нуль-конструктор, создаёт пустой объект класса
        resultStates();

        resultStates(lineState* stv, unsigned stc, readState mc);

        // Деструктор
        ~resultStates();

        // Конструктор-копия
        resultStates(const resultStates& other);

        // Копирование через назначение
        resultStates& operator=(const resultStates& other);

        // Отправить содержание чанка в поток
        void print(std::ostream& out);

        // Добавляет статус в результирующие
        void append_state(lineState state, std::ostream& log);

        readState set_mid_chunk(readState mc);
        readState get_mid_chunk();

    private:
        lineState* states;
        unsigned states_c;
        readState mid_chunk;
};