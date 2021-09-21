
#include <TFile.h>
#include <TTree.h>

#include "ClusterTreePionPlotter.C"

#include <string>

void plotPi() { 
  std::string fname("ml_pions.root");
  TFile* f = new TFile(fname.c_str(),"READ"); 
  if ( f != nullptr ) { 
    TTree* t = (TTree*)f->FindObjectAny("ClusterTree"); 
    if ( t == nullptr ) { return; } 
    ClusterTreePionPlotter* pl = new ClusterTreePionPlotter(t);
    pl->Loop(); 
  }
}
