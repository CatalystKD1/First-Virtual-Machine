CC = g++
CC_FLAGS = -Wall -Wextra -g -std=c++23
DEBUG_FLAGS = -DDEBUG=1

SRC = main.cc assembler.cc

all:
	$(CC) $(SRC) $(CC_FLAGS) $(DEBUG_FLAGS) -o cvm

clean:
	rm -f cvm