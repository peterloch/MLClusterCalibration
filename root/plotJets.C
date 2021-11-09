
#include <TFile.h>
#include <TTree.h>

#include "ClusterTreePlotter.C"

#include <string>

#include <iostream>

void plotJets() { 
  std::string fname("ml_jets.root");
  int  pdgId(-1);
  bool absPdg(false); 
  TFile* f = new TFile(fname.c_str(),"READ"); 
  if ( f != nullptr ) { 
    TTree* t = (TTree*)f->FindObjectAny("ClusterTree"); 
    if ( t == nullptr ) { return; } 
    ClusterTreePlotter* pl = new ClusterTreePlotter(t);
    pl->setJetPtMin    (ClusterTreePlotter::JetScale::LCJES,20.);
    pl->setJetAbsRapMax(ClusterTreePlotter::JetScale::LCJES,0.4);
    std::cout << *pl;
    pl->Loop(pdgId,absPdg); 
  }
}
