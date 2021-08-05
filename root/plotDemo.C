
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>

#include <string>

#include <cstdio>

#include "ClusterTreeDemo.C"

void plotDemo(const std::string& inFileName="jet.topo-cluster.pool.root",const std::string& outFileName="jet.topo-cluster.hist.root") { 
  
  TFile* pfile = new TFile(inFileName.c_str(),"READ"); 
  if ( pfile == nullptr ) { printf("[plotDemo] ABRT input file \042%s\042 not accessible\n",inFileName.c_str()); return;  }
  TTree* ptree = (TTree*)pfile->FindObjectAny("ClusterTree"); 
  if ( ptree == nullptr ) { printf("[plotDemo] ABRT tree \042ClusterTree\042 not accessible\n"); return;  }

  printf("[plotDemo] INFO found tree \042%s\042 in file \042%s\042\n",ptree->GetName(),pfile->GetName());

  ClusterTreeDemo* pdemo = new ClusterTreeDemo(ptree); 
  printf("[plotDemo] INFO instantiated ClusterTreeDemo at %p\n",(void*)pdemo);
  
  pdemo->Loop(outFileName); 
}
