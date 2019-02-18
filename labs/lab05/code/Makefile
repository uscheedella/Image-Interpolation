matVecTiming:
	gcc matvecTiming.c VectorND.c Matrix.c -fopenmp -o bin/matVecTiming


runMatVecTimingSquare:
	./bin/matVecTiming 10 10
	./bin/matVecTiming 20 20
	./bin/matVecTiming 40 40
	./bin/matVecTiming 80 80
	./bin/matVecTiming 160 160
	./bin/matVecTiming 320 320
	./bin/matVecTiming 640 640
	./bin/matVecTiming 1280 1280
	./bin/matVecTiming 2560 2560
	./bin/matVecTiming 5120 5120
	

colOuter:
	gcc matvecColOuter.c VectorND.c Matrix.c -fopenmp -o bin/colOuter

checkCacheColOuterSquare:
	valgrind --tool=cachegrind bin/colOuter 10 10
	valgrind --tool=cachegrind bin/colOuter 20 20
	valgrind --tool=cachegrind bin/colOuter 40 40
	valgrind --tool=cachegrind bin/colOuter 80 80
	valgrind --tool=cachegrind bin/colOuter 160 160
	valgrind --tool=cachegrind bin/colOuter 320 320
	valgrind --tool=cachegrind bin/colOuter 640 640
	valgrind --tool=cachegrind bin/colOuter 1280 1280
	valgrind --tool=cachegrind bin/colOuter 2560 2560
	valgrind --tool=cachegrind bin/colOuter 5120 5120

rowOuter:
	gcc matvecRowOuter.c VectorND.c Matrix.c -fopenmp -o bin/rowOuter

checkCacheRowOuterSquare:
	valgrind --tool=cachegrind bin/rowOuter 10 10
	valgrind --tool=cachegrind bin/rowOuter 20 20
	valgrind --tool=cachegrind bin/rowOuter 40 40
	valgrind --tool=cachegrind bin/rowOuter 80 80
	valgrind --tool=cachegrind bin/rowOuter 160 160
	valgrind --tool=cachegrind bin/rowOuter 320 320
	valgrind --tool=cachegrind bin/rowOuter 640 640
	valgrind --tool=cachegrind bin/rowOuter 1280 1280
	valgrind --tool=cachegrind bin/rowOuter 2560 2560
	valgrind --tool=cachegrind bin/rowOuter 5120 5120

matVecOMP:
	gcc matvecOMP.c VectorND.c Matrix.c -fopenmp -o bin/matVecOMP

runMatVecOMP:
	./bin/matVecOMP 10 10
	./bin/matVecOMP 20 20
	./bin/matVecOMP 40 40
	./bin/matVecOMP 80 80
	./bin/matVecOMP 160 160
	./bin/matVecOMP 320 320
	./bin/matVecOMP 640 640
	./bin/matVecOMP 1280 1280
	./bin/matVecOMP 2560 2560
	./bin/matVecOMP 5120 5120

clean:
	rm -f cachegrind.*
	rm -f bin/*
