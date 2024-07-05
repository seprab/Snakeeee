# Snake Game on SDL

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

## Credits

- [Original Snake Game base code](https://github.com/udacity/CppND-Capstone-Snake-Gam)
- [SDL Template project with ttf support](https://github.com/JodyAndrews/SDL2_Basic_Setup/)

