
// #include <TTree.h>
// #include <TFile.h>

#include <ROOT/RDataFrame.hxx>

#include <string>


void convertToCSV(const std::string& inputFileName,const std::string& outputFileName,const std::string& treeName="ClusterTree") { 
  // create a data frame
  ROOT::RDataFrame rdf = ROOT::RDF::MakeCsvDataFrame(inputFileName); 
  // take and store a snapshot
  rdf.Snapshot(treeName,outputFileName); 
}

