echo "experiment, M, N, nTrials, row total(s), row avg(s)"
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