CC = g++
CFLAGS = -Wall -Wextra -Wpedantic -fsanitize=address

BUILD_DIRECTORY = ./build/
EXE_NAME = $(BUILD_DIRECTORY)main
LOG_NAME = log.txt

all: run_

run_: dir execute

run:
	$(EXE_NAME)

dir:
	mkdir -p $(BUILD_DIRECTORY)
	touch $(LOG_NAME)

build: clean main.cpp
	date +"[%Y-%m-%d %T]" >> $(LOG_NAME)
	$(CC) $(CFLAGS) -c main.cpp -o $(BUILD_DIRECTORY)main.o 2>> $(LOG_NAME)
	$(CC) $(CFLAGS) $(BUILD_DIRECTORY)main.o -o $(EXE_NAME) -lglut -lGL -lGLU -lGLEW 2>> $(LOG_NAME)
	rm $(BUILD_DIRECTORY)main.o


execute: build 
	$(EXE_NAME)


clean:
	rm -rf $(BUILD_DIRECTORY)*

cleanlog:
	rm log.txt
	touch log.txt
