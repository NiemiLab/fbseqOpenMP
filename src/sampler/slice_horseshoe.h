#ifndef SLICE_HORSESHOE_H
#define SLICE_HORSESHOE_H

/* Taken from James Scott (2020)
 * "Parameter expansion in local-shrinkage models"
 * on arXiv
 * See the beginning of Section 2.2.
 */

double exp_cdf(double x, double rate){
  return 1.0 - exp(-rate*x);
}

double exp_invcdf(double u, double rate){
  return -log(1.0 - u)/rate;
}

args_t slice_horseshoe(chain_t *dd, args_t args){
  double eta = 1.0/args.x0;
  double u = runiform(dd, args.idx, 0.0, 1.0/(1.0 + eta));
  double upper = exp_cdf((1.0 - u)/u, args.A);
  double u2 = runiform(dd, args.idx, 0.0, upper);
  eta = exp_invcdf(u2, args.A);
  args.x = 1.0/eta;
  return args;
}

#endif // SLICE_HORSESHOE_H
