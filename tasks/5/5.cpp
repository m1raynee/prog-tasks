#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

typedef unsigned int uint;

void __OutAi(ostream *f, float *A, uint b) {
    for (uint i = 0; i < b; i++) {*f << A[i] << '\t';}
    *f << '\n';
}
void Out1(float **A, uint *size, ostream *f) {
    for (uint i = 0; i < size[0]; i++) {__OutAi(f, A[i], size[1]);}
}
uint *CalcSize(ifstream *f) {
    float tmp;
    char s;// = ' ';
    static uint size[2]{0, 0};  // TODO: ограницение
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
    return size;
}

float **ReadFile(ifstream *f, uint *size) {
    char s;
    static float **A = new float*[size[0]];
    for (uint i = 0; i < size[0]; i++) {
        s = '!';

        A[i] = new float[size[1]];
        for (uint j = 0; j < size[1]; j++) *f >> A[i][j];

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

    // ничего лишнего

    // обращение к функциям:
    // calc_size
    cout << "Расчёт файла: ";
    uint *size = CalcSize(&f);
    f.close();
    uint real_size;
    if (size[0] > size[1]) real_size = size[1];
    else real_size = size[0];

    cout << "Реальный размер матрицы: " << real_size << '\n';

    f.open(name);
    if (!f.is_open()) {
        cout << "ERR: Файл не открылся\n";
        return 0;
    }
    // <- f ->
    // input
    float **A = ReadFile(&f, size);
    f.close();
    cout << "\n\n\n";

    // out1 - отправка сформированного массива

    // fstream result;
    // result.open("result.txt", ios::out);

    Out1(A, size, &cout);
    // process
    // out2 - отправка ответа на задание 

    return 0;
}