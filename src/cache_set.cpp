/*********************************************************
 * File: cache_set.cpp
 * Description: This file contains the implementation of the
 * CacheSet class as well as functions and methods for the
 * class.
 * 
 * Author: jfhansen
 * Last modification: 13/07/2020
 *********************************************************/

#include "cache_set.hpp"
#include <algorithm>

CacheSet::CacheSet(uint32_t numWays)
{
    _blocks.resize(numWays);
    _dirty_bits.resize(numWays);
    _priority.resize(numWays, 0);
}

std::tuple<bool, bool> CacheSet::access_set(uint64_t tag, bool type)
{
    // Search through set to see whether tag matches any of blocks in set.
    std::vector<uint64_t>::iterator match = std::find(_blocks.begin(), _blocks.end(), tag);
    //unsigned index = search_set(tag);
    // Check whether access is a hit or miss.
    bool hit = match != _blocks.end();

    unsigned latest_way;
    // Compute which way was just accessed.
    if (!hit) {
        // If miss, the way whose block was just replaced.
        latest_way = replace_block(tag);
    } else {
        // If hit, the way that contains the accessed block.
        latest_way = std::distance(_blocks.begin(), match);
    }
    // Update the dirty state of the way that was just accessed
    // and check if dirty eviction happened
    bool dirty_evic = update_dirty_bit(latest_way, type, hit);

    // Update priorities of blocks in set.
    update_priorities(latest_way);

    return std::make_tuple(dirty_evic, hit);
}

uint32_t CacheSet::replace_block(uint64_t tag)
{
    // Check if all ways in set are used
    if (_used_ways < _blocks.size())
    {
        _blocks[_used_ways] = tag;
        _used_ways++;
        return _used_ways - 1;
    }
    // Find maximum element in priority vector
    std::vector<uint32_t>::iterator it;
    it = std::max_element(_priority.begin(), _priority.end());

    // Find index of maximum element
    unsigned index = std::distance(_priority.begin(), it);

    // Replace block at index
    _blocks[index] = tag;

    // Return way of block that was replaced
    return index;
}

bool CacheSet::update_dirty_bit(uint32_t way, bool type, bool hit)
{
    // Dirty write-backs occur on misses, when the replaced way is modified.
    bool dirty_wb = !(hit) && _dirty_bits[way];
    // The dirty bit must be set on all stores, or if the block is already
    // dirty and a hit occurs.
    _dirty_bits[way] = type || (hit && _dirty_bits[way]);
    return dirty_wb;
}

void CacheSet::update_priorities(uint32_t latest_way)
{
    std::vector<uint32_t>::iterator it;
    // Increment priority of all blocks in set.
    for (it = _priority.begin(); it != _priority.end(); it++)
        (*it)++;
    // Reset priority of block that was most recently used.
    _priority[latest_way] = 0;
}

uint32_t CacheSet::search_set(uint64_t tag)
{
    unsigned index;
    for (index = 0; index < _blocks.size(); index++)
    {
        if (_blocks[index] == tag)
            break;
    }
    return index;
}
