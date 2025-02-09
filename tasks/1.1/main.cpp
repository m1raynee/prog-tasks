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

    bool next(unsigned i) {
        return this->symbols[i] != this->mark;
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

    void print_to(ostream &out, bool show_mark = true, bool newline = true) {
        unsigned i = 0;
        while (this->next(i)) out << this->symbols[i++];
        if (show_mark) out << this->symbols[i];
        if (newline) out << endl;
    }

    void put(char ch, unsigned *at) {
        this->symbols = (char *)realloc(this->symbols, (*at)+1);
        if (this->symbols == NULL) exit(2);
        this->symbols[(*at)++] = ch;
    }
};

str *input1(istream &in, unsigned *v) {
    *v = 0;
    char delimeter, mark;
    int ch;
    str *strings = (str *)malloc(*v * sizeof(str));

    in >> noskipws;
    in >> delimeter >> mark;
    while ((ch = in.get()) and ch != '\n' and ch != -1);

    if (in.eof()) {
        exit(1);
    }

    while (!in.eof()) {
        unsigned size = 0;
        int delimeter_pos = -1;
        int mark_pos = -1;

        str l;
        l.symbols = (char *)malloc(size);
        l.mark = mark;

        while ((ch = in.get()) and ch != '\n' and ch != -1) {
            if (delimeter_pos != -1) continue;
            if (l.symbols == NULL) exit(2);
            if (ch == delimeter and delimeter_pos == -1) {
                delimeter_pos = size;
                continue;
            }
            else if (ch == mark and mark_pos == -1) mark_pos = size;

            l.put((char)ch, &size);
        }

        if (mark_pos == -1) l.put(mark, &size);
        else if (delimeter_pos == -1) l.put(mark, &size);

        strings = (str *)realloc(strings, (*v + 1) * sizeof(str));
        if (strings == NULL) exit(3);
        strings[(*v)++] = l;
    }

    std::cout << endl;
    return strings;
}

str *input2(istream &in, unsigned *v) {
    *v = 0;
    char mark;
    int ch;
    str *strings = (str *)malloc(*v * sizeof(str));

    in >> noskipws;
    in >> mark;
    while ((ch = in.get()) and ch != '\n' and ch != -1);

    if (in.eof()) {
        exit(1);
    }

    while (!in.eof()) {
        unsigned size = 0;
        int mark_pos = -1;

        str l;
        l.symbols = (char *)malloc(size);
        l.mark = mark;

        while ((ch = in.get()) and ch != '\n' and ch != -1) {
            if (l.symbols == NULL) exit(2);
            if (ch == mark and mark_pos == -1) mark_pos = size;
            l.put((char)ch, &size);
        }

        if (mark_pos == -1) l.put(mark, &size);

        strings = (str *)realloc(strings, (*v + 1) * sizeof(str));
        if (strings == NULL) exit(3);
        strings[(*v)++] = l;
    }

    std::cout << endl;
    return strings;
}


int main() {
    ifstream in;
    in.open("in.txt");

    unsigned string_count = 0;
    str *strings = input1(in, &string_count);

    for (unsigned i = 0; i < string_count; ++i) {
        strings[i].process();
        strings[i].print_to(std::cout);
    }
}
