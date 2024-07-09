//
// Created by Sergio Prada on 8/07/24.
//

#ifndef SNAKEEEEE_OBSTACLE_H
#define SNAKEEEEE_OBSTACLE_H


#include <SDL_rect.h>

class Obstacle
        {
public:
    Obstacle(int x, int y, int _moveX, int _moveY);
    ~Obstacle();

    SDL_Point position;
    bool moveX = false;
    bool moveY = false;
    int deltaX = 0;
    int deltaY = 0;

    [[nodiscard]] int GetX() const;
    [[nodiscard]] int GetY() const;
    void MoveX();
    void MoveY();
};


#endif //SNAKEEEEE_OBSTACLE_H
