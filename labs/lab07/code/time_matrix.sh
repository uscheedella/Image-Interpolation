#!/bin/bash

echo "strong scalability"
echo "=================="
echo "experiment, n_threads, n_trials, N, matvec, matvec_triangular, matvec_triangular guided"

export OMP_NUM_THREADS=1
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=2
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=3
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=4
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=5
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=6
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=7
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=8
./bin/experiment_matrix 10000 20

echo ""
echo ""

echo "weak scalability"
echo "=================="
echo "experiment, n_threads, n_trials, N, matvec, matvec_triangular, matvec_triangular guided"

export OMP_NUM_THREADS=1
./bin/experiment_matrix 10000 20

export OMP_NUM_THREADS=2
./bin/experiment_matrix 14142 20

export OMP_NUM_THREADS=3
./bin/experiment_matrix 17320 20

export OMP_NUM_THREADS=4
./bin/experiment_matrix 20000 20

export OMP_NUM_THREADS=5
./bin/experiment_matrix 22360 20

export OMP_NUM_THREADS=6
./bin/experiment_matrix 24494 20

export OMP_NUM_THREADS=7
./bin/experiment_matrix 26457 20

export OMP_NUM_THREADS=8
./bin/experiment_matrix 28284 20
