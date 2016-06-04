#ifndef UTIL_ESTIMATES_UPDATE_H
#define UTIL_ESTIMATES_UPDATE_H

/*
 * Numerically stable cumulative sum due to Welford, B. P. (1962),
 * "Note on a method for calculating corrected sums of squares and products",
 * Technometrics 4(3), 419–420.
 */
double wf(double x_n, double x_mean, int n){
  double diff = x_n - x_mean;
  diff /= ((double) n);
  return x_mean + diff;
}

void estimates_update_kernel1(chain_t *dd, int m){
  int l;

  dd->nuPostMean[0] = wf(dd->nu[0], dd->nuPostMean[0], m);
  dd->tauPostMean[0] = wf(dd->tau[0], dd->tauPostMean[0], m);

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMean[l] = wf(dd->sigmaSquared[l], dd->sigmaSquaredPostMean[l], m);
    dd->thetaPostMean[l] = wf(dd->theta[l], dd->thetaPostMean[l], m);
  }
}

void estimates_update_kernel2(chain_t *dd, int m){
  int l;

  dd->nuPostMeanSquare[0] = wf(dd->nu[0]*dd->nu[0], dd->nuPostMeanSquare[0], m);
  dd->tauPostMeanSquare[0] = wf(dd->tau[0]*dd->tau[0], dd->tauPostMeanSquare[0], m);

  for(l = 0; l < dd->L; ++l){
    dd->sigmaSquaredPostMeanSquare[l] = wf(dd->sigmaSquared[l]*dd->sigmaSquared[l], dd->sigmaSquaredPostMeanSquare[l], m);
    dd->thetaPostMeanSquare[l] = wf(dd->theta[l]*dd->theta[l], dd->thetaPostMeanSquare[l], m);
  }
}

void estimates_update_kernel3(chain_t *dd, int m){
  int id, l, n;
  #pragma omp parallel for num_threads(dd->threads) private(l, n)
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMean[id] = wf(dd->gamma[id], dd->gammaPostMean[id], m);
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMean[I(l, id)] = wf(dd->beta[I(l, id)], dd->betaPostMean[I(l, id)], m);
      dd->xiPostMean[I(l, id)] = wf(dd->xi[I(l, id)], dd->xiPostMean[I(l, id)], m);
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMean[I(n, id)] = wf(dd->epsilon[I(n, id)], dd->epsilonPostMean[I(n, id)], m);
  }
}

void estimates_update_kernel4(chain_t *dd, int m){
  int id, l, n;
  #pragma omp parallel for num_threads(dd->threads) private(l, n)
  for(id = IDX; id < dd->G; id += NTHREADSX){
    dd->gammaPostMeanSquare[id] = wf(dd->gamma[id]*dd->gamma[id], dd->gammaPostMeanSquare[id], m);
    for(l = 0; l < dd->L; ++l){
      dd->betaPostMeanSquare[I(l, id)] = wf(dd->beta[I(l, id)]*dd->beta[I(l, id)], dd->betaPostMeanSquare[I(l, id)], m);
      dd->xiPostMeanSquare[I(l, id)] = wf(dd->xi[I(l, id)]*dd->xi[I(l, id)], dd->xiPostMeanSquare[I(l, id)], m);
    }
    for(n = 0; n < dd->N; ++n)
      dd->epsilonPostMeanSquare[I(n, id)] = wf(dd->epsilon[I(n, id)]*dd->epsilon[I(n, id)], dd->epsilonPostMeanSquare[I(n, id)], m);
  }
}

void estimates_update_kernel5(chain_t *dd, int m){
  int c, g, truth, l, p;
  double contrast;
  #pragma omp parallel for num_threads(dd->threads) private(c, truth, l, p, contrast)
  for(g = IDX; g < dd->G; g += NTHREADSX){
    for(p = 0; p < dd->P; ++p){
      truth = 1;

      for(c = 0; c < dd->C; ++c){
        if(!dd->propositions[Ipropositions(p, c)]) continue;
        contrast = 0.0;
        for(l = 0; l < dd->L; ++l)
          contrast = wf(dd->contrasts[Icontrasts(c, l)] * dd->beta[I(l, g)], contrast, l + 1);
        truth *= (contrast > dd->bounds[c]);
      }

      dd->probs[I(p, g)] = wf(truth, dd->probs[I(p, g)], m);
    }
  }
}

void estimates_update(SEXP hh, chain_t *hd, chain_t *dd, int m){
  estimates_update_kernel1(dd, m);
  estimates_update_kernel2(dd, m);
  estimates_update_kernel3(dd, m);
  estimates_update_kernel4(dd, m);
  estimates_update_kernel5(dd, m);
}

#endif // UTIL_ESTIMATES_UPDATE_H
