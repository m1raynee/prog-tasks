// Преобразовать заданную строку следующим образом: каждую точку заменить многоточием

#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>

using std::istream, std::ifstream, std::ofstream, std::ostream;
using std::endl;


struct str {
    char *symbols;
    char mark = '#';

    int ellipsis_length = 3;

    bool next(unsigned i) {
        return this->symbols[i] != this->mark;
    }

    void process() {
        unsigned i = 0, j = 0, dots_count = 0;
        char *new_symbols;

        while (this->next(i)) {
            if (this->symbols[i++] == '.') ++dots_count;
        }

        new_symbols = new char[1 + i + dots_count*(this->ellipsis_length - 1)];
        i = 0; j = 0;

        while (this->next(i)) {
            if (this->symbols[i] == '.') {
                for (unsigned k = 0; k < this->ellipsis_length; ++k) new_symbols[j++] = '.';
                ++i;
            } else {
                new_symbols[j++] = this->symbols[i++];
            }
        }

        new_symbols[j++] = '#';

        delete [] this->symbols;
        this->symbols = new_symbols;
    }

    void print_to(ostream &out, bool mark = true, bool newline = false) {
        unsigned i = 0;
        while (this->next(i)) out << this->symbols[i++];
        if (mark) out << this->symbols[i];
        if (newline) out << endl;
    }
};


int main() {
    ifstream in;
    in.open("in.txt");

    str a;
    char *meow = new char[6]{'m', 'e', 'o', 'w', '.', '#'};
    a.symbols = meow;
    a.mark = '#';

    a.process();
    a.print_to(std::cout);

}
