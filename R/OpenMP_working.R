#' @title Function \code{OpenMP_working}
#' @description Checks if OpenMP is working.
#' @export
#' @return TRUE/FALSE value
OpenMP_working = function(){
  as.logical(.Call("OpenMP_working", PACKAGE = "fbseqOpenMP"))
}
