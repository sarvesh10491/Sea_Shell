# the compiler: gcc for C program
seashell: seashell.o shell.o builtin.o
	gcc -Wall -o seashell seashell.o shell.o builtin.o -pthread -lm -lrt

seashell.o: seashell.c
	gcc -c seashell.c shell.h

builtin.o: builtin.c
	gcc -c builtin.c builtin.h

shell.o: shell.c
	gcc -c shell.c shell.h
	
clean:
	rm -f seashell *.o *.gch