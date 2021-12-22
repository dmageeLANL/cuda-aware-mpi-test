/*
 * Program that shows the use of CUDA-aware macro and runtime check.
 * Requires Open MPI v2.0.0 or later.
 */

/*
 * COMPILE LINE:
 * mpicxx mpi_cuda_aware.cpp -o mcuda_aware -I${MPI_ROOT}/include
 */

#include <stdio.h>
#include "mpi.h"

#ifdef OMPI_RELEASE_VERSION
#include "mpi-ext.h" /* Needed for OPENMPI */
#endif

int main(int argc, char *argv[])
{
    printf("Compile time check\nMPI VERSION: %d.%d:\n", MPI_VERSION, MPI_SUBVERSION);
#if defined(MPIX_CUDA_AWARE_SUPPORT) && MPIX_CUDA_AWARE_SUPPORT
    printf("This MPI library has CUDA-aware support.\n", MPIX_CUDA_AWARE_SUPPORT);
#elif defined(MPIX_CUDA_AWARE_SUPPORT) && !MPIX_CUDA_AWARE_SUPPORT
    printf("This MPI library does not have CUDA-aware support.\n");
#else
    printf("This MPI library cannot determine if there is CUDA-aware support.\n");
#endif /* MPIX_CUDA_AWARE_SUPPORT */
 
    printf("Run time check:\n");
#if defined(MPIX_CUDA_AWARE_SUPPORT)
    if (1 == MPIX_Query_cuda_support()) {
        printf("This MPI library has CUDA-aware support.\n");
    } else {
        printf("This MPI library does not have CUDA-aware support.\n");
    }
#else /* !defined(MPIX_CUDA_AWARE_SUPPORT) */
    printf("This MPI library cannot determine if there is CUDA-aware support.\n");
#endif /* MPIX_CUDA_AWARE_SUPPORT */
 
    return 0;
}
