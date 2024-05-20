# Copyright (c) 1993-2015, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

######################################################################
## ARGUMENTS THAT CAN BE OVERRIDDEN AT COMMAND LINE
######################################################################

# Compilers
MPICC		?=cc
MPILD		?=CC
NVCC		?=nvcc
CCBIN   	?=$(MPICC)

SMS     	?=80
CUDA_HOME 	?= $(CUDA_PATH)
OFLAG     	?= -O3
GDR_FLAGS	?= -lgdrapi
MPI_GTL     ?= $(CRAY_MPICH_BASEDIR)/../gtl/lib
CUDA_COMPAT ?= $(CUDA_HOME)/compat

######################################################################
## ARGUMENTS TO COMPILATION RULES
######################################################################

NVCC        += -ccbin $(CCBIN)
ifneq ("$(wildcard $(MPI_GTL))","")
  MPI_GTL_FLAGS    = -L$(MPI_GTL) -lmpi_gtl_cuda
endif

ifneq ("$(wildcard $(CUDA_COMPAT))","")
  CUDA_DRV_FLAGS   = -L$(CUDA_COMPAT) -lcuda
endif

# Flags
CFLAGS 			 = -std=c99 $(OFLAG) -march=native -w
MPICFLAGS        = -I$(MPI_HOME)/include $(MPI_GTL_FLAGS) $(GDR_FLAGS)
GENCODE_FLAGS    = -gencode arch=compute_$(SMS),code=sm_$(SMS)

CUDACFLAGS		 = -I$(CUDA_HOME)/include
NVCCFLAGS        = $(OFLAG) $(GENCODE_FLAGS)
NVCCFLAGS       += -Xcompiler -march=native -allow-unsupported-compiler
CUDALDFLAGS      = $(MPI_GTL_FLAGS) $(OFLAG) $(CUDA_DRV_FLAGS)
CUDALDFLAGS     += -L$(CUDA_HOME)/lib64 -lcudart

# Description of binaries
BINDIR=../bin
JACOBI_CUDA_NORMAL_MPI=$(BINDIR)/jacobi_cuda_normal_mpi
JACOBI_CUDA_AWARE_MPI=$(BINDIR)/jacobi_cuda_aware_mpi
BINARIES=$(JACOBI_CUDA_NORMAL_MPI) $(JACOBI_CUDA_AWARE_MPI)
OBJS = Jacobi.o Input.o Host.o Device.o

# Commands
.PHONY: clean doc mkdr
all: $(BINARIES)

mkdr:
	mkdir -p $(BINDIR)

%.o: %.cu Jacobi.h Makefile
	$(NVCC) $(MPICFLAGS) $(NVCCFLAGS) -c $< -o $@

%.o: %.c Jacobi.h Makefile
	$(MPICC) $(MPICFLAGS) $(CUDACFLAGS) $(CFLAGS) -c $< -o $@

$(JACOBI_CUDA_NORMAL_MPI): CUDA_Normal_MPI.o $(OBJS) | mkdr
	$(MPILD) -o $@ $^ $(CUDALDFLAGS)

$(JACOBI_CUDA_AWARE_MPI): CUDA_Aware_MPI.o $(OBJS) | mkdr
	$(MPILD) -o $@ $^ $(CUDALDFLAGS)

doc: CUDA_Normal_MPI.c CUDA_Aware_MPI.c Device.cu Host.c Input.c Jacobi.c Jacobi.h Jacobi.doxygen
	doxygen Jacobi.doxygen

clean:
	rm -rf *.o *~ $(BINARIES)
