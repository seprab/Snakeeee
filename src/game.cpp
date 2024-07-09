#include <iostream>
#include <thread>
#include "SDL.h"
#include "game.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      random_move(0, 10)
      {
        PlaceFood();
        obstacle_thread = std::thread(&Game::PlaceObstacles, this);
        moveObstaclesThread = std::thread(&Game::MoveObstaclesAsync, this);
      }

Game::~Game()
{
    if(obstacle_thread.joinable())
    {
        obstacle_thread.join();
    }
    if(moveObstaclesThread.joinable())
    {
        moveObstaclesThread.join();
    }
}
void Game::Run(Controller const &controller, const std::shared_ptr<Renderer>& renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, RenderGame - the main game loop.
    controller.HandleInput(running, snake);
    if (!Update()) break;
      renderer->RenderGame(snake, food, obstacles);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

bool Game::Update()
{
  if (!snake.alive)
  {
      std::cout<<"Snake died"<<std::endl;
      return false;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  if(CheckObstacleCollision())
  {
      snake.Kill();
      return false;
  }
  return true;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::PlaceObstacles()
{
    float counter = 0;
    while(snake.alive)
    {
        if (counter > 7000)
        {
            int x = random_w(engine);
            int y = random_h(engine);
            int moveX = random_move(engine);
            int moveY = random_move(engine);
            std::lock_guard<std::mutex> guard(obstacle_mutex);
            obstacles.emplace_back(x, y, moveX, moveY);
            counter = 0;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds (1));
        counter++;
    }
}
/// Check if the snake has hit an obstacle.
/// \return true if the snake hit an obstacle, false otherwise.
bool Game::CheckObstacleCollision() const
{
    for(const Obstacle& obstacle : obstacles)
    {
        if(static_cast<int>(snake.head_x) == obstacle.GetX() && static_cast<int>(snake.head_y) == obstacle.GetY())
        {
            return true;
        }
    }
    return false;
}

void Game::MoveObstaclesAsync() {
    while (snake.alive) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::lock_guard<std::mutex> guard(obstacle_mutex);
        for (Obstacle& obstacle : obstacles)
        {
            obstacle.MoveX();
            obstacle.MoveY();
        }
    }
}
