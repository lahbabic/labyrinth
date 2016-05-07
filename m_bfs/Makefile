FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION

include= ../include
lib= ../lib

m_bfs.o: m_bfs.c m_bfs.h 
	gcc $(FLAGS) -c $< -I $(include) -l $(lib) m_bfs.h

install: m_bfs.o m_bfs.h
	cp -v m_bfs.o ../lib

clean:
	rm m_bfs.o
	rm m_bfs.h.gch
