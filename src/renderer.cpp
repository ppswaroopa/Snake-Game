#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL with Audio
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
    std::cerr << "SDL_Mixer Initialization Error: " << Mix_GetError() << "\n";
  }
  
  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  Mix_Quit(); // Destroy Music Object
  SDL_Quit(); // Destroy SDL Obkect
}

void Renderer::Render(Snake const snake, SDL_Point const &food, 
                      SDL_Point const &lemon, SDL_Point const &morgue) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food as Green
  SDL_SetRenderDrawColor(sdl_renderer, 0x5C, 0xE4, 0x1A, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render Lemon as Yellow
  SDL_SetRenderDrawColor(sdl_renderer, 0xFA, 0xFA, 0x33, 0xFF);
  block.x = lemon.x * block.w;
  block.y = lemon.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render Morgue as Brown
  SDL_SetRenderDrawColor(sdl_renderer, 0xC0, 0x56, 0x20, 0xFF);
  block.x = morgue.x * block.w;
  block.y = morgue.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderStart() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Initialize TTF
  TTF_Init();
  if (TTF_Init() < 0) {
    std::cerr<<"Error Initializing SDL_ttf: "<< TTF_GetError() <<"\n";
  }

  std::string basePath = SDL_GetBasePath();
  std::string fontPath = basePath + "fonts/SummerPixel.ttf";

  TTF_Font* font = TTF_OpenFont((basePath + "fonts/SummerPixel.ttf").c_str(),32);
  if (!font) {
    std::cerr<<"Failed to load font: "<< TTF_GetError() <<"\n";
  }

  TTF_Font* game_font = TTF_OpenFont((basePath + "fonts/Debrosee-ALPnL.ttf").c_str(),56);
  if (!game_font) {
    std::cerr<<"Failed to load font: "<< TTF_GetError() <<"\n";
  }
  
  // Create an SDL_Surface with the text
  SDL_Color textColor = {255, 255, 255}; // White color
  SDL_Surface* gameTitle = TTF_RenderText_Solid(game_font, "Snake", textColor);
  SDL_Surface* startTextSurface = TTF_RenderText_Solid(font, "Press ENTER to START", textColor);
  SDL_Surface* quitTextSurface = TTF_RenderText_Solid(font, "Press ESC to Quit", textColor);
  if ( !startTextSurface or ! quitTextSurface) {
	  std::cerr << "Failed to render text: " << TTF_GetError() << "\n";
  }

  // Create an SDL_Texture from the surface
  SDL_Texture* startTextTexture = SDL_CreateTextureFromSurface(sdl_renderer, startTextSurface);
  SDL_Texture* quitTextTexture = SDL_CreateTextureFromSurface(sdl_renderer, quitTextSurface);
  SDL_Texture* gameTitleTextTexture = SDL_CreateTextureFromSurface(sdl_renderer, gameTitle);

  // get dimensions of the Game Title
  int GametextWidth = gameTitle->w;
  int GametextHeight = gameTitle->h;

  // get dimensions of the StartText
  int StextWidth = startTextSurface->w;
  int StextHeight = startTextSurface->h;

  // get dimensions of the StartText
  int QtextWidth = quitTextSurface->w;
  int QtextHeight = quitTextSurface->h;

  // For positioning at the center
  SDL_Rect GametextRect;
  GametextRect.x = screen_width / 2 - GametextWidth / 2;
  GametextRect.y = screen_height / 4;
  
  // For positioning at the center
  SDL_Rect StextRect;
  StextRect.x = screen_width / 2 - StextWidth / 2;
  StextRect.y = screen_height / 2 - (GametextHeight + StextHeight + QtextHeight) / 2;

  SDL_Rect quitTextRect;
  quitTextRect.x = screen_width / 2 - QtextWidth / 2;
  quitTextRect.y = screen_height / 2 - (GametextHeight + StextHeight + QtextHeight) / 2 + 30;

  // Set the width and height of the destination rectangle
  GametextRect.w = GametextWidth;
  GametextRect.h = GametextHeight;
  StextRect.w = StextWidth; // Use the width of the text surface
  StextRect.h = StextHeight; // Use the height of the text surface
  quitTextRect.w = QtextWidth;
  quitTextRect.h = QtextHeight;

  SDL_RenderCopy( sdl_renderer, gameTitleTextTexture, NULL, &GametextRect);
  SDL_RenderCopy( sdl_renderer, startTextTexture , NULL, &StextRect);
  SDL_RenderCopy( sdl_renderer, quitTextTexture , NULL, &quitTextRect);

  // Cleanup the surface and font
  SDL_FreeSurface(startTextSurface);
  TTF_CloseFont(font);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::RenderEnd(int score) {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Initialize TTF
  TTF_Init();
  if (TTF_Init() < 0) {
    std::cout<<"Error Initializing SDL_ttf: "<< TTF_GetError() <<"\n";
  }

  std::string basePath = SDL_GetBasePath();
  TTF_Font* font = TTF_OpenFont((basePath + "fonts/SummerPixel.ttf").c_str(),32);
  if (!font) {
    std::cout<<"Failed to load font: "<< TTF_GetError() <<"\n";
  }
  
  std::string score_string = "Your score is " + std::to_string(score);
  // Create an SDL_Surface with the text
  SDL_Color textColor = {255, 255, 255}; // White color
  SDL_Surface* startTextSurface = TTF_RenderText_Solid(font, "Game Over", textColor);
  SDL_Surface* quitTextSurface = TTF_RenderText_Solid(font, score_string.c_str(), textColor);
  SDL_Surface* restartTextSurface = TTF_RenderText_Solid(font, "Restart? Press ENTER", textColor);
  if ( !startTextSurface or ! quitTextSurface) {
	  std::cout << "Failed to render text: " << TTF_GetError() << "\n";
  }

  // Create an SDL_Texture from the surface
  SDL_Texture* startTextTexture = SDL_CreateTextureFromSurface(sdl_renderer, startTextSurface);
  SDL_Texture* quitTextTexture = SDL_CreateTextureFromSurface(sdl_renderer, quitTextSurface);
  SDL_Texture* restartTextTexture = SDL_CreateTextureFromSurface(sdl_renderer, restartTextSurface);

  // get dimensions of the StartText
  int StextWidth = startTextSurface->w;
  int StextHeight = startTextSurface->h;

  // get dimensions of the StartText
  int QtextWidth = quitTextSurface->w;
  int QtextHeight = quitTextSurface->h;

  // get dimensions of the StartText
  int RtextWidth = restartTextSurface->w;
  int RtextHeight = restartTextSurface->h;

  // For positioning at the center
  SDL_Rect StextRect;
  StextRect.x = screen_width / 2 - StextWidth / 2;
  StextRect.y = screen_height / 2 - (StextHeight + QtextHeight + QtextHeight) / 2;

  SDL_Rect quitTextRect;
  quitTextRect.x = screen_width / 2 - QtextWidth / 2;
  quitTextRect.y = screen_height / 2 - (StextHeight + QtextHeight + QtextHeight) / 2 + 30;

  SDL_Rect restartTextRect;
  restartTextRect.x = screen_width / 2 - RtextWidth / 2;
  restartTextRect.y = screen_height / 2 - (StextHeight + QtextHeight + QtextHeight) / 2 + 70;

  // Set the width and height of the destination rectangle
  StextRect.w = StextWidth; // Use the width of the text surface
  StextRect.h = StextHeight; // Use the height of the text surface
  quitTextRect.w = QtextWidth;
  quitTextRect.h = QtextHeight;
  restartTextRect.w = RtextWidth;
  restartTextRect.h = RtextHeight;

  SDL_RenderCopy( sdl_renderer, startTextTexture , NULL, &StextRect);
  SDL_RenderCopy( sdl_renderer, quitTextTexture , NULL, &quitTextRect);
  SDL_RenderCopy( sdl_renderer, restartTextTexture , NULL, &restartTextRect);

  // Cleanup the surface and font
  SDL_FreeSurface(startTextSurface);
  TTF_CloseFont(font);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}