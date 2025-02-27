// Преобразовать заданную строку следующим образом: каждую точку заменить многоточием

#include <fstream>
#include <iostream>
#include <iomanip>

using std::istream, std::ifstream, std::ofstream, std::ostream;
using std::noskipws;
using std::endl;

class StringLen {
    public:
        // Null constructor
        StringLen() : _text(nullptr), _len(0) {};

        // Rich constructor
        StringLen(char* t, unsigned l) : _text(new char[l]{}), _len(l) {
            for (unsigned i = 0; i < l; ++i) {
                _text[i] = t[i];
            }
        }

        // I. Destructor
        ~StringLen() { delete [] _text; }

        // II. copy constructor
        StringLen(const StringLen& other)
            : StringLen(other._text, other._len) {}

        // III. copy assignment
        StringLen& operator=(const StringLen& other) {
            StringLen temp(other);
            std::swap(_text, temp._text);
            std::swap(_len, temp._len);
            return *this;
        }

        // Make task
        void process();

        // Print to the stream
        void print(ostream&);

    private:
        char* _text;
        unsigned _len;
};

void StringLen::process() {
    unsigned j = 0, dots_count = 0;
    char *new_text;

    for (unsigned i = 0; i < _len; ++i) {
        if (_text[i] == '.') ++dots_count;
    }

    new_text = new char[1 + _len + dots_count*(3 - 1)];

    for (unsigned i = 0; i < _len; ++i) {
        if (_text[i] == '.') {
            for (unsigned k = 0; k < 3; ++k) new_text[j++] = '.';
        } else new_text[j++] = _text[i];
    }

    delete[] _text;
    _text = new_text;
    _len = j;
}

void StringLen::print(ostream& o) {
    for (unsigned i = 0; i < _len; ++i) o << _text[i];
    if (_len == 0) o << "(пустая строка)";
    o << endl;
}

StringLen* input(istream& in, unsigned* len, char *delim) {
    StringLen* result;
    int ch;
    char d = *delim;


    unsigned str_count = 1;

    while ((ch = in.get()) and ch != '\n' and ch != -1);
    while ((ch = in.get()) and ch != -1) if (ch == '\n') ++str_count;

    result = new StringLen[str_count];

    in.clear(); in.seekg(0);

    if (d == '\0') in >> d;
    while ((ch = in.get()) and ch != '\n' and ch != -1);

    while (!in.eof()) {
        unsigned char_count = 0;
        char* text = (char*)calloc(char_count, sizeof(char));
        bool d_found = false;

        while (
            (ch = in.get())
            and ch != '\n'
            and ch != -1
        ) {
            if (!d_found) {
                if (ch == d) {
                    d_found = true;
                    continue;
                }
                text = (char*)realloc(text, char_count+1);
                text[char_count++] = (char)ch;
            }
        }

        result[(*len)++] = StringLen(text, char_count);
        delete [] text;
    }

    *(delim) = d;
    return result;
}

int main() {
    ifstream in;
    in.open("in.txt");
    in >> noskipws;

    ofstream out;
    out.open("out.txt");

    in >> noskipws;
    std::cout << "Задание: Преобразовать заданную строку следующим образом: "
    << "каждую точку заменить многоточием\nДаричев Егор а.г. 4352\n"
    << "Введите номер варианта ввода: ";

    StringLen* strings;
    unsigned length = 0;
    char delim = '\0';
    switch (std::cin.get()) {
    case '1':
        break;
    case '2':
        delim = '\n';
        break;
    default:
        std::cout << "Неверный номер варианта" << endl;
        return 0;
    }
    strings = input(in, &length, &delim);

    for (unsigned i = 0; i < length; ++i) {
        out << "Строка No." << i+1 << ":\nСчитано:    ";
        strings[i].print(out);

        strings[i].process();
        out << "Результат:  ";
        strings[i].print(out);
    }
    std::cout << "Ответ записан в файле вывода" << endl;

    delete [] strings;

    return 0;
}