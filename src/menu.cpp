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
        SDL_SetRenderDrawColor(m_Renderer, 0x1E, 0x1E, 0x1E, 0xFF);
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

void Menu::RenderScoreboard()
{
    LoadScores();
    while (true)
    {
        SDL_SetRenderDrawColor(m_Renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(m_Renderer);
    // Assuming a simple vertical list of scores
    int yOffset = 100; // Starting Y position
    for (const auto& score : scores)
    {
        SDL_Surface* tempSurface = TTF_RenderText_Solid(m_Font, score.c_str(), {255, 255, 255, 255}); // White text
        SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(m_Renderer, tempSurface);
        SDL_Rect scoreRect = {250, yOffset, tempSurface->w, tempSurface->h};
        SDL_RenderCopy(m_Renderer, tempTexture, NULL, &scoreRect);

        SDL_FreeSurface(tempSurface);
        SDL_DestroyTexture(tempTexture);
        yOffset += 50; // Move down for the next score
    }

    SDL_Rect exitRect = {100, 300, m_ExitSurface->w, m_ExitSurface->h };
    SDL_Event event;
    SDL_RenderCopy(m_Renderer, m_ExitTexture, NULL, &exitRect);
    SDL_RenderPresent(m_Renderer);
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Point point = {x, y};
             if (SDL_PointInRect(&point, &exitRect))
            {
                return;
            }
        }
    }
    }
}

void Menu::LoadScores()
{
    scores.clear();
    // Placeholder: Load scores from a file or initialize them
    scores.push_back("Player1 - 100");
    scores.push_back("Player2 - 90");
    // etc.
}

void Menu::RenderUsernameScreen(std::string& username)
{
    std::string inputText = "Enter Name: ";
    SDL_StartTextInput();
    SDL_Event e;
    bool enterPressed = false;

    while (!enterPressed)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                enterPressed = true;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_RETURN)
                {
                    enterPressed = true;
                }
                else if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 11)
                {
                    inputText.pop_back();
                }
            }
            else if (e.type == SDL_TEXTINPUT)
            {
                inputText += e.text.text;
            }
        }

        SDL_SetRenderDrawColor(m_Renderer, 0x1E, 0x1E, 0x1E, 0xFF);
        SDL_RenderClear(m_Renderer);

        // Render the current input text
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(m_Font, inputText.c_str(), {255, 255, 255, 255});
        SDL_Texture* message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);
        SDL_Rect message_rect; // Set the position and size for your text
        message_rect.x = 100;
        message_rect.y = 100;
        message_rect.w = surfaceMessage->w;
        message_rect.h = surfaceMessage->h;

        SDL_RenderCopy(m_Renderer, message, NULL, &message_rect);
        SDL_RenderPresent(m_Renderer);

        SDL_FreeSurface(surfaceMessage);
        SDL_DestroyTexture(message);
    }

    SDL_StopTextInput();
    username = inputText.substr(11); // Remove the prompt part from the input text
}
