
#include <TFile.h>
#include <TTree.h>

#include <string>

void readCSV(const std::string& csvFileName,const std::string& rootFileName) {

  TFile* outf = new TFile(rootFileName.c_str(),"RECREATE"); 
  TTree* tree = new TTree("ClusterTree","ClusterTree"); 
  tree->ReadFile(csvFileName.c_str(),"",','); 
  tree->Write();
  outf->Close();
 
}
