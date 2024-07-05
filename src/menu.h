//
// Created by Sergio Prada on 29/06/24.
//

#ifndef SDL2TEST_MENU_H
#define SDL2TEST_MENU_H


#include <SDL.h>
#include <SDL_ttf.h>

class Menu{

public:
    enum class OPTIONS{
        PLAY,
        SCOREBOARD,
        QUIT
    };

    explicit Menu(SDL_Renderer *renderer);
    ~Menu();

    OPTIONS Show();

private:
    TTF_Font *m_Font;
    SDL_Surface *m_PlaySurface;
    SDL_Surface *m_ScoreboardSurface;
    SDL_Surface *m_ExitSurface;
    SDL_Texture *m_PlayTexture;
    SDL_Texture *m_ScoreboardTexture;
    SDL_Texture *m_ExitTexture;
    SDL_Renderer *m_Renderer;
};


#endif //SDL2TEST_MENU_H
