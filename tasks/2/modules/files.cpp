#include "files.hpp"
#include <iomanip>

txtPivots::txtPivots() : starts(NULL), ends(NULL), pivots_c(0) {}
txtPivots::txtPivots(int* st, int* en, unsigned strc)
    : starts(new int[strc]{}), ends(new int[strc]{}), pivots_c(strc)
{
    for (unsigned i = 0; i < strc; ++i) { starts[i] = st[i]; ends[i] = en[i]; }
}
txtPivots::~txtPivots()
{
    if (starts != NULL) delete [] starts;
    if (ends != NULL) delete [] ends;
}
txtPivots::txtPivots(const txtPivots& other) : txtPivots(other.starts, other.ends, other.pivots_c) {}
txtPivots& txtPivots::operator=(const txtPivots& other)
{
    txtPivots temp(other);
    std::swap(pivots_c, temp.pivots_c);
    std::swap(starts, temp.starts);
    std::swap(ends, temp.ends);
    return *this;
}
void txtPivots::print(std::ostream& o)
{
    o << "Text pivots:\n";
    o << "starts   ends\n";
    for (unsigned i = 0; i < pivots_c; ++i)
    {
        o << std::setw(6) << starts[i] << std::setw(6) << ends[i] << '\n';
    }
    o << std::endl;
}
int txtPivots::get_start(unsigned i) { return starts[i]; }
int txtPivots::get_end(unsigned i) { return ends[i]; }
int txtPivots::get_len(unsigned i) { return ends[i] - starts[i]; }
unsigned txtPivots::get_c() { return pivots_c; }

unsigned count_lines(std::istream& in)
{
    std::streamoff pos = in.tellg();
    in.clear();
    in.seekg(0);
    int ch;
    unsigned line_count = 1;
    while ((ch = in.get()) and ch != -1) if (ch == '\n') ++line_count;
    in.clear();
    in.seekg(pos);
    return line_count;
}

txtPivots find_pivots(std::istream& in)
{
    int ch;

    std::streamoff pos = in.tellg();
    in.clear();
    in.seekg(0);
    unsigned line_count = count_lines(in);

    int* starts = new int[line_count]{};
    int* ends = new int[line_count]{};

    unsigned curr_i = 0;
    int curr_pos = 0;
    bool make_start = true;
    while ((ch = in.get()))
    {
        if (make_start) { starts[curr_i] = curr_pos; make_start = false; }
        if (ch == '\n' or ch == -1)
        {
            make_start = true;
            ends[curr_i++] = (int)curr_pos;
            if (ch == -1) break;
        }
        curr_pos++;
    }
    txtPivots res = txtPivots(starts, ends, line_count);
    delete [] starts;
    delete [] ends;

    in.clear();
    in.seekg(pos);
    return res;
}
