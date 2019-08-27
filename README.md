# Tic-Tac-Toe Game Example
This is a Capstone Project for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
The design was adpated from this [Grid Structure](https://github.com/catsocks/sdl-grid) tutorial. The main solving algorithm is based on the [Negative Minmax Implementation](http://blog.gamesolver.org/solving-connect-four/03-minmax/).


Since the project is using the SDL2 library, the pre-requisities are as listed in [this Snake Game example](https://github.com/udacity/CppND-Capstone-Snake-Game):

## Setup for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* Google Test (for tests)
  * [Installation instructions](https://github.com/google/googletest)


## Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./TicTacToe`.

## Test Instructions

1. Set path to the GTest root in test/CmakeLists.txt: `set(GTEST_ROOT /usr/lib/gtest)`
2. Make a build directory for tests: `cd test && mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./testRunner`.