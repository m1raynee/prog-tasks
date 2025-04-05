// Удалить:
// 6) список;
// 7) второй и предпоследний по порядку элементы с заданным значением;

#include "headers/L1.hpp"
#include "headers/strL.hpp"
#include "headers/files.hpp"
#include <fstream>

using std::ifstream, std::ofstream, std::endl;

int main() {
    ifstream in, inq;
    ofstream out;
    in.open("in.txt");
    inq.open("inq.txt");
    out.open("out.txt");

    list l = readfile(in);
    list q = readfile(inq);

    out << "Контрольный вывод:\n";
    l.print(out);
    bar(out);
    q.print(out);
    bar(out);

    if (l.is_empty() or q.is_empty()) return 0;

    int count = l.count_elem(q.first->val);
    std::cout << count; 
    l.begin();
    process(l, q, count);
    out << "Ответ:\n\n";
    l.print(out);
    out << endl;

    l.destroy_list();
    q.destroy_list();

    return 0;
}