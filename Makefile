# Makefile for OS assignments
#
#
all:
	gcc -o p2 p2.c memoria.c memoria_list.c list_procesos.c procesos.c -g -Wall
	

clean:
	rm  p1
