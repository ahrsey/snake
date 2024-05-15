.PHONY: build

CC = clang

build:
	$(CC) snake.c -o snake -Wall -Wextra -pedantic -g -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

clean:
	rm ./snake
