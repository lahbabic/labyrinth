#include <stdio.h>
#include <stdlib.h>
#include "m_dijkstra.h"
#include "m_file.h"
#include "laby.h"
#include "m_init.h"

int			**remem_tt_int(int **x, int i);
int 		*remem_t_int(int *p, int i);
int 		*min(int *tab, int n);



void 			dijkstra(graph gr)
{
	int i,j,n,i0,som_c;
	int **tmp;
	int *lmb = (int*)malloc(2*sizeof(int)); 
	n = gr->size[0]*gr->size[1];
	lmb = (int**)malloc(sizeof(int*));
	tmp[0] = (int*)malloc(n*sizeof(int));
	som_c = gr->sommet[gr->I[0]][gr->I[1]];
	for (i = 0; i < n; ++i)
	{
		tmp[0][i] = -1;
	}
	do
	{
		printf("som_c = %d\n",som_c );
		lmb = min(gr->adj[som_c],n);
		printf("som_suivant :%d de poid %d\n",lmb[1],lmb[0] );
		som_c = lmb[1];
		for (j = 0; j < n; ++j)
		{
			//if(lmb[0]+)
		}
	}while(som_c!=0);
}

int 		*min(int *tab, int n)
{
	int i;
	int *min = (int*)malloc(2*sizeof(int)); 
	min[0] = 10000000;
	for (i = 0; i < n; ++i)
	{
		if((tab[i]<=min[0])&&(tab[i]!=0)){
			min[0] = tab[i];
			min[1] = i;
		}
	}
	return min;
}
int			**remem_tt_int(int **x, int i)
{
	int **aux0;
	aux0 = (int**)realloc(x, i*sizeof(int*));
	aux0[0]= (int*)malloc(sizeof(int));
	if(aux0==NULL){
		printf("Erreur d'allocation de memoire'\n");
		exit(-1);
	}
	x = aux0; 
	return x; 
}

int 		*remem_t_int(int *p, int i)
{
	int *aux;
	aux = (int*)realloc(p, i*sizeof(int));
	if(aux==NULL){
		printf("Erreur d'allocation de memoire'\n");
		exit(-1);
	}
	p = aux; 
	return p; 
}