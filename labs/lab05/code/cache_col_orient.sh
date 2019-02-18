echo "experiment, M, N, nTrials, col total(s), col avg(s)"
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