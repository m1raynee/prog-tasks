#pragma once

#include "const.hpp"
#include "strL.hpp"
#include "files.hpp"
#include "readState.hpp"

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
        void print(std::ostream& o, readState state);

        // Заменить i-тую строку на данную
        strL& set_str(strL &str, unsigned i);
        strL& get_str(unsigned i);

    private:
        strL* lines;
        unsigned lines_c;
};

// Разбивает весь исходный файл на блоки
chunk_count count_chunks(std::istream& in);

// Читает чанк текста x-овой строки, y-ого столбца
chunkL read_chunk(std::ostream& log, std::istream& in, txtPivots pivots, int x, int y);

// Просчитывает чанк
void parse_chunk(std::ostream& log, std::istream& in, resultStates* res_ptr, chunkL chunk);
