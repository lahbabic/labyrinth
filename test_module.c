#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "laby/laby.h"
#include "m_init/m_init.h"
#include "m_file/m_file.h"
#include "m_affich/m_affich.h"
#include "m_bfs/m_bfs.h"
#include "m_f_exit/m_f_exit.h"
#include "m_dijkstra/m_dijkstra.h"


void 			BFS(char *size, char *file_name, char *O, char *E);
void			convert_int(char *tmp, int *tmp1);
void 			Dij(char *size, char *file_name, char *O, char *E);
int main(int argc, char *const argv[])
{

						/////////************ BFS ****************/////////
	/*int *ex = NULL;
	file f;
	graph gr;
	tree root = NULL;
	//gr = choose_laby_size();
	gr = init_graph();
	gr->size[0] = 7; 		gr->size[1] = 9;
	gr->adj = create_matrix(63,63);//32
	//gr = choose_I_O(gr);
	gr->I[0] = 6;			gr->I[1] = 8;
	gr->O[0] = 0;			gr->O[1] = 0;
	f = read_file_make_pointer("m_file/graph1.txt");
	gr = init_laby(gr);
	gr = create_laby(gr, f);
	//print_matrix(gr->adj, 32, 32);
	//print_matrix(gr->sommet,gr->size[0],gr->size[1]);
	root = bfs(gr);
	ex = find_exit(root,gr);
	affiche(gr,ex);
	affichage(gr,ex,root);
	*/
						//////////********** Dijkstra *************//////
	/*graph gr;
	gr = init_graph();
	gr->size[0] = 4; 		gr->size[1] = 8;
	gr->I[0] = 0;			gr->I[1] = 0;
	gr->O[0] = 3;			gr->O[1] = 7;
	gr->adj = create_matrix(32,32);
	gr = init_laby(gr);
	gr = read_file_make_lab_dij("m_file/dij.txt", gr);
	print_matrix(gr->adj, 32, 32);
	//affiche(gr,0);
	dijkstra(gr);*/
	int             c;
	char *file_name;
	char *E;		char *O;		char *size;
	const char    * short_opt = ":h:f:m:z:s:e:";
	struct option   long_opt[] =
	{
		{"help",          no_argument,       NULL, 'h'},
		{"file",          required_argument, NULL, 'f'},
		{"size",          required_argument, NULL, 'z'},
		{"start",         required_argument, NULL, 's'},
		{"end",           required_argument, NULL, 'e'},
		{"mode",          required_argument, NULL, 'm'},
		{NULL,            0,                 NULL,  0 }
	};

	while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
	{
		switch(c)
		{
			case -1:       /* no more arguments */
			case 0:        /* long options toggles */
				break;

			case 'f':
				file_name = optarg;
				break;

			case 'e':
				E = optarg;
				break;

			case 's':
				O = optarg;
				break;

			case 'z':
				size = optarg;
				break;

			case 'm':
				if(strcmp(optarg,"BFS")==0){
					BFS(size, file_name, O, E);
				}
				else if(strcmp(optarg,"Dij")==0){
					Dij(size, file_name, O, E);
				}
				break;

			case 'h':
				printf("Usage: %s [OPTIONS]\n", argv[0]);
				printf("  -m, --mode                mode BFS or Dijkstra   (ex: -m BFS / -m Dij)\n");
				printf("  -f, --file                file to construct laby (ex:  m_file/fichier.txt)\n");
				printf("  -z, --size                size of the labyrinth\n");
				printf("  -s, --start               Robby start case\n");
				printf("  -e, --end                 Robby end case\n");
				printf("  -h, --help                print help and exit\n");
				printf("\n");
			return(0);

			case ':':
			case '?':
				fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
				return(-1);

			default:
				fprintf(stderr, "%s: invalid option -- %c\n", argv[0], c);
				fprintf(stderr, "Try `%s --help' for more information.", argv[0]);
				return(-1);
		};
	}
	return 0;
}

void 			Dij(char *size, char *file_name, char *O, char *E)
{
	int n,m;
	graph gr;
	gr = init_graph();
	convert_int(size,gr->size);
	convert_int(E,gr->I);
	convert_int(O,gr->O);

	n = gr->size[0];	m = gr->size[1];
	gr->adj = create_matrix(n*m,n*m);
	gr = init_laby(gr);
	gr = read_file_make_lab_dij("m_file/dij.txt", gr);
	print_matrix(gr->adj, n*m, n*m);
	//affiche(gr,0);
	dijkstra(gr);
}

void 			BFS(char *size, char *file_name, char *O, char *E)
{
	int n,m;
	int *ex = NULL;
	file f;
	graph gr;
	tree root = NULL;
	gr = init_graph();

	convert_int(size,gr->size);
	convert_int(E,gr->I);
	convert_int(O,gr->O);

	n = gr->size[0];	m = gr->size[1];
	gr->adj = create_matrix(n*m,n*m);
	f = read_file_make_pointer(file_name);
	gr = init_laby(gr);
	gr = create_laby(gr, f);
	//print_matrix(gr->adj, 32, 32);
	//print_matrix(gr->sommet,gr->size[0],gr->size[1]);
	root = bfs(gr);
	ex = find_exit(root,gr);
	affiche(gr,ex);
	affichage(gr,ex,root);
}

void			convert_int(char *tmp, int *tmp1)
{
	int n ,m, n1,m1;
	n = (int)tmp[0]-48;
	m = (int)tmp[1]-48;
	if((n<10)&&(0<=n)&&(m<10)){
		tmp1[0] = (10*n)+m;
		n1 = (int)tmp[3]-48;
		m1 = (int)tmp[4]-48;
		if((n1<10)&&(0<=n1)&&(m1<10))
			tmp1[1] = (10*n1)+m1;
		else if((n1<10)&&(0<=n1)&&(m1>10))
			tmp1[1] = n1;
		else{
			printf("Error reading options, please enter integer for (size ,start, end)\n");
			exit(-1);
		}
	}
	else if((n<10)&&(0<=n)&&(m>10)){
		tmp1[0] = n;
		n1 = (int)tmp[2]-48;
		if(tmp[3]==0)
			m1 = -1;
		else
			m1 = (int)tmp[3]-48;
		if((n1<10)&&(0<=n1)&&(m1!=-1))
			tmp1[1] = (10*n1)+m1;
		else if((n1<10)&&(0<=n1)&&(m1==-1))
			tmp1[1] = n1;
		else{
			printf("Error reading options, please enter integer for (size ,start, end)\n");
			exit(-1);
		}
	}
	else{
		printf("Error reading options, please enter integer for (size ,start, end)\n");
	}
}