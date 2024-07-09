# Snake Game on SDL

## Added features
- Added a high score counter that persists between sessions
- Added moving obstacles that spawn over time
- Added an interactable menu with options to start a new game, view the high score, and exit the game
- Extended the controls to include the arrow keys and the WASD keys

## Installation

Xcode Command Line Tools ( if not already installed )

- xcode-select --install

SDL2 Installs

- brew install sdl2
- brew install sdl2_image
- brew install sdl2_mixer
- brew install sdl2_ttf

## Building with CLion

I use CLion although it's not required ( see a below step for building without CLion ). 

You should be able to clone this repo and open the root folder in CLion. This will auto run CMake against the root _CMakeLists.txt_ file and create a _cmake_build_debug_ folder, within which will be a _bin_ folder and sample resources. Once you've built the project the executable will be compiled to there.

## Command Line Build

- mkdir out
- cd out
- cmake ../
- make

## Rubric Points Addressed
- [A README with instructions is included with the project](README.md)
- [The README indicates the new features you added to the game.](README.md)
- [The README includes information about each rubric point addressed.](README.md)
- [The submission must compile and run without errors on the Udacity project workspace.](README.md)
- [The project demonstrates an understanding of C++ functions and control structures.](src)
- [The project reads data from a file and process the data, or the program writes data to a file.](src/ScoreManager.h)
- [The project accepts user input and processes the input.](src/menu.cpp)
- [The project uses data structures and immutable variables.](src/ScoreManager.h)
- [One or more classes are added to the project with appropriate access specifiers for class members.](src/Obstacle.h)
- [Class constructors utilize member initialization lists.](src/Obstacle.cpp)
- [The project makes use of references in function declarations.](src/ScoreManager.cpp)
- [The project uses destructors appropriately.](src/game.cpp)
- [The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.](src/main.cpp)
- [The project follows the Rule of 5.](src/menu.h)
- [The project uses smart pointers instead of raw pointers.](src/main.cpp)
- [The project uses multithreading.](src/game.cpp)
- [A mutex or lock is used in the project.](src/game.cpp)



## Credits

- [Original Snake Game base code](https://github.com/udacity/CppND-Capstone-Snake-Gam)
- [SDL Template project with ttf support](https://github.com/JodyAndrews/SDL2_Basic_Setup/)

