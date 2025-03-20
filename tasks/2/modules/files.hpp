#pragma once
#include <iostream>

class txtPivots {
    public:
        // Нуль-конструктор, создаёт пустой объект класса
        txtPivots();

        // Конструктор, создающий марки из указателей
        txtPivots(int* starts, int* ends, unsigned count);

        // Деструктор
        ~txtPivots();

        // Конструктор-копия
        txtPivots(const txtPivots& other);

        // Копирование через назначение
        txtPivots& operator=(const txtPivots& other);

        // Отправить содержание чанка в поток
        void print(std::ostream& out);

        int get_start(unsigned i);
        int get_end(unsigned i);
        int get_len(unsigned i);
        unsigned get_c();

    private:
        int* starts;
        int* ends;
        unsigned pivots_c;
};
unsigned count_lines(std::istream& in);
txtPivots find_pivots(std::istream& in);