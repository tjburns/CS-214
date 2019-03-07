all: memgrind

mymalloc: mymalloc.c
	gcc -O -g -o mymalloc.o mymalloc.c

memgrind: memgrind.c mymalloc.o mymalloc.h
	gcc -O -g -o memgrind memgrind.c mymalloc.o

clean: 
	rm -f memgrind mymalloc.o