/*********************************************************
 * File: cache_sim.hpp
 * Description: This file contains the definition of the
 * CacheSim class as well as functions and methods for the
 * class. 
 * 
 * Author: jfhansen
 * Last modification: 13/07/2020
 *********************************************************/

#include <iomanip>
#include "cache_sim.hpp"

CacheSim::CacheSim(uint32_t batchSize, CacheConfig config)
    : _cache(Cache(config)), 
    _ca(batchSize, config.get_trace_file_path())
{ }

double CacheSim::miss_rate() {
    // Overall Miss Rate = 1 - (TotalHits) / (TotalAccesses)
    double missRate = (double)(_cache.get_store_hits() + _cache.get_load_hits()); 
    missRate /= (double)(_cache.get_load_accesses() + _cache.get_store_accesses());
    missRate = 1 - missRate;
    return missRate;
}

double CacheSim::dirty_evic_rate() {
    // Dirty Eviction Rate = (DirtyEvictions) / (TotalEvictions)
    double dirtyEvicRate = (double)_cache.get_dirty_evictions();
    dirtyEvicRate /= (double)_cache.get_total_evictions();
    return dirtyEvicRate;
}

double CacheSim::memory_cpi(uint64_t memAccesses, double missRate, double dirtyEvicRate)
{
    // Memory CPI = Memory Stall Cycles per instruction:
    // MemoryAccesses / Instructions * MissRate * ( MissPenalty + DirtyEvicRate * DirtyWriteBackPenalty )
    double memCPI =  _cache.get_miss_penalty();
    memCPI += dirtyEvicRate * (double)_cache.get_dirty_wb_penalty();
    memCPI *= missRate * (double)memAccesses / (double)_instructions;
    return memCPI;
}

double CacheSim::amat(double missRate, double dirtyEvicRate)
{
    // Average Memory Access Time (AMAT):
    // AMAT = TimeForHit + MissRate * ( MissPenalty + DirtyEvicRate * DirtyWriteBackPenalty )
    // TimeForHit = 0
    double amat = _cache.get_miss_penalty();
    amat += dirtyEvicRate * (double)_cache.get_dirty_wb_penalty();
    amat *= missRate;
    return amat;
}

void CacheSim::run()
{
    unsigned long addr, accs = 0;
    bool type;
    unsigned instrs, accesses;
    while ( (accesses = _ca.fetch_batch()) != 0)
    {
        accs += accesses;
        while (accesses > 0)
        {
            std::tie(addr, type, instrs) = _ca.get_access();
            accesses--;
            _memory_cycles += _cache.access_cache(addr, type, instrs);
            _instructions += instrs;
        }
    }
    // Compute overall miss rate
    double missRate = miss_rate();

    // Compute load miss rate
    float loadMissRate = 1 - (double)_cache.get_load_hits() / (double)_cache.get_load_accesses();

    // Compute store miss rate
    float storeMissRate = 1 - (double)_cache.get_store_hits() / (double)_cache.get_store_accesses();

    // Compute dirty eviction rate
    double dirtyEvicRate = dirty_evic_rate();

    // Compute Memory CPI = miss_rate * miss_penalty
    double memCPI = memory_cpi(accs, missRate, dirtyEvicRate);

    // Compute AMAT
    double AMAT = amat(missRate, dirtyEvicRate);

    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
    std::cout << "Simulation Results: " << std::endl;

    std::cout << "\tinstructions: " << _instructions << "." << std::endl;

    std::cout << "\ttotal execution time: " << _memory_cycles + _instructions << " cycles." << std::endl;

    std::cout << "\tmemory accesses: " << accs << std::endl;

    std::cout << "\tload hits: " << _cache.get_load_hits() << std::endl;

    std::cout << "\tload accesses: " << _cache.get_load_accesses() << std::endl;
    
    std::cout << "\tload miss rate: " << loadMissRate << std::endl;

    std::cout << "\tstore hits: " << _cache.get_store_hits() << std::endl;

    std::cout << "\tstore accesses: " << _cache.get_store_accesses() << std::endl;

    std::cout << "\tstore miss rate: " << storeMissRate << std::endl;

    std::cout << "\toverall miss rate: " << missRate << std::endl;

    std::cout << "\tdirty evictions: " << _cache.get_dirty_evictions() << std::endl;

    std::cout << "\ttotal evictions: " << _cache.get_total_evictions() << std::endl;

    std::cout << "\tdirty eviction rate: " << dirtyEvicRate << std::endl;

    std::cout << "\tmemory CPI: " << memCPI << std::endl;
    
    std::cout << "\ttotal CPI: " << memCPI + 1 << std::endl;

    std::cout << "\taverage memory access time: " << AMAT << " cycles." << std::endl;

}