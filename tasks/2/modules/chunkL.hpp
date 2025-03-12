#pragma once

#include "const.hpp"
#include "strL.hpp"

struct chunk_count {
    unsigned w_count;
    unsigned h_count;
};

class chunkL {
    public:
        // Нуль-конструктор, создаёт пустой объект класса
        chunkL();

        // Конструктор, создающий строку из указателя
        chunkL(strL* strings, unsigned count);

        // Деструктор
        ~chunkL();

        // Конструктор-копия
        chunkL(const chunkL& other);

        // Копирование через назначение
        chunkL& operator=(const chunkL& other);

        // Make task
        void process();

        // Отправить содержание чанка в поток
        void print(std::ostream& out);

        private:
        strL* textv;
        unsigned textc;
    };
