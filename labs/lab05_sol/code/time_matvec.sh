echo "experiment, M, N, nTrials, row total(s), row avg(s), col total(s), col avg(s)"
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