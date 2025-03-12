#pragma once

#include <iostream>

class strL {
    public:
        // Нуль-конструктор, создаёт пустой объект класса
        strL();

        // Конструктор, создающий строку из указателя
        strL(char* symbols, unsigned count);

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

    private:
        char* chv;
        unsigned chc;
};
