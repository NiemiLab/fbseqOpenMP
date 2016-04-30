#ifndef UTIL_CURAND_USAGE_H
#define UTIL_CURAND_USAGE_H

double runiform(chain_t *dd, int g, double LB, double UB){
  return runif(LB, UB);
}

double rnormal(chain_t *dd, int g, double mean, double sd){
  return rnorm(mean, sd);
}

double rt(chain_t *dd, int g, double mean, double scale, int df){
  double z = rnormal(dd, g, 0.0, 1.0), v = 0, x, t;
  int i;
  for(i = 0; i < df; ++i){
    x = rnormal(dd, g, 0.0, 1.0);
    v += x*x;
  }
  t = z/sqrt(v/df);
  return t*scale + mean;
}

#endif // UTIL_CURAND_USAGE_H
