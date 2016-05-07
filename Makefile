.PHONY: incl m_affich m_f_exit m_dijkstra laby m_file m_init m_bfs test_module clean
FLAGS=-DUSECOLORS -Wall -g -DPRODUCTION


laby:

	cd laby && make install && cd ..
	
m_affich: m_bfs m_f_exit
	cd m_affich && make install && cd ..

m_file: laby m_init
	cd m_file && make install && cd ..

m_init: 
	cd m_init && make install && cd ..

m_bfs:
	cd m_bfs && make install && cd ..	

m_f_exit:
	cd m_f_exit && make install && cd ..

m_dijkstra:
	cd m_dijkstra && make install && cd ..

test_module: test_module.c m_file m_dijkstra m_affich m_bfs m_f_exit 
	gcc $(FLAGS) -o $@ $< -I include lib/* 

incl:
	if [ ! -d "./include" ]; then\
		mkdir include;\
	fi
	if [ ! -d "./lib" ]; then\
		mkdir lib;\
	fi
	cp -rf m_file/*.h include
	cp -rf laby/*.h include
	cp -rfv m_affich/*.h include
	cp -rf m_bfs/*.h include
	cp -rf m_init/*.h include
	cp -rf m_f_exit/*.h include
	cp -rf m_dijkstra/*.h include

install: incl test_module

test: 
	./test_module -f m_file/graph.txt -s 0x0 -e 3x7 -z 4x8 -m BFS
test1:
	./test_module -f m_file/graph1.txt -s 0x0 -e 6x8 -z 7x9 -m BFS
test2:
	./test_module -f m_file/dij.txt -s 0x0 -e 3x7 -z 4x8 -m Dij
exec: test test1
exec_dij: test2

clean:
	cd laby && make clean && cd ..
	cd m_affich && make clean && cd ..
	cd m_file && make clean && cd ..
	cd m_init && make clean && cd ..
	cd m_f_exit && make clean && cd ..
	cd m_dijkstra && make clean && cd ..
	cd m_bfs && make clean && cd ..
	rm test_module
	cd include && rm * && cd ..
	cd lib && rm * && cd ..
create_sauv:
	cd .. & mkdir sauv_laby

save:
	cp -R -v * ../sauv_laby/ 
