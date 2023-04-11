all: main

main: main.c
	gcc *.c  -g -O3 -Wall -std=c2x  -L/use/lib -lncurses -ltinfo
