# Cache Simulator
This repository contains the source code for a Cache Simulator that runs and measures performance based on a trace file.

## Trace File Format
The format of the trace file is as follows:

    # LS ADDRESS IC
where LS is type of access, 0 for a load and 1 for a store, ADDRESS is a 8-character hexadecimal number containing the address of the load/store, and IC is the number of instructions between previous and current memory access. A single space is used to separate each field, and a new line separates two accesses. An example:

    # 0 3019b6c8 2
    # 0 300e20d8 2
    # 0 3026e398 5
    # 0 30192830 1
    # 1 30192830 3
which contains 4 loads and 1 store.

## Usage
**NOTE:** Before making project, make sure to create a folder called "build" in your folder.

This Cache Simulator is a command line program that takes arguments from either the command line, or from a configuration file.

The program prints usage, if unrecognized arguments are passed, or no arguments are passed. The usage is repeated here for convenience:

    Usage: ./build/driver -i <tracefile> [OPTIONS]
        -i <tracefile>  :   Path to trace file.
        -b batchsize    :   Batch Size (must be first argument if used).
        -a assoctvty    :   Cache set associativity.
        -l blocksize    :   Size of cache blocks in bytes.
        -s cachesize    :   Cache size in KiB.
        -mp misspen     :   Miss penalty in cycles.
        -dp dirtypen    :   Dirty write-back penalty in cycles.
        -r replace      :   Replacement scheme, e.g. 'LRU'.
        -w writeschem   :   Write Scheme, e.g. 'WB' for Write-Back.
        -m misschem     :   Write Miss Scheme, e.g. 'WA' for Write-Allocate.
        -c <cachecfg>   :   Path to Cache Config file. The Cache config file 
                            is just a file containing the same option flags 
                            as defined here.

**NOTE:** The '-b' argument must be the first argument in the list, if used. Default batch size is 100.

An example of usage could be:

    ./build/driver -b 50 -i \<trace-file-path> -a 1 -l 16 -s 16 -mp 30 -dp 2

It is highly recommended that associativity, block size, cache size, miss penalty and dirty write penalty are defined in arguments, as all these parameters will take on default values, which might be undesired by the user.

The default values for replacement scheme, write scheme and write miss scheme are respectively LRU, Write-back and Write-allocate, which are very popular policies in caches.

## Development Status
Under development: 
* Trace file parsing (finished)
    * Testing of trace file parsing (finished)
* Cache configuration class (finished)
* Front-End (finished)
    * CLI Commands (finished)
    * Testing of front-end (finished)
* Basic Cache Class (finished)
    * Cache Set Class (finished)
* Cache Simulator (finished)
    * Cache Performance Statistics (finished)
    * Testing of Cache Simulator (finished)
        * Tested against results from [this page](https://www.cs.oberlin.edu/%7Ectaylor/classes/210SP13/cache.html).
* More advanced caches (pending)
    * Alternative replacement policies (pending)
    * Implementation of Write-through policy (pending)
    * Implementation of Write-no-allocate policy (pending)
    * L2 (and L3) caches (pending)

More will be added to the list with time...
