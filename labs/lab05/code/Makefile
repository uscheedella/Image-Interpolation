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

clean:
	rm -f cachegrind.*
	rm -f bin/*
