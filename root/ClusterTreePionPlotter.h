//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 20 10:05:15 2021 by ROOT version 6.20/06
// from TTree ClusterTree/ClusterTree
// found on file: ML/ml_pions.root
//////////////////////////////////////////////////////////

#ifndef ClusterTreePionPlotter_h
#define ClusterTreePionPlotter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>

// Header file for the classes stored in the TTree if any.

class ClusterTreePionPlotter {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         entry;
   Float_t         runNumber;
   Float_t         eventNumber;
   Float_t         truthE;
   Float_t         truthPt;
   Float_t         truthEta;
   Float_t         truthPhi;
   Float_t         truthPDG;
   Float_t         nCluster;
   Float_t         clusterIndex;
   Float_t         cluster_nCells;
   Float_t         cluster_nCells_tot;
   Float_t         clusterECalib;
   Float_t         clusterPtCalib;
   Float_t         clusterEtaCalib;
   Float_t         clusterPhiCalib;
   Float_t         cluster_sumCellECalib;
   Float_t         cluster_fracECalib;
   Float_t         cluster_fracECalib_ref;
   Float_t         clusterE;
   Float_t         clusterPt;
   Float_t         clusterEta;
   Float_t         clusterPhi;
   Float_t         cluster_sumCellE;
   Float_t         cluster_time;
   Float_t         cluster_fracE;
   Float_t         cluster_fracE_ref;
   Float_t         cluster_EM_PROBABILITY;
   Float_t         cluster_HAD_WEIGHT;
   Float_t         cluster_OOC_WEIGHT;
   Float_t         cluster_DM_WEIGHT;
   Float_t         cluster_ENG_CALIB_TOT;
   Float_t         cluster_ENG_CALIB_OUT_T;
   Float_t         cluster_ENG_CALIB_DEAD_TOT;
   Float_t         cluster_CENTER_MAG;
   Float_t         cluster_FIRST_ENG_DENS;
   Float_t         cluster_FIRST_PHI;
   Float_t         cluster_FIRST_ETA;
   Float_t         cluster_SECOND_R;
   Float_t         cluster_SECOND_LAMBDA;
   Float_t         cluster_DELTA_PHI;
   Float_t         cluster_DELTA_THETA;
   Float_t         cluster_DELTA_ALPHA;
   Float_t         cluster_CENTER_X;
   Float_t         cluster_CENTER_Y;
   Float_t         cluster_CENTER_Z;
   Float_t         cluster_CENTER_LAMBDA;
   Float_t         cluster_LATERAL;
   Float_t         cluster_LONGITUDINAL;
   Float_t         cluster_ENG_FRAC_EM;
   Float_t         cluster_ENG_FRAC_MAX;
   Float_t         cluster_ENG_FRAC_CORE;
   Float_t         cluster_SECOND_ENG_DENS;
   Float_t         cluster_ISOLATION;
   Float_t         cluster_ENG_BAD_CELLS;
   Float_t         cluster_N_BAD_CELLS;
   Float_t         cluster_N_BAD_CELLS_CORR;
   Float_t         cluster_BAD_CELLS_CORR_E;
   Float_t         cluster_BADLARQ_FRAC;
   Float_t         cluster_ENG_POS;
   Float_t         cluster_SIGNIFICANCE;
   Float_t         cluster_CELL_SIGNIFICANCE;
   Float_t         cluster_CELL_SIG_SAMPLING;
   Float_t         cluster_AVG_LAR_Q;
   Float_t         cluster_AVG_TILE_Q;
   Float_t         cluster_ENG_BAD_HV_CELLS;
   Float_t         cluster_N_BAD_HV_CELLS;
   Float_t         cluster_PTD;
   Float_t         cluster_MASS;
   Float_t         cluster_SECOND_TIME;
   Float_t         CalibratedE;
   Float_t         Delta_Calib_E ;
   Float_t         Delta_E;

   // List of branches
   TBranch        *b_entry;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_truthE;   //!
   TBranch        *b_truthPt;   //!
   TBranch        *b_truthEta;   //!
   TBranch        *b_truthPhi;   //!
   TBranch        *b_truthPDG;   //!
   TBranch        *b_nCluster;   //!
   TBranch        *b_clusterIndex;   //!
   TBranch        *b_cluster_nCells;   //!
   TBranch        *b_cluster_nCells_tot;   //!
   TBranch        *b_clusterECalib;   //!
   TBranch        *b_clusterPtCalib;   //!
   TBranch        *b_clusterEtaCalib;   //!
   TBranch        *b_clusterPhiCalib;   //!
   TBranch        *b_cluster_sumCellECalib;   //!
   TBranch        *b_cluster_fracECalib;   //!
   TBranch        *b_cluster_fracECalib_ref;   //!
   TBranch        *b_clusterE;   //!
   TBranch        *b_clusterPt;   //!
   TBranch        *b_clusterEta;   //!
   TBranch        *b_clusterPhi;   //!
   TBranch        *b_cluster_sumCellE;   //!
   TBranch        *b_cluster_time;   //!
   TBranch        *b_cluster_fracE;   //!
   TBranch        *b_cluster_fracE_ref;   //!
   TBranch        *b_cluster_EM_PROBABILITY;   //!
   TBranch        *b_cluster_HAD_WEIGHT;   //!
   TBranch        *b_cluster_OOC_WEIGHT;   //!
   TBranch        *b_cluster_DM_WEIGHT;   //!
   TBranch        *b_cluster_ENG_CALIB_TOT;   //!
   TBranch        *b_cluster_ENG_CALIB_OUT_T;   //!
   TBranch        *b_cluster_ENG_CALIB_DEAD_TOT;   //!
   TBranch        *b_cluster_CENTER_MAG;   //!
   TBranch        *b_cluster_FIRST_ENG_DENS;   //!
   TBranch        *b_cluster_FIRST_PHI;   //!
   TBranch        *b_cluster_FIRST_ETA;   //!
   TBranch        *b_cluster_SECOND_R;   //!
   TBranch        *b_cluster_SECOND_LAMBDA;   //!
   TBranch        *b_cluster_DELTA_PHI;   //!
   TBranch        *b_cluster_DELTA_THETA;   //!
   TBranch        *b_cluster_DELTA_ALPHA;   //!
   TBranch        *b_cluster_CENTER_X;   //!
   TBranch        *b_cluster_CENTER_Y;   //!
   TBranch        *b_cluster_CENTER_Z;   //!
   TBranch        *b_cluster_CENTER_LAMBDA;   //!
   TBranch        *b_cluster_LATERAL;   //!
   TBranch        *b_cluster_LONGITUDINAL;   //!
   TBranch        *b_cluster_ENG_FRAC_EM;   //!
   TBranch        *b_cluster_ENG_FRAC_MAX;   //!
   TBranch        *b_cluster_ENG_FRAC_CORE;   //!
   TBranch        *b_cluster_SECOND_ENG_DENS;   //!
   TBranch        *b_cluster_ISOLATION;   //!
   TBranch        *b_cluster_ENG_BAD_CELLS;   //!
   TBranch        *b_cluster_N_BAD_CELLS;   //!
   TBranch        *b_cluster_N_BAD_CELLS_CORR;   //!
   TBranch        *b_cluster_BAD_CELLS_CORR_E;   //!
   TBranch        *b_cluster_BADLARQ_FRAC;   //!
   TBranch        *b_cluster_ENG_POS;   //!
   TBranch        *b_cluster_SIGNIFICANCE;   //!
   TBranch        *b_cluster_CELL_SIGNIFICANCE;   //!
   TBranch        *b_cluster_CELL_SIG_SAMPLING;   //!
   TBranch        *b_cluster_AVG_LAR_Q;   //!
   TBranch        *b_cluster_AVG_TILE_Q;   //!
   TBranch        *b_cluster_ENG_BAD_HV_CELLS;   //!
   TBranch        *b_cluster_N_BAD_HV_CELLS;   //!
   TBranch        *b_cluster_PTD;   //!
   TBranch        *b_cluster_MASS;   //!
   TBranch        *b_cluster_SECOND_TIME;   //!
   TBranch        *b_CalibratedE;   //!
   TBranch        *b_Delta_Calib_E ;   //!
   TBranch        *b_Delta_E;   //!

   ClusterTreePionPlotter(TTree *tree=0);
   virtual ~ClusterTreePionPlotter();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(double pdgId=0,bool absVal=false);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   virtual void     binNormalize(TH1* h); 
};

#endif

#ifdef ClusterTreePionPlotter_cxx
ClusterTreePionPlotter::ClusterTreePionPlotter(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ML/ml_pions.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("ML/ml_pions.root");
      }
      f->GetObject("ClusterTree",tree);

   }
   Init(tree);
}

ClusterTreePionPlotter::~ClusterTreePionPlotter()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ClusterTreePionPlotter::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ClusterTreePionPlotter::LoadTree(Long64_t entry)
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

void ClusterTreePionPlotter::Init(TTree *tree)
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

   fChain->SetBranchAddress("entry", &entry, &b_entry);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("truthE", &truthE, &b_truthE);
   fChain->SetBranchAddress("truthPt", &truthPt, &b_truthPt);
   fChain->SetBranchAddress("truthEta", &truthEta, &b_truthEta);
   fChain->SetBranchAddress("truthPhi", &truthPhi, &b_truthPhi);
   fChain->SetBranchAddress("truthPDG", &truthPDG, &b_truthPDG);
   fChain->SetBranchAddress("nCluster", &nCluster, &b_nCluster);
   fChain->SetBranchAddress("clusterIndex", &clusterIndex, &b_clusterIndex);
   fChain->SetBranchAddress("cluster_nCells", &cluster_nCells, &b_cluster_nCells);
   fChain->SetBranchAddress("cluster_nCells_tot", &cluster_nCells_tot, &b_cluster_nCells_tot);
   fChain->SetBranchAddress("clusterECalib", &clusterECalib, &b_clusterECalib);
   fChain->SetBranchAddress("clusterPtCalib", &clusterPtCalib, &b_clusterPtCalib);
   fChain->SetBranchAddress("clusterEtaCalib", &clusterEtaCalib, &b_clusterEtaCalib);
   fChain->SetBranchAddress("clusterPhiCalib", &clusterPhiCalib, &b_clusterPhiCalib);
   fChain->SetBranchAddress("cluster_sumCellECalib", &cluster_sumCellECalib, &b_cluster_sumCellECalib);
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
   fChain->SetBranchAddress("CalibratedE", &CalibratedE, &b_CalibratedE);
   fChain->SetBranchAddress("Delta_Calib_E ", &Delta_Calib_E , &b_Delta_Calib_E );
   fChain->SetBranchAddress("Delta_E", &Delta_E, &b_Delta_E);
   Notify();
}

Bool_t ClusterTreePionPlotter::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ClusterTreePionPlotter::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ClusterTreePionPlotter::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef ClusterTreePionPlotter_cxx
