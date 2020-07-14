#include <iostream>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <tuple>
#include <vector>
#include <cstring>
#include <chrono>
#include <math.h>

#include "cache_config.hpp"

void print_usage()
{
    std::cout << "Usage: ./driver -i <tracefile> [OPTIONS]" << std::endl;
    std::cout << "\t-i <tracefile>\t:\tPath to trace file." << std::endl;
    std::cout << "\t-a assoctvty\t:\tCache set associativity." << std::endl;
    std::cout << "\t-l blocksize\t:\tSize of cache blocks in bytes." << std::endl;
    std::cout << "\t-s cachesize\t:\tCache size in KiB." << std::endl;
    std::cout << "\t-mp misspen\t:\tMiss penalty in cycles." << std::endl;
    std::cout << "\t-dp dirtypen\t:\tDirty write-back penalty in cycles." << std::endl;
    std::cout << "\t-r replace\t:\tReplacement scheme, e.g. 'LRU'." << std::endl;
    std::cout << "\t-w writeschem\t:\tWrite Scheme, e.g. 'WB' for Write-Back." << std::endl;
    std::cout << "\t-m misschem\t:\tWrite Miss Scheme, e.g. 'WA' for Write-Allocate." << std::endl;
    std::cout << "\t-c <cachecfg>\t:\tPath to Cache Config file. The Cache config file is just" << std::endl;
    std::cout << "\t\t\t\ta file containing the same option flags as defined here." << std::endl;
}

CacheConfig* parse_cli_args( int argc, std::vector<std::string> argv)
{
    size_t i = 0;
    CacheConfig *ccfg = new CacheConfig("");

    while (i < argc)
    {
        if (argv[i] == "-i") {
            i++;
            ccfg->set_trace_file_path(argv[i]);
            i++;
        } else if (argv[i] == "-a") {
            i++;
            ccfg->set_associativity(std::stoi(argv[i]));
            i++;
        } else if (argv[i] == "-l") {
            i++;
            ccfg->set_block_size(std::stoi(argv[i]));
            i++;
        } else if (argv[i] == "-s") {
            i++;
            ccfg->set_cache_size(1 << ( 10 + int( std::log2( std::stoi( argv[i] ) ) ) ) );
            i++;
        } else if (argv[i] == "-mp") {
            i++;
            ccfg->set_miss_penalty(std::stoi(argv[i]));
            i++;
        } else if (argv[i] == "-dp") {
            i++;
            ccfg->set_writeback_penalty(std::stoi(argv[i]));
            i++;
        } else if (argv[i] == "-r") {
            i++;
            ccfg->set_replacement_scheme(argv[i]);
            i++;
        } else if (argv[i] == "-w") {
            i++;
            ccfg->set_write_scheme(argv[i]);
            i++;
        } else if (argv[i] == "-m") {
            i++;
            ccfg->set_write_miss_scheme(argv[i]);
            i++;
        } else {
            print_usage();
            exit(0);
        }
    }
    return ccfg;
}

std::tuple<int, std::vector<std::string>> parse_config_file(std::string filePath)
{
    int count = 0;
    std::vector<std::string> vector;
    std::ifstream file(filePath);
    std::string line;
    if (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word)
        {
            if (word != "\0")
            {
                count++;
                vector.push_back(word);
            }
        }
    }
    return std::make_tuple(count, vector);
}

int main( int argc, char *argv[] )
{
    auto t1 = std::chrono::high_resolution_clock::now();
    assert(argc > 1);
    CacheConfig *config;
    if (std::strcmp(argv[1],"-c") == 0)
    {
        int count;
        std::vector<std::string> v;
        std::tie(count, v) = parse_config_file(argv[2]);
        config = parse_cli_args(count, v);
    }
    else 
    {
        std::vector<std::string> args(argv + 1, argv + argc);
        config = parse_cli_args(argc-1, args);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    std::cout << "Execution time: " << dur << " µs." << std::endl;
    std::cout << config;
    return 0;
}