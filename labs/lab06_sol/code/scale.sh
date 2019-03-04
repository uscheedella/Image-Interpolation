echo "Doing scaling study with 1, 2, 4, 8, and 16 cores."
#make clean
#make omp
export OMP_NUM_THREADS=1
./bin/pi_omp 1000000000
export OMP_NUM_THREADS=2
./bin/pi_omp 1000000000
export OMP_NUM_THREADS=4
./bin/pi_omp 1000000000
export OMP_NUM_THREADS=8
./bin/pi_omp 1000000000
export OMP_NUM_THREADS=16
./bin/pi_omp 1000000000
