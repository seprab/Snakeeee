//
// Created by Sergio Prada on 8/07/24.
//

#include "Obstacle.h"

Obstacle::Obstacle(int x, int y)  : position{x, y} {

}

Obstacle::~Obstacle() = default;

int Obstacle::GetX() const {
    return position.x;
}

int Obstacle::GetY() const {
    return position.y;
}
