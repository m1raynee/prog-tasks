#include "../headers/files.hpp"

list readfile(istream& in) {
    list res = list();
    res.init_list();

    int ch = 0;
    char *line;
    in.clear(); in.seekg(0);
    while (!in.eof() and ch != -1) {
        int line_length = 0;
        while ((ch = in.get()) and ch != '\n' and ch != -1) ++line_length;
        if (line_length) {
            int offset = -line_length-1;

            if (in.eof()) {
                in.clear();
                ++offset;
            }

            in.seekg(offset, in.cur);
            line = new char[line_length];
            for (int i = 0; i < line_length; ++i) line[i] = (char)in.get();
            while ((ch = in.get()) and ch != '\n' and ch != -1);
        }
        else line = new char[1]{""};
        res.push_back(strL().init(line, line_length));
    }

    return res;
}
void bar(ostream& out) {
    for (int i = 0; i < 20; ++i) out << '_';
    out << "\n\n";
}