/***************************************************************************
 *
 * Sequential version of Matrix-Matrix multiplication
 *
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define SIZE 1024
#define NR_OF_THREADS 8
#define TH_LIMIT SIZE/NR_OF_THREADS
static double a[SIZE][SIZE];
static double b[SIZE][SIZE];
static double c[SIZE][SIZE];

static void init_matrix(void) {
    int i, j;

    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
	    /* Simple initialization, which enables us to easy check
	     * the correct answer. Each element in c will have the same 
	     * value as SIZE after the matmul operation.
	     */
	    a[i][j] = 1.0;
	    b[i][j] = 1.0;
        }
}

static void matmul_seq() {
    int i, j, k;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            c[i][j] = 0.0;
            for (k = 0; k < SIZE; k++)
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
        }
    }
}

static void print_matrix(void) {
    int i, j;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++)
	    printf(" %7.2f", c[i][j]);
	printf("\n");
    }
}

static void* matmul_par(void* param) {
    	int i, j, k, l;
	int start = *(int*)param;
	for (i = start; i < (start + TH_LIMIT); i++){
        	for (j = 0; j < SIZE; j++) {
            		c[i][j] = 0.0;
            		for (k = 0; k < SIZE; k++)
                		c[i][j] += a[i][k] * b[k][j];
        	}
	}
	free(param);
	pthread_exit(0);
}

int main(int argc, char **argv) {
	pthread_t threads[NR_OF_THREADS];
	int start = 0;	
    	init_matrix();
	int i = 0;
    	for (; i < NR_OF_THREADS; i++){
		
		int* arg = malloc(sizeof(*arg));
		*arg = start;
		pthread_create(&threads[i], NULL, matmul_par, arg);
		start += TH_LIMIT;
	}
	int k = 0;
	for (; k < NR_OF_THREADS; k++){
		pthread_join(threads[k], NULL);
	}
    //print_matrix();
}



