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
    std::cout << a.h << ' ' << a.w << std::endl;
    txtPivots b = find_pivots(in);
    b.print(std::cout);

    chunkL chunk;
    resultStates result = resultStates();
    for (int y = 0; y < a.h; ++y) {
        for (int x = 0; x < a.w; ++x)
        {
            std::cout << "Чанк " << x << ':' << y << '\n';
            chunk = read_chunk(in, b, x, y);
            parse_chunk(&result, chunk, ((x == a.w-1) ? true : false), out);
            chunk.print(std::cout, result.get_mid_chunk());
            std::cout << '\n';
        }
        std::cout << "Конец строки\n";
        result.set_mid_chunk(readState());
    }
    return 0;
}
