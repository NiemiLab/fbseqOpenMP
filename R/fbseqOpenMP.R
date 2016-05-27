#' @title Function \code{fbseqOpenMP}
#' @description Calls the OpenMP C code behind the \code{fbseq()} function
#' in the \code{fbseq} package.
#' 
#' @export
#' @return a \code{Chain} object with updated parameter values. You can feed
#' this object back into another call to \code{fbseq} to continue the chain
#' from where you left off.
#'
#' @param chain object of type \code{Chain}. This \code{chain} argument could be
#' a newly created \code{Chain} object from \code{Chain(...)}. Alternatively,
#' if \code{chain} is the output from a previous call to \code{fbseq(...)},
#' then the function will continue the MCMC from where it left off.
fbseqOpenMP = function(chain){
  Chain(slots = .Call("fbseqOpenMP", PACKAGE = "fbseqOpenMP", s4list(chain)))
}
