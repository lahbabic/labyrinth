#include <stdio.h>
#include <stdlib.h>
#include "../include/m_init.h"
#include "m_bfs.h"


typedef enum {false, true} bool;



liste 		create_liste(liste x, int som, int suc);
bool		som_dans_ferme(liste tmp, int s);
liste 		mettre_succ_dans_O(liste l, int succ, graph gr);
tree 		add_branche(tree a, int som);
tree 		search_tree(tree a, int som);
tree 		mettre_som_dans_arbre(tree a, tree root, liste l);



bool		som_dans_ferme(liste tmp, int s)
{
	while(tmp){
		if (s == tmp->som)
			return true;
		tmp = tmp->s;
	}
	return false;	
}

liste 		create_liste(liste x, int som, int suc)
{
	x = malloc(sizeof(struct liste_s));
	if (x){
		x->som = som;	//sommet 
		x->suc = suc;
		x->s = NULL;
	}
	return x;
}

tree 		add_branche(tree a, int som)
{
	a = malloc(sizeof(struct tree_s));
	if(a){
		a->s = som;
		a->suc0 = NULL;
		a->suc1 = NULL;
		a->suc2 = NULL;
		a->suc3 = NULL;
	}
	return a;
}

tree 		mettre_som_dans_arbre(tree a, tree root, liste l)
{

	int sp = a->s;								//sommet a traiter
	while((sp!=l->som)&&(l->s))
		l = l->s;
	while((sp==l->som))
	{
		if(!search_tree(root,l->suc)){						//si le sommet n'est pas deja dans l'arbre
			if (!a->suc0){								//si la branche n'existe pas
				a->suc0 = add_branche(a->suc0, l->suc);					//creer une branche 
				//printf("1 br %d\n",a->suc0->s);
			}
			else if ((!a->suc1) && (a->suc0)){
				a->suc1 = add_branche(a->suc1, l->suc);
				//printf("2 br %d\n",a->suc1->s);
			}
			else if ((!a->suc2) && (a->suc1) && (a->suc0)){
				a->suc2 = add_branche(a->suc2, l->suc);
				//printf("3 br %d\n",a->suc2->s);
			}
			else if ((!a->suc3) && (a->suc2) && (a->suc1) && (a->suc0)){
				a->suc3 = add_branche(a->suc3, l->suc);
				//printf("4 br %d\n",a->suc3->s);
			}
		}
		if(l->s)
			l = l->s;
		else if(l)
			break;
	}	
	return a;
}

void 		free_tree(tree root)
{
	while(1){

		if(root==NULL)
			break;
		else if (root->suc0){								
			free_tree(root->suc0);	
			root->suc0 = NULL;			
		}
		else if (root->suc1){
			free_tree(root->suc1);
			root->suc1 = NULL;
		}
		else if (root->suc2) {
			free_tree(root->suc2);
			root->suc2 = NULL;
		}
		else if (root->suc3){
			free_tree(root->suc3);
			root->suc3 = NULL;
		}
		else{
			free(root);
			root = NULL;
		}
	}
}

tree 		search_tree(tree a, int som)		// recherche recursive dans l'arbre
{
	tree tmp, tmp1, tmp2, tmp3;
	if(a)
	{
		if(a->s == som)
			return a;
		else{
			if((tmp = search_tree(a->suc0, som))){ // si tmp n'est pas vide
				return tmp;
			}
			else if((!tmp)&&(tmp1 = search_tree(a->suc1, som))){ // tmp vide et tmp1 non vide 
				return tmp1;
			}
			else if((!tmp)&&(!tmp1)&&(tmp2= search_tree(a->suc2, som))){// ...
				return tmp2;
			}
			else if((!tmp)&&(!tmp1)&&(!tmp2)&&(tmp3 = search_tree(a->suc3, som))) {
				return tmp3;
			}
		}
	}
	else return NULL;
	return 0;
}

liste 		mettre_succ_dans_O(liste O, int succ, graph gr)
{
	liste tmp = O;
	int n, i;
	n = gr->size[0]*gr->size[1];
	while (tmp->s){				// tant que tmp->s n'est pas NULL, aller au suivant
		tmp = tmp->s;
	}
	for (i = 0; i < n; ++i)
	{	
		if (gr->adj[succ][i]==1){	// mettre les successeurs 
			tmp->s = create_liste(tmp->s, succ, i);
			tmp = tmp->s;
		}
	}
	return O;
}

liste 		mettre_som_dans_ferme(liste F, int som)
{
	liste tmp = F;
	if(F->som == -1){
		F->som = som;
	}
	else
	{
		while (F->s){
			F = F->s;
		}
		F->s = create_liste(F->s, som, -1);
	}
	return tmp;
}

liste 		sup_som_O(liste O)
{
	liste tmp;
	if (!O->s){		// si le successeur est NULL
		free(O);
		O = NULL;
		return O;
	}
	else{		// sinon retenir le successeur et free le père
		tmp = O->s;
		free(O);
		O = NULL;
	}
	return tmp;
}

void 		print_tree(tree a)
{
	if(a)
		printf("  %d \n",a->s );
	if(a->suc0)
		print_tree(a->suc0);
	if(a->suc1)
		print_tree(a->suc1);
	if(a->suc2)
		print_tree(a->suc2);
	if(a->suc3)
		print_tree(a->suc3);
}

tree 		bfs(graph gr)
{
	int i, som;
	liste O = NULL, F = NULL;			tree root = NULL, tmp = NULL;
	som = gr->sommet[gr->I[0]][gr->I[1]];		//sommet de depart choisit par l'utilisateur
	O = create_liste(O, som, som);				// liste d'ouvert
	F = create_liste(F, -1,-1);				//liste de fermé
	root = add_branche(root, som);
	tmp  = add_branche(tmp,-1);
	while (O){									// tant que O n'est pas vide
		i = O->suc;
		if (!som_dans_ferme(F, i)){				// si le sommet n'est pas dans fermer
			O = mettre_succ_dans_O(O, i, gr);
			tmp  = search_tree(root, i);		// chercher l'adresse du sommet i dans l'arbre
			if (tmp){
				//printf("search tree ***************** %d = %d\n",i,tmp->s );
				tmp = mettre_som_dans_arbre(tmp, root, O);
			}
			F = mettre_som_dans_ferme(F, i);
		}
		O = sup_som_O(O);
	}
	//printf("Les sommets dans l'arbre\n");
	//print_tree(root);
	//free_tree(root);
	return root;
}
