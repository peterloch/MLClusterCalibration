# MLClusterCalibration

This respository contains code to plot responses and other cluster features in the context of the ML-based topo-cluster calibration project. In addition several scripts are available converting inputs from root to csv and vice versa, setup the environment and others. 

## Setup

## Generating response plots 🆕

Plotting uses the `ROOT` tuple as input. This tuple can be constructed from a csv file by 
```
root -l 'readCSV.C("results.csv","ml_pions.root")'
```
for single particles (typically a mixed file with clusters from neutral and charged pions) or
```
root -l `readCSV.C("results.csv","ml_jets.root")'
```
for jets. **It is highly recommended to use the output (ROOT) file names given in these examples. They are expected by the plotting scripts.** [^1]
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

[^1]: :hammer_and_wrench: Allow user-defined file names in plotting scripts `plotPi.C`, `plotPi0.C`, `plotPiCharged.C` and `plotJets.c`.   

## Generating summary plots
