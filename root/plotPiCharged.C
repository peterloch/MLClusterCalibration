
#include <TFile.h>
#include <TTree.h>

#include "ClusterTreePionPlotter.C"

#include <string>

void plotPiCharged() { 
  std::string fname("ml_pions.root");
  int pdgId(211);
  TFile* f = new TFile(fname.c_str(),"READ"); 
  if ( f != nullptr ) { 
    TTree* t = (TTree*)f->FindObjectAny("ClusterTree"); 
    if ( t == nullptr ) { return; } 
    ClusterTreePionPlotter* pl = new ClusterTreePionPlotter(t);
    pl->Loop(pdgId,true); 
  }
}
