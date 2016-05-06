FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION


laby.o: laby.c laby.h 
	gcc $(FLAGS) -c $^

install: laby.o laby.h
	cp -v laby.o ../lib
	cp -v laby.h ../include

clean:
	rm laby.o
	rm laby.h.gch