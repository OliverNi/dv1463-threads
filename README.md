# dv1463-threads

### Build
````
make [ all | matrix | mbrot | qsort | clean ]
  [all]: 	builds all sources below and outputs to bin/
  matrix: 	builds from source in matrix/ and outputs a binary to bin/frac
  mbrot:	builds from source in mandelbrot/ and outputs a binary to bin/mbrot
  qsort:	builds from source in quicksort/ and outputs a binary to bin/qsort
  clean:	removes all binaries from bin directory
````

### Running
Run each application using the following commands:
````
./bin/matrix	(runs threaded or sequential matrix multiplication)
./bin/matrix_seq

./bin/mbrot	(runs threaded or sequential mandelbrot fractal calculations)
./bin/mbrot_seq

./bin/qsort	(runs threaded or sequential quicksort algorithm)
./bin/qsort_seq
````

Best regards,
Dino & Oliver
