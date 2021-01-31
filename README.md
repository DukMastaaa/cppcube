# cppcube

## About
`cppcube` is a Rubik's Cube speedsolving timer in the terminal. It supports scrambles
and visualisation for NxNxN cubes, and basic summary statistics of previous times. 
UI design is inspired by the legendary `https://cstimer.net`.
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
- A `struct` with time, scramble and penalty fields (POD)
- Penalty controls and display
- Record list
- Record list view
- Organise header files into folders
- Restructure `main()` to use controller and app class
- Enforce const correctness
- Use `unique_ptr` in BaseController class, https://docs.microsoft.com/en-us/cpp/cpp/object-lifetime-and-resource-management-modern-cpp
- Explicitly specify `override` for overriden virtual functions
- More keyboard controls
- Window title
- Handle terminal resize events

### Will implement
- Refactor `cubes.cpp` and `cubes.h`
- Develop popup window classes
- Generate info popup for scramble
- Change side length of cube during run-time through popup
- Shrink views if too large and display popups instead
- Record summary statistics
- Data export/import
- Automatic saving (location of save file most likely OS-dependent)

### Could possibly implement
- Arrow key navigation instead of entirely keyboard controls
- Support for non-cubic WCA puzzles (pyraminx etc). Not likely to get visualisation
  but scrambles are possible... if i can make a model somehow..
- Try to get orange colours to appear on terminal? Not sure if this is feasible given
  ncurses' limitations.

### Out of scope
- Algorithm lists and visualisations

## Controls
Eventually I'm planning to get arrow key controls throughout the program (with 
highlighting of buttons etc.) but for now I'm going to just do keyboard controls.

| Key            | Function                               |ok|
|:--------------:| -------------------------------------- |--|
| `<Space>`      | Start, stop timing                     |Y |
| `2`            | Toggle +2 penalty on most recent time  |Y |
| `d`            | Toggle DNF penalty on most recent time |Y |
| `x`            | Delete most recent time                |N |
| `<Shift-2>`    | Toggle +2 penalty on selected time     |Y |
| `<Shift-d>`    | Toggle DNF penalty on selected time    |Y |
| `<Shift-x>`    | Delete selected time in record list    |N |
| `p`            | Change puzzle type                     |N |
| `n`            | Generate new scramble                  |Y |
| `<Up-Arrow>`   | Scroll up through recorded times       |Y |
| `<Down-Arrow>` | Scroll down through recorded times     |Y |
| `i`            | Show info for selected time            |N |
| `j`            | Jump to index in recorded times        |N |
| `t`            | Jump to top of recorded times          |Y |
| `b`            | Jump to bottom of recorded times       |Y |
| `g`            | Generate summary statistics            |N |
| `E` (shift)    | Export times                           |N |
| `h`            | Display help pop-up                    |N |

## What about the previous `cppcube`?
The original `cppcube` was simply a header and `.cpp` file providing an
NxNxN cube model. There was also code to measure performance, and an equivalent
Python implementation of the algorithm. The Python code can be found in `/python`
and the `cubes` header/implementation are `/src/include/cubes.h` and 
`src/model/cubes.cpp` respectively. The interface has changed, but the model can
still print a net of the cube to `std::cout` using 
`void CubeModel::coutDisplayNet()`. 

## Current bugs
- Screen refreshes agressively when generating new scramble (`n`).
- Some terminals which allow vertical scrolling display binary characters
  when the window is scrolled up during runtime. This seems like weird
  `ncurses` behaviour, and I have tried to mitigate it by judiciously
  choosing `wclear()` over `werase()`. Calling `clearok(curscr, TRUE)` 
  before every `doupdate()` works but is overkill as every handled
  keyboard input will refresh the screen, causing flickering.
  - Similar bug using windows terminal (may not be isolated to this emulator)
    where agressively changing window size will eventually lead to very slow
    resizing behaviour, lagging the mouse around the terminal window.