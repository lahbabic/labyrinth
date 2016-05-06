typedef struct graph_s *graph;
typedef struct tree_s *tree;
typedef enum {false, true} bool;
void 		affiche(graph gr,int *ex);
bool		in_tab(int *ex, int x);
void		affichage(graph gr, int *ex, tree root);