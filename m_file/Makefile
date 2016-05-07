FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION


m_file.o: m_file.c m_file.h 
	gcc $(FLAGS) -c $^

install: m_file.o m_file.h
	cp -v m_file.o ../lib

clean:
	rm m_file.o
	rm m_file.h.gch
