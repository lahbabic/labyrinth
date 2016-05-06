struct graph_s{
	int **adj;
	int *I;
	int *O;
	int *size;
	int **sommet;
};
typedef struct file_s *file;
typedef struct graph_s *graph;
graph 		choose_matrix_size_and_create();
graph 		init_laby(graph gr);
graph  		create_laby(graph gr, file f);
graph 		choose_laby_size();
graph 		choose_I_O(graph gr);

graph 		init_graph();			//a enlever