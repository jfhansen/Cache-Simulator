#include <iostream>
#include <assert.h>
#include <sstream>

#include "access.hpp"


int main( int argc, char *argv[] )
{
    // Assert that batch size and file path has been passed as variables.
    assert(argc == 3);

    unsigned batchSize = std::strtol(argv[1], nullptr, 10);
    std::string filePath = argv[2];
    CacheAccess ca(batchSize, filePath);

    unsigned accesses = ca.fetch_batch();

    uint64_t address;
    bool type;
    unsigned instrs;
    
    for (size_t i = 0; i < accesses; i++)
    {
        // Get memory address, type of access and #instructions for access.
        std::tie(address, type, instrs) = ca.get_access();

        std::string type_str = type ? "Store" : "Load";
        std::cout << "Access " << i << std::endl;
        std::cout << "Type of access: " << type_str << std::endl;
        std::cout << "Memory Address accessed: " << std::hex << address << std::endl;
        std::cout << "Number of instrs between consecutive accesses: " << instrs << std::endl;
    }

    return 0;
}