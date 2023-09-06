#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  bool play = false; // User choice to play | Yes / No

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  // Start the game
  play = game.GameStart(controller, renderer, kMsPerFrame);

  while (play) {
    game.Run(controller, renderer, kMsPerFrame);
    play = game.GameEnd(controller, renderer, kMsPerFrame);
    game.ResetGame();
  }

  return 0;
}