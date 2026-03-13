CC = g++
CC_FLAGS = -Wall -Wextra -g -std=c++17
DEBUG_FLAGS = -DDEBUG=0

SRC = main.cc assembler.cc

all:
	$(CC) $(SRC) $(CC_FLAGS) $(DEBUG_FLAGS) -o svm

clean:
	rm -f svm