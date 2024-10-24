/*
Задание: В массивах хранятся 2 упорядоченных множества F и G соответственно. Сформировать новый массив с множеством H = F ^ G (симметрическая разность)
Ограничения: -10^10 < a(i) < 10^10 с точностью до 30 знаков после запятой.
Автор: Даричев Е.М.
Версия: 4.1.15
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


const float eps = 1.e-30f;

int main() {
    cout << "Задание: В массивах хранятся 2 упорядоченных множества F и G соответственно. "
    "Сформировать новый массив с множеством H = F ^ G (симметрическая разность)" << endl;
    cout << "Ограничения: -10^10 < a(i) < 10^10 с точностью до 30 знаков после запятой." << endl;
    cout << "Автор: Даричев Е.М." << endl;

    fstream fF, fG;
    fstream* cur_file;

    float *F, *G;
    char file_chars[] = "FG";

    float* H;
    unsigned int iH = 0;

    unsigned int i = 0, len, lenF = 0, lenG = 0, iF = 0, iG = 0;

    float** bufs[] = {&F, &G};
    fstream* fs[] = {&fF, &fG};

    char filename[100]{};

    fstream result;
    result.open("result.txt", ios::out);

    if (!result.is_open()) {
        cout << "Не удалось открыть выходной файл." << endl;
        goto EXIT;
    }

    while (i <= 6) {
        cout << "Введите путь к файлу " << (i <= 3 ? 'F' : 'G') << ": ";
        cur_file = &(i <= 3 ? fF : fG);
        for (;;) {
            if (cin.eof()) break;
            cin.getline(filename, 100);
            cur_file->open(filename, ios::in);
            if ((cur_file)->is_open()) {
                i = i <= 3 ? 4 : 7;
                break;
            } else {
                cout << "Не удалось открыть файл " << (i <= 3 ? 'F' : 'G') << "\"" << filename << "\"." << endl;
                cin.clear();
                i++;
                if (i > 3 and !fF.is_open()) {
                    cout << "Превышено количество попыток ввода пути для файла F. " << endl;
                }
                break;
            }
        }
    }
    if (!(fF.is_open() and fG.is_open())) {
        cout << "Превышено количество попыток ввода пути для файла G. " << endl;
        goto EXIT;
    }



    for (i = 0; i < 2; i++) {
        len = 0;
        cout << "Файл " << *(file_chars+i) << ':' << endl;
        result << "Файл " << *(file_chars+i) << ':' << endl;

        while (!(*(fs+i))->eof()) {
            **(fs+i) >> *reinterpret_cast<float*>(*(bufs+i));
            len++;
        }

        (*(fs+i))->seekp(0).clear();
        **(bufs+i) = new float[len];

        while (iF < len) {
            **(fs+i) >> *((**(bufs+i)) + iF++);
        }

        (i == 0 ? lenF : lenG) = iF;
        (*(fs+i))->close();

        cout << "Считан массив (" << iF << " элементов): " << endl << "[";
        result << "Считан массив (" << iF << " элементов): " << endl << "[";
        for (unsigned int m = 0; m < iF; m++) {
            cout << ' ' << *((**(bufs+i))+m);
            result << ' ' << *((**(bufs+i))+m);
        }
        cout << " ]" << endl;
        result << " ]" << endl;

        iF = 0;
    }

    result << "Новый массив H:" << endl;
    H = new float[lenF + lenG];

    while (iF < lenF and iG < lenG) {
        if (abs(*(F+iF) - *(G+iG)) < eps) {
            iF++; iG++;
        } else {
            *(H + iH++) = (*(F+iF) < *(G+iG) ? *(F+iF++) : *(G+iG++));
        }
    }
    while (iF < lenF) {
        *(H + iH++) = *(F+iF++);
    }
    while (iG < lenG) {
        *(H + iH++) = *(G+iG++);
    }

    for (i = 0; i < iH; i++) result << *(H+i) << ' ';

EXIT:
    result.close();
    if (fF.is_open()) fF.close();
    if (fG.is_open()) fG.close();
    cout << endl << "Работа программы завершена" << endl;
    return 0;
}
