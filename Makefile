CC=gcc

all: matrix mbrot qsort
dir:
	@mkdir -p bin/

matrix: dir
	$(CC) matrix/main.c -o bin/matrix -lpthread
	$(CC) matrix/seq.c -o bin/matrix_seq

mbrot: dir
	$(CC) mandelbrot/main.c -o bin/mbrot -lpthread
	$(CC) mandelbrot/seq.c -o bin/mbrot_seq

qsort: dir
	$(CC) quicksort/main.c -o bin/qsort -lpthread
	$(CC) quicksort/seq.c -o bin/qsort_seq

clean:
	@rm bin/* ||:
