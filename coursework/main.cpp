#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>

#define inrangefrom(var, from, to) for (unsigned var = (from); var < (to); ++var)
#define inrange(var, to) inrangefrom(var, 0, to)

using std::istream, std::ifstream, std::ofstream, std::ostream;
using std::noskipws, std::skipws, std::setw, std::endl, std::left, std::right;
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
void protoE2(ostream &out, unsigned count, bool is_line = false) {
    out << "В файле не обнаружено достаточное количество "
        << "точек для построения хотя бы одной прямой ("
        << (is_line ? "построено прямых: " : "найдено точек: ") << count << ")\n";
}

// заголовок протокола
void protoRead(ostream &out, unsigned *counts) {
    out << "В файле считано строк: "       << counts[0]
        << ", из которых содержат точки: " << counts[1]
        << endl;
}

void outIndex(ostream &out, unsigned i) {out << setw(4) << left << i << right;}

// вывод точки
void outPoint(ostream &out, double point[2]) {
    out << "x: " << setw(4) << point[0]
        << " y: " << setw(4) << point[1];
}
// вывод линии
void outLine(ostream &out, double line[3]) {
    out << "A: "  << setw(4) << line[0]
        << " B: " << setw(4) << line[1]
        << " C: " << setw(4) << line[2]
        << endl;
}

// вывод результата успешного чтения строки в протокол
void protoReadLine(ostream &out, unsigned line_index, double point[2], bool too_many = false) {
    outIndex(out, line_index);
    outPoint(out, point);
    if (too_many) {
        out << " (лишние числа опущены)";
    }
    out << endl;
}

// вывод результата безуспешного чтения строки в протокол
void protoReadLine(ostream &out, unsigned line_index, bool too_few = false) {
    out << line_index << ":\tНе подходит: "
        << (too_few ? "только одно значение" : "пустая строка")
        << endl;
}
// protocol, line_count, i, j, lines[line_count]
void protoLine(ostream &out, unsigned line_index, unsigned pt0, unsigned pt1) {
    out << "Точки " << pt0 << " и " << pt1
        << " не образуют прямую: одна и та же точка"
        << endl;
}
void protoLine(ostream &out, unsigned line_index, unsigned pt0, unsigned pt1, double *line) {
    out << "Точки " << pt0 << " и " << pt1
    << " образуют прямую #" << line_index << ": ";
    outLine(out, line);
}
// protoDistinction(protocol, is_distinct, lines, distinct_indexes[d], i);
void protoDistinction(
    ostream &out,
    bool is_distinct,
    unsigned distinct_i,
    unsigned i
) {
    out << "Прямая #" << i << ' ';
    if (is_distinct) {
        out << "не повторялась" << endl;
        return;
    }
    out << "- это прямая #" << distinct_i << endl;
}

// запись считанных точек в выход
void outPoints(ostream &out, double **points, unsigned points_v) {
    out << "Считано точек: " << points_v << endl;
    inrange(i, points_v) {
        outIndex(out, i);
        outPoint(out, points[i]);
        out << endl;
    }
}
void outLines(ostream &out, double **lines, unsigned lines_v) {
    out << "Составлено прямых: " << lines_v << endl;
    inrange(i, lines_v) {
        out << setw(4)
            << left << i << right;
        outLine(out, lines[i]);
    }
}
void protoProcess(ostream &out, unsigned l) {
    out << "На прямой #" << l << ':' << endl;
}
void protoProcess(ostream &out, unsigned l, double point[2]) {
    out << "    находится точка (" << point[0]
        << ' ' << point[1] << ')'
        << endl;
}
void protoProcessResult(ostream &out, unsigned v) {
    out << "    итого: " << v << endl;
}
// void outProcessLinePoints(ostream &out, )
void outResult(
    ostream &out,
    unsigned *line_counts, unsigned **lines_points,
    unsigned *indexes, unsigned indexes_v,
    double **lines, double **points
) {
    unsigned line_i, point_i;

    out << "Максимальное количество точек: " << line_counts[*indexes] << endl;
    inrange(l, indexes_v) {
        line_i = indexes[l];
        out << "    достигается на прямой #" << line_i
            << " (A=" << lines[l][0]
            << " B="  << lines[l][1]
            << " C="  << lines[l][2]
            << ") с точками:"
            << endl;

        inrange(p, line_counts[line_i]) {
            point_i = lines_points[line_i][p];
            out << "        ";
            outIndex(out, point_i);
            outPoint(out, points[point_i]);
            out << endl;
        }
    }

    out << "\nитого прямых: " << indexes_v << endl;
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
        in >> skipws >> point[0]
        >> point[1] >> noskipws;
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

    unsigned j = 0;

    inrange(i, counts[0]) {
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
            points[j] = readFileLine(in, calc[0]);
            protoReadLine(protocol, i, points[j]);
            j++; break;

        default:
            points[j] = readFileLine(in, calc[0]);
            protoReadLine(protocol, i, points[j], true);
            j++; break;
        }
        delete [] calc;
    }
    return points;
}


bool equals(double v1, double v2 = 0, double eps = EPS) {return abs(v1 - v2) < eps;}
unsigned maxLineCount(unsigned point_v) {return (point_v)*(point_v-1)/(2);}
double zeromod(double v) {return (double)(equals(v) ? 0 : v);}

double *getLineFromPoints(double p0[2], double p1[2]) {
    double ab[2]{p1[0]-p0[0], p1[1]-p0[1]};
    double *result = new double[3]{
        zeromod(ab[1]),
        zeromod(-(ab[0])),
        zeromod(-(ab[1]*p0[0]) + ab[0]*p0[1])
    };
    return result;
}

bool isSameLine(double line1[3], double line2[3]) {
    return (equals(line1[0]*line2[1], line2[0]*line1[1])
        and equals(line1[1]*line2[2], line2[1]*line1[2])
        and equals(line1[2]*line2[0], line2[2]*line1[0])
    );
}


bool isPointOnLine(double line[3], double point[2]) {
    return equals(line[0]*point[0]+line[1]*point[1]+line[2]);
}

double **constructLines(ostream &protocol, double **points, unsigned points_v, unsigned *lines_v) {
    *lines_v = 0;
    double **lines = new double*[maxLineCount(points_v)]{};
    inrange(i, points_v-1) {
        inrangefrom(j, i+1, points_v) {
            if (points[i][0] == points[j][0] and points[i][1] == points[j][1]) {
                protoLine(protocol, *lines_v, i, j);
                continue;
            }

            lines[*lines_v] = getLineFromPoints(points[i], points[j]);
            protoLine(protocol, *lines_v, i, j, lines[*lines_v]);
            (*lines_v)++;
        }
    }
    return lines;
}

double **findDistinctLines(ostream &protocol, double **lines, unsigned lines_v, unsigned *distinct_v) {
    *distinct_v = 0;
    unsigned *distinct_indexes = new unsigned[lines_v]{};

    inrange(i, lines_v) {
        bool is_distinct = true;
        unsigned d = 0;
        for (; d < *distinct_v; ++d) {
            if (isSameLine(lines[distinct_indexes[d]], lines[i])) {
                is_distinct = false; break;
            }
        }
        protoDistinction(protocol, is_distinct, distinct_indexes[d], i);
        if (is_distinct) distinct_indexes[(*distinct_v)++] = i;
    }

    double **result = new double*[*distinct_v]{};
    inrange(i, *distinct_v) {
        result[i] = lines[distinct_indexes[i]];
    }

    delete [] distinct_indexes;
    return result;
}


unsigned *processLines(
    ostream &protocol,
    double **distinct_lines, unsigned distinct_v,
    double **points, unsigned points_v,
    unsigned **&line_points
) {
    line_points = new unsigned*[distinct_v]{};
    unsigned *result = new unsigned[distinct_v]{};

    inrange(l, distinct_v) {
        protoProcess(protocol, l);
        unsigned *res = new unsigned[points_v];

        inrange(p, points_v) {
            if (isPointOnLine(distinct_lines[l], points[p])) {
                res[result[l]++] = p;
                protoProcess(protocol, l, points[p]);
            }
        }

        line_points[l] = new unsigned[result[l]]{};
        inrange(i, result[i]) {
            line_points[l][i] = res[i];
        }
        delete [] res;

        protoProcessResult(protocol, result[l]);
    }
    return result;
}

// **processed_line = [[points_count], [points]]
unsigned *processedLinesSort(unsigned arr[], unsigned v, unsigned *result_v) {
    unsigned *indexes = new unsigned[v]{};
    *result_v = 0;
    inrange(i, v) indexes[i] = 0;

    unsigned mx = 0;
    inrange(j, v) {
        if (mx < arr[j]) {
            mx = arr[j];
            *result_v = 0;
            indexes[(*result_v)++] = j;
        }
        else {
            if (mx == arr[j]) {
                indexes[(*result_v)++] = j;
            }
        }
    }
    unsigned *result_indexes = new unsigned[*result_v]{};
    inrange(i, *result_v) result_indexes[i] = indexes[i];
    return result_indexes;
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

    unsigned *counts = calcFile(in);
    protoRead(protocol, counts);

    if (counts[1] < 2) {
        protoE2(protocol, counts[1]);
        delete [] counts;
        return 0;
    }

    double **points = readFile(protocol, in, counts);
    outPoints(out, points, counts[1]);


    // добавить проверки на отсутствие прямых
    unsigned lines_v = 0;
    double **lines = constructLines(protocol, points, counts[1], &lines_v);
    if (!lines_v) {
        protoE2(protocol, lines_v, true);
        delete [] counts;
        delete [] lines;
        return 0;
    }


    unsigned distinct_v = 0;
    double **distinct_lines = findDistinctLines(protocol, lines, lines_v, &distinct_v);
    outLines(out, distinct_lines, distinct_v);
    outLines(protocol, distinct_lines, distinct_v);

    unsigned **lines_points;
    unsigned *line_counts = processLines(
        protocol,
        distinct_lines, distinct_v,
        points, counts[1],
        lines_points
    );

    unsigned max_lines_count = 0;
    unsigned *indexes = processedLinesSort(line_counts, distinct_v, &max_lines_count);

    outResult(out, line_counts, lines_points, indexes, max_lines_count, distinct_lines, points);

    in.close();
    out.close();
    protocol.close();

    inrange(i, counts[1]) {
        delete [] lines[i];
    }
    inrange(i, lines_v) {
        delete [] lines[i];
    }
    inrange(i, distinct_v) {
        delete [] lines_points[i];
    }
    delete [] lines;
    delete [] counts;
    delete [] distinct_lines;
    delete [] lines_points;
    delete [] indexes;
    delete [] line_counts;
    return 0;
}
