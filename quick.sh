#!/bin/bash

#SBATCH --qos=debug
#SBATCH --nodes=8
#SBATCH --time=30:00
#SBATCH --licenses=scratch
#SBATCH --constraint=cpu

if [ "$#" -ne 1 ]; then
	echo "Usage: $0 <exec>"
	exit 1
fi

EXEC=/global/homes/n/nb-t/workspace/misc-cpp/$1
#DATA=/global/cfs/cdirs/m4646/nb-t/$1/$1_1.fasta
#LB=2
#UB=50
#T=$2
#OUT=$SCRATCH/out
#K=$4

srun -N 1 -n 1 -c 1 --cpu_bind=cores ${EXEC} $
wait
