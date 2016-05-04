# fbseqSerial

The [`fbseqSerial`](https://github.com/wlandau/fbseqSerial) package is an internal backend of the [`fbseq`](https://github.com/wlandau/fbseq) package that runs the Markov chain Monte Carlo (MCMC) procedure behind the scenes. It should install on most machines, but it is slow for large datasets. For a faster backend, which uses parallel computing via CUDA-capable general-purpose graphics processing units (GPUs), use the [`fbseqCUDA`](https://github.com/wlandau/fbseqCUDA) package.

# System requirements

The required R version and R packages listed in the  "Depends", "Imports", and "Suggests" fields of the "package's [DESCRIPTION](https://github.com/wlandau/fbseqSerial/blob/master/DESCRIPTION) file.

# Installation

## Option 1: install a stable release (recommended).

Navigate to a [list of stable releases](https://github.com/wlandau/fbseqSerial/releases) on the project's [GitHub page](https://github.com/wlandau/fbseqSerial). Download the desired `tar.gz` bundle, then install it either with `install.packages(..., repos = NULL, type="source")` from within R  `R CMD INSTALL` from the Unix/Linux command line.

## Option 2: use `install_github` to install the development version.

For this option, you need the `devtools` package, available from CRAN or GitHub. Open R and run 

```{r, eval=F}
library(devtools)
install_github("wlandau/fbseqSerial")
```

## Option 3: build the development version from the source.

Open a command line program such as Terminal in Mac/Linux and enter the following commands.

```
git clone git@github.com:wlandau/fbseqSerial.git
R CMD build fbseqSerial
R CMD INSTALL ...
```

where `...` is replaced by the name of the tarball produced by `R CMD build`. 
