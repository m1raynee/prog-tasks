#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>

using std::istream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::noskipws;
using std::skipws;
using std::setw;
using std::endl;



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
void protoO1(ostream &out, unsigned *counts) {
    out << "В файле считано строк: "<< counts[0] << ", из которых содержат точки: " << counts[1] << endl;
}
void protoO2(ostream &out, unsigned line_index, float point_x, float point_y, bool too_many = false) {
    out << line_index << ":\tx: " << setw(8) << point_x << " y: " << setw(8) << point_y
        << (too_many ? " (лишние числа опущены)" : "") << endl;
}
void protoO2(ostream &out, unsigned line_index, bool too_few = false) {
    out << line_index << ":\tНе подходит: " << (too_few ? "только одно значение" : "пустая строка") << endl;
}


unsigned *calcLine(istream &in, bool to_offset_back = true) {
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


float *readLine(istream &in, unsigned count) {
    float *point = new float[2]{0, 0};
    unsigned i = 0;

    if (count >= 2) {
        in >> skipws;
        in >> point[0];
        in >> point[1];
        in >> noskipws;
        i = 2;
    }

    for (; i < count; ++i) {
        float x;
        in >> skipws >> x >> noskipws;
    }
    in.get();  // '\n' at the end

    return point;
}


unsigned *calcFile(istream &in) {
    unsigned *counts = new unsigned[2]{0, 0};
    unsigned *calc;
    while (!in.eof()) {
        calc = calcLine(in, false);

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


float **readFile(ostream &protocol, istream &in, unsigned counts[]) {
    float **points = new float *[counts[1]];
    unsigned *calc;

    bool end_f = false;
    for (unsigned i = 0; i < counts[0]; ++i) {
        calc = calcLine(in);


        // if (calc[0] == (unsigned)-1) {
        //     break;
        // };

        switch (calc[0])
        {
        case 0:
            readLine(in, calc[0]);
            protoO2(protocol, i);
            break;
        case 1:
            readLine(in, calc[0]);
            protoO2(protocol, i, true);
            break;
        case 2:
            points[i] = readLine(in, calc[0]);
            protoO2(protocol, i, points[i][0], points[i][1]);
            break;

        default:
            points[i] = readLine(in, calc[0]);
            protoO2(protocol, i, points[i][0], points[i][1], true);
            break;
        }
        if (end_f) break;
    }
    delete [] calc;
    return points;
}


int main() {
    ifstream in;
    ofstream out, protocol;
    in.open("in.txt");
    out.open("out.txt", std::ios::out);
    protocol.open("protocol.txt", std::ios::out);

    if (!(in.is_open() and out.is_open() and protocol.is_open())) {
        protoE1(in, out, protocol);
        return 0;
    }

    float **points;
    unsigned *counts;

    counts = calcFile(in);
    protoO1(protocol, counts);

    points = readFile(protocol, in, counts);

    in.close();
    out.close();
    protocol.close();
    return 0;
}
