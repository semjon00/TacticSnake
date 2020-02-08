cmake_minimum_required(VERSION 3.14)
project(TacticSnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static -std=c++17")

add_executable(TacticSnake main.cpp engine.cpp engine.h ui.cpp ui.h snake.cpp snake.h version.h GameSettings.cpp GameSettings.h Game.cpp Game.h Player.cpp Player.h)
