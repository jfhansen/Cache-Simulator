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

## Development Status
Under development: 
* Trace file parsing (finished)
    * Testing of trace file parsing (finished)
* Cache configuration class (finished)
* Front-End (finished)
    * CLI Commands (finished)
    * Testing of front-end (finished)
* Basic Cache Class (in-progress)
    * Cache Set Class (pending)
* Cache Performance Statistics (pending)

More will be added to the list with time.
