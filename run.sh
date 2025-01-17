#!/bin/bash
#SBATCH --qos=debug
#SBATCH --nodes=8
#SBATCH --time=30:00
#SBATCH --licenses=scratch
#SBATCH --constraint=cpu

EXEC=/global/homes/n/nb-t/workspace/cpp/$1

srun -N 1 -n 1 -c 128 --cpu_bind=cores ${EXEC} &
wait
