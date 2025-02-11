// Преобразовать заданную строку следующим образом: каждую точку заменить многоточием

#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>

using std::istream, std::ifstream, std::ofstream, std::ostream;
using std::noskipws;
using std::endl;


struct str {
    char *symbols;
    char mark;

    unsigned ellipsis_length = 3;

    bool next(unsigned i, char s = '\0') {
        if (s == '\0') s = this->mark;
        return this->symbols[i] != s;
    }

    void process() {
        unsigned i = 0, j = 0, dots_count = 0;
        char *new_symbols;

        while (this->next(i)) if (this->symbols[i++] == '.') ++dots_count;
        new_symbols = new char[1 + i + dots_count*(this->ellipsis_length - 1)];
        i = 0; j = 0;

        while (this->next(i)) {
            if (this->symbols[i] == '.') {
                for (unsigned k = 0; k < this->ellipsis_length; ++k) new_symbols[j++] = '.';
                ++i;
            } else new_symbols[j++] = this->symbols[i++];
        }

        new_symbols[j++] = mark;

        delete [] this->symbols;
        this->symbols = new_symbols;
    }

    void print_to(ostream &out, char until = '\0') {
        unsigned i = 0;
        while (this->next(i, until)) out << this->symbols[i++];
        out << this->symbols[i] << endl;
    }

    void put(char ch, unsigned *at) {
        this->symbols = (char *)realloc(this->symbols, (*at)+1);
        if (this->symbols == NULL) exit(2);
        this->symbols[(*at)++] = ch;
    }
};

str *input1(istream &in, unsigned *v, char *delimeter) {
    *v = 0;
    char mark;
    int ch;
    str *strings = (str *)malloc(*v * sizeof(str));

    in >> mark;
    if (*delimeter == '\0') in >> *delimeter;
    while ((ch = in.get()) and ch != '\n' and ch != -1);

    while (!in.eof()) {
        unsigned size = 0;
        int delimeter_pos = -1;
        int mark_pos = -1;

        str l;
        l.symbols = (char *)malloc(size);
        l.mark = mark;

        while ((ch = in.get()) and ch != '\n' and ch != -1) {
            if (delimeter_pos != -1) continue;
            if (ch == *delimeter and delimeter_pos == -1) {
                delimeter_pos = size;
            }
            else if (ch == mark and mark_pos == -1) mark_pos = size;

            l.put((char)ch, &size);
        }

        if (mark_pos == -1 and delimeter_pos != -1) {
            l.symbols[size-1] = mark;
            mark_pos = size;
            l.put(*delimeter, &size);
            delimeter_pos = size;
        }
        else if (mark_pos == -1) l.put(mark, &size);
        if (delimeter_pos == -1) l.put(*delimeter, &size);

        strings = (str *)realloc(strings, (*v + 1) * sizeof(str));
        if (strings == NULL) exit(3);
        strings[(*v)++] = l;
    }

    return strings;
}

str *input2(istream &in, unsigned *v, char *delimeter) {
    *delimeter = '\n';
    return input1(in, v, delimeter);
}


int main() {
    ifstream in;
    ofstream out;
    str *strings;
    unsigned string_count = 0;
    char delimeter = '\0';

    in.open("in.txt");
    if (!in.is_open()) {
        std::cout << "Не удалось открыть файл ввода" << endl;
        return 0;
    }

    out.open("out.txt");
    if (!out.is_open()) {
        std::cout << "Не удалось открыть файл вывода" << endl;
        return 0;
    }

    in >> noskipws;
    std::cout << "Задание: Преобразовать заданную строку следующим образом: "
    << "каждую точку заменить многоточием\nДаричев Егор а.г. 4352\n"
    << "Введите номер варианта ввода: ";

    switch (std::cin.get())
    {
    case '1':
        strings = input1(in, &string_count, &delimeter);
        break;
    case '2':
        strings = input2(in, &string_count, &delimeter);
        break;

    default:
        std::cout << "Неверный номер варианта" << endl;
        return 0;
    }


    std::cout << "Вывод результата в консоль и выходной файл:" << endl;
    for (unsigned i = 0; i < string_count; ++i) {
        std::cout << "Строка No. " << i << "\nКонтрольный вывод:" << endl;
        out << "Строка No. " << i << "\nКонтрольный вывод:" << endl;

        strings[i].print_to(std::cout, delimeter);
        strings[i].print_to(out, delimeter);

        strings[i].process();

        std::cout << "Результат:" << endl;
        out << "Результат:" << endl;
        strings[i].print_to(std::cout);
        strings[i].print_to(out);

        std::cout << "\n";
        out << "\n";

        delete [] strings[i].symbols;
    }
    delete [] strings;
}
