all:
	make run
	make debug

run: project1
	./project1

debug:
	./project1 debug

project1: project1.o iofunction.o
	gcc -o project1 project1.o iofunction.o

project1.o: project1.c
	gcc -ansi -pedantic-errors -Wall -c project1.c

iofunction.o: iofunction.c
	gcc -ansi -pedantic-errors -Wall -c iofunction.c

clean:
	rm project1.o iofunction.o
