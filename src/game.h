#ifndef GAME_H
#define GAME_H

#include <random>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "Obstacle.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  ~Game();
  void Run(Controller const &controller, const std::shared_ptr<Renderer>& renderer,
           std::size_t target_frame_duration);
  [[nodiscard]] int GetScore() const;
  [[nodiscard]] int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_move;

  int score{0};

  std::vector<Obstacle> obstacles;
  void PlaceObstacles();
  [[nodiscard]] bool CheckObstacleCollision() const;

  std::thread obstacle_thread;
  std::mutex obstacle_mutex;

  void PlaceFood();
  bool Update();
  void MoveObstaclesAsync();
  std::thread moveObstaclesThread;
};

#endif