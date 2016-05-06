
struct file_s{
	char **p;
	int size;
};
typedef struct file_s *file;
typedef struct graph_s *graph;

file 		read_file_make_pointer(char *name);
void 		free_mat_f(file f);
graph		read_file_make_lab_dij(char *name, graph gr);
int 		get_int(char *str, int i);
