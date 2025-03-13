#include "chunkL.hpp"
#include "strL.hpp"
#include "files.hpp"

chunkL::chunkL() : textv(NULL), textc(0) {}
chunkL::chunkL(strL* strv, unsigned strc) : textv(new strL[strc]{}), textc(strc)
{
    for (unsigned i = 0; i < strc; ++i) textv[i] = strv[i];
}
chunkL::~chunkL() { if (textv != NULL) delete [] textv; }
chunkL::chunkL(const chunkL& other) : chunkL(other.textv, other.textc) {}
chunkL& chunkL::operator=(const chunkL& other)
{
    chunkL temp(other);
    std::swap(textc, temp.textc);
    std::swap(textv, temp.textv);
    return *this;
}
void chunkL::print(std::ostream& o)
{
    for (unsigned i = 0; i < textc; ++i)
    textv[i].print(o);
}
strL& chunkL::set_str(strL &str, unsigned i)
{
    return textv[i] = str;
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
        .w = max_line / CHUNK_W + (max_line % CHUNK_W ? 1 : 0),
        .h = line_count / CHUNK_H + (line_count % CHUNK_H ? 1 : 0)
    };
}
chunkL read_chunk(std::istream& in, txtPivots pivots, int x, int y)
{
    strL* temp_strs = new strL[CHUNK_H]{};
    chunkL chunk = chunkL(temp_strs, CHUNK_H);
    delete [] temp_strs;

    in.clear();
    for (unsigned i = 0; i < CHUNK_H; ++i)
    {
        int chc = pivots.get_len(y * CHUNK_H + i) - x * CHUNK_W;
        in.seekg(pivots.get_start(y * CHUNK_H + i) + x * CHUNK_W + i + y * CHUNK_H);
        chc = (chc > CHUNK_W) ? CHUNK_W : chc;
        chc = (chc < 0) ? 0 : chc;
        char* temp = new char[chc];
        for (int j = 0; j < chc; ++j) temp[j] = (char)in.get();
        strL str = strL(temp, chc);
        delete [] temp;
        chunk.set_str(str, i);
    }
    return chunk;
}

