#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define KILO (1024)
#define MEGA (1024*1024)
#define MAX_ITEMS (64*MEGA)
#define MAX_THREAD 3 // 2^3 = 8

#define swap(v, a, b) {unsigned tmp; tmp=v[a]; v[a]=v[b]; v[b]=tmp;}

static int *v;

/* quick sort */
void quick_sort(int *, unsigned, unsigned, int);

/* arguments struct for quicksort_thread */
typedef struct {
        int *v;		/* array */
        unsigned low;	/* low */
        unsigned high;	/* high */
        int limit;	/* limit */
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

static args_s init_args(int *v, unsigned low, unsigned high, int limit) {
        args_s args;
        args.v = v;
        args.low = low;
        args.high = high;
        args.limit = limit;
	return args;
}

static unsigned partition(int *v, unsigned low, unsigned high, unsigned pivot_index) {
    /* move pivot to the bottom of the vector */
    if (pivot_index != low)
        swap(v, low, pivot_index);

    pivot_index = low;
    low++;

    /* invariant:
     * v[i] for i less than low are less than or equal to pivot
     * v[i] for i greater than high are greater than pivot
     */

    /* move elements into place */
    while (low <= high) {
        if (v[low] <= v[pivot_index])
            low++;
        else if (v[high] > v[pivot_index])
            high--;
        else
            swap(v, low, high);
    }

    /* put pivot back between two groups */
    if (high != pivot_index)
        swap(v, pivot_index, high);

    return high;
}

void* quick_sort_thread(void *s) {
	args_s *args = s;
	quick_sort(args->v, args->low, args->high, args->limit);
	pthread_exit(0);
}

void quick_sort(int *v, unsigned low, unsigned high, int limit) {
	unsigned pivot_index;

	if(low >= high)
		return;

	pivot_index = (low + high)/2;
	pivot_index = partition(v, low, high, pivot_index);

	if (limit-- > 0) {
		pthread_t thread;
		pthread_attr_t attr;
		pthread_attr_init(&attr);

		args_s args1 = init_args(v, low, pivot_index - 1, limit);
		args_s args2 = init_args(v, pivot_index + 1, high, limit);

		if (low < pivot_index) pthread_create(&thread, &attr, quick_sort_thread, (void*)&args1);
		if (pivot_index < high) pthread_create(&thread, &attr, quick_sort_thread, (void*)&args2);

		pthread_join(thread, NULL);
	} else {
		if (low < pivot_index) quick_sort(v, low, pivot_index - 1, 0);
		if (pivot_index < high) quick_sort(v, pivot_index + 1, high, 0);
	}
}

int main(int argc, char **argv) {
    	init_array();
	//print_array();
    	quick_sort(v, 0, MAX_ITEMS-1, MAX_THREAD);
	//print_array();
}

