#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing && !shrinking) {
    // Remove the tail from the vector.
    body.erase(body.begin());
    // std::cout<<"Snake Size "<<size<<"\n";
  } 
  else if (shrinking) {
    if (size <= 1)
    {
      body.erase(body.begin());
      shrinking = false;
    }
    else
    {
      body.erase(body.begin());
      body.erase(body.begin());
      size -= 1;
      shrinking = false;
      // std::cout<<"Snake Size "<<size<<"\n";
    }
  }
  else {
    growing = false;
    size++;
    // std::cout<<"Snake Size "<<size<<"\n";
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

/*
Grow Body sets the value of boolean 'growing' to true.
This allows the UpdateBody function to add body length.
*/
void Snake::GrowBody() { growing = true; }

/*
Shrink Body sets the value of boolean 'shrinking' to true.
This allows the UpdateBody function to reduce body length.
*/
void Snake::ShrinkBody() { shrinking = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::ResetSnake(Snake& obj){
  alive = true;
  head_x = grid_height/2;
  head_y = grid_width/2;
  while (size > 1){
    body.erase(body.begin());
    size -= 1;
  }
}