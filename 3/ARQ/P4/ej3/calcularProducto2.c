//P3 arq 2019-2020
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "arqo3.h"

tipo compute(tipo **matrix,int n);

int main( int argc, char *argv[])
{
	int n, i, j, k;
	tipo **m=NULL, **m2=NULL, **res=NULL;
	struct timeval fin,ini;
	float aux, *aux2;


	//printf("Word size: %ld bits\n",8*sizeof(tipo));

	if( argc!=3 )
	{
		printf("Error: ./%s <matrix size>\n", argv[0]);
		return -1;
	}
	n=atoi(argv[2]);

	aux2 = (float*)calloc(n, sizeof(float));
	
	for (j = 0; j < n; j++){
		aux2[j] = 0;
	}

	m=generateMatrix(n);
	
	if( !m )
	{
		return -1;
	}
	
	m2=generateMatrix(n);
	
	if( !m2 )
	{
		return -1;
	}
	
	res=generateEmptyMatrix(n);
	
	if( !res )
	{
		return -1;
	}
	
	gettimeofday(&ini,NULL);

	/* Main computation */
	for (i = 0; i < n; i++) {
		#pragma omp parallel for private(j,k) firstprivate(m, m2, i, n) shared(res) num_threads(atoi(argv[1]))
        for(j = 0; j < n; j++) {
            for(k = 0; k < n; k++) {
                res[i][j] = res[i][j] + m[i][k] * m2[k][j];
            }
        } 
		
    }
	/* End of computation */

	gettimeofday(&fin,NULL);
	printf("Execution time: %f\n", ((fin.tv_sec*1000000+fin.tv_usec)-(ini.tv_sec*1000000+ini.tv_usec))*1.0/1000000.0);
	//printf("Total: %lf\n",res);

	freeMatrix(m);
	freeMatrix(m2);
	freeMatrix(res);
	free(aux2);
	return 0;
}
