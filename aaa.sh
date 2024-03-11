#!/bin/bash

gcc -I/opt/intel/oneapi/mkl/2024.0/include -o $1 $1.c -L/opt/intel/oneapi/mkl/2024.0/lib -lm -lmkl_core -lmkl_rt
