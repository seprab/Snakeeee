//
// Created by Sergio Prada on 8/07/24.
//

#ifndef SNAKEEEEE_OBSTACLE_H
#define SNAKEEEEE_OBSTACLE_H


#include <SDL_rect.h>

class Obstacle
        {
public:
    Obstacle(int x, int y);
    ~Obstacle();

    SDL_Point position;

    [[nodiscard]] int GetX() const;
    [[nodiscard]] int GetY() const;

};


#endif //SNAKEEEEE_OBSTACLE_H
