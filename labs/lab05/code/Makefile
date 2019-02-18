matvecTiming:
	mkdir -p bin
	gcc matvecTiming.c VectorND.c Matrix.c -fopenmp -o bin/matvecTiming


runMatVecTimingSquare:
	./bin/matvecTiming 10 10
	./bin/matvecTiming 20 20
	./bin/matvecTiming 40 40
	./bin/matvecTiming 80 80
	./bin/matvecTiming 160 160
	./bin/matvecTiming 320 320
	./bin/matvecTiming 640 640
	./bin/matvecTiming 1280 1280
	./bin/matvecTiming 2560 2560
	./bin/matvecTiming 5120 5120
	

colOrient:
	mkdir -p bin
	gcc matvecColOrient.c VectorND.c Matrix.c -fopenmp -o bin/colOrient

checkCacheColOrientSquare:
	valgrind --tool=cachegrind bin/colOrient 10 10
	valgrind --tool=cachegrind bin/colOrient 20 20
	valgrind --tool=cachegrind bin/colOrient 40 40
	valgrind --tool=cachegrind bin/colOrient 80 80
	valgrind --tool=cachegrind bin/colOrient 160 160
	valgrind --tool=cachegrind bin/colOrient 320 320
	valgrind --tool=cachegrind bin/colOrient 640 640
	valgrind --tool=cachegrind bin/colOrient 1280 1280
	valgrind --tool=cachegrind bin/colOrient 2560 2560
	valgrind --tool=cachegrind bin/colOrient 5120 5120

rowOrient:
	mkdir -p bin
	gcc matvecRowOrient.c VectorND.c Matrix.c -fopenmp -o bin/rowOrient

checkCacheRowOrientSquare:
	valgrind --tool=cachegrind bin/rowOrient 10 10
	valgrind --tool=cachegrind bin/rowOrient 20 20
	valgrind --tool=cachegrind bin/rowOrient 40 40
	valgrind --tool=cachegrind bin/rowOrient 80 80
	valgrind --tool=cachegrind bin/rowOrient 160 160
	valgrind --tool=cachegrind bin/rowOrient 320 320
	valgrind --tool=cachegrind bin/rowOrient 640 640
	valgrind --tool=cachegrind bin/rowOrient 1280 1280
	valgrind --tool=cachegrind bin/rowOrient 2560 2560
	valgrind --tool=cachegrind bin/rowOrient 5120 5120

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
