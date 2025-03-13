#pragma once

#include "const.hpp"
#include "strL.hpp"
#include "files.hpp"

struct chunk_count {
    unsigned w;
    unsigned h;
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

        // Отправить содержание чанка в поток
        void print(std::ostream& out);

        // Заменить i-тую строку на данную
        strL& set_str(strL &str, unsigned i);

    private:
        strL* textv;
        unsigned textc;
};

// Разбивает весь исходный файл на блоки
chunk_count count_chunks(std::istream& in);

// Читает чанк текста x-овой строки, y-ого столбца
chunkL read_chunk(std::istream& in, txtPivots pivots, int x, int y);