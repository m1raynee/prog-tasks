#include "modules/chunkL.hpp"
#include <fstream>

int main()
{
    chunkL chunk;
    readState mid_chunk;
    std::ifstream in;
    std::ofstream out;
    in.open("in.txt");
    out.open("out.txt");
    in >> std::noskipws;
    resultStates result = resultStates();

    chunk_count counts = count_chunks(in);
    txtPivots pivots = find_pivots(in);
    pivots.print(out);

    for (int y = 0; y < counts.h; ++y) {
        for (int x = 0; x < counts.w; ++x)
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
