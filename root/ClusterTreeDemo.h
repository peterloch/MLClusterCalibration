// -*- c++ -*-
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 22 11:02:14 2021 by ROOT version 6.24/00
// from TTree ClusterTree/ClusterTree
// found on file: jet.topo-cluster.pool.root
//////////////////////////////////////////////////////////

#ifndef ClusterTreeDemo_h
#define ClusterTreeDemo_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <string>

#include <cstdio>

// Header file for the classes stored in the TTree if any.

class ClusterTreeDemo {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

  // Fixed size dimensions of array or collections stored in the TTree if any.

  // extra entry 
  Int_t            entry       = { -1 };
  // Declaration of leaf types
  Int_t           runNumber    = { 0  };
  Int_t           eventNumber  = { 0  };
  // ------------------------------------------------------- [detector jet]
  Float_t         jetCalE      = { 0. };
  Float_t         jetCalPt     = { 0. };
  Float_t         jetCalEta    = { 0. };
  Float_t         jetCalPhi    = { 0. };
  Float_t         jetRawE      = { 0. };
  Float_t         jetRawPt     = { 0. };
  Float_t         jetRawEta    = { 0. };
  Float_t         jetRawPhi    = { 0. };
  Int_t           jetNConst    = { 0  };    
  // ------------------------------------------------------- [truth jet]
  Float_t         truthJetMatchRadius;                                     // dR = sqrt(deltaRap^2+deltaPhi^2)
  Float_t         truthJetE    = { 0. }; 
  Float_t         truthJetPt   = { 0. };
  Float_t         truthJetRap  = { 0. };
  Float_t         truthJetPhi  = { 0. };
  // ------------------------------------------------------- [cluster stuff - same as single particles]
  Int_t           nCluster                     = { 0  };  
  Int_t           clusterIndex 		       = { 0  };
  Int_t           cluster_nCells 	       = { 0  };
  Int_t           cluster_nCells_tot	       = { 0  };
  Float_t         clusterECalib  	       = { 0. };
  Float_t         clusterPtCalib	       = { 0. };
  Float_t         clusterEtaCalib	       = { 0. };
  Float_t         clusterPhiCalib	       = { 0. };
  Float_t         cluster_sumCellECalib        = { 0. };
  Float_t         cluster_fracECalib	       = { 0. };
  Float_t         cluster_fracECalib_ref       = { 0. };
  Float_t         clusterE                     = { 0. };
  Float_t         clusterPt 		       = { 0. };
  Float_t         clusterEta 		       = { 0. };
  Float_t         clusterPhi 		       = { 0. };
  Float_t         cluster_sumCellE 	       = { 0. };
  Float_t         cluster_time 		       = { 0. };
  Float_t         cluster_fracE 	       = { 0. };
  Float_t         cluster_fracE_ref 	       = { 0. };
  Float_t         cluster_EM_PROBABILITY       = { 0. }; 
  Float_t         cluster_HAD_WEIGHT           = { 0. };
  Float_t         cluster_OOC_WEIGHT 	       = { 0. };
  Float_t         cluster_DM_WEIGHT 	       = { 0. };
  Float_t         cluster_ENG_CALIB_TOT        = { 0. };
  Float_t         cluster_ENG_CALIB_OUT_T      = { 0. };
  Float_t         cluster_ENG_CALIB_DEAD_TOT   = { 0. };
  Float_t         cluster_CENTER_MAG           = { 0. };
  Float_t         cluster_FIRST_ENG_DENS       = { 0. };
  Float_t         cluster_FIRST_PHI	       = { 0. };
  Float_t         cluster_FIRST_ETA	       = { 0. };
  Float_t         cluster_SECOND_R	       = { 0. };
  Float_t         cluster_SECOND_LAMBDA        = { 0. };
  Float_t         cluster_DELTA_PHI 	       = { 0. };
  Float_t         cluster_DELTA_THETA	       = { 0. };
  Float_t         cluster_DELTA_ALPHA	       = { 0. };
  Float_t         cluster_CENTER_X	       = { 0. };
  Float_t         cluster_CENTER_Y	       = { 0. };
  Float_t         cluster_CENTER_Z	       = { 0. };
  Float_t         cluster_CENTER_LAMBDA        = { 0. };
  Float_t         cluster_LATERAL	       = { 0. };
  Float_t         cluster_LONGITUDINAL	       = { 0. };
  Float_t         cluster_ENG_FRAC_EM	       = { 0. };
  Float_t         cluster_ENG_FRAC_MAX 	       = { 0. };
  Float_t         cluster_ENG_FRAC_CORE        = { 0. };
  Float_t         cluster_SECOND_ENG_DENS      = { 0. };
  Float_t         cluster_ISOLATION 	       = { 0. };
  Float_t         cluster_ENG_BAD_CELLS        = { 0. };
  Float_t         cluster_N_BAD_CELLS 	       = { 0. };
  Float_t         cluster_N_BAD_CELLS_CORR     = { 0. };
  Float_t         cluster_BAD_CELLS_CORR_E     = { 0. };
  Float_t         cluster_BADLARQ_FRAC 	       = { 0. };
  Float_t         cluster_ENG_POS	       = { 0. };
  Float_t         cluster_SIGNIFICANCE	       = { 0. };
  Float_t         cluster_CELL_SIGNIFICANCE    = { 0. };
  Float_t         cluster_CELL_SIG_SAMPLING    = { 0. };
  Float_t         cluster_AVG_LAR_Q	       = { 0. };
  Float_t         cluster_AVG_TILE_Q	       = { 0. };
  Float_t         cluster_ENG_BAD_HV_CELLS     = { 0. };
  Float_t         cluster_N_BAD_HV_CELLS       = { 0. };
  Float_t         cluster_PTD		       = { 0. };
  Float_t         cluster_MASS		       = { 0. };
  Float_t         cluster_SECOND_TIME	       = { 0. };
  Float_t         CalibratedE		       = { 0. };
  Float_t         Delta_Calib_E 	       = { 0. };
  Float_t         Delta_E                      = { 0. };             
  

   // List of branches
  TBranch*        b_entry                       = { (TBranch*)0 };  //!
  TBranch*        b_runNumber                   = { (TBranch*)0 };  //!
  TBranch*        b_eventNumber                 = { (TBranch*)0 };  //!
  TBranch*        b_jetCalE                     = { (TBranch*)0 };  //!
  TBranch*        b_jetCalPt                    = { (TBranch*)0 };  //!
  TBranch*        b_jetCalEta                   = { (TBranch*)0 };  //!
  TBranch*        b_jetCalPhi                   = { (TBranch*)0 };  //!
  TBranch*        b_jetRawE                     = { (TBranch*)0 };  //!
  TBranch*        b_jetRawPt                    = { (TBranch*)0 };  //!
  TBranch*        b_jetRawEta                   = { (TBranch*)0 };  //!
  TBranch*        b_jetRawPhi                   = { (TBranch*)0 };  //!
  TBranch*        b_jetNConst                   = { (TBranch*)0 };  //!
  TBranch*        b_truthJetMatchRadius         = { (TBranch*)0 };  //!
  TBranch*        b_truthJetE                   = { (TBranch*)0 };  //!
  TBranch*        b_truthJetPt                  = { (TBranch*)0 };  //!
  TBranch*        b_truthJetRap                 = { (TBranch*)0 };  //!
  TBranch*        b_truthJetPhi                 = { (TBranch*)0 };  //!
  TBranch*        b_nCluster                    = { (TBranch*)0 };  //!
  TBranch*        b_clusterIndex                = { (TBranch*)0 };  //!
  TBranch*        b_cluster_nCells              = { (TBranch*)0 };  //!
  TBranch*        b_cluster_nCells_tot          = { (TBranch*)0 };  //!
  TBranch*        b_clusterECalib               = { (TBranch*)0 };  //!
  TBranch*        b_clusterPtCalib              = { (TBranch*)0 };  //!
  TBranch*        b_clusterEtaCalib             = { (TBranch*)0 };  //!
  TBranch*        b_clusterPhiCalib             = { (TBranch*)0 };  //!
  TBranch*        b_cluster_sumCellECAlib       = { (TBranch*)0 };  //!
  TBranch*        b_cluster_fracECalib          = { (TBranch*)0 };  //!
  TBranch*        b_cluster_fracECalib_ref      = { (TBranch*)0 };  //!
  TBranch*        b_clusterE                    = { (TBranch*)0 };  //!
  TBranch*        b_clusterPt                   = { (TBranch*)0 };  //!
  TBranch*        b_clusterEta                  = { (TBranch*)0 };  //!
  TBranch*        b_clusterPhi                  = { (TBranch*)0 };  //!
  TBranch*        b_cluster_sumCellE            = { (TBranch*)0 };  //!
  TBranch*        b_cluster_time                = { (TBranch*)0 };  //!
  TBranch*        b_cluster_fracE               = { (TBranch*)0 };  //!
  TBranch*        b_cluster_fracE_ref           = { (TBranch*)0 };  //!
  TBranch*        b_cluster_EM_PROBABILITY      = { (TBranch*)0 };  //!
  TBranch*        b_cluster_HAD_WEIGHT          = { (TBranch*)0 };  //!
  TBranch*        b_cluster_OOC_WEIGHT          = { (TBranch*)0 };  //!
  TBranch*        b_cluster_DM_WEIGHT           = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_CALIB_TOT       = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_CALIB_OUT_T     = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_CALIB_DEAD_TOT  = { (TBranch*)0 };  //!
  TBranch*        b_cluster_CENTER_MAG          = { (TBranch*)0 };  //!
  TBranch*        b_cluster_FIRST_ENG_DENS      = { (TBranch*)0 };  //!
  TBranch*        b_cluster_FIRST_PHI           = { (TBranch*)0 };  //!
  TBranch*        b_cluster_FIRST_ETA           = { (TBranch*)0 };  //!
  TBranch*        b_cluster_SECOND_R            = { (TBranch*)0 };  //!
  TBranch*        b_cluster_SECOND_LAMBDA       = { (TBranch*)0 };  //!
  TBranch*        b_cluster_DELTA_PHI           = { (TBranch*)0 };  //!
  TBranch*        b_cluster_DELTA_THETA         = { (TBranch*)0 };  //!
  TBranch*        b_cluster_DELTA_ALPHA         = { (TBranch*)0 };  //!
  TBranch*        b_cluster_CENTER_X            = { (TBranch*)0 };  //!
  TBranch*        b_cluster_CENTER_Y            = { (TBranch*)0 };  //!
  TBranch*        b_cluster_CENTER_Z            = { (TBranch*)0 };  //!
  TBranch*        b_cluster_CENTER_LAMBDA       = { (TBranch*)0 };  //!
  TBranch*        b_cluster_LATERAL             = { (TBranch*)0 };  //!
  TBranch*        b_cluster_LONGITUDINAL        = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_FRAC_EM         = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_FRAC_MAX        = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_FRAC_CORE       = { (TBranch*)0 };  //!
  TBranch*        b_cluster_SECOND_ENG_DENS     = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ISOLATION           = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_BAD_CELLS       = { (TBranch*)0 };  //!
  TBranch*        b_cluster_N_BAD_CELLS         = { (TBranch*)0 };  //!
  TBranch*        b_cluster_N_BAD_CELLS_CORR    = { (TBranch*)0 };  //!
  TBranch*        b_cluster_BAD_CELLS_CORR_E    = { (TBranch*)0 };  //!
  TBranch*        b_cluster_BADLARQ_FRAC        = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_POS             = { (TBranch*)0 };  //!
  TBranch*        b_cluster_SIGNIFICANCE        = { (TBranch*)0 };  //!
  TBranch*        b_cluster_CELL_SIGNIFICANCE   = { (TBranch*)0 };  //!
  TBranch*        b_cluster_CELL_SIG_SAMPLING   = { (TBranch*)0 };  //!
  TBranch*        b_cluster_AVG_LAR_Q           = { (TBranch*)0 };  //!
  TBranch*        b_cluster_AVG_TILE_Q          = { (TBranch*)0 };  //!
  TBranch*        b_cluster_ENG_BAD_HV_CELLS    = { (TBranch*)0 };  //!
  TBranch*        b_cluster_N_BAD_HV_CELLS      = { (TBranch*)0 };  //!
  TBranch*        b_cluster_PTD                 = { (TBranch*)0 };  //!
  TBranch*        b_cluster_MASS                = { (TBranch*)0 };  //!
  TBranch*        b_cluster_SECOND_TIME         = { (TBranch*)0 };  //!
  TBranch*        b_CalibratedE                 = { (TBranch*)0 };  //!
  TBranch*        b_Delta_Calib_E               = { (TBranch*)0 };  //!
  TBranch*        b_Delta_E                     = { (TBranch*)0 };  //!

  ClusterTreeDemo(TTree *tree=0);
  virtual ~ClusterTreeDemo();
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(const std::string& outFile,Long64_t kentries=-1);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);
  
  bool   newEvent(); 
  bool   newJet(); 
  double stdPhi(double phi); 

  int    m_runNumber   = { -1  };
  int    m_eventNumber = { -1  };

  int    m_jetNConst   = { -1  };
  double m_jetCalE     = { -1. }; 
};

#endif

#ifdef ClusterTreeDemo_cxx
ClusterTreeDemo::ClusterTreeDemo(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("jet.topo-cluster.pool.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("jet.topo-cluster.pool.root");
      }
      f->GetObject("ClusterTree",tree);

   }
   Init(tree);
}

ClusterTreeDemo::~ClusterTreeDemo()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ClusterTreeDemo::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ClusterTreeDemo::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void ClusterTreeDemo::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   if ( fChain->FindLeaf("entry") != nullptr ) { printf("[ClusterTreeDemo::Init()] INFO Tree \042%s\042 added leaf [%+02i]{entry}\n",fChain->GetName(),fChain->SetBranchAddress("entry",&entry,&b_entry)); }
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("jetCalE", &jetCalE, &b_jetCalE);
   fChain->SetBranchAddress("jetCalPt", &jetCalPt, &b_jetCalPt);
   fChain->SetBranchAddress("jetCalEta", &jetCalEta, &b_jetCalEta);
   fChain->SetBranchAddress("jetCalPhi", &jetCalPhi, &b_jetCalPhi);
   fChain->SetBranchAddress("jetRawE", &jetRawE, &b_jetRawE);
   fChain->SetBranchAddress("jetRawPt", &jetRawPt, &b_jetRawPt);
   fChain->SetBranchAddress("jetRawEta", &jetRawEta, &b_jetRawEta);
   fChain->SetBranchAddress("jetRawPhi", &jetRawPhi, &b_jetRawPhi);
   fChain->SetBranchAddress("jetNConst", &jetNConst, &b_jetNConst);
   fChain->SetBranchAddress("truthJetMatchRadius", &truthJetMatchRadius, &b_truthJetMatchRadius);
   fChain->SetBranchAddress("truthJetE", &truthJetE, &b_truthJetE);
   fChain->SetBranchAddress("truthJetPt", &truthJetPt, &b_truthJetPt);
   fChain->SetBranchAddress("truthJetRap", &truthJetRap, &b_truthJetRap);
   fChain->SetBranchAddress("truthJetPhi", &truthJetPhi, &b_truthJetPhi);
   fChain->SetBranchAddress("nCluster", &nCluster, &b_nCluster);
   fChain->SetBranchAddress("clusterIndex", &clusterIndex, &b_clusterIndex);
   fChain->SetBranchAddress("cluster_nCells", &cluster_nCells, &b_cluster_nCells);
   fChain->SetBranchAddress("cluster_nCells_tot", &cluster_nCells_tot, &b_cluster_nCells_tot);
   fChain->SetBranchAddress("clusterECalib", &clusterECalib, &b_clusterECalib);
   fChain->SetBranchAddress("clusterPtCalib", &clusterPtCalib, &b_clusterPtCalib);
   fChain->SetBranchAddress("clusterEtaCalib", &clusterEtaCalib, &b_clusterEtaCalib);
   fChain->SetBranchAddress("clusterPhiCalib", &clusterPhiCalib, &b_clusterPhiCalib);
   fChain->SetBranchAddress("cluster_sumCellECalib", &cluster_sumCellECalib, &b_cluster_sumCellECAlib);
   fChain->SetBranchAddress("cluster_fracECalib", &cluster_fracECalib, &b_cluster_fracECalib);
   fChain->SetBranchAddress("cluster_fracECalib_ref", &cluster_fracECalib_ref, &b_cluster_fracECalib_ref);
   fChain->SetBranchAddress("clusterE", &clusterE, &b_clusterE);
   fChain->SetBranchAddress("clusterPt", &clusterPt, &b_clusterPt);
   fChain->SetBranchAddress("clusterEta", &clusterEta, &b_clusterEta);
   fChain->SetBranchAddress("clusterPhi", &clusterPhi, &b_clusterPhi);
   fChain->SetBranchAddress("cluster_sumCellE", &cluster_sumCellE, &b_cluster_sumCellE);
   fChain->SetBranchAddress("cluster_time", &cluster_time, &b_cluster_time);
   fChain->SetBranchAddress("cluster_fracE", &cluster_fracE, &b_cluster_fracE);
   fChain->SetBranchAddress("cluster_fracE_ref", &cluster_fracE_ref, &b_cluster_fracE_ref);
   fChain->SetBranchAddress("cluster_EM_PROBABILITY", &cluster_EM_PROBABILITY, &b_cluster_EM_PROBABILITY);
   fChain->SetBranchAddress("cluster_HAD_WEIGHT", &cluster_HAD_WEIGHT, &b_cluster_HAD_WEIGHT);
   fChain->SetBranchAddress("cluster_OOC_WEIGHT", &cluster_OOC_WEIGHT, &b_cluster_OOC_WEIGHT);
   fChain->SetBranchAddress("cluster_DM_WEIGHT", &cluster_DM_WEIGHT, &b_cluster_DM_WEIGHT);
   fChain->SetBranchAddress("cluster_ENG_CALIB_TOT", &cluster_ENG_CALIB_TOT, &b_cluster_ENG_CALIB_TOT);
   fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_T", &cluster_ENG_CALIB_OUT_T, &b_cluster_ENG_CALIB_OUT_T);
   fChain->SetBranchAddress("cluster_ENG_CALIB_DEAD_TOT", &cluster_ENG_CALIB_DEAD_TOT, &b_cluster_ENG_CALIB_DEAD_TOT);
   fChain->SetBranchAddress("cluster_CENTER_MAG", &cluster_CENTER_MAG, &b_cluster_CENTER_MAG);
   fChain->SetBranchAddress("cluster_FIRST_ENG_DENS", &cluster_FIRST_ENG_DENS, &b_cluster_FIRST_ENG_DENS);
   fChain->SetBranchAddress("cluster_FIRST_PHI", &cluster_FIRST_PHI, &b_cluster_FIRST_PHI);
   fChain->SetBranchAddress("cluster_FIRST_ETA", &cluster_FIRST_ETA, &b_cluster_FIRST_ETA);
   fChain->SetBranchAddress("cluster_SECOND_R", &cluster_SECOND_R, &b_cluster_SECOND_R);
   fChain->SetBranchAddress("cluster_SECOND_LAMBDA", &cluster_SECOND_LAMBDA, &b_cluster_SECOND_LAMBDA);
   fChain->SetBranchAddress("cluster_DELTA_PHI", &cluster_DELTA_PHI, &b_cluster_DELTA_PHI);
   fChain->SetBranchAddress("cluster_DELTA_THETA", &cluster_DELTA_THETA, &b_cluster_DELTA_THETA);
   fChain->SetBranchAddress("cluster_DELTA_ALPHA", &cluster_DELTA_ALPHA, &b_cluster_DELTA_ALPHA);
   fChain->SetBranchAddress("cluster_CENTER_X", &cluster_CENTER_X, &b_cluster_CENTER_X);
   fChain->SetBranchAddress("cluster_CENTER_Y", &cluster_CENTER_Y, &b_cluster_CENTER_Y);
   fChain->SetBranchAddress("cluster_CENTER_Z", &cluster_CENTER_Z, &b_cluster_CENTER_Z);
   fChain->SetBranchAddress("cluster_CENTER_LAMBDA", &cluster_CENTER_LAMBDA, &b_cluster_CENTER_LAMBDA);
   fChain->SetBranchAddress("cluster_LATERAL", &cluster_LATERAL, &b_cluster_LATERAL);
   fChain->SetBranchAddress("cluster_LONGITUDINAL", &cluster_LONGITUDINAL, &b_cluster_LONGITUDINAL);
   fChain->SetBranchAddress("cluster_ENG_FRAC_EM", &cluster_ENG_FRAC_EM, &b_cluster_ENG_FRAC_EM);
   fChain->SetBranchAddress("cluster_ENG_FRAC_MAX", &cluster_ENG_FRAC_MAX, &b_cluster_ENG_FRAC_MAX);
   fChain->SetBranchAddress("cluster_ENG_FRAC_CORE", &cluster_ENG_FRAC_CORE, &b_cluster_ENG_FRAC_CORE);
   fChain->SetBranchAddress("cluster_SECOND_ENG_DENS", &cluster_SECOND_ENG_DENS, &b_cluster_SECOND_ENG_DENS);
   fChain->SetBranchAddress("cluster_ISOLATION", &cluster_ISOLATION, &b_cluster_ISOLATION);
   fChain->SetBranchAddress("cluster_ENG_BAD_CELLS", &cluster_ENG_BAD_CELLS, &b_cluster_ENG_BAD_CELLS);
   fChain->SetBranchAddress("cluster_N_BAD_CELLS", &cluster_N_BAD_CELLS, &b_cluster_N_BAD_CELLS);
   fChain->SetBranchAddress("cluster_N_BAD_CELLS_CORR", &cluster_N_BAD_CELLS_CORR, &b_cluster_N_BAD_CELLS_CORR);
   fChain->SetBranchAddress("cluster_BAD_CELLS_CORR_E", &cluster_BAD_CELLS_CORR_E, &b_cluster_BAD_CELLS_CORR_E);
   fChain->SetBranchAddress("cluster_BADLARQ_FRAC", &cluster_BADLARQ_FRAC, &b_cluster_BADLARQ_FRAC);
   fChain->SetBranchAddress("cluster_ENG_POS", &cluster_ENG_POS, &b_cluster_ENG_POS);
   fChain->SetBranchAddress("cluster_SIGNIFICANCE", &cluster_SIGNIFICANCE, &b_cluster_SIGNIFICANCE);
   fChain->SetBranchAddress("cluster_CELL_SIGNIFICANCE", &cluster_CELL_SIGNIFICANCE, &b_cluster_CELL_SIGNIFICANCE);
   fChain->SetBranchAddress("cluster_CELL_SIG_SAMPLING", &cluster_CELL_SIG_SAMPLING, &b_cluster_CELL_SIG_SAMPLING);
   fChain->SetBranchAddress("cluster_AVG_LAR_Q", &cluster_AVG_LAR_Q, &b_cluster_AVG_LAR_Q);
   fChain->SetBranchAddress("cluster_AVG_TILE_Q", &cluster_AVG_TILE_Q, &b_cluster_AVG_TILE_Q);
   fChain->SetBranchAddress("cluster_ENG_BAD_HV_CELLS", &cluster_ENG_BAD_HV_CELLS, &b_cluster_ENG_BAD_HV_CELLS);
   fChain->SetBranchAddress("cluster_N_BAD_HV_CELLS", &cluster_N_BAD_HV_CELLS, &b_cluster_N_BAD_HV_CELLS);
   fChain->SetBranchAddress("cluster_PTD", &cluster_PTD, &b_cluster_PTD);
   fChain->SetBranchAddress("cluster_MASS", &cluster_MASS, &b_cluster_MASS);
   fChain->SetBranchAddress("cluster_SECOND_TIME", &cluster_SECOND_TIME, &b_cluster_SECOND_TIME);
   if ( fChain->FindLeaf("CalibratedE"  ) != nullptr ) { printf("[ClusterTreeDemo::Init()] INFO Tree \042%s\042 added leaf [%+02i]{CalibratedE}\n"  ,fChain->GetName(),fChain->SetBranchAddress("CalibratedE"  , &CalibratedE  , &b_CalibratedE  )); } 
   if ( fChain->FindLeaf("Delta_Calib_E") != nullptr ) { printf("[ClusterTreeDemo::Init()] INFO Tree \042%s\042 added leaf [%+02i]{Delta_Calib_E}\n",fChain->GetName(),fChain->SetBranchAddress("Delta_Calib_E", &Delta_Calib_E, &b_Delta_Calib_E)); }
   if ( fChain->FindLeaf("Delta_E"      ) != nullptr ) { printf("[ClusterTreeDemo::Init()] INFO Tree \042%s\042 added leaf [%+02i]{Delta_E}\n"      ,fChain->GetName(),fChain->SetBranchAddress("Delta_E"      , &Delta_E      , &b_Delta_E      )); } 
   Notify();
}

Bool_t ClusterTreeDemo::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ClusterTreeDemo::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ClusterTreeDemo::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ClusterTreeDemo_cxx
