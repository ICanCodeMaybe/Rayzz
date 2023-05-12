cmake_minimum_required(VERSION 3.18.1)
project(rayzz)

set(RAYZZ_CPP src/main.cpp)
set(CUBE_INCLUDE_DIR src/)

add_executable(${PROJECT_NAME} ${RAYZZ_CPP})

