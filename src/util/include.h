#ifndef UTIL_INCLUDE_H
#define UTIL_INCLUDE_H

#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <Rmath.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath.h>

#ifdef _OPENMP
   #define USING_OPENMP 1
   #include <omp.h>
#else
   #define USING_OPENMP 0
   #define omp_get_num_threads() 0
#endif

#endif // UTIL_INCLUDE_H
