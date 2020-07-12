/*********************************************************
 * File: cache_config.hpp
 * Description: This file contains the definition of the
 * CacheConfig class as well as methods for configuring
 * the cache. The CacheConfig is passed to the Cache Simulator
 * and is used for setting the performance parameters of the
 * cache.
 * 
 * Author: jfhansen
 * Last modification: 12/07/2020
 *********************************************************/

#ifndef CACHE_CONFIG_HPP
#define CACHE_CONFIG_HPP

#include <string>
#include <iostream>

class CacheConfig
{
    public:
        CacheConfig();
        CacheConfig(std::string filePath);
        ~CacheConfig() = default;

        void set_cache_size(unsigned cacheSize);
        void set_block_size(unsigned blockSize);
        void set_associativity(unsigned setAssociativity);
        void set_miss_penalty(unsigned missPenalty);
        void set_writeback_penalty(unsigned wbPenalty);
        void set_replacement_scheme(std::string scheme);
        void set_write_scheme(std::string scheme);
        void set_write_miss_scheme(std::string scheme);
        void set_trace_file_path(std::string filePath);

        unsigned get_cache_size();
        unsigned get_block_size();
        unsigned get_associativity();
        unsigned get_miss_penalty();
        unsigned get_writeback_penalty();
        std::string get_replacement_scheme();
        std::string get_write_scheme();
        std::string get_write_miss_scheme();
        std::string get_trace_file_path();

    private:
        // Cache size (in bytes).
        // Default: 16 KiB
        unsigned _cache_size = (1 << 14);
        // Block size (in bytes)
        // Default: 64 B
        unsigned _block_size = 64;
        // Set associativity, i.e. number of ways a block can be placed in the cache.
        // Default: 4 ways.
        unsigned _set_associativity = 4;
        // Penalty on cache misses (in cycles)
        // Default: 100 cycles.
        unsigned _miss_penalty = 100;
        // Dirty Writeback Penalty (in cycles)
        // Default: 10 cycles.
        unsigned _dirty_wb_penalty = 10;
        // Block Replacement Scheme (e.g. "LRU")
        // Default: LRU
        std::string _replacement_scheme = "LRU";
        // Find a better way to be able to define Write Scheme (i.e. Write-back, "WB", or write-through, "WT")
        // Default: Write-back
        std::string _write_scheme = "WB";
        // Write miss scheme (e.g. Write-Allocate, "WA", or No-Write-Allocate, "NWA")
        // Default: Write-Allocate.
        std::string _write_miss_scheme = "WA";
        // Trace File Path
        std::string _trace_file_path = NULL;
};

std::ostream& operator<< (std::ostream &os, CacheConfig *cfg);

#endif
