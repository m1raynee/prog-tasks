#include "file.hpp"
#include "abstracts.hpp"
#include <fstream>

int main() {
    std::ifstream in1, in2;
    std::ofstream out;
    in1.open("in.txt");
    in2.open("in copy.txt");
    out.open("out.txt");

    strings l1 = readfile(in1);
    strings l2 = readfile(in2);

    out << "l1 (исходный список, in.txt)\n\n";
    l1.print(out);
    bar(out);

    out << "l2 (сгруппировать, перевернуть, "
    << "вставить в конец l1, in copy.txt)\n\n";
    l2.print(out);
    bar(out);

    process(&l1, &l2);

    out << "l1 (результирующий список)\n\n";
    l1.print(out);
    l1.destroy();
    return 0;
}