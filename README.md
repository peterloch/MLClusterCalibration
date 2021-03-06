# <a name="top">MLClusterCalibration</a>

This respository contains code to plot responses and other cluster features in the context of the ML-based topo-cluster calibration project. In addition several scripts are available converting inputs from root to csv and vice versa, setup the environment and others. 

---

## <a name="toc">Table of contents</a>
1. [Setup](#setup)
1. [Workflow](#workflow) 
   1. [Filling response and other distributions](#workflow_fill)
   1. [Refined analysis](#workflow_plots)
1. [Analyzing response](#analysis)
   1. [Converting and collecting data](#analysis_fill)
   2. [Fully formatted response plots](#analysis_plot)
   3. [Graphs with averages and errors](#analysis_graph)
---
 
## <a name="setup">Setup</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

## <a name="workflow">Workflow</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

The code in this repository supports a basic workflow consisting of two blocks. First, the output from the DNN training/testing is converted into the appropriate ROOT tree structure. This is usually only needed if the resulting data is in a CSV file format.[^1] 

### <a name="workflow_fill">Filling response and other distributions</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

![Workflow for filling distributions](root/doc/PlotWorkFlow_1_2.png)
[:link: PDF file](root/doc/PlotWorkFlow_1_2.pdf) [:link: JPEG file](root/doc/PlotWorkFlow_1_2.jpg)

The typical workflow for making plots to evaluate the topo-cluster response as function of cluster signals and moments (inputs to the DNN calibration) comprise 1️⃣ the transformation of the testing output to `root` files with a tree `ClusterTree` (default) as needed, followed by 2️⃣ the filling and storing of (mostly) 2-dimensional histograms showing the responses together with kinematic variables of the cluster, both at various scales (EM, LCW and ML-based). In addition, distributions of kinematic variables of the particles (in case of topo-clusters from pions) and the jets (in case of topo-clusters in jets) are produced. All other scripts producing summary plots use the distributions generated in step 2️⃣ to extract additional features or calculate average behaviours. 

The code needed for these two steps is:

- :one: This step needs the [`readCSV.C`](root/readCSV.C) script which reads a CSV file with column headers and saving its content into a ROOT tuple ([`TTree`](https://root.cern/doc/master/classTTree.html)). This script is only needed if the DNN testing output is not directly available in a ROOT tree with known branch names. It uses the [`TTree::ReadFile`](https://root.cern/doc/master/classTTree.html#a9c8da1fbc68221b31c21e55bddf72ce7) method to fill the tree (link points to the ROOT reference manual).
- :two: This step comprises the actual collection of the data and a partial analysis. Each source of topo-clusters has their own specific macro, which deplay the basic universal analysis coded in `ClusterTreePlotter.C` with the appropriate configuration. The differerent macros are:
  - [`plotPi0.C`](root/plotPi0.C) selects topo-clusters generated by single &pi;<sup>0</sup> from file `ml_pions.root` and fills the distributions for neutral response. The macro saves the filled distributions to a file `ml_pions.hist.root`;
  - [`plotPiCharged.C`](root/plotPiCharged.C) selects topo-clusters generated by single &pi;<sup>&pm;</sup> from file `ml_pions.root` and fills distributions for the charged response. The macro saves the filled distributions to a file `ml_pions.hist.root`;
  - [`plotPi.C`](root/plotPi.C) fills topo-cluster distributions for the inclusive pion response from file `ml_pions.root` and saves those to a file `ml_pions.hist.response`.
  - [`plotJets.C`](root/plotJets.C) extracts topo-clusters from jets stored in `ml_jets.root`, fills the distributions for the _topo-cluster-in-jet_ response and saves them to `ml_jets.hist.root`.
 

### <a name="workflow_plots">Refined analysis</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

![Workflow for plotting distributions](root/doc/PlotWorkFlow_3_4.png)
[:link: PDF file](root/doc/PlotWorkFlow_3_4.pdf) [:link: JPEG file](root/doc/PlotWorkFlow_3_4.jpg)

The workflow combining step 1️⃣ and 2️⃣ described above produces the inputs for more refined analyses with well-formatted plots. The common data used by these analyses are contained in `ml_pions.hist.root` and `ml_jets.hist.root`, respectively. Step 3️⃣ shown in the schematics above is the first step in the analysis workflow, where well-formatted plots are produced and graphs of the average response with error bars representing both the RMS and the error on the averages are stored. In the following step 4️⃣ plots of these graphs or plots of the response functions in bins of various observables are produced.

- 3️⃣ In this step the [`plotClusters.C`](root/plotClusters.C) macro is used to produce plots of the response distributions filled in step 2️⃣ overlaid with the averages and error bars indicating the asymmetric RMS of the response distribution.
- 4️⃣ This step collects all modules for refined analysis. Presently available are:
  - [`plotSummary.C`](root/plotSummary.C) loads the graphs produced in 3️⃣  and produces plots overlaying the average response as functions of various DNN inputs for EM, LCW and ML-based response scales;
  - [`plotResponseHists.C`](root/plotResponseHists.C) extracts the response functions at EM, LCW and ML-based scales and produces plots overlaying those in each bin of the DNN input variables. 

## <a name="analysis">Analyzing response</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

### <a name="analysis_fill">Converting and collecting data</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

Various distributions are filled from the ROOT tree in `ml_pions.root` or `ml_jets.root`. The respective trees can be filled from tabular data stored in a CSV file. The first entry (row) in this file should contain a comma-separated list of column headers, which are used as branch names in the `ClusterTree` tree created for storage of the data in ROOT files. The following command line produces the file `ml_pions.root` for test/trainig results for topo-clusters in single pion events stored in a (text) file `results.csv`.    
```
root -l 'readCSV.C("results.csv","ml_pions.root")'
```
Typically `results.csv` contains data from both neutral and charged pions leading to `ml_pions.root` containing topo-clusters from an inclusive pion selection. No filters are applied in this conversion. For topo-clusters in jets, the command line
```
root -l `readCSV.C("results.csv","ml_jets.root")'
```
creates the ROOT file with the same tree `ClusterTree` as for single pions, with slightly different branches for the cluster source &ndash; for pions the particle kinematics and the particle identification code are provided, while for jets the kinematic at fully calibrated scale and at constituent scale are stored together with the corresponding matching truth jet variables. **It is highly recommended to use the output (ROOT) file names given in these examples. They are expected by the plotting scripts.**[^2]

Next, the main plotter module coded in [`ClusterTreePlotter.C`](root/ClusterTreePlotter.C) is run. This module is universal, it can be used for topo-clusters from single pions as well as those from jets. It will configure and fill source-sepcific plots automatically. In additoin, it produces an output file with a presently hard-coded name `ml_pions.hist.root` for pions (same for neutral, charged or mixed samples) and `ml_jets.hist.root` for jets. These outputs (mostly 2-dimensional histograms of type [`TH2D`](https://root.cern/doc/master/classTH2D.html)) are used for further analysis.

It is recommended to not use `ClusterTeePlotter.C` directly. Rather, use the specific scripts provided for the plotting:

| Topo-cluster source | Script                                    | Expected input  | Output files         |
| ------------------- | ----------------------------------------- | --------------- | -------------------- |
| &pi;<sup>0</sup>    | [`plotPi0.C`](root/plotPi0.C)             | `ml_pions.root` | `ml_pions.hist.root` |
| &pi;<sup>&pm;</sup> | [`plotPiCharged.C`](root/plotPiCharged.C) | `ml_pions.root` | `ml_pions.hist.root` |
| mixed &pi; sample   | [`plotPi.C`](root/plotPi.C)               | `ml_pions.root` | `ml_pions.hist.root` |
| jets                | [`plotJets.C`](root/plotJets.C)           | `ml_jets.root`  | `ml_jets.hist.root`  |

**Note:** The `ml_pions.root` file should contain topo-clusters from both neutral and charged pions - it is just the output from the training and/or testing of the DNN calibration.

**Note:** The output file names are constructed from the input file name by adding `.hist` before the file name extension/file type `root`.

The plotting scripts are simply run by[^3]
```
root -l -b -q plotPiCharged.C++
root -l -b -q plotJets.C++
```
**Note:** The input and output file names of these macros are hardcoded. The consecutive invocation of two of these scripts for two different pion selections will lead to the second script overwriting the output file of the first script. For example, `plotPi0.C` executed directly after `plotPiCharged.C` replaces the output file containing the distributions for charged pions with a file containing the distributions for neutral pions. Running `plotJets.C` after e.g., `plotPiCharged.C` (or vice versa, and for any other single pion script) will not overwrite any output file as both scripts use different input and output file names.  

### <a name="analysis_plot">Fully formatted response plots</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

The final formatting and display of the distributions created by the plotting scripts is done using the [`plotCusters.C`](root/plotClusters.C) macro. It is invoked by 
```
root -l 'plotClusters.C++("ml_pions.hist.root","plots",50)'
```
The use of the `++` (or `+`) is motivated by the complexity and size of the invoked code. Pre-compilation makes bug finding easier and execution faster. Similar to what has been discussed for the plotting scripts in [footnote 3](#compile) at the bottom of this page.

The `plotClusters.C` macro has three optional arguments, 
```
plotClusters(<input_file_name>,<output_plot_directory>,<minimum_entries>)
```
with 
| Argument                  | Default setting        | Description                                                                                    |
| ------------------------- | ---------------------- | ---------------------------------------------------------------------------------------------- |
| `<input_file_name>`       | `"ml_pions.hist.root"` | Name of input file produced by one of the plotting scripts                                     |
| `<output_plot_directory>` | `"plots"`              | Name of directory to store produced plots in (see remarks below)                               |
| `<minimum_entries>`       | `50`                   | Minimum entries required in a histogram slice to calculate the average and standard deviations |

The script generates the fully formatted plots and saves them into the directory `<output_plot_directory` which is expected to exist in the same directory as the input file. **This directory needs to be created before running the script for the first time!** In case the directory is already existing, the files in it will be overwritten. 

Each plot is saved as a PDF and a PNG file (two files per plot). In addition, all distributions, graphs and canvases are saved into a ROOT file for further analysis and/or display. The output file name is constructed internally using the first part of the input file name, e.g. input file name `ml_jets.hist.root` yields output file name `ml_jets_summary.root`. The output file is saved in the present working directory.

#### <a name="analysis_plots_example">Example for plot storage</a> 

| Input file file name               | Directory for files with plots | Output file               |
| ---------------------------------- | ------------------------------ | ------------------------- |
| `ml_pions.hist.root`               | `./plots`                      | `./ml_pions_summary.root` |
| `my_analysis/ml_pions.hist.root`   | `./my_analysis/plots`          | `./ml_pions_summary.root` |
| `/home/me/test/ml_pions.hist.root` | `/home/me/test/plots`          | `./ml_pions_summary.root` |
   
### <a name="analysis_graph">Graphs with averages and errors</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

The graphs shown in the scatter plots can be plotted without the distributions. This is done by
```
root -l 'plotSummary.C++("./ml_pions_summary.root","RMS")'
```
The input arguments for this macro are the input file name (no default, must be supplied by the user) and the error bar option (default is `"RMS"`, meaning the error bars shown in the plots represent the standard deviations). If the option `"ERR"` is given, the error of the means will be shown instead. Both the standard deviations as well as the errors on the mean are asymmetric. The results will be stored in the `plots` directory which needs to be in the same path as the input file.[^4]

The `plotSummary.C` macro has two arguments,
```
plotSummary(<input_file_name>,<error_bar_option>)
```
with 
| Argument                  | Default setting    | Description                                                                                    |
| ------------------------- | ------------------ | ---------------------------------------------------------------------------------------------- |
| `<input_file_name>`       | &laquo;none&raquo; | Name of input file produced in step 3️⃣                                                         |
| `<error_bar_option>`      | `"RMS"`            | Option for error bars, possible values are `"ERR"` for errors of the mean and `"RMS"` for RMS  |

Each produced plot shows the average response with the selected option for the error bars, with EM, LCW and MC-based scales orverlaid, as a function of the studied DNN input variables. Each plot is stored as PDF and as PNG file (both generated by ROOT) in the `plots` directory. This macro does not produce any further output. 

### <a name="analysis_hists">Response functions in bins of DNN inputs</a>&nbsp;&nbsp;&nbsp;[![TableOfContent](root/doc/back-to-top.png)](#top)

The response function in each bin of a given DNN input variable are produced using the ROOT batch mode by 
```
root -l -b -q 'plotResponseHists.C++("ml_jets_summary.root","plots/hists",true)'
```
This is highly recommended, as the `plotResponseHists.C` macro produces a large number of canvases, which may slow down its execution significantly if all of those are shown on the terminal (like in an interactive ROOT session). The script can be executed in full interactive mode by 
```
root -l 'plotResponseHists.C++("ml_jets_summary.root","plots/hists",false)'
```
which requires keyboard input after each canvas is shown offering the option to terminate the script.  

The `plotResponseHists.C` macro has three arguments, two of which are mandatory,
```
plotResponseHists(<input_file_name>,<output_plot_directory>,<batch_mode_flag>)
```
with 
| Argument                  | Default setting        | Description                                                                                    |
| ------------------------- | ---------------------- | ---------------------------------------------------------------------------------------------- |
| `<input_file_name>`       | &laquo;none&raquo;     | Name of input file produced in step 3️⃣                                                         |
| `<output_plot_directory>` | &laquo;none&raquo;     | Name of directory to store produced plots in                                                   |
| `<batch_mode_flag>`       | `false`                | Flag indicating interactive (`false`) or batch mode (`true`)                                   |


[^1]: The Summer 2020/2021 student projects uses python-generated CSV files as input for training and as output from testing. The internal tabuiar stucture of these files is shown in   
[^2]: :hammer_and_wrench: TODO: allow user-defined file names in plotting scripts `plotPi.C`, `plotPi0.C`, `plotPiCharged.C` and `plotJets.c`.
[^3]: <a name="compile">It is recommended to run the scripts in batch mode (`-b` option in the `root` command line &ndash; the `-q` option just terminates `root` after the script is executed. Also, to speed up future invacations of the plotting script, it is useful to compile the script by adding the `++` after the file extension `.C` when compiling the script for the first time orr after `ClusterTreePlotter.C` has been changed. A repeated invocation of the same script can then use the command line `root -l -b -q plotPiCharged.C+` with the a single `+` added after the file extension.</a> 
[^4]: 🛠️:exclamation::exclamation: There is a limitation in the present implementation of `plotSummary.C`. To avoid crashes and unpredictable behaviour, the input file name should always contain a path. This means that instead of using `ml_jets_summary.root` one should use `./ml_jets_summary.root` if the input file is in the present working directory. The `plots` directory needs to exist, as in case of the plots with the distributions. Future implementations should allow the user to provide a valid path other than this default option.  
