matvecTiming:
	mkdir -p bin
	gcc matvecTiming.c VectorND.c Matrix.c -fopenmp -o bin/matvecTiming

rowOrient:
	mkdir -p bin
	gcc matvecRowOrient.c VectorND.c Matrix.c -fopenmp -o bin/rowOrient

colOrient:
	mkdir -p bin
	gcc matvecColOrient.c VectorND.c Matrix.c -fopenmp -o bin/colOrient

matvecOMP:
	mkdir -p bin
	gcc matvecOMP.c VectorND.c Matrix.c -fopenmp -o bin/matvecOMP

runMatVecOMP:
	./bin/matvecOMP 10 10
	./bin/matvecOMP 20 20
	./bin/matvecOMP 40 40
	./bin/matvecOMP 80 80
	./bin/matvecOMP 160 160
	./bin/matvecOMP 320 320
	./bin/matvecOMP 640 640
	./bin/matvecOMP 1280 1280
	./bin/matvecOMP 2560 2560
	./bin/matvecOMP 5120 5120

clean:
	rm -f cachegrind.*
	rm -f bin/*
