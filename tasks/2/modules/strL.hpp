#pragma once

#include <iostream>

class strL {
    public:
        // Нуль-конструктор, создаёт пустой объект класса
        strL();

        // Конструктор, создающий строку из указателя
        strL(char*, unsigned);

        // Деструктор
        ~strL();

        // Конструктор-копия
        strL(const strL&);

        // Копирование через назначение
        strL& operator=(const strL&);

        // Make task
        void process();

        // Отправить содержание строки в поток
        void print(std::ostream&);

    private:
        char* chv;
        unsigned chc;
};
