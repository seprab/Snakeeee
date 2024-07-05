//
// Created by Sergio Prada on 29/06/24.
//

#include <SDL.h>
#include <SDL_ttf.h>
#include "menu.h"
#include <iostream>

Menu::OPTIONS Menu::Show(SDL_Renderer *renderer)
{
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return OPTIONS::QUIT;
    }

    // Load the font
    TTF_Font* font = TTF_OpenFont("resources/OpenSans-Regular.ttf", 24);
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return OPTIONS::QUIT;
    }

    // Define the color of the text
    SDL_Color textColor = {255, 255, 255, 255};

    // Create the surfaces
    SDL_Surface* playSurface = TTF_RenderText_Solid(font, "Play", textColor);
    SDL_Surface* scoreboardSurface = TTF_RenderText_Solid(font, "Scoreboard", textColor);
    SDL_Surface* exitSurface = TTF_RenderText_Solid(font, "Exit", textColor);

    // Create the textures
    SDL_Texture* playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Texture* scoreboardTexture = SDL_CreateTextureFromSurface(renderer, scoreboardSurface);
    SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);

    // Define the rectangles that will hold the positions of the menu options
    SDL_Rect playRect = { 100, 100, playSurface->w, playSurface->h };
    SDL_Rect scoreboardRect = { 100, 200, scoreboardSurface->w, scoreboardSurface->h };
    SDL_Rect exitRect = { 100, 300, exitSurface->w, exitSurface->h };

    SDL_Event event;
    bool running = true;

    while (running) {
        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw the menu options
        SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
        SDL_RenderCopy(renderer, scoreboardTexture, NULL, &scoreboardRect);
        SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);

        // Show the changes on the screen
        SDL_RenderPresent(renderer);

        // Handle the user input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
            {
                running = false;
                return OPTIONS::QUIT;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point point = {x, y};
                // Check if the user has clicked on any of the menu options
                if (SDL_PointInRect(&point, &playRect))
                {
                    return OPTIONS::PLAY;
                }
                else if (SDL_PointInRect(&point, &scoreboardRect))
                {
                    return OPTIONS::SCOREBOARD;
                }
                else if (SDL_PointInRect(&point, &exitRect)) {
                    return OPTIONS::QUIT;
                }
            }
        }
    }

    // Clean up
    SDL_DestroyTexture(playTexture);
    SDL_DestroyTexture(scoreboardTexture);
    SDL_DestroyTexture(exitTexture);

    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(scoreboardSurface);
    SDL_FreeSurface(exitSurface);

    TTF_CloseFont(font);
    TTF_Quit();
}

Menu::Menu() {

}

Menu::~Menu() {

}
