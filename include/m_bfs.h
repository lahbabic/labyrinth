
//liste d'ouvert et de fermer
typedef struct liste_s *liste;
struct liste_s{	
	int som;	//	le sommet 
	int suc;	//  s'est successeur
	liste s;
};
//arbre bfs ou chaque sommet peut avoir 4 successeur
typedef struct tree_s *tree;
struct tree_s{
	int s;
	tree suc0;
	tree suc1;
	tree suc2;
	tree suc3;
};

tree 		bfs();
tree 		search_tree(tree a, int som);
void 		free_tree(tree root);