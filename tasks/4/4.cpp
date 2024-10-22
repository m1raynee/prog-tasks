#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


const float eps = 1.e-30f;

const unsigned BUFFER_SIZE = 200;

int main() {
    fstream fF, fG;
    fstream* cur_file;

    float bufferF[BUFFER_SIZE], bufferG[BUFFER_SIZE];
    float* cur_buff;
    char file_char = 'F';

    unsigned int i = 0, len, lenF = 0, lenG = 0, iF = 0, iG = 0;

    char filename[100];
    char* start;

    fstream f;
    f.open("result.txt", ios::out);

    if (!f.is_open()) {
        cout << "Не удалось открыть выходной файл." << endl;
        goto EXIT;
    }

    while (i <= 6) {
        cout << "Введите путь к файлу " << (i <= 3 ? 'F' : 'G') << ": ";
        cur_file = &(i <= 3 ? fF : fG);
        for (;;) {
            cin.getline(filename, 100);
            for (start = filename; *start and *start == ' '; start++);
            len = 0;
            if (*start) {
                while (start[len] and start[len] != ' ') len++;
                start[len] = '\0';
            }
            if (len) {
                cur_file->open(start, ios::in);
                if ((cur_file)->is_open()) {
                    i = i <= 3 ? 4 : 7;
                    break;
                } else {
                    cout << "Не удалось открыть файл " << (i <= 3 ? 'F' : 'G') << "\"" << start << "\"." << endl;
                    cin.clear();
                    ++i;
                    if (i > 3 and !fF.is_open()) {
                        cout << "Превышено количество попыток ввода пути для файла F. " << endl;
                    }
                    break;
                }
            } else if (cin.eof()) break;
        }
    }
    if (!(fF.is_open() and fG.is_open())) {
        cout << "Превышено количество попыток ввода пути для файла G. " << endl;
        return 0;
    }

    cur_file = &fF; cur_buff = bufferF;
    for (i = 0; i < 2; i++) {
        *cur_file >> cur_buff[0];
        cout << "Файл " << file_char << ':' << endl;
        f << "Файл " << file_char << ':' << endl;
        if (cur_file->eof()) {
            len = 0;
            cout << "Ошибка, отсутствует заявление о числе элементов" << endl;
            f << "Ошибка, отсутствует заявление о числе элементов" << endl;
        } else {
            len = unsigned(cur_buff[0]);
            if ((abs(float(len) - cur_buff[0]) >= eps) or (cur_buff[0] < 0.f)) {
                cout << "Заявленное число элементов не может быть отрицательным или нецелым." << endl;
                f << "Заявленное число элементов не может быть отрицательным или нецелым." << endl;
                len = 0;
            }
        }

        while (iF < len and iF < BUFFER_SIZE) {
            if (cur_file->eof()) {
                cout << "Считано " << iF << " значений элементов, что меньше заявленного их числа." << endl;
                f << "Считано " << iF << " значений элементов, что меньше заявленного их числа." << endl;
                break;
            }
            *cur_file >> cur_buff[iF++];
        }
        if (len > BUFFER_SIZE and iF == BUFFER_SIZE) {
            cout << "Считаны первые " << BUFFER_SIZE << " значений." << endl;
            f << "Считаны первые " << BUFFER_SIZE << " значений." << endl;
        }

        (cur_file == &fF ? lenF : lenG) = iF;
        cur_file->close();

        cout << "Считан массив (" << iF << " элементов): " << endl << "[";
        f << "Считан массив (" << iF << " элементов): " << endl << "[";
        for (unsigned int m = 0; m < len; m++) {
            cout << ' ' << cur_buff[m];
            f << ' ' << cur_buff[m];
        }
        cout << " ]" << endl;
        f << " ]" << endl;

        iF = 0;
        cur_file = &fG; cur_buff = bufferG; file_char = 'G';
    }

    f << "Новый массив H:" << endl;

    while (iF < lenF and iG < lenG) {
        if (abs(bufferF[iF] - bufferG[iG]) < eps) {
            iF++; iG++;
        } else if (bufferF[iF] < bufferG[iG]) {
            f << bufferF[iF] << ' ';
            iF++;
        } else {
            f << bufferG[iG] << ' ';
            iG++;
        }
    }
    while (iF < lenF) {
        f << bufferF[iF] << ' ';
        iF++;
    }
    while (iG < lenG) {
        f << bufferG[iG] << ' ';
        iG++;
    }

EXIT:
    f.close();
    if (fF.is_open()) fF.close();
    if (fG.is_open()) fG.close();
    return 0;
}
