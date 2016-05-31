#ifndef UTIL_CUDA_USAGE_H
#define UTIL_CUDA_USAGE_H

#define IDX 0
#define IDY 0
#define NTHREADSX 1
#define NTHREADSY 1

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a < b ? a : b)

extern "C" SEXP OpenMP_working(){
  int i, threads;
  #pragma omp parallel for num_threads(2)
  for(i = 0; i < 2; ++i)
    threads = omp_get_num_threads();
  SEXP result = PROTECT(allocVector(INTSXP, 1));
  INTEGER(result)[0] = threads > 1;
  UNPROTECT(1);
  return result;
}

void check_omp_runtime(int requested_threads){
  int i, threads;
  if(!USING_OPENMP){
    Rprintf("OpenMP disabled. Using 1 thread per process.\n");
    return;
  }
  #pragma omp parallel for num_threads(requested_threads)
  for(i = 0; i < 2; ++i)
    threads = omp_get_num_threads();
  Rprintf("Using %d OpenMP threads.\n", threads);
}

void reduce_aux(chain_t *dd){
  int g;
  double out = 0.0;
  #pragma omp parallel for reduction(+:out) num_threads(dd->threads)
  for(g = 0; g < dd->G; ++g)
    out = out + dd->aux[g];
  dd->aux[0] = out;
}

#endif // UTIL_CUDA_USAGE_H
