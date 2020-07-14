/*********************************************************
 * File: cache.hpp
 * Description: This file contains the implementation of the
 * Cache class as well as functions and methods for the
 * class.
 * 
 * Author: jfhansen
 * Last modification: 12/07/2020
 *********************************************************/

#include "cache.hpp"
#include <math.h>
#include <cstdint>
#include <bit>

Cache::Cache(CacheConfig config) 
    : _block_size(config.get_block_size()), 
    _num_blocks(config.get_cache_size() / config.get_block_size()),
    _num_sets(_num_blocks / config.get_associativity()),
    _associativity(config.get_associativity()), 
    _miss_penalty(config.get_miss_penalty()),
    _dirty_wb_penalty(config.get_writeback_penalty()), 
    _offset_index(std::popcount(_block_size - 1)),
    _index_mask(_num_sets - 1), 
    _tag_offset(std::popcount(_num_sets - 1) + _offset_index)
{
    std::fill_n(std::back_inserter(_sets), _num_sets, 
        CacheSet(config.get_associativity()));
}

uint64_t Cache::get_store_hits() {
    return _store_hits;
}
uint64_t Cache::get_load_hits() {
    return _load_hits;
}
uint64_t Cache::get_store_accesses() {
    return _store_accesses;
}
uint64_t Cache::get_load_accesses() {
    return _load_accesses;
}
uint64_t Cache::get_dirty_evictions() {
    return _dirty_evictions;
}
uint64_t Cache::get_total_evictions() {
    return _total_evictions;
}
const uint32_t Cache::get_miss_penalty() {
    return _miss_penalty;
}
const uint32_t Cache::get_dirty_wb_penalty() {
    return _dirty_wb_penalty;
}

uint32_t Cache::access_cache(uint64_t addr, bool type, uint32_t instrs)
{
    unsigned set;
    unsigned long tag;
    bool dirty_wb, hit;
    // Compute which set access should go to, and memory access tag
    set = (addr >> _offset_index) & _index_mask;
    tag = (addr >> _tag_offset);

    // Access set
    std::tie(dirty_wb, hit) = _sets[set].access_set(tag, type);

    _store_hits += (hit && type);
    _load_hits += (hit && !(type));
    _store_accesses += type;
    _load_accesses += !(type);
    _dirty_evictions += dirty_wb;
    _total_evictions += !(hit);

    return (_miss_penalty * !(hit) + _dirty_wb_penalty * dirty_wb);
}