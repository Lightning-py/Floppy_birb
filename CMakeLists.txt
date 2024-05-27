cmake_minimum_required(VERSION 3.10)
project(FlappyBird VERSION 0.1.0 LANGUAGES CXX)


set(HEADERS headers)
set(SOURCES sources)

set(SOURCE_FILES ${SOURCES}/bird.cpp ${SOURCES}/generator.cpp ${SOURCES}/map.cpp ${SOURCES}/pylon.cpp ${SOURCES}/bonus.cpp ${SOURCES}/grid.cpp ${SOURCES}/font.cpp)

include_directories(${HEADERS})


set(GLUTILS ${HEADERS}/glUtils.hpp ${SOURCES}/glUtils.cpp)
set(RANDOMUTILS ${HEADERS}/randomUtils.hpp ${SOURCES}/randomUtils.cpp)

add_library(LIB_UTILS STATIC ${GLUTILS} ${RANDOMUTILS})

add_link_options(-lglut -lGL -lGLU -lGLEW)
add_executable(FlappyBird main.cpp ${SOURCE_FILES})

target_link_libraries(FlappyBird LIB_UTILS)
