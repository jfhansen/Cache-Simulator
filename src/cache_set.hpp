/*********************************************************
 * File: cache_set.hpp
 * Description: This file contains the definition of the
 * CacheSet class as well as functions and methods for the
 * class. 
 * This class is responsible for handling accesses
 * on the blocks whose cache index fits in the set. It does
 * this by computing whether an access was a hit or miss,
 * as well as checking if a dirty write-back has occured.
 * This class accomplishes these things by keeping track of
 * the tags of the blocks stored in the set, as well as whether
 * block has been modified.
 * 
 * As of last modification, only the true LRU replacement
 * policy has been implemented for replacement of blocks.
 * In the future, random replacement as well as the enhanced
 * LRU replacement algorithm, where clean blocks are removed
 * before dirty blocks.
 * 
 * Author: jfhansen
 * Last modification: 13/07/2020
 *********************************************************/

#ifndef CACHE_SET_HPP
#define CACHE_SET_HPP

#include <vector>
#include <stdint.h>
#include <tuple>

class CacheSet
{
    public:
        CacheSet(uint32_t numWays);
        ~CacheSet() = default;

        // Access CacheSet. Takes block tag and access type as inputs
        // returns tuple <dirty_wb, hit>.
        std::tuple<bool, bool> access_set(uint64_t tag, bool type);

        // Find block in set. Takes block tag as input
        // Returns index of match on hit or last way in set.
        uint32_t search_set(uint64_t tag);

        // Replaces block according to replacement scheme.
        // Returns cache way whose block was replaced.
        uint32_t replace_block(uint64_t tag);

        // Updates dirty bit for block in 'way'. 
        // Returns whether dirty block was replaced.
        bool update_dirty_bit(uint32_t way, bool type, bool hit);

        // Updates priorities for blocks in cache set
        void update_priorities(uint32_t latest_way);

    private:
        // Vector holding the tags of the blocks in the set.
        std::vector<uint64_t> _blocks;
        // Number of ways that are filled in the set
        uint32_t _used_ways = 0;
        // Vector holding Dirty bit of each block in set.
        std::vector<bool> _dirty_bits;
        // Vector holding priority bits, used for choosing block to replace
        // Lower values are better
        std::vector<uint32_t> _priority;
};

#endif