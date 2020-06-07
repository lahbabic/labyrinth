#include <stdio.h>
#include <stdlib.h>
#include "../laby/laby.h"
#include "m_init.h"
#include "../m_file/m_file.h"

#define Cred  "\x1B[31m"
#define Cwhite  "\x1B[37m"

graph 		init_graph();

graph 		init_graph()
{
	graph gr;
	gr = (graph)malloc(sizeof(struct graph_s));
	gr->I = (int*)malloc(2*sizeof(int));
	gr->O = (int*)malloc(2*sizeof(int));
	gr->size = (int*)malloc(2*sizeof(int));
	return gr;
}

graph 		choose_laby_size()
{
	int n,m;
	graph gr;
	gr = init_graph();
	printf("Veuillez entrer la taille du labyrinthe (nxm): ");
	if(scanf("%dx%d",&n,&m)!=2){
		printf("%sErreur %slors de la saisie!\n", Cred, Cwhite);
		exit(1);
	}
	gr->adj = create_matrix(n*m, n*m);
	gr->size[0] = n;	gr->size[1]	= m;
	return gr;
}

graph 		choose_I_O(graph gr)
{
	int n,m;
	printf("Veuillez choisir la case d'entree et de sortie\n");
	printf("I:");
	if((scanf("%dx%d",&n,&m)!=2)){
		printf("%sErreur %slors de la saisie!\n", Cred, Cwhite);
		exit(1);
	}
	if((n >= gr->size[0])||(m >= gr->size[1])){
		printf("%sErreur%s, veuillez choisir une case inferieur a la taille du labyrinthe!\n", Cred, Cwhite);
		exit(1);
	}
	gr->I[0] = n;	gr->I[1] = m;
	printf("O:");
	if(scanf("%dx%d",&n,&m)!=2){
		printf("%sErreur%s lors de la saisie!\n", Cred, Cwhite);
		exit(1);
	}
	if((n >= gr->size[0])||(m >= gr->size[1])){
		printf("%sErreur%s, veuillez choisir une case inferieur a la taille du labyrinthe!\n", Cred, Cwhite);
		exit(1);
	}
	gr->O[0] = n;	gr->O[1] = m;
	return gr;
}

graph  		create_laby(graph gr, file f)
{
	int i, j=6, som, som_adj , s_i, s_j, s_i0, s_j0;
	for (i = 0; i < f->size; ++i)
	{
		s_i0 = (int)(f->p[i][1])%48;
		s_j0 = (int)(f->p[i][3])%48;
		j= 6;
		while(j+2 < f->p[i][0])
		{
			s_i = (int)(f->p[i][j])%48;
			s_j = (int)(f->p[i][j+2])%48;
			//printf("%d--%d\n",s_i,s_j );
			if((s_i >= gr->size[0])||(s_j >= gr->size[1]))
			{
				printf("%sErreur%s du choix de la taille du labyrinthe ou dans le fichier d'entree.\n", Cred, Cwhite);
				exit(1);
			}
			som = gr->sommet[s_i0][s_j0];
			som_adj = gr->sommet[s_i][s_j];
			gr->adj[som][som_adj] = 1;
			gr->adj[som_adj][som] = 1;
			j = j+4;
		}
	}
	free_mat_f(f);
	return gr;
}

graph 		init_laby(graph gr)
{
	int i, j, c=0;
	gr->sommet = (int **)malloc(gr->size[0]*sizeof(int*));
	for (i = 0; i < gr->size[0]; ++i)
	{
		gr->sommet[i] = (int*)malloc(gr->size[1]*sizeof(int));
	}
	for (i = 0; i < gr->size[0]; ++i)
	{
		for (j = 0; j < gr->size[1] ; ++j)
		{
			gr->sommet[i][j] = c;
			c++;
		}
		
	}
	return gr;
}




/*
int 		main(int argc, char const *argv[])
{
	//int i=0,j=0;
	int n;
	file f;
	graph gr;
	gr = choose_laby_size();
	gr = choose_I_O(gr);
	f = read_file_make_pointer("../m_file/graph.txt");
	for (i = 0; i < (f->size) ; ++i)
	{
		for (j = 1; j <= (f->p[i][0]); ++j)
		{
			printf("%c",f->p[i][j] );
		}
	}
	gr = init_laby(gr);
	n = gr->size[0]*gr->size[1];
	gr = create_laby(gr, f);
	print_matrix(gr->adj, n, n);
	free(f);
	return 0;
}
*/