#include "controller.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      snake.alive = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
        case SDLK_ESCAPE:
          snake.alive = false;
          // running = false;
          break;
      }
    }
  }
}

/*
Handles keyboard input for the Start and End screen.
Input: Enter key OR Enter key from the keypad sets variable start to 1
This allows the player to play the game.
Input: Pressing the quit window button or Escape key, sets variable to 2
This quits the game.
*/
void Controller::HandleInputStartEnd(int &start) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      start = 2;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_RETURN:
          start = 1;
          break;
        case SDLK_KP_ENTER:
          start = 1;
          break;
        case SDLK_ESCAPE:
          start = 2;
          break;
      }
    }
  }
}