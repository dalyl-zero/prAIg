cmake_minimum_required(VERSION 3.10)

project(prAIg)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SRC src/*h src/*cpp)

add_executable(prAIg ${SRC})