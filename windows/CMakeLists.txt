cmake_minimum_required(VERSION 3.17)
project(pbrain-gomoku-ai)

set(CMAKE_CXX_STANDARD 14)

include_directories(../include)

add_executable(pbrain-gomoku-ai
    ../src/Main.cpp
    ../src/Start.cpp
    ../src/Gomoku.cpp
    ../src/Tools.cpp
    ../src/game/Game.cpp
    ../src/game/Cmd.cpp
    ../src/IA/IA.cpp
    ../src/IA/Evaluate.cpp
)

install (TARGETS pbrain-gomoku-ai DESTINATION .)