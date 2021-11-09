
#include <TFile.h>
#include <TTree.h>

#include "ClusterTreePlotter.C"

#include <string>

void plotPi0() { 
  std::string fname("ml_pions.root");
  int pdgId(111);
  TFile* f = new TFile(fname.c_str(),"READ"); 
  if ( f != nullptr ) { 
    TTree* t = (TTree*)f->FindObjectAny("ClusterTree"); 
    if ( t == nullptr ) { return; } 
    ClusterTreePlotter* pl = new ClusterTreePlotter(t);
    pl->Loop(pdgId,true); 
  }
}
