echo "Doing scaling study with 1, 2, 4, 8, and 16 cores."
make clean
make omp
export OMP_NUM_THREADS=1
make run_omp
export OMP_NUM_THREADS=2
make run_omp
export OMP_NUM_THREADS=4
make run_omp
export OMP_NUM_THREADS=8
make run_omp
export OMP_NUM_THREADS=16
make run_omp
