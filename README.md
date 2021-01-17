# cppcube

## About
`cppcube` is a Rubik's Cube speedsolving timer in the terminal. It supports scrambles
and visualisation for NxNxN cubes, and basic summary statistics of previous times.
Exporting and saving of times will be implemented in the near future once
all graphical elements have been developed.

## Features
This project is heavy in development, so features will be added/removed frequently from
the following lists.

### Implmented
- NxNxN cube model and move parser
    - Parser accepts moves in the form `(\d)*([UFRBOG])(w)?(['2])?`
      where a `w` with no beginning digit implies depth of `2`
- NxNxN cube scrambler
- Cube net view
- Scramble view (and made window/view separation more robust)
- Timer view using block characters
- Finish CubeTimer class
- Actual timing functionality
- Proper formatting of scramble (only break line on space)

### Will implement
- Window title
- Handle terminal resize events
- A `struct` with time, scramble and penalty fields (POD)
- Penalties (+2, DNF)
- Change side length of cube during run-time
- Shrink views if too large and display popups instead
- Record list
- Record list view
- Record summary statistics
- Data export/import
- Automatic saving (location of save file most likely OS-dependent)

### Could possibly implement
- Support for non-cubic WCA puzzles (pyraminx etc). Not likely to get visualisation
  but scrambles are possible... if i can make a model somehow..
- Try to get orange colours to appear on terminal? Not sure if this is feasible given
  ncurses' limitations.

### Out of scope
- Algorithm lists and visualisations

## What about the previous `cppcube`?
The original `cppcube` was simply a header and `.cpp` file providing an
NxNxN cube model. There was also code to measure performance, and an equivalent
Python implementation of the algorithm. The Python code can be found in `/python`
and the `cubes` header/implementation are `/src/include/cubes.h` and 
`src/model/cubes.cpp` respectively. Not much has changed since the original implementation.
