#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include <vector>

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  int HighScore();
  bool GameStart(Controller const &controller, Renderer &renderer, 
            std::size_t target_frame_duration);
  bool GameEnd(Controller const &controller, Renderer &renderer,
            std::size_t target_frame_duration);
  void ResetGame(){
    snake.ResetSnake();
    score = 0;
  }

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point lemon;
  SDL_Point morgue;
  int repeat = 1;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};
  std::vector<int> scoreboard;

  void PlaceFood();
  void Update(bool &running);
};

#endif