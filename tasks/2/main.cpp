#include "modules/files.hpp"
#include <fstream>

int main()
{
    std::ifstream in;
    in.open("in.txt");
    chunk_count a = count_chunks(in);
    std::cout << a.h_count << ' ' << a.w_count << std::endl;
    txtPivots b = find_pivots(in);
    b.print(std::cout);
    return 0;
}
