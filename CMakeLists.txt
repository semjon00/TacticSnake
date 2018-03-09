cmake_minimum_required(VERSION 3.14)
project(TacticSnake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc -static")

add_executable(TacticSnake main.cpp engine.cpp engine.h lobby.cpp lobby.h net.cpp net.h snake.cpp snake.h version.h)
