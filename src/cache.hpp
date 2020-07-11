/*********************************************************
 * File: cache.hpp
 * Description: This file includes the definition of the
 * cache class as well as functions and methods for the
 * class.
 *********************************************************/

#ifndef CACHE_HPP
#define CACHE_HPP

struct cache_performance_t
{
    // Time it takes to access Cache.
    unsigned int AccessTime;
    // Time it takes to fetch new block on miss.
    unsigned int MissTime;
    // Time it takes to fetch data from block on hit.
    unsigned int HitTime;
};


class Cache
{
public:
    // Default Constructor
    Cache() : _numBlocks(64), _blockSize(64), _setAssociativity(8) {}
    // Constructor
    Cache(unsigned int numBlocks, unsigned int blockSize, unsigned int setAssociativity) :
        _numBlocks(numBlocks), _blockSize(blockSize), _setAssociativity(setAssociativity) {}
    
private:
    unsigned int _numBlocks;
    unsigned int _blockSize;
    unsigned int _setAssociativity;
    cache_performance_t _performance;
    // Decide whether to do Cache Emulator, or Cache Simulator for performance testing
};

#endif