#include "modules/files.hpp"
#include "modules/chunkL.hpp"
#include <fstream>

int main()
{
    std::ifstream in;
    in.open("in.txt");
    chunk_count a = count_chunks(in);
    std::cout << a.h << ' ' << a.w << std::endl;
    txtPivots b = find_pivots(in);
    b.print(std::cout);
    chunkL chunk = read_chunk(in, b, 0, 2);
    chunk.print(std::cout);
    return 0;
}
