
all: frac mbrot qsort
dir:
	@mkdir -p bin/

frac: dir
	gcc fractal/main.c -o bin/frac

mbrot: dir
	gcc mandelbrot/main.c -o bin/mbrot

qsort: dir
	gcc quicksort/main.c -o bin/qsort

clean:
	@rm bin/* ||:
