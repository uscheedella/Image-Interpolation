#!/bin/bash

#SBATCH -n 8
#SBATCH -t 01:00:00
#SBATCH - pnormal_q

#SBATCH -A cmda3634

#Change to the directory from which the job was submitted

cd $SLURM_SUBMIT_DIR

echo $SLURM_SUBMIT_DIR

pwd

#Load modules
module purge; 
module load gcc

bash time_matrix.sh
bash time_vector.sh
