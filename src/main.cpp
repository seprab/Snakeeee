#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "menu.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;

/*
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Menu", 100, 100, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Menu menu;
    Menu::OPTIONS option = menu.Show(renderer);
    switch (option)
    {
        case Menu::OPTIONS::PLAY:
            std::cout << "Play option selected" << std::endl;
            break;
        case Menu::OPTIONS::SCOREBOARD:
            std::cout << "Scoreboard option selected" << std::endl;
            break;
        case Menu::OPTIONS::QUIT:
            std::cout << "Quit option selected" << std::endl;
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
    */
}