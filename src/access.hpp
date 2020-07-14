/*********************************************************
 * File: access.hpp
 * Description: This file includes the definition of the
 * CacheAccess class as well as functions and methods for the
 * parsing through the inputted trace file.
 * 
 * Author: jfhansen
 * Last modification: 11/07/2020
 *********************************************************/

#ifndef ACCESS_HPP
#define ACCESS_HPP

#include <string>
#include <vector>
#include <tuple>

class CacheAccess
{
    public:
        // Constructor for CacheAccess Class
        CacheAccess(unsigned batch_size, std::string trace_file);
        // Destructor
        ~CacheAccess() = default;

        // Gets memory access currently pointed at in fetched data.
        // Returns memory address, type of access and number of instructions
        // between consecutive accesses.
        std::tuple<uint64_t, bool, uint32_t> get_access();

        // Fetches new batch from input file.
        unsigned fetch_batch();

        // Parses through the current batch of the input file, 
        // updating the member variables in the process,
        // and returns number of accesses parsed
        unsigned parse_input_file();

    private:
        // Data Members
        // Addresses
        std::vector<uint64_t> _addresses;

        // Types of memory accesses
        std::vector<bool> _types;

        // Number of instructions between consecutive accesses
        std::vector<uint32_t> _numInstructions;

        // Name of input file
        const std::string _fileName;

        // Current memory access
        unsigned _currentAccess = 0;

        // Position in file
        unsigned _filePosition = 0;
};

#endif