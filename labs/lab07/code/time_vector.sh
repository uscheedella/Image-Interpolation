#!/bin/bash

echo "strong scalability"
echo "=================="
echo "experiment, n_threads, n_trials, N, norm, normalize, axpy, inner_product"

export OMP_NUM_THREADS=1
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=2
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=3
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=4
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=5
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=6
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=7
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=8
./bin/experiment_vector 10000000 20

echo ""
echo ""

echo "weak scalability"
echo "=================="
echo "experiment, n_threads, n_trials, N, norm, normalize, axpy, inner_product"

export OMP_NUM_THREADS=1
./bin/experiment_vector 10000000 20

export OMP_NUM_THREADS=2
./bin/experiment_vector 20000000 20

export OMP_NUM_THREADS=3
./bin/experiment_vector 30000000 20

export OMP_NUM_THREADS=4
./bin/experiment_vector 40000000 20

export OMP_NUM_THREADS=5
./bin/experiment_vector 50000000 20

export OMP_NUM_THREADS=6
./bin/experiment_vector 60000000 20

export OMP_NUM_THREADS=7
./bin/experiment_vector 70000000 20

export OMP_NUM_THREADS=8
./bin/experiment_vector 80000000 20
