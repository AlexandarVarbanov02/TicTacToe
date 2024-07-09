cmake_minimum_required(VERSION 3.13)
project(tic_tac_toe)
set(PROJECT_NAME tic_tac_toe_project)

set(SOURCES
    main.cpp
    tic_tac_toe.cpp
    tic_tac_toe_computer.cpp)

set(HEADERS
    tic_tac_toe.hpp
    tic_tac_toe_computer.hpp)

add_executable(Game ${SOURCES} ${HEADERS})