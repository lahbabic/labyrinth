FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION

include= ../include
lib= ../lib

m_dijkstra.o: m_dijkstra.c m_dijkstra.h 
	gcc $(FLAGS) -c $< -I $(include) -l $(lib)

install: m_dijkstra.o m_dijkstra.h
	cp -v m_dijkstra.o ../lib
	cp -v m_dijkstra.h ../include

clean:
	rm m_dijkstra.o
