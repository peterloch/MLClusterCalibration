

#include <TFile.h>
#include <TChain.h>

#include "ClusterTreeDemo.C"

#include <string>

#include <cstdio>

void plotJetResponse(const std::string& inFile="JZ3.full.topo-cluster.root",const std::string& outFile="JZ3.full.topo-cluster.hist.root",Long64_t kentries=-1) {
  // open file
  TFile* f = new TFile(inFile.c_str(),"READ");
  if ( f == nullptr ) { printf("[plotJetResponse(...)] ABRT cannot open file \042%s\042\n",inFile.c_str()); return; }
  // allocate TChain
  TChain* t = (TChain*)f->FindObjectAny("ClusterTree");
  if ( t == nullptr ) { printf("[plotJetResponse(...)] ABRT cannot access tree \042ClusterTree\042\n"); return; }
  printf("[plotJetResponse(...)] INFO found tree \042%s\042 in file \042%s\042\n",t->GetName(),f->GetName());
  // make plots
  ClusterTreeDemo* pdemo = new ClusterTreeDemo(t); 
  pdemo->Loop(outFile,kentries); 
}
