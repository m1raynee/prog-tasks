#pragma once
#include <iostream>
#include "chunkL.hpp"

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

    private:
        int* starts;
        int* ends;
        unsigned textc;
};

// Разбивает весь исходный файл на блоки
chunk_count count_chunks(std::istream& in);

// Возвращает класс с началом и концом строк
txtPivots find_pivots(std::istream& in);