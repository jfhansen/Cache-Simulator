/*********************************************************
 * File: access.cpp
 * Description: This file contains the implementation of the
 * CacheAccess class as well as functions and methods for the
 * parsing through the inputted trace file.
 * 
 * Author: jfhansen
 * Last modification: 11/07/2020
 *********************************************************/

#include "access.hpp"
#include <fstream>
#include <sstream>

// Constructor for CacheAccess Class
CacheAccess::CacheAccess(unsigned batch_size, std::string trace_file)
    : _fileName(trace_file)
{
    // Resize address, type and instructions vectors according to
    // batch size
    _addresses.resize(batch_size);
    _types.resize(batch_size);
    _numInstructions.resize(batch_size);
    _filePosition = 0;
    _currentAccess = 0;
}

// Gets memory access currently pointed at in fetched data.
// Returns memory address, type of access and number of instructions
// between consecutive accesses.
std::tuple<uint64_t, bool, uint32_t> CacheAccess::get_access()
{
    // Create return tuple
    auto return_tup = std::make_tuple(_addresses[_currentAccess], 
        _types[_currentAccess], _numInstructions[_currentAccess]);
    
    // Increment _currentAccess variable.
    _currentAccess++;
    // Return tuple
    return return_tup;
}

// Fetches new batch from input file.
unsigned CacheAccess::fetch_batch()
{
    // Reset _currentAccess to zero.
    _currentAccess = 0;
    // Return number of accesses parsed.
    return parse_input_file();
}

// Parses through the current batch of the input file, 
// updating the member variables in the process,
// and returns number of accesses parsed
unsigned CacheAccess::parse_input_file()
{
    // Initialize file in '_fileName' path as input file
    std::ifstream file(_fileName);
    // Go to current position in file.
    file.seekg(_filePosition);

    // Read in one batch at most
    size_t i;
    for (i = 0; i < _addresses.size(); i++)
    {
        std::string line;
        if (std::getline(file, line))
        {
            // Create stringstream object from 'line'
            std::stringstream ss(line);

            std::string sink;
            uint64_t addr;
            bool type;
            unsigned instr;
            // Read from line.
            // First field is unused.
            ss >> sink;
            // Second field is boolean value indicating type.
            ss >> type;
            // Third field contains address string.
            ss >> std::hex >> addr;
            // Fourth field contains number of instructions between consecutive accesses.
            ss >> std::dec >> instr;
            
            // Insert parsed line into CacheAccess member variables.
            _addresses[i] = addr;
            _types[i] = type;
            _numInstructions[i] = instr;

        }
        else
        {
            // If file ended early, exit loop.
            break;
        }
    }
    // Get current file position
    _filePosition = file.tellg();
    // Return number of accesses parsed.
    return i;
}

