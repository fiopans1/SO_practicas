# Makefile for OS assignments
#
#
all:
	gcc -o p1 p1.c memoria.c memoria_list.c -g -Wall
	

clean:
	rm  p1
