make:
	mkdir -p bin
	gcc -o ./bin/pi pi.c -O3 -lm
run:
	./bin/pi
omp:
	mkdir -p bin
	gcc -o ./bin/pi_omp pi_omp.c -O3 -lm -fopenmp
run_omp:
	./bin/pi_omp
clean:
	rm -rf ./bin/*
	rm *.txt
