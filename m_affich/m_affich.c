#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/m_init.h"
#include "../include/m_bfs.h"
#include "../include/m_f_exit.h"
#include "m_affich.h"


#define Cnormal  "\x1B[0m"
#define Cred  "\x1B[31m"
#define Cgreen  "\033[01;32m"
#define Cyellow  "\x1B[33m"
#define Cblue  "\x1B[34m"
#define Cmagenta  "\x1B[35m"
#define Ccyan "\x1B[36m"
#define Cwhite  "\x1B[37m"

//typedef enum {false, true} bool;
bool		in_tab(int *ex, int x);


bool		in_tab(int *ex, int x)
{
	int i;
	for (i = 1; i <= ex[0]; ++i)
	{
		if(ex[i]==x)
			return true;
	}
	return false;
}
void		affichage(graph gr, int *ex, tree root)
{
	printf("\033[2J");
	int i,j,x;
	if(gr->I[0]>gr->O[0]){
		x = gr->I[0];
		gr->I[0] = gr->O[0];
		gr->O[0] = x;
		x = gr->I[1];
		gr->I[1] = gr->O[1];
		gr->O[1] = x;
	}
	else if(gr->I[1]>gr->O[1]){
		x = gr->I[0];
		gr->I[0] = gr->O[0];
		gr->O[0] = x;
		x = gr->I[1];
		gr->I[1] = gr->O[1];
		gr->O[1] = x;
	}		
	for (i = 0; i < gr->size[0]-1; ++i)
	{
		for (j = 0; j < gr->size[1]; ++j)
		{
			if(in_tab(ex, gr->sommet[i][j+1])&&
							(gr->adj[gr->sommet[i][j+1]][ gr->sommet[gr->I[0] ][gr->I[1] ]] ==1)){
				free(ex);		ex =NULL;		free_tree(root);	
				gr->I[0] = i;		gr->I[1] = j+1;
				root = bfs(gr);
				ex = find_exit(root,gr);
				printf("\033[2J");
				affiche(gr, ex);
				usleep(100000);
			}
			else if(in_tab(ex, gr->sommet[i][j-1])&&
							(gr->adj[gr->sommet[i][j-1]][ gr->sommet[gr->I[0] ][gr->I[1] ]] ==1)){
				free(ex);		ex =NULL;		free_tree(root);	
				gr->I[0] = i;		gr->I[1] = j-1;
				root = bfs(gr);
				ex = find_exit(root,gr);
				printf("\033[2J");
				affiche(gr, ex);
				usleep(100000);
				j= j-4;	
			}
			else if((i+1<gr->size[0]-1)&&in_tab(ex, gr->sommet[i+1][j])&&
							(gr->adj[gr->sommet[i+1][j]][ gr->sommet[gr->I[0] ][gr->I[1] ]] ==1)){
				free(ex);		ex =NULL;		free_tree(root);	
				gr->I[0] = i+1;		gr->I[1] = j;
				root = bfs(gr);
				ex = find_exit(root,gr);
				printf("\033[2J");
				affiche(gr, ex);
				usleep(100000);
				i = i+1;	j=j-1;
			}
			else if((i+1==gr->size[0]-1)&&in_tab(ex, gr->sommet[i+1][j])&&
							(gr->adj[gr->sommet[i+1][j]][ gr->sommet[gr->I[0] ][gr->I[1] ]] ==1)){
				free(ex);		ex =NULL;		free_tree(root);	
				gr->I[0] = i+1;		gr->I[1] = j;
				root = bfs(gr);
				ex = find_exit(root,gr);
				printf("\033[2J");
				affiche(gr, ex);
				usleep(100000);
				i = i+1;	j=j-1;
			}
			else if(in_tab(ex, gr->sommet[i-1][j])&&
							(gr->adj[gr->sommet[i-1][j]][ gr->sommet[gr->I[0] ][gr->I[1] ]] ==1)){
				free(ex);		ex =NULL;		free_tree(root);	
				gr->I[0] = i-1;		gr->I[1] = j;
				root = bfs(gr);
				ex = find_exit(root,gr);
				printf("\033[2J");
				affiche(gr, ex);
				usleep(100000);
				i = i-1;	j=j-1;						//aaaaaaaaaaaaaaaaaaa revoir		
			}
		}
	}
}

void 		affiche(graph gr, int *ex)
{
	int i,j,n,m,s0,s1;
	n = gr->size[0];
	m = gr->size[1];
	printf("\n");
	for (i = 0; i < m; ++i)
	{
		printf("%s+ - ",Cwhite);
	}
	printf("%s+\n",Cwhite);
	for (i = 0; i < n; ++i)
	{	
		printf("%s|",Cwhite);
		for (j = 0; j < m-1; ++j)
		{

			if ((gr->I[0]==i)&&(gr->I[1]==j)){
				printf("%s'*'",Cyellow);
			}
			else if((gr->O[0]==i)&&(gr->O[1]==j)){
				printf("%s O ",Cyellow);
			}
			else if((i<n-1)&&((ex!=NULL)&&in_tab(ex,gr->sommet[i][j]))&&((in_tab(ex,gr->sommet[i][j+1])
						   ||in_tab(ex,gr->sommet[i+1][j])||in_tab(ex,gr->sommet[i-1][j])))){
					printf("%s * ",Ccyan);
			}
			else if((i==n-1)&&(in_tab(ex,gr->sommet[i][j])
						  ))
				printf("%s * ",Ccyan);
			else
				printf("   ");

			s0 = gr->sommet[i][j];
			s1 = gr->sommet[i][j+1];
			if(gr->adj[s0][s1]==1)
				printf(" ");
			else if(gr->adj[s0][s1]==0)
				printf("%s|",Cwhite);

			if(j+1==m-1){
				if((gr->O[0]==i)&&(gr->O[1]==j+1))
					printf("%s O %s|",Cyellow,Cwhite);
				else if((gr->I[0]==i)&&(gr->I[1]==j+1))
					printf("%s'ô'%s|",Cyellow,Cwhite);
				else if((ex!=NULL)&&in_tab(ex,gr->sommet[i][j+1])&&in_tab(ex,gr->sommet[i+1][j+1]))
					printf("%s * %s|",Ccyan,Cwhite );
				else
					printf("   %s|",Cwhite);	
			}


		}
		printf("\n");
		for (j = 0; j < m; ++j)
		{
			if (i< n-1)
			{
				s0 = gr->sommet[i][j];
				s1 = gr->sommet[i+1][j];
				if(gr->adj[s0][s1]==0)
					printf("%s+ - ",Cwhite);
				else if((gr->adj[s0][s1]==1)&&((ex!=NULL)&&in_tab(ex,s0)&&in_tab(ex,s1)))
					printf("%s+   ",Cwhite);
				else 
					printf("%s+   ",Cwhite);
				/*else if((ex!=NULL)&&in_tab(ex,s0)&&in_tab(ex,s1)){
					printf("%s+ . ",Cgreen );*/
			}
		}
		if (i<n-1)
			printf("+\n");
	}
	for (i = 0; i < m; ++i)
	{
		printf("%s+ - ",Cwhite);
	}
	printf("+\n");
	printf("%s\n",Cwhite );

}