//
// Created by Sergio Prada on 8/07/24.
//
#include <random>
#include "Obstacle.h"
#include "config.h"
Obstacle::Obstacle(int x, int y, int _moveX, int _moveY):
position{x, y}
{
    moveX = _moveX % 2;
    moveY = _moveY % 2;
    deltaX = ((_moveX + _moveY)%2) ? 1 : -1;
    deltaY = ((_moveX * _moveY)%2) ? 1 : -1;
}

Obstacle::~Obstacle() = default;

int Obstacle::GetX() const {
    return position.x;
}

int Obstacle::GetY() const {
    return position.y;
}

void Obstacle::MoveX() {
    if(moveX)
        position.x += deltaX;

    if(deltaX>0 && position.x > kGridWidth)
        position.x = 0;

    if(deltaX<0 && position.x < 0)
        position.x = kGridWidth;
}

void Obstacle::MoveY() {
    if(moveY)
        position.y += deltaY;

    if(deltaY>0 && position.y > kGridHeight)
        position.y = 0;
    if(deltaY<0 && position.y < 0)
        position.y = kGridHeight;
}
