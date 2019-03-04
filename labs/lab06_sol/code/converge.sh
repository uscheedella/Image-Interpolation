echo "Doing scaling study with 1, 2, 4, 8, and 16 cores."
#make clean
#make omp
export OMP_NUM_THREADS=2
./bin/pi_omp 100
./bin/pi_omp 1000
./bin/pi_omp 10000
./bin/pi_omp 100000
./bin/pi_omp 1000000
./bin/pi_omp 10000000
./bin/pi_omp 100000000
./bin/pi_omp 1000000000
./bin/pi_omp 10000000000
