#pragma once

#include <iostream>

class strL {
    public:
        // Нуль-конструктор, создаёт пустой объект класса
        strL();

        // Конструктор, создающий строку из указателя
        strL(char* symbols, unsigned count);
        // Конструктор, создающий строку из указателя
        strL(char* symbols, unsigned count, int offset);

        // Деструктор
        ~strL();

        // Конструктор-копия
        strL(const strL& other);

        // Копирование через назначение
        strL& operator=(const strL& other);

        // Make task
        void process();

        // Отправить содержание строки в поток
        void print(std::ostream& out);

        // Заменить i-тый символ
        char& set_char(char ch, unsigned i);
        char get_char(unsigned i);
        unsigned get_chc();
        int get_offset();

    private:
        char* chars;
        unsigned chars_c;
        int offset;
};
