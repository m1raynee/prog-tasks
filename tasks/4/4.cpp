/*
Задание: В массивах хранятся 2 упорядоченных множества F и G соответственно. Сформировать новый массив с множеством H = F ^ G (симметрическая разность)
Ограничения: -10^10 < a(i) < 10^10 с точностью до 30 знаков после запятой.
Автор: Егор Даричев (гр. 4352)   Версия: 4.1.15
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


const float eps = 1.e-30f;

const unsigned int BUFFER_SIZE = 200;

int main() {
    cout << "Задание: В массивах хранятся 2 упорядоченных множества F и G соответственно. "
    "Сформировать новый массив с множеством H = F ^ G (симметрическая разность)" << endl;
    cout << "Ограничения: -10^10 < a(i) < 10^10 с точностью до 30 знаков после запятой." << endl;
    cout << "Автор: Егор Даричев (гр. 4352)   Версия: 4.1.15" << endl;

    fstream fF, fG;
    fstream* cur_file;

    float F[BUFFER_SIZE], G[BUFFER_SIZE];
    float* cur_array;
    char file_char = 'F';

    float H[BUFFER_SIZE * 2] = {};

    unsigned int i = 0, len, lenF = 0, lenG = 0, iF = 0, iG = 0, iH = 0;

    fstream result;
    result.open("result.txt", ios::out);
    if (!result.is_open()) {
        cout << "Ошибка, не удалось открыть выходной файл." << endl;
        goto EXIT;
    }

    fF.open("prF", ios::in);
    fG.open("prG", ios::in);

    if (!(fF.is_open() and fG.is_open())) {
        cout << "Ошибка, не удалось открыть один из входных файлов." << endl;
        goto EXIT;
    }

    cur_file = &fF; cur_array = F;
    for (i = 0; i < 2; i++) {
        *cur_file >> cur_array[0];
        cout << "Файл " << file_char << ':' << endl;
        result << "Файл " << file_char << ':' << endl;
        if (cur_file->eof()) {
            cout << "Ошибка, файл закончился." << endl;
            result << "Ошибка, файл закончился." << endl;
            goto EXIT;
        } else {
            len = unsigned(cur_array[0]);
            if ((abs(float(len) - cur_array[0]) >= eps) or (cur_array[0] < 0.f)) {
                cout << "Ошибка, заявленное число элементов не может быть отрицательным или нецелым." << endl;
                result << "Ошибка, заявленное число элементов не может быть отрицательным или нецелым." << endl;
                goto EXIT;
            }
        }

        while (iF < len and iF < BUFFER_SIZE) {
            if (cur_file->eof()) {
                iF--;
                break;
            }
            *cur_file >> cur_array[iF++];
        }

        (cur_file == &fF ? lenF : lenG) = iF;
        cur_file->close();

        cout << "Считан массив (" << iF << " элементов, заявлено " << len << "): " << endl << "[";
        result << "Считан массив (" << iF << " элементов, заявлено " << len << "): " << endl << "[";
        for (unsigned int m = 0; m < iF; m++) {
            cout << ' ' << cur_array[m];
            result << ' ' << cur_array[m];
        }
        cout << " ]" << endl;
        result << " ]" << endl;

        iF = 0;
        cur_file = &fG; cur_array = G; file_char = 'G';
    }


    while (iF < lenF and iG < lenG) {
        if (abs(F[iF] - G[iG]) < eps) {
            iF++; iG++;
        } else if (F[iF] < G[iG]) {
            H[iH++] = F[iF++];
        } else {
            H[iH++] = G[iG++];
        }
    }
    while (iF < lenF) {
        H[iH++] = F[iF++];
    }
    while (iG < lenG) {
        H[iH++] = G[iG++];
    }

    result << "Новый массив H (" << iH << " элементов):" << endl;
    for (i = 0; i < iH; i++) result << H[i] << ' ';

EXIT:
    result.close();
    if (fF.is_open()) fF.close();
    if (fG.is_open()) fG.close();
    return 0;
}
