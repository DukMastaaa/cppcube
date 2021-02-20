# cppcube

![Main Window Screenshot](docs/images/mainWindow.png?raw=true)

## About
`cppcube` is a Rubik's Cube speedsolving timer in the terminal using `ncurses`. It supports scrambles
and visualisation for NxNxN cubes, and basic summary statistics of previous times. 
UI design is inspired by the legendary https://cstimer.net.
Exporting and saving of times will be implemented in the near future once
all graphical elements have been developed.


## Features
`cppcube` can:
- Generate scrambles and views of NxNxN cubes
- Apply +2/DNF penalties to selected times in the record history
- Calculate summary statistics (tba)
- Export times (tba)

A full list of the program's features can be found [here](docs/Features.md).


## Build
To build `cppcube`:
1. Clone the repository. 
2. Run `make` in the top-level repository folder. Make sure you have `ncurses` installed 
   in your system and that your terminal has colour support.
3. Then, just run `./main`.


## Controls
Eventually I'm planning to get arrow key controls throughout the program but for now keyboard controls are the way to go.

| Key            | Function                               |Implemented|
|:--------------:| -------------------------------------- |--|
| `<Space>`      | Start, stop timing                     |Y |
| `2`            | Toggle +2 penalty on most recent time  |Y |
| `d`            | Toggle DNF penalty on most recent time |Y |
| `x`            | Delete most recent time                |N |
| `<Shift>` + `2`/`d`/`x` | Apply deletion/penalty to selected time |kinda |
| `p`            | Change puzzle type                     |Y |
| `n`            | Generate new scramble                  |Y |
| `<Up>`/`<Down>`| Scroll through recorded times          |Y |
| `i`            | Show info for selected time            |N |
| `j`            | Jump to index in recorded times        |N |
| `t`            | Jump to top of recorded times          |Y |
| `b`            | Jump to bottom of recorded times       |Y |
| `g`            | Generate summary statistics            |N |
| `E` (shift)    | Export times                           |N |
| `h`            | Display help pop-up                    |N |
| `v`            | Display cube view in pop-up            |Y |

## What about the previous `cppcube`?
The original `cppcube` was simply a header and `.cpp` file providing an
NxNxN cube model. There was also code to measure performance, and an equivalent
Python implementation of the algorithm. The Python code can be found in `/python`.
For the cube model, see `/src/include/cubes.h`, `/src/include/cubes.tpp` and 
`src/model/cubes.cpp`. The interface has changed, but the model can still print a 
net of the cube to `std::cout` using `void CubeModel::coutDisplayNet()`. 