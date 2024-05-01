cmake_minimum_required(VERSION 3.10)

project(FlappyBird)

add_link_options(-lglut -lGL -lGLU -lGLEW)
add_executable(main main.cpp bird.cpp generator.cpp map.cpp pylon.cpp)