#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

typedef unsigned int uint;

void __OutAi(ostream *f, float *A, uint size_b) {
    for (uint i = 0; i < size_b; i++) {*f << A[i] << '\t';}
    *f << '\n';
}
void Out1(float **A, uint size_a, uint size_b, ostream *f) {
    for (uint i = 0; i < size_a; i++) {__OutAi(f, A[i], size_b);}
}

uint *ReadMK(ifstream *f) {
    static uint r[2];

    f->seekg(0, f->beg);
    *f >> r[0] >> r[1];
    *f >> noskipws;
    int ch;
    if (static_cast<char>((ch = f->get())) != '\n') {
        cout << "ERR: Ошибка чтения параметров m и k\n"
        << r[0] << ' ' << r[1] << ' ' << static_cast<char>(ch);
        return 0;
    }
    if (r[0] > r[1]) {
        cout << "ERR: m не может быть больше k\n";
        return 0;
    }
    cout << "Считаны параметры: m=" << r[0] << ", k=" << r[1] << "\n";
    return r;
}

uint CalcSize(ifstream *f) {
    char s;
    uint size[2]{0, 0};
    uint tmp_size = 0;
    *f >> noskipws;

    while (!f->eof()) {
        do {
            *f >> s;
        } while (s != '\t' and s != '\n');

        if (!f->eof()) {
            tmp_size++;

            if (s == '\n') {
                if (size[1] > tmp_size or size[0] == 0) {
                    size[1] = tmp_size;
                }
                tmp_size = 0;
                size[0]++;
            }
        }
    }
    *f >> skipws;

    if (size[0] > size[1]) return size[1];
    else return size[0];
}

float **ReadFile(ifstream *f, uint size_a, uint size_b) {
    ReadMK(f);

    char s;
    static float **A = new float*[size_a];

    for (uint i = 0; i < size_a; i++) {
        s = '!';

        A[i] = new float[size_b];
        for (uint j = 0; j < size_b; j++) *f >> A[i][j];

        *f >> noskipws;
        while (!f->eof() and s != '\n') *f >> s;
        *f >> skipws;
    }
    return A;
}

int main() {
    char name[100] = "C:/Users/peche/OneDrive/Документы/Github/prog-tasks/tasks/5/0.txt";

    ifstream f;
    f.open(name);

    if (!f.is_open()) {
        cout << "ERR: Файл не открылся\n";
        return 0;
    }

    uint *mk = ReadMK(&f);
    if (mk[0] == 0) {
        return 0;
    }

    cout << "Расчёт файла: ";
    uint size = CalcSize(&f);

    cout << "Реальный размер матрицы: " << size << '\n';

    if (mk[1] >= size) {
        cout << "ERR: Параметр m=" << mk[1]
        << " не может быть больше размера матрицы.\n";
    }

    float **A = ReadFile(&f, size, size);
    f.close();

    cout << "\n\n\n";
    Out1(A, size, size, &cout);

    ofstream result;
    result.open("result.txt", ios::out);

    Out1(A, size, size, &result);


    // process
    // out2 - отправка ответа на задание 

    return 0;
}