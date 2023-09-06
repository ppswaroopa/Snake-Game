#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "SDL.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;
  void HandleInputStartEnd(int &running) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif