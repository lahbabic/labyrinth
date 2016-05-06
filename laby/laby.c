#include <stdio.h>
#include <stdlib.h>



int 		**create_matrix(int n, int m)
{
	int i, j;
	int **mat;
	mat = (int**)malloc(n*sizeof(int*));
	for(i=0; i<n; i++){
		mat[i] = (int *)malloc(m*sizeof(int));
	}
	for(j = 0; j < n; j++){
		for(i = 0; i < m; i++){
			mat[j][i] = 0;
		}
	}	
	return mat;
}

void 		print_matrix(int **mat, int n, int m){
	int i,j;
	for(j = 0; j < n; j++){
		for (i = 0; i < m; ++i)
		{
			if (mat[n-1][m-1]<10)
				printf("+ - ");
			else if(mat[n-1][m-1]>=10)
				printf("+ -- ");
			
		}
		printf("+\n");
		for(i = 0; i < m; i++){
			if (mat[n-1][m-1]<10)
				printf("| %d ",mat[j][i]);
			else if(mat[n-1][m-1]>=10)
				printf("| %2d ",mat[j][i]);
			
		}
		printf("|\n");
	}	
	for (i = 0; i < m; ++i)
	{
		if (mat[n-1][m-1]<10)
			printf("+ - ");
		else if(mat[n-1][m-1]>=10)
			printf("+ -- ");
	}
	printf("+\n");

}

/*
struct	som_s{
	int x;
	int y;
	int p;
};

int 		main(int argc, char *argv[]){
	som **mat;
	mat = create_matrix(4,8);
	return 0;
}

som 		**create_matrix(int n,int m){
	int i;
	i=0;

	som **mat;
	mat = (som**)malloc(n*sizeof(struct som_s*));
	for(i=0; i<n; i++){
		mat[i] = (som*)malloc(m*sizeof(struct som_s));
	}
	(mat[0][1]).x  = 0; 
	return mat;
}
*/

/*int 		main(int argc, char const *argv[])
{
	int **mat;
	int i;
	file f;
	mat = create_matrix(2,2);	
	print_matrix(mat,2,2);
	f = read_file_make_pointer("graph.txt");
	printf("%d\n",f->size);
	//for (i = 1; i < f->size ; i++)
	{
		printf("%c",f->p[i]);
	//}
	return 0;
}
*/ 