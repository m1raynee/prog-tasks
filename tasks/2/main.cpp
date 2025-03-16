#include "modules/files.hpp"
#include "modules/chunkL.hpp"
#include "modules/readState.hpp"
#include <fstream>

int main()
{
    std::ifstream in;
    std::ofstream out;
    in.open("in.txt");
    out.open("out.txt");
    in >> std::noskipws;

    chunk_count a = count_chunks(in);
    txtPivots pivots = find_pivots(in);
    pivots.print(out);

    chunkL chunk;
    readState mid_chunk;
    resultStates result = resultStates();
    for (int y = 0; y < a.h; ++y) {
        for (int x = 0; x < a.w; ++x)
        {
            chunk = read_chunk(out, in, pivots, x, y);
            parse_chunk(out, in, &result, chunk);
            out << '\n';
        }
        out << "Конец строки\n";
        result.set_mid_chunk(readState());
    }
    return 0;
}
