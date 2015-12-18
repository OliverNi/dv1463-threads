#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define KILO (1024)
#define MEGA (1024*1024)
#define MAX_ITEMS (64*MEGA)
#define MAX_THREAD 8

#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

static int *v;

/* quick sort */
void quick_sort(int *, unsigned, unsigned, unsigned);

/* arguments struct for quicksort_thread */
typedef struct {
        int *v;		/* array */
        unsigned low;	/* low */
        unsigned high;	/* high */
        unsigned lim;	/* limit for the recursion */
} args_s;

static void print_array(void) {
    int i;

    for (i = 0; i < MAX_ITEMS; i++)
        printf("%d \n", v[i]);
    printf("\n");
}

static void init_array(void) {
    int i;

    v = (int *) malloc(MAX_ITEMS*sizeof(int));
    for (i = 0; i < MAX_ITEMS; i++)
        v[i] = rand();
}

args_s init_args(int *v, unsigned low, unsigned high, int limit) {
        args_s args;
        args.v    = v;
        args.low  = low;
        args.high = high;
        args.lim  = limit;
	return args;
}

static unsigned partition(int *v, unsigned low, unsigned high, unsigned pivot_index) {
    /* move pivot to the bottom of the vector */
    if (pivot_index != low) swap(v, low, pivot_index);

    pivot_index = low;
    low++;

    /* invariant:
     * v[i] for i less than low are less than or equal to pivot
     * v[i] for i greater than high are greater than pivot
     */

    /* move elements into place */
    while (low <= high) {
        if (v[low] <= v[pivot_index]) low++;
        else if (v[high] > v[pivot_index]) high--;
        else swap(v, low, high);
    }

    /* put pivot back between two groups */
    if (high != pivot_index) swap(v, pivot_index, high);

    return high;
}

void* quick_sort_thread(void *s) {
	args_s *args = s;
	quick_sort(args->v, args->low, args->high, args->lim);
	pthread_exit(0);
}

void quick_sort(int *v, unsigned low, unsigned high, unsigned limit) {
	if(low >= high) return;

	unsigned pivot_index = (low + high)/2;
		 pivot_index = partition(v, low, high, pivot_index);

	if (limit-- > 0) {
		pthread_t thread;

		if (low < pivot_index) {
			args_s a = init_args(v, low, pivot_index - 1, limit);
			pthread_create(&thread, NULL, quick_sort_thread, (void*)&a);
		}

		quick_sort(v, pivot_index + 1, high, limit);
		pthread_join(thread, NULL);
	} else {
		quick_sort(v, low, pivot_index - 1,  0);
		quick_sort(v, pivot_index + 1, high, 0);
	}
}

void error_checker() {
	printf("Error checking started ...\n");
        int i;
        int e = 0;
        for(i = 1;i < MAX_ITEMS;i++)
                if (v[i - 1] > v[i]) e++;

        printf("Error checking ended. Found %d errors", e);
}

int main(int argc, char **argv) {
    	init_array();

    	quick_sort(v, 0, MAX_ITEMS-1, (unsigned)log2(MAX_THREAD));

	// Do not supply args when using time ./<this binary>
	if (argc > 1) error_checker();
}

