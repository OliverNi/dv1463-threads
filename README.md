# dv1463-threads

### Build
````
make [ all | matrix | mbrot | qsort | clean ]
  [all]: 	builds all sources below and outputs to bin/
  matrix: 	builds from source in matrix/ and outputs a binaries to bin/
  mbrot:	builds from source in mandelbrot/ and outputs a binaries to bin/
  qsort:	builds from source in quicksort/ and outputs a binaries to bin/
  clean:	removes all binaries from bin directory
````

### Running
Run each application using the commands described below.

Runs threaded or sequential matrix multiplication
````
./bin/matrix
./bin/matrix_seq
````

Runs threaded or sequential mandelbrot fractal calculations
````
./bin/mbrot
./bin/mbrot_seq
````

Runs threaded or sequential quicksort algorithm
````
./bin/qsort
./bin/qsort_seq
````

### Time
To generate reports, do:
````
./time
````
All files in /bin will be timed.

Best regards,
Dino & Oliver
