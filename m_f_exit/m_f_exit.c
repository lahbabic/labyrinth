#include <stdio.h>
#include <stdlib.h>
#include "../include/m_affich.h"
#include "../include/m_bfs.h"
#include "../include/m_init.h"
#include "m_f_exit.h"

typedef void *dont_know_type;


dont_know_type 		find(tree root, int *ex, int sortie, int i);
int 		*s_tab(int *ex);


int  		*find_exit(tree root, graph gr)
{
	int sortie, n = gr->size[0]*gr->size[1];
	int i=0;
	int *ex = (int*)malloc(n*sizeof(int));
	for (i = 0; i < n; ++i)
	{
		ex[i] = -1;
	}
	sortie = gr->sommet[gr->O[0]][gr->O[1]];
	//printf("%d\n",sortie );
	ex = find(root, ex, sortie, 0);
	ex = s_tab(ex);
	return ex;
}

int 		*s_tab(int *ex)
{
	int i, j;
	if(ex==0){
		printf("Impossible de trouver la sortie, arbre pas connexe!!\n");
		exit(0);
	}
	for (i = 1; i < ex[0]; ++i)
	{
		if(ex[i] == -1){
			for (j = i; j < ex[0]; j++)
			{
				ex[j] = ex[j+1];
			}
			ex[0]= ex[0]-1;
		}
	}
	return ex;
}


dont_know_type 		find(tree root, int *ex, int sortie, int i)
{
	ex[0] = i;
	tree tmp, tmp1, tmp2, tmp3;
	tree sauv=root;
	if(root)
	{
		sauv = root;
		if(root->s == sortie){
			i = i+1;
			ex[0] = i;
			ex[i] = root->s;
			//printf("%d et i = %d\n",ex[i],i );
			return ex;
		}
		else{
			if((tmp = find(root->suc0, ex, sortie, i= i+1))&&tmp){
				ex[i] = root->s;
				//printf("%d pp 0: %d\n",ex[i],i );
				return tmp;
			}
			else if((!tmp)&&(tmp1 = find(root->suc1, ex, sortie, i= i+1))){
				ex[i] = root->s;
				//printf("%d pp 1: %d\n",ex[i],i );
				return tmp1;
			}
			else if((!tmp)&&(!tmp1)&&(tmp2= find(root->suc2, ex, sortie, i= i+1))){
				ex[i] = root->s;
				//printf("%d pp 2: %d\n",ex[i],i );
				return tmp2;
			}
			else if((!tmp)&&(!tmp1)&&(!tmp2)&&(tmp3 = find(root->suc3, ex, sortie, i= i+1))) {
				ex[i] = root->s;
				//printf("%d pp 3: %d\n",ex[i],i );
				return tmp3;
			}
		}
	}
	else if((!root)&&(!in_tab(ex,sortie)&&(sauv))){
		root = sauv;
		return find(root, ex, sortie, i);
	}
	return 0;
}

