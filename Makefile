CC=gcc

all: matrix mbrot qsort
dir:
	@mkdir -p bin/

matrix: dir
	$(CC) -pthread matrix/main.c -o bin/matrix
	$(CC)  matrix/seq.c -o bin/matrix_seq

mbrot: dir
	$(CC) mandelbrot/main.c -o bin/mbrot
	$(CC) mandelbrot/seq.c -o bin/mbrot_seq

qsort: dir
	$(CC) -pthread quicksort/main.c -o bin/qsort
	$(CC) quicksort/seq.c -o bin/qsort_seq

clean:
	@rm bin/* ||:
