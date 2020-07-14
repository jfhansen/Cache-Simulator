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
#include "cache_set.hpp"

class Cache
{
    public:
        // Constructor. Takes CacheConfig object as argument.
        Cache(CacheConfig config);
        // Destructor
        ~Cache() = default;

        // Performs cache access, finds relevant set in cache and checks
        // whether access was hit or miss. Returns number of cycles
        // memory stalls after access. For hit it returns 0, for miss
        // it returns miss_penalty (+ dirty_wb_penalty if relevant)
        uint32_t access_cache(uint64_t addr, bool type, uint32_t instrs);

        uint64_t get_store_hits();
        uint64_t get_load_hits();
        uint64_t get_store_accesses();
        uint64_t get_load_accesses();
        uint64_t get_dirty_evictions();
        uint64_t get_total_evictions();
        const uint32_t get_miss_penalty();
        const uint32_t get_dirty_wb_penalty();

    private:
        // Vector of Cache Sets (i.e. the ways that a block can be placed in).
        std::vector<CacheSet> _sets;

        // Block size (in bytes).
        const uint32_t _block_size;
        // Number of blocks in Cache
        const uint64_t _num_blocks;
        // Number of sets in Cache
        const uint64_t _num_sets;
        // Cache Set Associativity.
        const uint64_t _associativity;
        // Miss Penalty (in cycles).
        const uint32_t _miss_penalty;
        // Dirty Write-back penalty (in cycles).
        const uint32_t _dirty_wb_penalty;
        // Offset until Cache Index (i.e. width of in-block byte offset in bits)
        const uint32_t _offset_index;
        // Cache Index mask
        const uint64_t _index_mask;
        // Tag Width (in bits)
        const uint64_t _tag_offset;

        // Number of hits on store accesses.
        uint64_t _store_hits = 0;
        // Number of hits on load accesses.
        uint64_t _load_hits = 0;
        // Number of total store accesses.
        uint64_t _store_accesses = 0;
        // Number of total load accesses.
        uint64_t _load_accesses = 0;
        // Number of dirty evictions, i.e. number of replaced dirty blocks.
        uint64_t _dirty_evictions = 0;
        // Total number of evictions.
        uint64_t _total_evictions = 0;
};

#endif