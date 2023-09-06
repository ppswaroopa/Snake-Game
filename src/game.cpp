#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  Mix_Music* music; // Initialize music and play music
  
  std::string basePath = SDL_GetBasePath();
  music = Mix_LoadMUS((basePath + "music/2020-03-22_-_A_Bit_Of_Hope_-_David_Fesliyan.mp3").c_str());

  if (!music) {
    std::cerr << "Failed to load music.\n";
    std::cerr << "SDL_Error: " << Mix_GetError() << "\n";
  }
  int result = Mix_PlayMusic( music, -1 ); // -1 will play the music indefinetly
  if ( result != 0 ) {
    std::cerr << "Failed to play music: " << Mix_GetError() << "\n";
  }
  
  while (snake.alive) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update(running);
    renderer.Render(snake, food, lemon, morgue);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

bool Game::GameStart(Controller const &controller, Renderer &renderer, 
                      std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  int start = 0;

  while (start == 0) {
    frame_start = SDL_GetTicks();

    // Input, Render
    controller.HandleInputStartEnd(start);
    renderer.RenderStart();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  if (start == 1) { return true; }
  else 
    return false;   

  return false;
}


bool Game::GameEnd(Controller const &controller, Renderer &renderer, 
                      std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  int start = 0;

  while (start == 0) {
    frame_start = SDL_GetTicks();

    // Input, Render
    controller.HandleInputStartEnd(start);
    int score = GetScore();
    renderer.RenderEnd(score);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  if (start == 1) { return true; }
  else 
    return false;

  return false;
}

/*
Place food function will place items on the grid for the players.
Green is the food to score points, Brown is the morgue which ends the game,
Yellow is a safe way to shed length and slow down.
*/
void Game::PlaceFood() {
  int x, y;
  int x1, y1; // Lemon Placement
  int x2, y2; // Morgue Placement
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    
    x1 = random_w(engine);
    y1 = random_h(engine);

    x2 = random_w(engine);
    y2 = random_h(engine);

    // Check that the location is not occupied by a snake item before placing
    // food.
    if ((!snake.SnakeCell(x, y)) && (!snake.SnakeCell(x1, y1)) & (!snake.SnakeCell(x2, y2))) {
      food.x = x;
      food.y = y;

      lemon.x = x1;
      lemon.y = y1;

      morgue.x = x2;
      morgue.y = y2;
      return;
    }
  }
}

void Game::Update(bool &running) {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check what's at the current location and update score, speed and grow/shrink the snake

  // If food->grow snake.
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.01;
  }
  // If lemon->shrink snake.
  else if (lemon.x == new_x && lemon.y == new_y) {
    PlaceFood();
    // Shrink snake and decrease speed.
    snake.ShrinkBody();
    snake.speed -= 0.001;
  }
  // Check if there's morgue->kill snake.
  else if (morgue.x == new_x && morgue.y == new_y) {
    snake.alive = false;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::ResetGame(){
    snake.ResetSnake();
    score = 0;
    PlaceFood();
  }