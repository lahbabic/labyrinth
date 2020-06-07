#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "m_file.h"
#include "../m_init/m_init.h"

char 		*remem_t(char *p, int i);
char 		**remem_tt(char **x, int i);

file init_file(){
	file pf;
	pf = (file)malloc(sizeof(struct file_s));
	pf->p = (char**)malloc(sizeof(char*));
	pf->p[0] = (char*)malloc(2*sizeof(char));
	return pf;
}
int 		get_int(char *str, int i)
{
	int nb, diz;
	nb = (int)(str[i])%48;
	if(i>=1)
	{
		diz = (int)(str[i-1])%48;
	}
	if((-1 < nb)&&(nb <10)&&(10 < diz))		//s'il ya que des unités
	{
		return nb;
	}
	else if((i>=1)&&(-1 < diz)&&(-1 < nb)&&(nb <10)&&(diz <10)) 	//s'il y a les dizaines
	{
		nb = (diz*10)+nb;
		return nb;
	}
	else{
		return -11;
	}
	return -1;
}

graph		read_file_make_lab_dij(char *name, graph gr)
{
	int i, som, som1, poid= 0, tmp1, tmp2;
	char *str;
	str = (char*)malloc(80*sizeof(char));
	FILE *fp;
	fp = fopen(name,"r");
	if(fp == NULL ){
		printf("Erreur d'ouverture du fichier %s\n",name);
	    exit(-1);
	}
	while(fgets(str, 80, fp)!=NULL){
		i = 0;
		while(str[i]!='\n')
		{
			if (str[i]=='\0')
				break;
			if(str[i]==58)				// si le char c'est ":" prendre le premier sommet  
			{
				tmp1 = get_int(str, i-1);
				if(tmp1<10){						//chercher le sommet dans la matrice sommet
					som = gr->sommet[get_int(str, i-3)][tmp1];
				}
				else if(tmp1>=10)					 
				{
					som = gr->sommet[get_int(str, i-4)][tmp1];
				}
			}
			else if(str[i]==124)		// si le char c'est "|" prendre le deuxieme sommet
			{
				tmp1 = get_int(str, i-1);
				tmp2 = get_int(str, i+2);
				if(tmp1<10){
					som1 = gr->sommet[get_int(str, i-3)][tmp1];
				}
				else if(tmp1>=10)
				{
					som1 = gr->sommet[get_int(str, i-4)][tmp1];
				}
				if(tmp2 == -11)
					poid = get_int(str, i+1);
				else
					poid = get_int(str, i+2);
				if((gr->adj[som][som1] == 0)&&(poid!=0))
					gr->adj[som][som1] = poid;		//remplir la matrice d'adj par le poid de l'arc
				else if((gr->adj[som][som1] == 0)&&(poid==0))
					gr->adj[som][som1] = -1;
					
				printf("(%d:%d)=%d\n",som,som1,poid);
				poid = 0;
			}
			i= i+1;
		}
		for (i = 0; i < 78; ++i)
		{
			str[i] = 32;
		}
		fseek( fp, 0, SEEK_CUR);
	}

	return gr;
}

file 		read_file_make_pointer(char *name)
{
	FILE *fp;
	fp = fopen(name,"r");
	if(fp == NULL ){
		printf("Erreur d'ouverture du fichier %s\n",name);
	    exit(-1);
	}
	char c=' ',b=' '; int i=1; int j=0;
	file pf;
	pf = init_file();
	c = fgetc(fp);
	while(1){ 
		b = fgetc(fp);
		if(b<0){
			i++;
			pf->p[j] = remem_t(pf->p[j],i+1);
			pf->p[j][i-1] = c;
			pf->p[j][i] = '\n';
			pf->p[j][0] = i;
			break;
		}else if((c !='\n')&&(b!=EOF)){
			i++;
			pf->p[j] = remem_t(pf->p[j],i+1);
			pf->p[j][i-1] = c;
			pf->p[j][0] = i;     				//nombre de char dans le tableau
		}else if((c == '\n')&&(b!=EOF)){
			pf->p[j][i]='\n';
			j++;
			pf->p = remem_tt(pf->p, j+1);
			pf->p[j] = (char*)malloc(2*sizeof(char));
			pf->size = j+1;      				//nombre de ligne dans le fichier
			i = 1;
		}
		c = b;
	}
	fclose(fp);
	return pf;
}

char 		**remem_tt(char **x, int i)
{
	char **aux0;
	aux0 = (char**)realloc(x, i*sizeof(char*));
	if(aux0==NULL){
		printf("Erreur d'allocation de memoire'\n");
		exit(-1);
	}
	x = aux0; 
	return x; 
}

char 		*remem_t(char *p, int i)
{
	char *aux;
	aux = (char*)realloc(p, i*sizeof(char));
	if(aux==NULL){
		printf("Erreur d'allocation de memoire'\n");
		exit(-1);
	}
	p = aux; 
	return p; 
}

void 		free_mat_f(file f)
{
	int i;
	for (i = 0; i < f->size; ++i)
	{
		free(f->p[i]);
	}
	free(f->p);
}