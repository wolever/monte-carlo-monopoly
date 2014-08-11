OPTS=-O2 

all: monopoly

monopoly: monopoly.c
	gcc $(OPTS) monopoly.c -o monopoly

debug: monopoly.c
	gcc $(OPTS) -g monopoly.c -o monopoly
	gdb monopoly
