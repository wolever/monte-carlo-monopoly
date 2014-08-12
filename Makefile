OPTS=-O2 -Wall

all: monopoly

monopoly: monopoly.c
	gcc $(OPTS) monopoly.c -o monopoly

debug: monopoly.c
	gcc $(OPTS) -O0 -g monopoly.c -o monopoly
	gdb monopoly
