#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>

using std::istream, std::ifstream, std::ofstream, std::ostream;
using std::noskipws, std::skipws, std::setw, std::endl;
using std::tgamma;


double EPS = 1e-6;

// выводит в протокол (или консоль) проблему с открытием файлов
void protoE1(ifstream &in, ofstream &out, ofstream &protocol) {
    if (!protocol.is_open()) {
        std::cout << "ERR: Файл \"протокол\" не открылся." << endl;
        return;
    }
    if (!in.is_open()) {
        if (!out.is_open()) {
            protocol << "ERR: Файлы ввода и вывода не открылись.";
        } else {
            protocol << "ERR: Файл ввода не открылся.";
        }
    } else {
        protocol << "ERR: Файл вывода не открылся.";
    }
    protocol << endl;
}

// заголовок протокола
void protoRead(ostream &out, unsigned *counts) {
    out << "В файле считано строк: "<< counts[0] << ", из которых содержат точки: " << counts[1] << endl;
}

// вывод точки
void outPoint(ostream &out, double point_x, double point_y) {
    out << "x: " << setw(8) << point_x << " y: " << setw(8) << point_y;
}

// вывод результата успешного чтения строки в протокол
void protoReadLine(ostream &out, unsigned line_index, double point_x, double point_y, bool too_many = false) {
    out << line_index << "\t";
    outPoint(out, point_x, point_y);
    if (too_many) {
        out << " (лишние числа опущены)";
    }
    out << endl;
}

// вывод результата безуспешного чтения строки в протокол
void protoReadLine(ostream &out, unsigned line_index, bool too_few = false) {
    out << line_index << ":\tНе подходит: " << (too_few ? "только одно значение" : "пустая строка") << endl;
}

// запись считанных точек в выход
void outPoints(ostream &out, double **points, unsigned points_v) {
    out << "Считано точек: " << points_v << endl;
    for (unsigned i = 0; i < points_v; ++i) {
        outPoint(out, points[i][0], points[i][1]);
    }
}

// считает сколько в строке чисел, выводит количество чисел и символов в строке
unsigned *calcFileLine(istream &in, bool to_offset_back = true) {
    unsigned *calc_res = new unsigned[2]{0, 0};
    int c = '|';

    in >> noskipws;
    while (c != '\n' and !in.eof()) {
        do {
            ++calc_res[1];
        } while ((c = in.get()) and c != ' ' and c != '\n' and !in.eof());
        if (calc_res[1] > 1) ++calc_res[0];
    }

    if (to_offset_back) {in.seekg(-((int)(calc_res[1])), in.cur);}
    return calc_res;
}


// считывает `count` чисел из строки, возвращает точку
double *readFileLine(istream &in, unsigned count) {
    double *point = new double[2]{0, 0};
    unsigned i = 0;

    if (count >= 2) {
        in >> skipws;
        in >> point[0];
        in >> point[1];
        in >> noskipws;
        i = 2;
    }

    for (; i < count; ++i) {
        double x;
        in >> skipws >> x >> noskipws;
    }
    in.get();  // '\n' at the end

    return point;
}

// считывает количество строк в файле, возвращает
// количество строк и количество "хороших" строк
unsigned *calcFile(istream &in) {
    unsigned *counts = new unsigned[2]{0, 0};
    unsigned *calc;
    while (!in.eof()) {
        calc = calcFileLine(in, false);

        if (calc[0] != (unsigned)-1 and !in.eof()) {
            ++counts[0];
            if (calc[0] >= 2) ++counts[1];
        }
        delete [] calc;
    }

    in.clear();
    in.seekg(0);

    return counts;
}

// считывает файл, выводя процесс в `protocol`, возвращает точки
double **readFile(ostream &protocol, istream &in, unsigned counts[]) {
    double **points = new double *[counts[1]];
    unsigned *calc;

    for (unsigned i = 0; i < counts[0]; ++i) {
        calc = calcFileLine(in);
        switch (calc[0])
        {
        case 0:
            readFileLine(in, calc[0]);
            protoReadLine(protocol, i);
            break;
        case 1:
            readFileLine(in, calc[0]);
            protoReadLine(protocol, i, true);
            break;
        case 2:
            points[i] = readFileLine(in, calc[0]);
            protoReadLine(protocol, i, points[i][0], points[i][1]);
            break;

        default:
            points[i] = readFileLine(in, calc[0]);
            protoReadLine(protocol, i, points[i][0], points[i][1], true);
            break;
        }
    }
    delete [] calc;
    return points;
}

bool equals(double v1, double v2, double eps = EPS) {return abs(v1 - v2) < eps;}
unsigned factorial(unsigned v) {return (unsigned)tgamma(v+1);}
unsigned maxLineCount(unsigned point_v) {return (point_v)*(point_v-1)/(2);}

// vector normalization
double *vecNorm(double vector[2]) {
    double length = pow(pow(vector[0], 2) + pow(vector[1], 2), 0.5);
    vector[0] /= length;
    vector[1] /= length;
    return vector;
}

double *getLineFromPoints(double p0[2], double p1[2]) {
    double ab[2]{p1[0]-p0[0], p1[1]-p0[1]};
    double *result = new double[3]{
        ab[1],
        -(ab[0]),
        -(ab[1]*p0[0]) + ab[0]*p0[1]
    };
    return result;
}

bool isDistinctLine(double line1[3], double line2[3]) {
    if (
        equals(line1[0]*line2[1], line2[0]*line1[1])
        and equals(line1[0]*line2[2], line2[0]*line1[2])
    ) return true;
    return false;
}

bool isPointOnLine(double line[3], double point[2]) {
    return equals(line[0]*point[0]+line[1]*point[1]+line[2], 0);
}

double **constructLines(double **points, unsigned points_v) {
    double **lines = new double*[maxLineCount(points_v)]{};
    unsigned line_count = 0;
    for (unsigned i = 0; i < points_v - 1; ++i) {
        for (unsigned j = i + 1; j < points_v; ++j) {
            if (points[i][0] == points[j][0] and points[i][1] == points[j][1]) continue;
            lines[line_count] = getLineFromPoints(points[i], points[j]);
            line_count++;
        }
    }
    return lines;
}

unsigned *findDistinctLines(double **lines, unsigned points_v, unsigned *distinct_v) {
    *distinct_v = 0;
    unsigned all_lines_count = maxLineCount(points_v);
    unsigned *distinct_indexes = new unsigned[all_lines_count]{};

    for (unsigned i = 0; i < all_lines_count; ++i) {
        bool is_distinct = true;
        unsigned d = 0;
        while (is_distinct and d < *distinct_v) {
            if (!isDistinctLine(lines[distinct_indexes[d]], lines[i])) is_distinct = false;
            d++;
        }
        if (is_distinct) distinct_indexes[(*distinct_v)++] = i;
    }

    unsigned *result = new unsigned[*distinct_v]{};
    for (unsigned i = 0; i < *distinct_v; ++i) {
        result[i] = distinct_indexes[i];
    }

    delete [] distinct_indexes;
    return result;
}


unsigned *processLines(
    double **distinct_lines,
    unsigned distinct_v,
    double **points,
    unsigned points_v
) {
    unsigned *result = new unsigned[distinct_v];
    for (unsigned l = 0; l < distinct_v; ++l) {
        for (unsigned p = 0; p < points_v; ++p) {
            if (isPointOnLine(distinct_lines[l], points[p])) {(result[l])++;}
        }
    }
    return result;
}

void indexMaxSort(unsigned arr[], unsigned v) {

}

int main() {
    ifstream in;
    ofstream out, protocol;
    in.open("in.txt");
    out.open("out.txt");
    protocol.open("protocol.txt");

    if (!(in.is_open() and out.is_open() and protocol.is_open())) {
        protoE1(in, out, protocol);
        return 0;
    }

    double **points;
    unsigned *counts;

    counts = calcFile(in);
    protoRead(protocol, counts);

    points = readFile(protocol, in, counts);
    outPoints(out, points, counts[1]);

    in.close();
    out.close();
    protocol.close();
    return 0;
}
