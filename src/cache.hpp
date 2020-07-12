/*********************************************************
 * File: cache.hpp
 * Description: This file contains the definition of the
 * Cache class as well as functions and methods for the
 * class.
 * 
 * Author: jfhansen
 * Last modification: 12/07/2020
 *********************************************************/

#ifndef CACHE_HPP
#define CACHE_HPP

#include <vector>

#include "cache_config.hpp"

class Cache
{
    public:
        // Constructor. Takes CacheConfig object as argument.
        Cache(CacheConfig config);
        // Destructor
        ~Cache() = default;

    private:
        // Vector of Cache Sets (i.e. the ways that a block can be placed in).
        // std::vector<CacheSet> _sets;

        // Block size (in bytes).
        const uint32_t _block_size;
        // Number of blocks in Cache
        const uint64_t _num_blocks;
        // Cache Set Associativity.
        const uint64_t _associativity;
        // Miss Penalty (in cycles).
        const uint32_t _miss_penalty;
        // Dirty Write-back penalty (in cycles).
        const uint32_t _dirty_wb_penalty;
        // Offset until Cache Index (i.e. width of in-block byte offset in bits)
        const uint32_t _offset_index;
        // Cache Index Width (in bits)
        const uint32_t _index_width;
        // Tag Width (in bits)
        const uint32_t _tag_width;

        // Number of hits on store accesses.
        uint64_t _store_hits;
        // Number of hits on load accesses.
        uint64_t _load_hits;
        // Number of total store accesses.
        uint64_t _store_accesses;
        // Number of total load accesses.
        uint64_t _load_accesses;
        // Number of dirty evictions, i.e. number of replaced dirty blocks.
        uint64_t _dirty_evictions;
        // Total number of evictions.
        uint64_t _total_evictions;
        // Number of instructions.
        uint64_t _instructions;
};

#endif