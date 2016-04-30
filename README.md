# fbseqSerial

`fbseqSerial` is an internal engine of the [`fbseq` package](https://github.com/wlandau/fbseq). This package is recommended for timing purposes only because the MCMC is slow. For serious computation, see the `fbseqCUDA` package, also on Github.

# System requirements

- R $\ge$ 3.2.0
- R packages `methods` and `knitr`, available through the [Comprehensive R Archive Network (CRAN](https://cran.r-project.org/).
- R [package `fbseq`](https://github.com/wlandau/fbseq), available through GitHub. (See the [`fbseq` package tutorial vignette](https://github.com/wlandau/fbseq/blob/master/vignettes/model.html) for installation instructions. For best viewing, download the html vignette to your desktop and open it with a browser).

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
