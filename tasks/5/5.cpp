#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

typedef unsigned int uint;

void __OutAi(ostream *out, float *A, uint size_b);
void Out1(float **A, uint size_a, uint size_b, ostream *out);
void Out2(float result, int *mk, ostream *out);
int *ReadMK(istream *in);
uint CalcSize(istream *in);
float **ReadFile(istream *in, uint size_a, uint size_b);
float Process(float **matrix, uint size_a, uint size_b, int *mk);


int main() {
    char name[100] = "C:/Users/peche/OneDrive/Документы/Github/prog-tasks/tasks/5/0.txt";

    ifstream f;
    ofstream result;
    f.open(name);
    result.open("result.txt");

    if (!(f.is_open() and result.is_open())) {
        cout << "ERR: Файл не открылся\n";
        return 0;
    }

    int *mk = ReadMK(&f);
    if (mk[0] == 0) {
        return 0;
    }

    cout << "Расчёт файла: ";
    uint N = CalcSize(&f);
    cout << "Реальный размер матрицы: " << N << '\n';

    if (N == 0) {
        cout << "ERR: считан нулевой размер.\n";
        return 0;
    }

    float **A = ReadFile(&f, N, N);
    f.close();

    Out1(A, N, N, &cout);
    Out1(A, N, N, &result);

    Out2(Process(A, N, N, mk), mk, &cout);
    Out2(Process(A, N, N, mk), mk, &result);

    return 0;
}

void __OutAi(ostream *out, float *A, uint size_b) {
    for (uint i = 0; i < size_b; i++) {*out << A[i] << "\t|";}
    *out << '\n';
}

void Out1(float **A, uint size_a, uint size_b, ostream *out) {
    *out << "*\t|";
    for (uint i = 0; i < size_a; i++) {
        *out << i << "\t|";
    }
    *out << "\n-\t|";
    for (uint i = 0; i < size_a; i++) {
        *out << "\t|";
    }
    *out << '\n';
    for (uint i = 0; i < size_a; i++) {
        *out << i << "\t|";
        __OutAi(out, A[i], size_b);}
}

void Out2(float result, int *mk, ostream *out) {
    *out << "Максимальное число в заданной области: " << result << '\n'
    << "m=" << mk[0] << " k=" << mk[1] << '\n';
}

int *ReadMK(istream *in) {
    static int r[2];

    in->clear();
    in->seekg(0, ios::beg);
    *in >> r[0] >> r[1];
    *in >> noskipws;
    int ch;
    if (static_cast<char>((ch = in->get())) != '\n') {
        cout << "ERR: Ошибка чтения параметров m и k\n"
        << r[0] << ' ' << r[1];
        return 0;
    }
    *in >> skipws;
    if (r[0] > r[1]) {
        cout << "ERR: m не может быть больше k\n";
        return 0;
    }
    cout << "Считаны параметры: m=" << r[0] << ", k=" << r[1] << "\n";
    return r;
}

uint CalcSize(istream *in) {
    char s;
    uint size[2]{0, 0};
    uint tmp_size = 0;
    *in >> noskipws;

    while (!in->eof()) {
        do {
            *in >> s;
        } while (s != '\t' and s != '\n');

        if (!in->eof()) {
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
    *in >> skipws;

    if (size[0] > size[1]) return size[1];
    else return size[0];
}

float **ReadFile(istream *in, uint size_a, uint size_b) {
    ReadMK(in);

    char s;
    static float **read_matrix = new float*[size_a];

    for (uint i = 0; i < size_a; i++) {
        s = '!';

        read_matrix[i] = new float[size_b];
        for (uint j = 0; j < size_b; j++) *in >> read_matrix[i][j];

        *in >> noskipws;
        while (!in->eof() and s != '\n') *in >> s;
        *in >> skipws;
    }
    return read_matrix;
}

float Process(float **matrix, uint size_a, uint size_b, int *mk) {
    static float max_value = -HUGE_VALF;
    for (uint i = 0; i < size_a; i++) {
        for (uint j = 0; j < size_b; j++) {
            if (
                (
                    (i >= mk[0] and i <= mk[1]) 
                    or (j >= mk[0] and j <= mk[1])
                )
                and max_value < matrix[i][j]
            ) max_value = matrix[i][j];
        }
    }

    return max_value;
}
