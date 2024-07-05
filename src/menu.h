//
// Created by Sergio Prada on 29/06/24.
//

#ifndef SDL2TEST_MENU_H
#define SDL2TEST_MENU_H


#include <SDL.h>

class Menu{

public:
    enum class OPTIONS{
        PLAY,
        SCOREBOARD,
        QUIT
    };

    Menu();
    ~Menu();

    OPTIONS Show(SDL_Renderer *renderer);

private:

};


#endif //SDL2TEST_MENU_H
