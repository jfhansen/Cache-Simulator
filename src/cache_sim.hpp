/*********************************************************
 * File: cache_sim.hpp
 * Description: This file contains the definition of the
 * CacheSim class as well as functions and methods for the
 * class. 
 * 
 * Author: jfhansen
 * Last modification: 13/07/2020
 *********************************************************/

#ifndef CACHE_SIM_HPP
#define CACHE_SIM_HPP

#include <iostream>
#include "cache_config.hpp"
#include "cache.hpp"
#include "access.hpp"

class CacheSim 
{
    public:
        // Constructor. Takes batch size and Cache Config as input.
        CacheSim(uint32_t batchSize, CacheConfig config);
        ~CacheSim() = default;

        // Runs simulation using configuration.
        void run();

        // Compute Overall Miss Rate
        double miss_rate();
        // Compute Dirty Eviction Rate
        double dirty_evic_rate();
        // Compute Memory CPI
        double memory_cpi(uint64_t memAccesses, double missRate, double dirtyEvicRate);
        // Compute Average Memory Access Time (AMAT)
        double amat(double missRate, double dirtyEvicRate);

    private:
    // Functional cache
    Cache _cache;
    // Cache Access class for parsing through trace file
    // and fetching memory access information.
    CacheAccess _ca;

    // Statistic variables

    // Number of instructions executed in program that
    // trace file originates from.
    uint64_t _instructions = 0;
    // Number of cycles used on memory stalls caused by
    // cache misses and dirty write-backs.
    uint64_t _memory_cycles = 0;

};

#endif