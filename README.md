# MLClusterCalibration

This respository contains code to plot responses and other cluster features in the context of the ML-based topo-cluster calibration project. In addition several scripts are available converting inputs from root to csv and vice versa, setup the environment and others. 

## Setup

## Workflow

### Making response plots

![Workflow for filling distributions](https://github.com/peterloch/MLClusterCalibration/blob/Plotters/root/doc/PlotWorkFlow.png)
[:link: PDF file](https://github.com/peterloch/MLClusterCalibration/blob/Plotters/root/doc/PlotWorkFlow.pdf) [:link: JPEG file](https://github.com/peterloch/MLClusterCalibration/blob/Plotters/root/doc/PlotWorkFlow.jpg)

The typical workflow for making plots to evaluate the topo-cluster response as function of cluster signals and moments (inputs to the DNN calibration) comprise 1️⃣ the transformation of the testing output to `root` files with a tree `ClusterTree` (default) as needed, followed by 2️⃣ the filling and storing of (mostly) 2-dimensional histgrams showing the responses at various scales (EM, LCW and ML-based). 

## Generating response plots 🆕

Plotting uses the `ROOT` tuple as input. This tuple can be constructed from a csv file by 
```
root -l 'readCSV.C("results.csv","ml_pions.root")'
```
for single particles (typically a mixed file with clusters from neutral and charged pions) or
```
root -l `readCSV.C("results.csv","ml_jets.root")'
```
for jets. **It is highly recommended to use the output (ROOT) file names given in these examples. They are expected by the plotting scripts.**[^1]
In both cases the output file contains a tree named `ClusterTree` with branches corresponding to the colummn headers in the csv file.

Next, the main plotter module coded in `ClusterTreePlotter.C` is run. This module is universal, it can be used for topo-clusters from single particles as well as those from jets. It will add some source-sepcific plots automatically. It also generates an output file with a presently hard-coded name `ml_pions.hist.root` for pions (same for neutral, charged or mixed samples) and `ml_jets.hist.root` for jets. These outputs (mostly 2-dimensional hstograms of type `TH2D`) are used for further analysis.

It is recommended to not use `ClusterTeePlotter.C` directly. Rather, use the specific scripts provided for the plotting:

| Topo-cluster source | Script            | Expected input  | Output files         |
| ------------------- | ----------------- | --------------- | -------------------- |
| &pi;<sup>0</sup>    | `plotPi0.C`       | `ml_pions.root` | `ml_pions.hist.root` |
| &pi;<sup>&pm;</sup> | `plotPiCharged.C` | `ml_pions.root` | `ml_pions.hist.root` |
| mixed &pi; sample   | `plotPi.C`        | `ml_pions.root` | `ml_pions.hist.root` |
| jets                | `plotJets.C`      | `ml_jets.root`  | `ml_jets.hist.root`  |

**Note:** The `ml_pions.root` file should contain topo-clusters from both neutral and charged pions - it is just the output from the training and/or testing of the DNN calibration.

**Note:** The output file names are constructed from the inout file name by adding `.hist` before the file name extension/file type `root`.

The plotting scripts are simply run by[^2]
```
root -l -b -q plotPiCharged.C++
```

[^1]: :hammer_and_wrench: TODO: allow user-defined file names in plotting scripts `plotPi.C`, `plotPi0.C`, `plotPiCharged.C` and `plotJets.c`.
[^2]: <a name="compile">It is recommended to run the scripts in batch mode (`-b` option in the `root` command line &ndash; the `-q` option just terminates `root` after the script is executed. Also, to speed up future invacations of the plotting script, it is useful to compile the script by adding the `++` after the file extension `.C` when compiling the script for the first time orr after `ClusterTreePlotter.C` has been changed. A repeated invocation of the same script can then use the command line `root -l -b -q plotPiCharged.C+` with the a single `+` added after the file extension.</a> 

## Generating summary plots

### 2-dimensional response distributions

The final formatting and display of the distributions created by the plotting scripts is done using the `plotCusters.C` macro. It is invoked by 
```
root -l 'plotClusters.C++("ml_pions.hist.root","plots",50)'
```
The use of the `++` (or `+`) is motivated by the complexity and size of the invoked code. Pre-compilation makes bug finding easier and execution faster. Similar to what has been discussed for the plotting scripts in [footnote 2](#compile) at the bottom of this page.

The `plotClusters.C` macro has three optional arguments, 
```
plotClusters(<input_file_name>,<output_plot_directory>,<minimum_entries>)
```
with 
| Argument                  | Default setting        | Description                                                                                    |
| ------------------------- | ---------------------- | ---------------------------------------------------------------------------------------------- |
| `<input_file_name>`       | `"ml_pions.hist.root"` | Name of input file produced by one of the plotting scripts                                     |
| `<output_plot_directory>` | `"plots"`              | Name of directory to store in produced plots in (see remarks below)                            |
| `<minimum_entries>`       | `50`                   | Minimum entries required in a histogram slice to calculate the average and standard deviations |

The script geberates the fully formatted plots and saves them into the directory `<output_plot_directory` which is expected to exist in the same directory as the input file. **This directory needs to be created before running the script for the first time!** In case the directory is already existing, the files in it will be overwritten. 

Each plot is saved as a PDf and a PNG file (two files per plot). In addition, all distributions, graphs and canvases are saved into a `ROOT` file for further analysis and/or display. The output file name is constructed internally using the first part of the input file name, e.g. input file name `ml_jets.hist.root` yields output file name `ml_jets_summary.root`. The output file is saved in the present working directory.

#### Example for plot storage

| Input file file name               | Directory for files with plots | Output file               |
| ---------------------------------- | ------------------------------ | ------------------------- |
| `ml_pions.hist.root`               | `./plots`                      | `./ml_pions_summary.root` |
| `my_analysis/ml_pions.hist.root`   | `./my_analysis/plots`          | `./ml_pions_summary.root` |
| `/home/me/test/ml_pions.hist.root` | `/home/me/test/plots`          | `./ml_pions_summary.root` |

### Graphs with averages and errors

The graphs shown in the scatter plots can be plotted without the distributions. This is done by
```
root -l 'plotSummary.C++("ml_pions_summary.root","RMS")'
```
The input arguments for this macro are the input file name (no default, must be supplied by the user) and the error bar option (default is `"RMS"`, meaning the errors shown in the plots are the standard deviations. If the option `"ERR"` is given, the error of the means will be shown instead. Both the standard deviations as well as the errors on the mean are asymmetric. The results will be stored in a `plots` which is in the same path as the input file.[^3]

[^3]: 🛠️:exclamation::exclamation: There is a limitation in the present implementation of `plotSummary.C`. To avoid crashes and unpredictable behaviour, the input file name should always contain a path. This means that instead of using `ml_jets_summary.root` one should use `./ml_jets_summary.root` if the input file is in the present working directory. The `plots` directory needs to exist, as in case of the plots with the distributions.
