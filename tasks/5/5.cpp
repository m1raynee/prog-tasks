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

    f->clear();
    f->seekg(0, ios::beg);
    *f >> r[0] >> r[1];
    *f >> noskipws;
    int ch;
    if (static_cast<char>((ch = f->get())) != '\n') {
        cout << "ERR: Ошибка чтения параметров m и k\n"
        << r[0] << ' ' << r[1];
        return 0;
    }
    *f >> skipws;
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
    static float **read_matrix = new float*[size_a];

    for (uint i = 0; i < size_a; i++) {
        s = '!';

        read_matrix[i] = new float[size_b];
        for (uint j = 0; j < size_b; j++) *f >> read_matrix[i][j];

        *f >> noskipws;
        while (!f->eof() and s != '\n') *f >> s;
        *f >> skipws;
    }
    return read_matrix;
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
    uint N = CalcSize(&f);
    cout << "Реальный размер матрицы: " << N << '\n';

    if (mk[1] >= N) {
        cout << "ERR: Параметр k=" << mk[1]
        << " не может быть больше размера матрицы.\n";
    }

    float **A = ReadFile(&f, N, N);
    f.close();

    cout << "\n\n\n";
    Out1(A, N, N, &cout);

    ofstream result;
    result.open("result.txt", ios::out);
    if (!f.is_open()) {
        cout << "ERR: Файл не открылся\n";
        return 0;
    }

    Out1(A, N, N, &result);



    // process
    // out2 - отправка ответа на задание 

    return 0;
}