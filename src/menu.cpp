//
// Created by Sergio Prada on 29/06/24.
//

#include <SDL.h>
#include <SDL_ttf.h>
#include "menu.h"
#include <iostream>

Menu::OPTIONS Menu::Show()
{
    std::cout << "Showing Menu" << std::endl;
    // Define the rectangles that will hold the positions of the menu options
    SDL_Rect playRect = {100, 100, m_PlaySurface->w, m_PlaySurface->h };
    SDL_Rect scoreboardRect = {100, 200, m_ScoreboardSurface->w, m_ScoreboardSurface->h };
    SDL_Rect exitRect = {100, 300, m_ExitSurface->w, m_ExitSurface->h };

    SDL_Event event;

    while (true)
    {
        SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0xFF);
        // Clear the screen
        int clearRenderer = SDL_RenderClear(m_Renderer);
        if(clearRenderer != 0)
        {
            std::cerr << "Error clearing the renderer" << std::endl;
            std::cerr <<SDL_GetError()<< std::endl;
            return OPTIONS::QUIT;
        }

        // Draw the menu options
        SDL_RenderCopy(m_Renderer, m_PlayTexture, NULL, &playRect);
        SDL_RenderCopy(m_Renderer, m_ScoreboardTexture, NULL, &scoreboardRect);
        SDL_RenderCopy(m_Renderer, m_ExitTexture, NULL, &exitRect);

        // Show the changes on the screen
        SDL_RenderPresent(m_Renderer);

        // Handle the user input
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
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
                else if (SDL_PointInRect(&point, &exitRect))
                {
                    return OPTIONS::QUIT;
                }
            }
        }
    }
}

Menu::Menu(SDL_Renderer *renderer) : m_Renderer(renderer)
{
    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    // Load the m_Font
    m_Font = TTF_OpenFont("resources/OpenSans-Regular.ttf", 24);
    if (m_Font == nullptr)
    {
        std::cerr << "Failed to load m_Font! SDL_ttf Error: " << TTF_GetError() << std::endl;
    }

    // Define the color of the text
    SDL_Color textColor = {255, 255, 255, 255};
    // Create the surfaces
    m_PlaySurface = TTF_RenderText_Solid(m_Font, "Play", textColor);
    m_ScoreboardSurface = TTF_RenderText_Solid(m_Font, "Scoreboard", textColor);
    m_ExitSurface = TTF_RenderText_Solid(m_Font, "Exit", textColor);

    // Create the textures
    m_PlayTexture = SDL_CreateTextureFromSurface(renderer, m_PlaySurface);
    m_ScoreboardTexture = SDL_CreateTextureFromSurface(renderer, m_ScoreboardSurface);
    m_ExitTexture = SDL_CreateTextureFromSurface(renderer, m_ExitSurface);
}

Menu::~Menu()
{
// Clean up
    SDL_DestroyTexture(m_PlayTexture);
    SDL_DestroyTexture(m_ScoreboardTexture);
    SDL_DestroyTexture(m_ExitTexture);

    SDL_FreeSurface(m_PlaySurface);
    SDL_FreeSurface(m_ScoreboardSurface);
    SDL_FreeSurface(m_ExitSurface);

    TTF_CloseFont(m_Font);
    TTF_Quit();
}
