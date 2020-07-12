/*********************************************************
 * File: cache_config.hpp
 * Description: This file contains the implementation of the
 * CacheConfig class as well as methods for configuring
 * the cache. The CacheConfig is passed to the Cache Simulator
 * and is used for setting the performance parameters of the
 * cache.
 * 
 * Author: jfhansen
 * Last modification: 12/07/2020
 *********************************************************/

#include "cache_config.hpp"
#include "assert.h"

CacheConfig::CacheConfig() {}

CacheConfig::CacheConfig(std::string filePath) : _trace_file_path(filePath) {}

void CacheConfig::set_cache_size(unsigned cacheSize)
{
    _cache_size = cacheSize;
}
void CacheConfig::set_block_size(unsigned blockSize)
{
    _block_size = blockSize;
}
void CacheConfig::set_associativity(unsigned setAssociativity)
{
    _set_associativity = setAssociativity;
}
void CacheConfig::set_miss_penalty(unsigned missPenalty)
{
    _miss_penalty = missPenalty;
}
void CacheConfig::set_writeback_penalty(unsigned wbPenalty)
{
    _dirty_wb_penalty = wbPenalty;
}
void CacheConfig::set_replacement_scheme(std::string scheme)
{
    // Assert that input is valid
    assert(scheme == "LRU" || scheme == "Random");
    _replacement_scheme = scheme;
}
void CacheConfig::set_write_scheme(std::string scheme)
{
    // Assert that input is valid
    assert(scheme == "WB" || scheme == "WT");
    _write_scheme = scheme;
}
void CacheConfig::set_write_miss_scheme(std::string scheme)
{
    // Assert that input is valid
    assert(scheme == "WA" || scheme == "NWA");
    _write_miss_scheme = scheme;
}
void CacheConfig::set_trace_file_path(std::string filePath)
{
    _trace_file_path = filePath;
}

unsigned CacheConfig::get_cache_size()
{
    return _cache_size;
}
unsigned CacheConfig::get_block_size()
{
    return _block_size;
}
unsigned CacheConfig::get_associativity()
{
    return _set_associativity;
}
unsigned CacheConfig::get_miss_penalty()
{
    return _miss_penalty;
}
unsigned CacheConfig::get_writeback_penalty()
{
    return _dirty_wb_penalty;
}
std::string CacheConfig::get_replacement_scheme()
{
    return _replacement_scheme;
}
std::string CacheConfig::get_write_scheme()
{
    return _write_scheme;
}
std::string CacheConfig::get_write_miss_scheme()
{
    return _write_miss_scheme;
}
std::string CacheConfig::get_trace_file_path()
{
    return _trace_file_path;
}

std::ostream& operator<<(std::ostream& os, CacheConfig *cfg)
{
    os << "Cache size: " << cfg->get_cache_size() << " KiB." << std::endl;
    os << "Block size: " << cfg->get_block_size() << " B." << std::endl;
    os << "Set associativity: " << cfg->get_associativity() << " ways." << std::endl;
    os << "Miss penalty: " << cfg->get_miss_penalty() << " cycles." << std::endl;
    os << "Dirty Write-back Penalty: " << cfg->get_writeback_penalty() << " cycles." << std::endl;
    os << "Replacement Scheme: " << cfg->get_replacement_scheme() << "." << std::endl;
    os << "Write Scheme: " << cfg->get_write_scheme() << "." << std::endl;
    os << "Write-Miss Scheme: " << cfg->get_write_miss_scheme() << "." << std::endl;
    os << "Trace-file path: " << cfg->get_trace_file_path() << std::endl;
    return os;
}