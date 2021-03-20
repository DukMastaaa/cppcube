# Feature List

## Implemented
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
- A `struct` with time, scramble and penalty fields (POD)
- Penalty controls and display
- Record list
- Record list view
- Organise header files into folders
- Restructure `main()` to use controller and app class
- Enforce const correctness
- Use `unique_ptr` in BaseController class
- Explicitly specify `override` for overriden virtual functions
- More keyboard controls
- Window title
- Handle terminal resize events
- Refactor `cubes.cpp` and `cubes.h`
- Templatise `cubes.h` into `cubes.tpp`
- Develop popup window classes (kind of)
- Make cube view popup
- Change side length of cube during run-time through popup
- Delete confirmation box
- Generate info popup for scramble
- Record summary statistics

## To be implemented
- Shrink views if too large and display popups instead
- Data export/import
- Automatic saving (location of save file most likely OS-dependent)
- Arrow key navigation

## Could possibly implement
- Arrow key navigation instead of entirely keyboard controls
- Support for non-cubic WCA puzzles (pyraminx etc). Not likely to get visualisation
  but scrambles are possible... if i can make a model somehow..
- Try to get orange colours to appear on terminal? Not sure if this is feasible given
  ncurses' limitations.
- Graph improvement?! 

## Out of scope
- Algorithm lists and visualisations