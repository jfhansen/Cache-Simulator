#include <iostream>
#include <assert.h>
#include <sstream>
#include <string>
#include <chrono>

#include "cache_set.hpp"
#include "access.hpp"

#define OFFS_BITS 6


int main( int argc, char *argv[] )
{
    // Assert that batch size (arg 2) and trace file path (arg 3) have been passed.
    assert(argc == 3);
    // Fetch CLI arguments 
    unsigned batchSize = std::strtol(argv[1], nullptr, 10);
    std::string filePath = argv[2];

    CacheAccess *ca = new CacheAccess(batchSize, filePath);
    CacheSet *cs = new CacheSet(8);

    auto t1 = std::chrono::high_resolution_clock::now();
    ca->fetch_batch();
    unsigned long addr, tag;
    bool type, dirty_wb, hit;
    unsigned instrs, no_hits = 0;
    std::cout << "acc no.\t:\ttag\ttype\thit\tdwb\t" << std::endl;
    for (size_t i = 0; i < batchSize; i++)
    {
        std::tie(addr, type, instrs) = ca->get_access();
        tag = addr >> OFFS_BITS;
        std::tie(dirty_wb, hit) = cs->access_set(tag, type);
        if (hit) ++no_hits;
        std::cout << "acc " << i << "\t:\t" << std::hex << tag << "\t" << type << "\t" << hit << "\t" << dirty_wb << "\t" << std::endl;
    }
    std::cout << "Number of hits: " << std::dec << no_hits << "/" << batchSize << std::endl;
    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    std::cout << "Execution Time: " << dur << "µs." << std::endl;
    return 0;
}