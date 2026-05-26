# Classic Snake Game in C++

A lightweight, console-based Snake game written in C++ for Windows. This project features custom boundary physics, real-time input handling, and directional speed pacing to ensure smooth gameplay right inside the command prompt. The game 

## Features
**Scoreline:** The game keeps scorline depending on how much fruit the snake has eaten.
**Smart Grid Boundaries:** Exact edge collision tracking matching the visual matrix layout. Collision possible with the snake's body itself.
**Paced Movement:** Directional delay balancing (faster horizontal tracking, steadier vertical steps).

## How to Compile and Run

Make sure you have `g++` (GCC) installed on your Windows machine (like `w64devkit` or MinGW).

1. Open your terminal or command prompt in the project folder.
2. Compile the source code:
   ```bash
   g++ main.cpp -o snake.exe
3. Start the game
    start snake.exe