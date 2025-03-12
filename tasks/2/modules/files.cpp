#include "files.hpp"
#include <iomanip>

txtPivots::txtPivots() : starts(NULL), ends(NULL), textc(0) {}
txtPivots::txtPivots(int* st, int* en, unsigned strc)
    : starts(new int[strc]{}), ends(new int[strc]{}), textc(strc)
{
    for (unsigned i = 0; i < strc; ++i) { starts[i] = st[i]; ends[i] = en[i]; }
}
txtPivots::~txtPivots()
{
    if (starts != NULL) delete [] starts;
    if (ends != NULL) delete [] ends;
}
txtPivots::txtPivots(const txtPivots& other) : txtPivots(other.starts, other.ends, other.textc) {}
txtPivots& txtPivots::operator=(const txtPivots& other)
{
    txtPivots temp(other);
    std::swap(textc, temp.textc);
    std::swap(starts, temp.starts);
    std::swap(ends, temp.ends);
    return *this;
}
void txtPivots::print(std::ostream& o)
{
    o << "Text pivots:\n";
    o << "starts   ends\n";
    for (unsigned i = 0; i < textc; ++i)
    {
        o << std::setw(6) << starts[i] << std::setw(6) << ends[i] << '\n';
    }
    o << std::endl;
}

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

chunk_count count_chunks(std::istream& in)
{
    std::streamoff pos = in.tellg();
    int ch;
    unsigned line_count = count_lines(in);

    unsigned curr_line = 0, max_line = 0;

    while ((ch = in.get()) and ch != -1)
    {
        if (ch == '\n')
        {
            if (curr_line > max_line) max_line = curr_line;
            curr_line = 0;
        }
        ++curr_line;
    }
    in.clear();
    in.seekg(pos, in.beg);

    return chunk_count{
        .w_count = max_line / CHUNK_W + (max_line % CHUNK_W ? 1 : 0),
        .h_count = line_count / CHUNK_H + (line_count % CHUNK_H ? 1 : 0)
    };
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
        if (ch != '\n' and ch != -1)
        {
            if (make_start) { starts[curr_i] = curr_pos; make_start = false; }
        }
        else
        {
            if (make_start) starts[curr_i] = curr_pos - 1;
            else make_start = true;
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
