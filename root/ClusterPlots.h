// -*- c++ -*-
#ifndef CLUSTERPLOTS_H
#define CLUSTERPLOTS_H

#include <TFile.h>
#include <TTree.h>

#include<string>

#include <cstdio>

template<class SERVER> class ClusterPlots : public SERVER
{
public:
  ClusterPlots();
  
  void setInputFile (const std::string& inputFile );
  void setOutputFile(const std::string& outputFile);
  void setTreeName  (const std::string& treeName  ); 

  const std::string& inputFileName () const; 
  const std::string& outputFileName() const;
  const std::string& treeName()       const;

  TTree* tree(); 
  TFile* inputFile(); 
  
  virtual void loop(const std::string& outFile,int kentries=-1);
  virtual void init();   
  virtual void loop(int nentries=-1); 

protected:

private:

  std::string m_treeName       = { "ClusterTree" };
  std::string m_outputFileName = { ""            };
  std::string m_inputFileName  = { ""            };
       
  TFile*      m_inputfile      = { (TFile*)0     };
  TTree*      m_tree           = { (TTree*)0     };

  bool        m_isSetup        = { false         }; 
};
#endif
