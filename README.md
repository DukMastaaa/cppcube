# cppcube

![Main Window Screenshot](docs/images/mainWindow.png?raw=true)

## About
`cppcube` is a Rubik's Cube speedsolving timer in the terminal using `ncurses`.
It is capable of generating scrambles and views of NxNxN cubes, and can export
sessions and display basic summary statistics. UI design is inspired by the 
legendary https://cstimer.net.

I can't get orange to display properly with `ncurses` yet - for now, the purple
colour shown in cube views represents orange, and the other orange-looky one is
for yellow. This is quite a substantial drawback and I'll try my best to resolve
it.


## Build
Here are build requirements:
- `g++` with `c++17` support
- `make`
- `ncurses`

To build `cppcube`:
1. Clone the repository. 
2. Run `make` in the top-level repository folder.
3. Then, just run `./main`.


## Controls
Maybe I'll get arrow key controls for navigation, but for the
meantime, these keyboard controls are the way to go.

| Key            | Function                               |
|:--------------:| -------------------------------------- |
| `<Space>`      | Start, stop timing                     |
| `2`            | Toggle +2 penalty on most recent time  |
| `d`            | Toggle DNF penalty on most recent time |
| `x`            | Delete most recent time                |
| `<Shift>` + `2`/`d`/`x` | Apply deletion/penalty to selected time |
| `p`            | Change puzzle type                     |
| `n`            | Generate new scramble                  |
| `<Up>`/`<Down>`| Scroll through recorded times          |
| `i`            | Show info for selected time            |
| `j`            | Jump to index in recorded times        |
| `t`            | Jump to top of recorded times          |
| `b`            | Jump to bottom of recorded times       |
| `g`            | Generate summary statistics            |
| `E` (shift)    | Export times                           |
| `L` (shift)    | Import times                           |
| `h`            | Display help pop-up                    |
| `v`            | Display cube view in pop-up            |
| `s`            | Display scramble in popup-up           |


## File Export/Import
`cppcube` will ask for a filename to export and import solves. As of 
now, only exporting to and importing from files in the *same directory* 
as the executable is allowed.


## What about the previous `cppcube`?
The original `cppcube` was simply a header and `.cpp` file providing an
NxNxN cube model. There was also code to measure performance, and an equivalent
Python implementation of the algorithm. The Python code can be found in `/python`.
For the cube model, see `/src/include/cubes.h`, `/src/include/cubes.tpp` and 
`src/model/cubes.cpp`. The interface has changed, but the model can still print a 
net of the cube to `std::cout` using `void CubeModel::coutDisplayNet()`. 
