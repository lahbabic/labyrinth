FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION
include= ../include
lib= ../lib

m_init.o: m_init.c m_init.h 
	gcc $(FLAGS) -c $< -I $(include) -l $(lib)

install: m_init.o m_init.h
	cp -v m_init.o ../lib

clean:
	rm m_init.o
