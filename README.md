# Snake Game

This is the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* sudo apt-get install libsdl2-ttf-dev

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## Scope & Implementations

I set out to add more features and make the game interesting.
1. Add <b>Boosts & Penalties</b> to add dynamism.
2. Play game for longer.
3. Add Time based challenges.
4. Add game music.
5. Make all game features accessible inside the window.

I have successfully implemented the 1st& 2nd feature. Rest of the features will be implemented later.

### Boosts and Penalties
In the game Green blocks are food, they grow the length of the snake and also increase speed of movement. Brown block is the Morgue, which when passed over will kill the snake and the game will end. Yellow blocks give a chance to decrease speed slightly and reduce length while still maintaining the score. As the snake keeps eating the food the speed will be difficult to manage so the player can use this as a way to keep them in the game.

### Play game for longer
Game can now be played for as long as the player wants to and the highest score will be displayed at the end. Player can press 'ESC' key or close the application to quit.


### Expected Behavior
The game starts and spawns the Snake(Blue), a Food block(Green), a Lemon(Shrinking Food - Yellow) & a Morgue(Kills - Brown). Player can use the keyboard arrow keys to change the direction of the snake travel.
* Eating Green colored block scores a point and increases the length and speed of the snake.
* Eating Yellow colored block scores no points and decreases the length of the snake.
* Eating Brown colored block kills the snake and ends the game.

### Rubric Points Addressed

1. Loops, Function, I/O

    Project uses Game Design Pattern and involves the Input-Update-Render loop that runs as the core Game loop. Using SDL Library Poll Event function keypresses from the player are used to change the direction of the snake movement.

    HighScore is a function from Game class that displays the highest score after the game ends.

    ShrinkBody is a function from Snake class that reduces the length of the snake body when the snake eats the Lemon.

    ResetSnake is a function from Snake class that resets the game. 

2. Object Oriented Programming

    Project is organized to use classes and the class objects are used to dynamically change game play. Ex: ShrinkBody function which is called when the snake eats the lemon (yellow blocks) it sets the class private variable "shrinking" to true which is used by the UpdateBody function of the Snake class.

    HighScore uses the ScoreBoard vector that is private to the Game class to return the highest score out of all the tries from the player. Scoreboard variable is abstracted from other uses and only functions defined in the class like HighScore are able to use the data.

    ResetSnake function modifies values of the private variable back to their original values acting as a safe access to the variables. 

3. Memory Management

    To prevent unncesary copying of class objects, on HighScore, ResetSnake object is passed by reference to the functions.

4. Concurrency

    HandleInput function is executed on a seperate thread. User inputs are now handled by a seperate thread.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
