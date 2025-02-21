// Преобразовать заданную строку следующим образом: каждую точку заменить многоточием

#include <fstream>
#include <iostream>
#include <iomanip>

using std::istream, std::ifstream, std::ofstream, std::ostream;
using std::noskipws;
using std::endl;

class StringLen {
    public:
        // Constructors
        StringLen()
            : _text(nullptr), _len(0), _buffer_size(0) {};

        StringLen(char* t, unsigned bs, unsigned l) : _text(new char[bs]{}), _len(l), _buffer_size(bs) {
            for (unsigned i = 0; i < bs; ++i) {
                _text[i] = t[i];
            }
        }
        // I. Destructor
        ~StringLen() { std::cout << "destructor called, len=" << _len << endl; delete [] _text; }

        // II. copy constructor
        StringLen(const StringLen& other)
            : StringLen(other._text, other._buffer_size, other._len) {
                std::cout << "copy constructor called, on len=" << _len << " other len=" << other._len << endl;
            }

            StringLen& operator=(const StringLen& other) {
                // III. copy assignment
                // implemented through copy-and-swap for brevity
                // note that this prevents potential storage reuse
            std::cout << "copy assignment called, on len=" << _len << " other len=" << other._len << endl;
            StringLen temp(other);
            std::swap(_text, temp._text);
            std::swap(_len, temp._len);
            std::swap(_buffer_size, temp._buffer_size);
            return *this;
        }
        void process();
        void out(ostream&);

    private:
        char* _text;
        unsigned _len;
        unsigned _buffer_size;
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

void StringLen::out(ostream& o) {
    for (unsigned i = 0; i < _len; ++i) o << _text[i];
    o << endl;
}

// StringLen* input1(istream& in, unsigned* len) {
//     StringLen* result;

//     return result;
// }

int main() {
    char* s1 = new char[3]{'1', '2', '.'};
    char* s2 = new char[1]{'.'};
    StringLen* ar = new StringLen[2]{};

    ar[0] = StringLen(s1, 3, 3);
    ar[1] = StringLen{s2, 1, 1};

    ar[0].out(std::cout);
    ar[1].out(std::cout);

    delete [] ar;
    return 0;
}