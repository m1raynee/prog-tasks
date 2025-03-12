#pragma once

#include "const.hpp"
#include "strL.hpp"

class chunkL {
    public:
        // Нуль-конструктор, создаёт пустой объект класса
        chunkL();

        // Конструктор, создающий строку из указателя
        chunkL(strL*, unsigned);

        // Деструктор
        ~chunkL();

        // Конструктор-копия
        chunkL(const chunkL&);

        // Копирование через назначение
        chunkL& operator=(const chunkL&);

        // Make task
        void process();

        // Отправить содержание чанка в поток
        void print(std::ostream&);

    private:
        strL* textv;
        unsigned textc;
};
