#include "chunkL.hpp"

chunkL::chunkL() : lines(NULL), lines_c(0) {}
chunkL::chunkL(strL* strv, unsigned strc) : lines(new strL[strc]{}), lines_c(strc)
{
    for (unsigned i = 0; i < strc; ++i) lines[i] = strv[i];
}
chunkL::~chunkL() { if (lines != NULL) delete [] lines; }
chunkL::chunkL(const chunkL& other) : chunkL(other.lines, other.lines_c) {}
chunkL& chunkL::operator=(const chunkL& other)
{
    chunkL temp(other);
    std::swap(lines_c, temp.lines_c);
    std::swap(lines, temp.lines);
    return *this;
}
void chunkL::print(std::ostream& o)
{
    for (unsigned i = 0; i < lines_c; ++i)
    {
        lines[i].print(o);
        o << '\n';
    }

}
void chunkL::print(std::ostream& o, readState state)
{
    for (unsigned i = 0; i < lines_c; ++i)
    {
        lines[i].print(o);
        state.l[i].print(o, false);
        o << '\n';
    }
}
strL& chunkL::set_str(strL &str, unsigned i) { return lines[i] = str; }
strL& chunkL::get_str(unsigned i) { return lines[i]; }
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
chunkL read_chunk(std::ostream& log, std::istream& in, txtPivots pivots, int x, int y)
{
    strL* temp_strs = new strL[CHUNK_H]{};
    chunkL chunk = chunkL(temp_strs, CHUNK_H);
    delete [] temp_strs;

    in.clear();
    for (unsigned i = 0; i < CHUNK_H; ++i)
    {
        int chars_c = pivots.get_len(y * CHUNK_H + i) - x * CHUNK_W;
        int offset = pivots.get_start(y * CHUNK_H + i) + x * CHUNK_W + i + y * CHUNK_H;
        if (offset-i-y*CHUNK_H > pivots.get_end(pivots.get_c()-1)) chars_c = 0;
        in.seekg(offset);
        chars_c = (chars_c > CHUNK_W) ? CHUNK_W : chars_c;
        chars_c = (chars_c < 0) ? 0 : chars_c;
        char* temp = new char[chars_c]{};
        for (int j = 0; j < chars_c; ++j) temp[j] = (char)in.get();
        strL str = strL(temp, chars_c, offset);
        delete [] temp;
        chunk.set_str(str, i);
    }
    log << "Блок " << x << ':' << y << " считан\n";
    return chunk;
}

bool is_valid_name_char(char ch)
{
    return ((ch >= 'A') and (ch <= 'Z'))
        or ((ch >= 'a') and (ch <= 'z'))
        // or ((ch >= '0') and (ch <= '9'))
        or (ch == '_');
}

// Просчитывает чанк
void parse_chunk(std::ostream& log, std::istream& in, resultStates* res_ptr, chunkL chunk)
{
    readState mid_chunk = res_ptr->get_mid_chunk();
    lineState* line_state = mid_chunk.l;  // ++ at the end of loop
    for (unsigned i = 0; i < CHUNK_H; ++i)
    {
        strL line = chunk.get_str(i);
        line.print(log);

        for (unsigned j = 0; j < line.get_char_c(); ++j)
        {
            int pos = line.get_offset() + j;
            char curr_ch = line.get_char(j);
            switch (line_state->state)
            {
            case nothing:
                if (is_valid_name_char(curr_ch))
                {
                    line_state->state = name;
                    line_state->name_start = pos;
                }
                break;
            case name:
                if (!is_valid_name_char(curr_ch))
                {
                    if (line_state->name_end == -1) line_state->name_end = pos;
                    if (curr_ch == '[')
                    {
                        line_state->opened_bracket = pos;
                        line_state->state = open_bracket;
                    }
                    else {
                        (*line_state) = lineState();
                        line_state->state = name;
                        line_state->name_start = pos;
                    }
                }
                break;
            case open_bracket:
                if (curr_ch == ']')
                {
                    line_state->closed_bracket = pos;
                    line_state->state = close_bracket;
                }
                break;
            case close_bracket:
                if (curr_ch == '[') line_state->state = second_brackets;
                if (curr_ch == '=' or curr_ch == '{' or curr_ch == ';')
                {
                    (*res_ptr).append_state(*line_state, log, in);
                    (*line_state) = lineState();
                }
                break;
            case second_brackets:
                if (curr_ch == ']') line_state->closed_bracket = pos;
                if (curr_ch == '=' or curr_ch == '{' or curr_ch == ';')
                {
                    (*res_ptr).append_state(*line_state, log, in);
                    (*line_state) = lineState();
                }
                break;
            default:
                break;
            }
        }
        line_state++; log << '\n';
    }
    res_ptr->set_mid_chunk(mid_chunk);
}
