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
  bool play = false; // user option of play/not

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);

  // Start the game
  play = game.GameStart(controller, renderer, kMsPerFrame);

  if (play) {
    // Run game if selection is to play
    game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Highest Score: " << game.HighScore() <<"\n";
    game.GameEnd(controller, renderer, kMsPerFrame);
  }

  game.GameEnd(controller, renderer, kMsPerFrame);
  return 0;
}