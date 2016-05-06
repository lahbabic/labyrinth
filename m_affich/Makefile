FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION

include= ../include
lib= ../lib

m_affich.o: m_affich.c m_affich.h 
	gcc $(FLAGS) -c $< -I $(include) -l $(lib)

install: m_affich.o m_affich.h
	cp -v m_affich.o ../lib
	cp -v m_affich.h ../include

clean:
	rm m_affich.o