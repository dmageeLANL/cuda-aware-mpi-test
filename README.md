## JACOBI TEST

Block Jacobi iteration code for CUDA+MPI, updated, adapted and generalized from https://github.com/NVIDIA-developer-blog/code-samples/tree/master/posts/cuda-aware-mpi-example.  This code is from a two part blog post, part 2 here: https://developer.nvidia.com/blog/benchmarking-cuda-aware-mpi/.

To run the jacobi test, be on a backend node, load an mpi compatible with slurm, enter the folder, and run the `runjac` script.
This script does not require any arguments, but it does accept arguments for build configuration in the form of key value pairs where the key is a variable assigned with ? in `jacobi_test/src/Makefile` which are the build options.
#### BUILD OPTIONS
Set any of these variables to empty on command line to disable

* MPICC		    - MPI C Compiler [cc]
* MPILD		    - MPI Linker C++ compiler [CC]
* NVCC		    - NVCC COMPILER [nvcc]
* CCBIN   	    - CUDA HOST COMPILER (companion for nvcc) [$(MPICC)]
* SMS     	    - Compute capability of target [80]
* OFLAG     	- Optimization flag [-O3]
* CUDA_HOME 	- Prefix for cuda install [$(CUDA_PATH)]
* CUDA_COMPAT 	- Prefix for cuda install [-L$(CUDA_PATH)/compat] [links -lcuda]
* GDR_FLAGS	    - GPU Direct library (SET GDR_FLAGS= to disable) [-lgdrapi]
* MPI_GTL       - Gtl library for cuda aware (cray only) [$(CRAY_MPICH_BASEDIR)/../gtl/lib] [links -lmpi_gtl_cuda]

#### RUNTIME OPTIONS

* topx        - Number of processes in x dimension [4]
* topy        - Number of processes in y dimension [2]
* srun_opts   - Arguments to srun apart from N and ntasks-per-node.  As a string. [none]

#### CONFIGURATION OPTIONS

Any UCX, OFI, OMPI, MCA, MPICH options should also be provided at the command line in the same format.

### OPERATION

The executables will be created in a new folder `jacobi_test/bin`. 
The `runjac` script will enter the rslt folder and use the runtime options provided to launch srun with the script `jacobi_test/rslt/run_mpi` which sets the visible gpu for each process before launching the main executable.
The main executables can also be launched directly, but doing so results in significant performance degridation.
Using the run_mpi script results in a 2+x speedup for the cuda aware program.

## Preprocessor test

To run the preprocessor test, be on a backend node, load an mpi compatible with slurm, enter the folder, and run the `cuda_aware_run` script which takes no arguments.

It'll create a bin folder, build a binary with a descriptive name in it, and run it with two processes on one node.
