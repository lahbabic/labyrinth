FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION

include= ../include
lib= ../lib

m_f_exit.o: m_f_exit.c m_f_exit.h 
	gcc $(FLAGS) -c $< -I $(include) -l $(lib) m_f_exit.h

install: m_f_exit.o m_f_exit.h
	cp -v m_f_exit.o ../lib

clean:
	rm m_f_exit.o
	rm m_f_exit.h.gch
