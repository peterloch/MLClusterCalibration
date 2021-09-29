// -*- c++ -*-
//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Sep 20 10:05:15 2021 by ROOT version 6.20/06
// from TTree ClusterTree/ClusterTree
// found on file: ML/ml_pions.root
//////////////////////////////////////////////////////////

#ifndef ClusterTreePlotter_h
#define ClusterTreePlotter_h

#include <TROOT.h>

#include <TFile.h>
#include <TChain.h>
#include <TTree.h>
#include <TBranch.h>

#include <vector>
#include <map>
#include <tuple>
#include <string>

#include <cstdio>
#include <cmath>

// Header file for the classes stored in the TTree if any.

class ClusterTreePionPlotter {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         entry         = { 0. };       
   Float_t         runNumber     = { 0. };
   Float_t         eventNumber   = { 0. };   
   // particle tuples
   Float_t         truthE        = { 0. };
   Float_t         truthPt 	 = { 0. };
   Float_t         truthEta 	 = { 0. };
   Float_t         truthPhi      = { 0. }; 
   Float_t         truthPDG;	 = { 0. };
   // jet tuples		 
   Float_t         jetCalE                   = { 0. };
   Float_t         jetCalPt		     = { 0. };
   Float_t         jetCalEta		     = { 0. };
   Float_t         jetCalPhi		     = { 0. };
   Float_t         jetRawE		     = { 0. };
   Float_t         jetRawPt                  = { 0. };
   Float_t         jetRawEta		     = { 0. };
   Float_t         jetRawPhi		     = { 0. };
   Int_t           jetNConst		     = { 0  };
   Float_t         truthJetMatchingRadius    = { 0. };
   Float_t         truthJetE                 = { 0. };
   Float_t         truthJetPt 		     = { 0. };
   Float_t         truthJetEta 		     = { 0. };
   Float_t         truthJetPhi 		     = { 0. };
   // cluster data			    
   Float_t         nCluster                       = { 0. };
   Float_t         clusterIndex 		  = { 0. };
   Float_t         cluster_nCells 		  = { 0. };
   Float_t         cluster_nCells_tot		  = { 0. };
   Float_t         clusterECalib		  = { 0. };
   Float_t         clusterPtCalib                 = { 0. };
   Float_t         clusterEtaCalib		  = { 0. };
   Float_t         clusterPhiCalib		  = { 0. };
   Float_t         cluster_sumCellECalib	  = { 0. };
   Float_t         cluster_fracECalib		  = { 0. };
   Float_t         cluster_fracECalib_ref         = { 0. };
   Float_t         clusterE			  = { 0. };
   Float_t         clusterPt			  = { 0. };
   Float_t         clusterEta			  = { 0. };
   Float_t         clusterPhi			  = { 0. };
   Float_t         cluster_sumCellE               = { 0. };
   Float_t         cluster_time 		  = { 0. };
   Float_t         cluster_fracE		  = { 0. };
   Float_t         cluster_fracE_ref		  = { 0. };
   Float_t         cluster_EM_PROBABILITY	  = { 0. };
   Float_t         cluster_HAD_WEIGHT             = { 0. };
   Float_t         cluster_OOC_WEIGHT		  = { 0. };
   Float_t         cluster_DM_WEIGHT		  = { 0. };
   Float_t         cluster_ENG_CALIB_TOT	  = { 0. };
   Float_t         cluster_ENG_CALIB_OUT_T	  = { 0. };
   Float_t         cluster_ENG_CALIB_DEAD_TOT     = { 0. };
   Float_t         cluster_CENTER_MAG		  = { 0. };
   Float_t         cluster_FIRST_ENG_DENS	  = { 0. };
   Float_t         cluster_FIRST_PHI		  = { 0. };
   Float_t         cluster_FIRST_ETA		  = { 0. };
   Float_t         cluster_SECOND_R               = { 0. };
   Float_t         cluster_SECOND_LAMBDA	  = { 0. };
   Float_t         cluster_DELTA_PHI		  = { 0. };
   Float_t         cluster_DELTA_THETA		  = { 0. };
   Float_t         cluster_DELTA_ALPHA		  = { 0. };
   Float_t         cluster_CENTER_X               = { 0. };
   Float_t         cluster_CENTER_Y		  = { 0. };
   Float_t         cluster_CENTER_Z		  = { 0. };
   Float_t         cluster_CENTER_LAMBDA	  = { 0. };
   Float_t         cluster_LATERAL		  = { 0. };
   Float_t         cluster_LONGITUDINAL           = { 0. };
   Float_t         cluster_ENG_FRAC_EM		  = { 0. };
   Float_t         cluster_ENG_FRAC_MAX  	  = { 0. };
   Float_t         cluster_ENG_FRAC_CORE	  = { 0. };
   Float_t         cluster_SECOND_ENG_DENS	  = { 0. };
   Float_t         cluster_ISOLATION              = { 0. };
   Float_t         cluster_ENG_BAD_CELLS	  = { 0. };
   Float_t         cluster_N_BAD_CELLS   	  = { 0. };
   Float_t         cluster_N_BAD_CELLS_CORR	  = { 0. };
   Float_t         cluster_BAD_CELLS_CORR_E	  = { 0. };
   Float_t         cluster_BADLARQ_FRAC           = { 0. };
   Float_t         cluster_ENG_POS		  = { 0. };
   Float_t         cluster_SIGNIFICANCE  	  = { 0. };
   Float_t         cluster_CELL_SIGNIFICANCE	  = { 0. };
   Float_t         cluster_CELL_SIG_SAMPLING	  = { 0. };
   Float_t         cluster_AVG_LAR_Q              = { 0. };
   Float_t         cluster_AVG_TILE_Q		  = { 0. };
   Float_t         cluster_ENG_BAD_HV_CELLS	  = { 0. };
   Float_t         cluster_N_BAD_HV_CELLS	  = { 0. };
   Float_t         cluster_PTD			  = { 0. };
   Float_t         cluster_MASS                   = { 0. };
   Float_t         cluster_SECOND_TIME		  = { 0. };
   Float_t         CalibratedE			  = { 0. };
   Float_t         Delta_Calib_E 		  = { 0. };
   Float_t         Delta_E			  = { 0. };

   // List of branches
   TBranch        *b_entry                      = { (TBranch*)0 }; //!
   TBranch        *b_runNumber		        = { (TBranch*)0 }; //!
   TBranch        *b_eventNumber	        = { (TBranch*)0 }; //!
   // particles				        
   TBranch        *b_truthE                     = { (TBranch*)0 }; //!
   TBranch        *b_truthPt		        = { (TBranch*)0 }; //!
   TBranch        *b_truthEta		        = { (TBranch*)0 }; //!
   TBranch        *b_truthPhi		        = { (TBranch*)0 }; //!
   TBranch        *b_truthPDG		        = { (TBranch*)0 }; //!
   // jets				        
   TBranch        *jetCalE                      = { (TBranch*)0 }; //!
   TBranch        *jetCalPt		        = { (TBranch*)0 }; //!
   TBranch        *jetCalEta		        = { (TBranch*)0 }; //!
   TBranch        *jetCalPhi		        = { (TBranch*)0 }; //!
   TBranch        *jetRawE		        = { (TBranch*)0 }; //!
   TBranch        *jetRawPt                     = { (TBranch*)0 }; //!
   TBranch        *jetRawEta		        = { (TBranch*)0 }; //!
   TBranch        *jetRawPhi		        = { (TBranch*)0 }; //!
   TBranch        *jetNConst		        = { (TBranch*)0 }; //!
   TBranch        *truthJetMatchingRadius       = { (TBranch*)0 }; //!
   TBranch        *truthJetE                    = { (TBranch*)0 }; //!
   TBranch        *truthJetPt 		        = { (TBranch*)0 }; //!
   TBranch        *truthJetEta 		        = { (TBranch*)0 }; //!
   TBranch        *truthJetPhi 		        = { (TBranch*)0 }; //!
   // clusters				        
   TBranch        *b_nCluster                   = { (TBranch*)0 }; //!
   TBranch        *b_clusterIndex               = { (TBranch*)0 }; //!
   TBranch        *b_cluster_nCells             = { (TBranch*)0 }; //!
   TBranch        *b_cluster_nCells_tot         = { (TBranch*)0 }; //!!
   TBranch        *b_clusterECalib              = { (TBranch*)0 }; //!
   TBranch        *b_clusterPtCalib	        = { (TBranch*)0 }; //!
   TBranch        *b_clusterEtaCalib	        = { (TBranch*)0 }; //!
   TBranch        *b_clusterPhiCalib	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_sumCellECalib      = { (TBranch*)0 }; //!
   TBranch        *b_cluster_fracECalib	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_fracECalib_ref     = { (TBranch*)0 }; //!
   TBranch        *b_clusterE		        = { (TBranch*)0 }; //!
   TBranch        *b_clusterPt                  = { (TBranch*)0 }; //!
   TBranch        *b_clusterEta		        = { (TBranch*)0 }; //!
   TBranch        *b_clusterPhi		        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_sumCellE	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_time               = { (TBranch*)0 }; //!
   TBranch        *b_cluster_fracE	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_fracE_ref	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_EM_PROBABILITY     = { (TBranch*)0 }; //!
   TBranch        *b_cluster_HAD_WEIGHT         = { (TBranch*)0 }; //!
   TBranch        *b_cluster_OOC_WEIGHT	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_DM_WEIGHT	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_CALIB_TOT      = { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_CALIB_OUT_T    = { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_CALIB_DEAD_TOT	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_CENTER_MAG		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_FIRST_ENG_DENS	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_FIRST_PHI          = { (TBranch*)0 }; //!
   TBranch        *b_cluster_FIRST_ETA		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_SECOND_R		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_SECOND_LAMBDA	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_DELTA_PHI          = { (TBranch*)0 }; //!
   TBranch        *b_cluster_DELTA_THETA	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_DELTA_ALPHA	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_CENTER_X		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_CENTER_Y           = { (TBranch*)0 }; //!
   TBranch        *b_cluster_CENTER_Z	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_CENTER_LAMBDA      = { (TBranch*)0 }; //!
   TBranch        *b_cluster_LATERAL	        = { (TBranch*)0 }; //!
   TBranch        *b_cluster_LONGITUDINAL       = { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_FRAC_EM	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_FRAC_MAX	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_FRAC_CORE	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_SECOND_ENG_DENS    = { (TBranch*)0 }; //!
   TBranch        *b_cluster_ISOLATION		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_BAD_CELLS	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_N_BAD_CELLS	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_N_BAD_CELLS_CORR   = { (TBranch*)0 }; //!
   TBranch        *b_cluster_BAD_CELLS_CORR_E	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_BADLARQ_FRAC	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_POS		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_SIGNIFICANCE       = { (TBranch*)0 }; //!
   TBranch        *b_cluster_CELL_SIGNIFICANCE	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_CELL_SIG_SAMPLING	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_AVG_LAR_Q		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_AVG_TILE_Q         = { (TBranch*)0 }; //!
   TBranch        *b_cluster_ENG_BAD_HV_CELLS	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_N_BAD_HV_CELLS	= { (TBranch*)0 }; //!
   TBranch        *b_cluster_PTD		= { (TBranch*)0 }; //!
   TBranch        *b_cluster_MASS               = { (TBranch*)0 }; //!
   TBranch        *b_cluster_SECOND_TIME	= { (TBranch*)0 }; //!
   TBranch        *b_CalibratedE		= { (TBranch*)0 }; //!
   TBranch        *b_Delta_Calib_E 		= { (TBranch*)0 }; //!
   TBranch        *b_Delta_E                    = { (TBranch*)0 }; //!

  ClusterTreePlotter(TTree *tree=0);
  virtual ~ClusterPionPlotter(); 
  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop(double pdgId=0,bool absVal=false);
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

  virtual void     binNormalize(TH1* h); 

  enum class ClusterScale { RAW=0x11, LCW  =0x12, ML   =0x14,           UNKNOWN=0x00 }; // cluster scales
  enum class JetScale     { RAW=0x21, LCJES=0x22, TRUTH=0x24,           UNKNOWN=0x00 }; // jet scale
  enum class ParticleScale{                       TRUTH=0x44,           UNKNOWN=0x00 }; // particle scale
  enum class ValueType    { E  =0x01,   PT =0x02, RAP  =0x04, PDG=0x08, UNKNOWN=0x00 }; // value type

  void setParticleEmin  (ParticleScale ps,double e                   );
  void setParticleAbsRap(ParticleScale ps,double rap                 );
  void setParticleAbsRap(ParticleScale ps,double rapmin,double rapmax);
  void setParticleRap   (ParticleScale ps,double rap                 );
  void setParticleRap   (ParticleScale ps,double rapmin,double rapmax);

  void setClusterEmin  (ClusterScale cs,double e                    );
  void setClusterPtmin (ClusterScale cs,double pt                   );
  void setClusterAbsRap(ClusterScale cs,double rap                  );
  void setClusterAbsRap(ClusterScale cs,double rapmin,double rap,max);
  void setClusterRap   (ClusterScale cs,double rap                  ); 
  void setClusterRap   (ClusterScale cs,double rapmin,double rap,max);

  void setJetEMin  (JetScale js,double e                   ); 
  void setJetPtMin (JetScale js,double pt                  ); 
  void setJetAbsRap(JetScale js,double rap                 );
  void setJetAbsRap(JetScale js,double rapmin,double rapmax);
  void setJetRap   (JetScale js,double rap                 );
  void setJetRap   (JetScale js,double rapmin,double rapmax);

private:

  // production flags 
  bool m_isParticle  = { false };
  bool m_isJet       = { false }; 

  // list of leaves
  std::map<std::string,bool> m_listOfLeaves;

  // event/object tag 
  int    m_event = { -1 };
  double m_jetPt = { 0. };

  // selections
  typedef unsigned int                               uint_t;
  typedef uint_t                                     key_t;
  typedef std::tuple<ValueType,Float_t,Float_t,bool> frange_t;
  std::multimap<key_t,frange_t>                      m_selectors;

  // accessors
  typedef std::tuple<ValueType,uint_t> vkey_t;
  typedef Float_t*                     vptr_t;
  typedef std::map<vkey_t,vptr_t*>     vmap_t;
  vmap_t m_accessCluster = { 
    { { ValueType::E,   (uint_t)ClusterScale::RAW }, &clusterE       },
    { { ValueType::E,   (uint_t)ClusterScale::LCW }, &clusterECalib  },
    { { ValueType::E,   (uint_t)ClusterScale::ML  }, &CalibratedE    },
    { { ValueType::PT,  (uint_t)ClusterScale::RAW }, &clusterPt      },
    { { ValueType::PT,  (uint_t)ClusterScale::LCW }, &clusterPtCalib },
    { { ValueType::RAP, (uint_t)ClusterScale::RAW }, &clusterEta     },
    { { ValueType::RAP, (uint_t)ClusterScale::LCW }, &clusterEtaCalib}
  };
  vmap_t m_accessJet = { 
    { { ValueType::E,   (uint_t)JetScale::RAW   }, &jetRawE    },
    { { ValueType::E,   (uint_t)JetScale::LCJES }, &jetCalE    },
    { { ValueType::E,   (uint_t)JetScale::TRUTH }, &truthJetE  },
    { { ValueType::PT,  (uint_t)JetScale::RAW   }, &jetRawPt   },
    { { ValueType::PT,  (uint_t)JetScale::LCJES }, &jetCalPt   },
    { { ValueType::PT,  (uint_t)JetScale::TRUTH }, &truthJetPt },
    { { ValueType::RAP, (uint_t)JetScale::RAW   }, &jetRawEta  },
    { { ValueType::RAP, (uint_t)JetScale::LCJES }, &jetCalEta  },
    { { ValueType::RAP, (uint_t)JetScale::TRUTH }, &truthJetEta}
  };
  vmap_t m_accessParticle = { 
    { { ValueType::E,   (uint_t)ParticleScale::TRUTH }, &truthE  },
    { { ValueType::PT,  (uint_t)ParticleScale::TRUTH }, &truthPt },
    { { ValueType::RAP, (uint_t)ParticleScale::TRUTH }, &truthEta},
    { { ValueType::PDG, (uint_t)ParticleScale::TRUTH }, &truthPDG}
  };
  const vmap_t m_accessEmpty;

  // helpers
  template<class T> bool isClusterKey(T key) { return ( key & 0x10 ) == 0x10; }
  template<class T> bool isJetKey    (T key) { return ( key & 0x20 ) == 0x20; }
  template<class T> bool isParticle  (T key) { return ( key & 0x40 ) == 0x40; } 
  template<class T> bool fillValue(ValueType vtype,uint_t vscale,T& val) {
    const vmap_t& map = isParticleKey<uint_t>(vscale) 
      ? m_accessParticle 
      : isJetKey<uint_t>(vscale)
      ? m_accessJet 
      : isClusterKey<uint_t>(vscale)
      ? m_accessCluster
      : m_accessEmpty; 
    auto fval(m_access.find(vtype)); if ( fval != m_access.end() ) { val = (T)*(fval->second); return true; } else { return false; }
  }

  bool isParticle();
  bool isJet()     ;

  // -- state control
  double m_truthPDG   = { 0. };
  double m_truthE     = { 0. };
  double m_truthJetE  = { 0. };
  double m_truthJetPt = { 0. };

protected:
  virtual bool hasBookedLeaf(const std::string& lname);

  virtual bool filter(ClusterScale  cs); 
  virtual bool filter(JetScale      js); 
  virtual bool filter(ParticleScale ps); 
  virtual bool newEvent();   // new simulation event
  virtual bool newObject();  // new particle or jet

  virtual bool fillParticle(bool final=false);
  virtual bool fillJet     (bool final=false); 
};

#endif

#ifdef ClusterTreePlotter_cxx
ClusterTreePionPlotter::ClusterTreePionPlotter(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      // TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ML/ml_pions.root");
      // if (!f || !f->IsOpen()) {
      //    f = new TFile("ML/ml_pions.root");
      // }
      // f->GetObject("ClusterTree",tree);
     printf("[ClusterTreePlotter::ClusterTreePlotter()] ABRT no valid pointer to ROOT tree, module inactive\n"); 
   } else { 
     printf("[ClusterTreePlotter::ClusterTreePlotter()] INFO initialize tree \042%s\042\n",tree->GetName());
     Init(tree);
   }
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

   if ( fChain->FindLeaf("entry"                      ) != nullptr ) { m_listOfLeaves["entry"                     ] = false; fChain->SetBranchAddress("entry"                      , &entry                    ,&b_entry                     ); } 
   if ( fChain->FindLeaf("runNumber"                  ) != nullptr ) { m_listOfLeaves["runNumber"                 ] = false; fChain->SetBranchAddress("runNumber"                  , &runNumber                ,&b_runNumber                 ); }
   if ( fChain->FindLeaf("eventNumber"                ) != nullptr ) { m_listOfLeaves["eventNumber"               ] = false; fChain->SetBranchAddress("eventNumber"                , &eventNumber              ,&b_eventNumber               ); }
   if ( fChain->FindLeaf("truthE"                     ) != nullptr ) { m_listOfLeaves["truthE"                    ] = false; fChain->SetBranchAddress("truthE"                     , &truthE                   ,&b_truthE                    ); }
   if ( fChain->FindLeaf("truthPt"                    ) != nullptr ) { m_listOfLeaves["truthPt"                   ] = false; fChain->SetBranchAddress("truthPt"                    , &truthPt                  ,&b_truthPt                   ); }
   if ( fChain->FindLeaf("truthEta"                   ) != nullptr ) { m_listOfLeaves["truthEta"                  ] = false; fChain->SetBranchAddress("truthEta"                   , &truthEta                 ,&b_truthEta                  ); }
   if ( fChain->FindLeaf("truthPhi"                   ) != nullptr ) { m_listOfLeaves["truthPhi"                  ] = false; fChain->SetBranchAddress("truthPhi"                   , &truthPhi                 ,&b_truthPhi                  ); }
   if ( fChain->FindLeaf("truthPDG"                   ) != nullptr ) { m_listOfLeaves["truthPDG"                  ] = false; fChain->SetBranchAddress("truthPDG"                   , &truthPDG                 ,&b_truthPDG                  ); }
   if ( fChain->FindLeaf("jetCalE"                    ) != nullptr ) { m_listOfLeaves["jetCalE"                   ] = true ; fChain->SetBranchAddress("jetCalE"                    , &jetCalE                  ,&b_jetCalE                   ); } 
   if ( fChain->FindLeaf("jetCalPt"		      ) != nullptr ) { m_listOfLeaves["jetCalPt"                  ] = true ; fChain->SetBranchAddress("jetCalPt"		   ,&jetCalPt                  ,&b_jetCalPt                  ); }
   if ( fChain->FindLeaf("jetCalEta"		      ) != nullptr ) { m_listOfLeaves["jetCalEta"		  ] = true ; fChain->SetBranchAddress("jetCalEta"		   ,&jetCalEta                 ,&b_jetCalEta                 ); }
   if ( fChain->FindLeaf("jetCalPhi"		      ) != nullptr ) { m_listOfLeaves["jetCalPhi"		  ] = true ; fChain->SetBranchAddress("jetCalPhi"		   ,&jetCalPhi                 ,&b_jetCalPhi                 ); }
   if ( fChain->FindLeaf("jetRawE"		      ) != nullptr ) { m_listOfLeaves["jetRawE"		          ] = true ; fChain->SetBranchAddress("jetRawE"		           ,&jetRawE                   ,&b_jetRawE                   ); }
   if ( fChain->FindLeaf("jetRawPt"                   ) != nullptr ) { m_listOfLeaves["jetRawPt"                  ] = true ; fChain->SetBranchAddress("jetRawPt"                   ,&jetRawPt                  ,&b_jetRawPt                  ); }
   if ( fChain->FindLeaf("jetRawEta"		      ) != nullptr ) { m_listOfLeaves["jetRawEta"		  ] = true ; fChain->SetBranchAddress("jetRawEta"		   ,&jetRawEta                 ,&b_jetRawEta                 ); }
   if ( fChain->FindLeaf("jetRawPhi"		      ) != nullptr ) { m_listOfLeaves["jetRawPhi"		  ] = true ; fChain->SetBranchAddress("jetRawPhi"		   ,&jetRawPhi                 ,&b_jetRawPhi                 ); }
   if ( fChain->FindLeaf("jetNConst"		      ) != nullptr ) { m_listOfLeaves["jetNConst"		  ] = true ; fChain->SetBranchAddress("jetNConst"		   ,&jetNConst		       ,&b_jetNConst                 ); }
   if ( fChain->FindLeaf("truthJetMatchingRadius"     ) != nullptr ) { m_listOfLeaves["truthJetMatchingRadius"    ] = true ; fChain->SetBranchAddress("truthJetMatchingRadius"     ,&truthJetMatchingRadius    ,&b_truthJetMatchingRadius    ); }
   if ( fChain->FindLeaf("truthJetE"                  ) != nullptr ) { m_listOfLeaves["truthJetE"                 ] = true ; fChain->SetBranchAddress("truthJetE"                  ,&truthJetE                 ,&b_truthJetE                 ); }
   if ( fChain->FindLeaf("truthJetPt" 		      ) != nullptr ) { m_listOfLeaves["truthJetPt" 		  ] = true ; fChain->SetBranchAddress("truthJetPt" 	           ,&truthJetPt 	       ,&b_truthJetPt                ); }
   if ( fChain->FindLeaf("truthJetEta" 		      ) != nullptr ) { m_listOfLeaves["truthJetEta" 		  ] = true ; fChain->SetBranchAddress("truthJetEta" 	           ,&truthJetEta 	       ,&b_truthJetEta               ); }
   if ( fChain->FindLeaf("truthJetPhi" 		      ) != nullptr ) { m_listOfLeaves["truthJetPhi" 		  ] = true ; fChain->SetBranchAddress("truthJetPhi" 	           ,&truthJetPhi 	       ,&b_truthJetPhi               ); }
   if ( fChain->FindLeaf("nCluster"                   ) != nullptr ) { m_listOfLeaves["nCluster"                  ] = false; fChain->SetBranchAddress("nCluster"                   ,&nCluster                  ,&b_nCluster                  ); }
   if ( fChain->FindLeaf("clusterIndex"               ) != nullptr ) { m_listOfLeaves["clusterIndex"              ] = false; fChain->SetBranchAddress("clusterIndex"               ,&clusterIndex              ,&b_clusterIndex              ); }
   if ( fChain->FindLeaf("cluster_nCells"             ) != nullptr ) { m_listOfLeaves["cluster_nCells"            ] = false; fChain->SetBranchAddress("cluster_nCells"             ,&cluster_nCells            ,&b_cluster_nCells            ); }
   if ( fChain->FindLeaf("cluster_nCells_tot"         ) != nullptr ) { m_listOfLeaves["cluster_nCells_tot"        ] = false; fChain->SetBranchAddress("cluster_nCells_tot"         ,&cluster_nCells_tot        ,&b_cluster_nCells_tot        ); }
   if ( fChain->FindLeaf("clusterECalib"              ) != nullptr ) { m_listOfLeaves["clusterECalib"             ] = false; fChain->SetBranchAddress("clusterECalib"              ,&clusterECalib             ,&b_clusterECalib             ); }
   if ( fChain->FindLeaf("clusterPtCalib"             ) != nullptr ) { m_listOfLeaves["clusterPtCalib"            ] = false; fChain->SetBranchAddress("clusterPtCalib"             ,&clusterPtCalib            ,&b_clusterPtCalib            ); }
   if ( fChain->FindLeaf("clusterEtaCalib"            ) != nullptr ) { m_listOfLeaves["clusterEtaCalib"           ] = false; fChain->SetBranchAddress("clusterEtaCalib"            ,&clusterEtaCalib           ,&b_clusterEtaCalib           ); }
   if ( fChain->FindLeaf("clusterPhiCalib"            ) != nullptr ) { m_listOfLeaves["clusterPhiCalib"           ] = false; fChain->SetBranchAddress("clusterPhiCalib"            ,&clusterPhiCalib           ,&b_clusterPhiCalib           ); }
   if ( fChain->FindLeaf("cluster_sumCellECalib"      ) != nullptr ) { m_listOfLeaves["cluster_sumCellECalib"     ] = false; fChain->SetBranchAddress("cluster_sumCellECalib"      ,&cluster_sumCellECalib     ,&b_cluster_sumCellECalib     ); }
   if ( fChain->FindLeaf("cluster_fracECalib"         ) != nullptr ) { m_listOfLeaves["cluster_fracECalib"        ] = false; fChain->SetBranchAddress("cluster_fracECalib"         ,&cluster_fracECalib        ,&b_cluster_fracECalib        ); }
   if ( fChain->FindLeaf("cluster_fracECalib_ref"     ) != nullptr ) { m_listOfLeaves["cluster_fracECalib_ref"    ] = false; fChain->SetBranchAddress("cluster_fracECalib_ref"     ,&cluster_fracECalib_ref    ,&b_cluster_fracECalib_ref    ); }
   if ( fChain->FindLeaf("clusterE"                   ) != nullptr ) { m_listOfLeaves["clusterE"                  ] = false; fChain->SetBranchAddress("clusterE"                   ,&clusterE                  ,&b_clusterE                  ); }
   if ( fChain->FindLeaf("clusterPt"                  ) != nullptr ) { m_listOfLeaves["clusterPt"                 ] = false; fChain->SetBranchAddress("clusterPt"                  ,&clusterPt                 ,&b_clusterPt                 ); }
   if ( fChain->FindLeaf("clusterEta"                 ) != nullptr ) { m_listOfLeaves["clusterEta"                ] = false; fChain->SetBranchAddress("clusterEta"                 ,&clusterEta                ,&b_clusterEta                ); }
   if ( fChain->FindLeaf("clusterPhi"                 ) != nullptr ) { m_listOfLeaves["clusterPhi"                ] = false; fChain->SetBranchAddress("clusterPhi"                 ,&clusterPhi                ,&b_clusterPhi                ); }
   if ( fChain->FindLeaf("cluster_sumCellE"           ) != nullptr ) { m_listOfLeaves["cluster_sumCellE"          ] = false; fChain->SetBranchAddress("cluster_sumCellE"           ,&cluster_sumCellE          ,&b_cluster_sumCellE          ); }
   if ( fChain->FindLeaf("cluster_time"               ) != nullptr ) { m_listOfLeaves["cluster_time"              ] = false; fChain->SetBranchAddress("cluster_time"               ,&cluster_time              ,&b_cluster_time              ); }
   if ( fChain->FindLeaf("cluster_fracE"              ) != nullptr ) { m_listOfLeaves["cluster_fracE"             ] = false; fChain->SetBranchAddress("cluster_fracE"              ,&cluster_fracE             ,&b_cluster_fracE             ); }
   if ( fChain->FindLeaf("cluster_fracE_ref"          ) != nullptr ) { m_listOfLeaves["cluster_fracE_ref"         ] = false; fChain->SetBranchAddress("cluster_fracE_ref"          ,&cluster_fracE_ref         ,&b_cluster_fracE_ref         ); }
   if ( fChain->FindLeaf("cluster_EM_PROBABILITY"     ) != nullptr ) { m_listOfLeaves["cluster_EM_PROBABILITY"    ] = false; fChain->SetBranchAddress("cluster_EM_PROBABILITY"     ,&cluster_EM_PROBABILITY    ,&b_cluster_EM_PROBABILITY    ); }
   if ( fChain->FindLeaf("cluster_HAD_WEIGHT"         ) != nullptr ) { m_listOfLeaves["cluster_HAD_WEIGHT"        ] = false; fChain->SetBranchAddress("cluster_HAD_WEIGHT"         ,&cluster_HAD_WEIGHT        ,&b_cluster_HAD_WEIGHT        ); }
   if ( fChain->FindLeaf("cluster_OOC_WEIGHT"         ) != nullptr ) { m_listOfLeaves["cluster_OOC_WEIGHT"        ] = false; fChain->SetBranchAddress("cluster_OOC_WEIGHT"         ,&cluster_OOC_WEIGHT        ,&b_cluster_OOC_WEIGHT        ); }
   if ( fChain->FindLeaf("cluster_DM_WEIGHT"          ) != nullptr ) { m_listOfLeaves["cluster_DM_WEIGHT"         ] = false; fChain->SetBranchAddress("cluster_DM_WEIGHT"          ,&cluster_DM_WEIGHT         ,&b_cluster_DM_WEIGHT         ); }
   if ( fChain->FindLeaf("cluster_ENG_CALIB_TOT"      ) != nullptr ) { m_listOfLeaves["cluster_ENG_CALIB_TOT"     ] = false; fChain->SetBranchAddress("cluster_ENG_CALIB_TOT"      ,&cluster_ENG_CALIB_TOT     ,&b_cluster_ENG_CALIB_TOT     ); }
   if ( fChain->FindLeaf("cluster_ENG_CALIB_OUT_T"    ) != nullptr ) { m_listOfLeaves["cluster_ENG_CALIB_OUT_T"   ] = false; fChain->SetBranchAddress("cluster_ENG_CALIB_OUT_T"    ,&cluster_ENG_CALIB_OUT_T   ,&b_cluster_ENG_CALIB_OUT_T   ); }
   if ( fChain->FindLeaf("cluster_ENG_CALIB_DEAD_TOT" ) != nullptr ) { m_listOfLeaves["cluster_ENG_CALIB_DEAD_TOT"] = false; fChain->SetBranchAddress("cluster_ENG_CALIB_DEAD_TOT" ,&cluster_ENG_CALIB_DEAD_TOT,&b_cluster_ENG_CALIB_DEAD_TOT); }
   if ( fChain->FindLeaf("cluster_CENTER_MAG"         ) != nullptr ) { m_listOfLeaves["cluster_CENTER_MAG"        ] = false; fChain->SetBranchAddress("cluster_CENTER_MAG"         ,&cluster_CENTER_MAG        ,&b_cluster_CENTER_MAG        ); }
   if ( fChain->FindLeaf("cluster_FIRST_ENG_DENS"     ) != nullptr ) { m_listOfLeaves["cluster_FIRST_ENG_DENS"    ] = false; fChain->SetBranchAddress("cluster_FIRST_ENG_DENS"     ,&cluster_FIRST_ENG_DENS    ,&b_cluster_FIRST_ENG_DENS    ); }
   if ( fChain->FindLeaf("cluster_FIRST_PHI"          ) != nullptr ) { m_listOfLeaves["cluster_FIRST_PHI"         ] = false; fChain->SetBranchAddress("cluster_FIRST_PHI"          ,&cluster_FIRST_PHI         ,&b_cluster_FIRST_PHI         ); }
   if ( fChain->FindLeaf("cluster_FIRST_ETA"          ) != nullptr ) { m_listOfLeaves["cluster_FIRST_ETA"         ] = false; fChain->SetBranchAddress("cluster_FIRST_ETA"          ,&cluster_FIRST_ETA         ,&b_cluster_FIRST_ETA         ); }
   if ( fChain->FindLeaf("cluster_SECOND_R"           ) != nullptr ) { m_listOfLeaves["cluster_SECOND_R"          ] = false; fChain->SetBranchAddress("cluster_SECOND_R"           ,&cluster_SECOND_R          ,&b_cluster_SECOND_R          ); }
   if ( fChain->FindLeaf("cluster_SECOND_LAMBDA"      ) != nullptr ) { m_listOfLeaves["cluster_SECOND_LAMBDA"     ] = false; fChain->SetBranchAddress("cluster_SECOND_LAMBDA"      ,&cluster_SECOND_LAMBDA     ,&b_cluster_SECOND_LAMBDA     ); }
   if ( fChain->FindLeaf("cluster_DELTA_PHI"          ) != nullptr ) { m_listOfLeaves["cluster_DELTA_PHI"         ] = false; fChain->SetBranchAddress("cluster_DELTA_PHI"          ,&cluster_DELTA_PHI         ,&b_cluster_DELTA_PHI         ); }
   if ( fChain->FindLeaf("cluster_DELTA_THETA"        ) != nullptr ) { m_listOfLeaves["cluster_DELTA_THETA"       ] = false; fChain->SetBranchAddress("cluster_DELTA_THETA"        ,&cluster_DELTA_THETA       ,&b_cluster_DELTA_THETA       ); }
   if ( fChain->FindLeaf("cluster_DELTA_ALPHA"        ) != nullptr ) { m_listOfLeaves["cluster_DELTA_ALPHA"       ] = false; fChain->SetBranchAddress("cluster_DELTA_ALPHA"        ,&cluster_DELTA_ALPHA       ,&b_cluster_DELTA_ALPHA       ); }
   if ( fChain->FindLeaf("cluster_CENTER_X"           ) != nullptr ) { m_listOfLeaves["cluster_CENTER_X"          ] = false; fChain->SetBranchAddress("cluster_CENTER_X"           ,&cluster_CENTER_X          ,&b_cluster_CENTER_X          ); }
   if ( fChain->FindLeaf("cluster_CENTER_Y"           ) != nullptr ) { m_listOfLeaves["cluster_CENTER_Y"          ] = false; fChain->SetBranchAddress("cluster_CENTER_Y"           ,&cluster_CENTER_Y          ,&b_cluster_CENTER_Y          ); }
   if ( fChain->FindLeaf("cluster_CENTER_Z"           ) != nullptr ) { m_listOfLeaves["cluster_CENTER_Z"          ] = false; fChain->SetBranchAddress("cluster_CENTER_Z"           ,&cluster_CENTER_Z          ,&b_cluster_CENTER_Z          ); }
   if ( fChain->FindLeaf("cluster_CENTER_LAMBDA"      ) != nullptr ) { m_listOfLeaves["cluster_CENTER_LAMBDA"     ] = false; fChain->SetBranchAddress("cluster_CENTER_LAMBDA"      ,&cluster_CENTER_LAMBDA     ,&b_cluster_CENTER_LAMBDA     ); }
   if ( fChain->FindLeaf("cluster_LATERAL"            ) != nullptr ) { m_listOfLeaves["cluster_LATERAL"           ] = false; fChain->SetBranchAddress("cluster_LATERAL"            ,&cluster_LATERAL           ,&b_cluster_LATERAL           ); }
   if ( fChain->FindLeaf("cluster_LONGITUDINAL"       ) != nullptr ) { m_listOfLeaves["cluster_LONGITUDINAL"      ] = false; fChain->SetBranchAddress("cluster_LONGITUDINAL"       ,&cluster_LONGITUDINAL      ,&b_cluster_LONGITUDINAL      ); }
   if ( fChain->FindLeaf("cluster_ENG_FRAC_EM"        ) != nullptr ) { m_listOfLeaves["cluster_ENG_FRAC_EM"       ] = false; fChain->SetBranchAddress("cluster_ENG_FRAC_EM"        ,&cluster_ENG_FRAC_EM       ,&b_cluster_ENG_FRAC_EM       ); }
   if ( fChain->FindLeaf("cluster_ENG_FRAC_MAX"       ) != nullptr ) { m_listOfLeaves["cluster_ENG_FRAC_MAX"      ] = false; fChain->SetBranchAddress("cluster_ENG_FRAC_MAX"       ,&cluster_ENG_FRAC_MAX      ,&b_cluster_ENG_FRAC_MAX      ); }
   if ( fChain->FindLeaf("cluster_ENG_FRAC_CORE"      ) != nullptr ) { m_listOfLeaves["cluster_ENG_FRAC_CORE"     ] = false; fChain->SetBranchAddress("cluster_ENG_FRAC_CORE"      ,&cluster_ENG_FRAC_CORE     ,&b_cluster_ENG_FRAC_CORE     ); }
   if ( fChain->FindLeaf("cluster_SECOND_ENG_DENS"    ) != nullptr ) { m_listOfLeaves["cluster_SECOND_ENG_DENS"   ] = false; fChain->SetBranchAddress("cluster_SECOND_ENG_DENS"    ,&cluster_SECOND_ENG_DENS   ,&b_cluster_SECOND_ENG_DENS   ); }
   if ( fChain->FindLeaf("cluster_ISOLATION"          ) != nullptr ) { m_listOfLeaves["cluster_ISOLATION"         ] = false; fChain->SetBranchAddress("cluster_ISOLATION"          ,&cluster_ISOLATION         ,&b_cluster_ISOLATION         ); }
   if ( fChain->FindLeaf("cluster_ENG_BAD_CELLS"      ) != nullptr ) { m_listOfLeaves["cluster_ENG_BAD_CELLS"     ] = false; fChain->SetBranchAddress("cluster_ENG_BAD_CELLS"      ,&cluster_ENG_BAD_CELLS     ,&b_cluster_ENG_BAD_CELLS     ); }
   if ( fChain->FindLeaf("cluster_N_BAD_CELLS"        ) != nullptr ) { m_listOfLeaves["cluster_N_BAD_CELLS"       ] = false; fChain->SetBranchAddress("cluster_N_BAD_CELLS"        ,&cluster_N_BAD_CELLS       ,&b_cluster_N_BAD_CELLS       ); }
   if ( fChain->FindLeaf("cluster_N_BAD_CELLS_CORR"   ) != nullptr ) { m_listOfLeaves["cluster_N_BAD_CELLS_CORR"  ] = false; fChain->SetBranchAddress("cluster_N_BAD_CELLS_CORR"   ,&cluster_N_BAD_CELLS_CORR  ,&b_cluster_N_BAD_CELLS_CORR  ); }
   if ( fChain->FindLeaf("cluster_BAD_CELLS_CORR_E"   ) != nullptr ) { m_listOfLeaves["cluster_BAD_CELLS_CORR_E"  ] = false; fChain->SetBranchAddress("cluster_BAD_CELLS_CORR_E"   ,&cluster_BAD_CELLS_CORR_E  ,&b_cluster_BAD_CELLS_CORR_E  ); }
   if ( fChain->FindLeaf("cluster_BADLARQ_FRAC"       ) != nullptr ) { m_listOfLeaves["cluster_BADLARQ_FRAC"      ] = false; fChain->SetBranchAddress("cluster_BADLARQ_FRAC"       ,&cluster_BADLARQ_FRAC      ,&b_cluster_BADLARQ_FRAC      ); }
   if ( fChain->FindLeaf("cluster_ENG_POS"            ) != nullptr ) { m_listOfLeaves["cluster_ENG_POS"           ] = false; fChain->SetBranchAddress("cluster_ENG_POS"            ,&cluster_ENG_POS           ,&b_cluster_ENG_POS           ); }
   if ( fChain->FindLeaf("cluster_SIGNIFICANCE"       ) != nullptr ) { m_listOfLeaves["cluster_SIGNIFICANCE"      ] = false; fChain->SetBranchAddress("cluster_SIGNIFICANCE"       ,&cluster_SIGNIFICANCE      ,&b_cluster_SIGNIFICANCE      ); }
   if ( fChain->FindLeaf("cluster_CELL_SIGNIFICANCE"  ) != nullptr ) { m_listOfLeaves["cluster_CELL_SIGNIFICANCE" ] = false; fChain->SetBranchAddress("cluster_CELL_SIGNIFICANCE"  ,&cluster_CELL_SIGNIFICANCE ,&b_cluster_CELL_SIGNIFICANCE ); }
   if ( fChain->FindLeaf("cluster_CELL_SIG_SAMPLING"  ) != nullptr ) { m_listOfLeaves["cluster_CELL_SIG_SAMPLING" ] = false; fChain->SetBranchAddress("cluster_CELL_SIG_SAMPLING"  ,&cluster_CELL_SIG_SAMPLING ,&b_cluster_CELL_SIG_SAMPLING ); }
   if ( fChain->FindLeaf("cluster_AVG_LAR_Q"          ) != nullptr ) { m_listOfLeaves["cluster_AVG_LAR_Q"         ] = false; fChain->SetBranchAddress("cluster_AVG_LAR_Q"          ,&cluster_AVG_LAR_Q         ,&b_cluster_AVG_LAR_Q         ); }
   if ( fChain->FindLeaf("cluster_AVG_TILE_Q"         ) != nullptr ) { m_listOfLeaves["cluster_AVG_TILE_Q"        ] = false; fChain->SetBranchAddress("cluster_AVG_TILE_Q"         ,&cluster_AVG_TILE_Q        ,&b_cluster_AVG_TILE_Q        ); }
   if ( fChain->FindLeaf("cluster_ENG_BAD_HV_CELLS"   ) != nullptr ) { m_listOfLeaves["cluster_ENG_BAD_HV_CELLS"  ] = false; fChain->SetBranchAddress("cluster_ENG_BAD_HV_CELLS"   ,&cluster_ENG_BAD_HV_CELLS  ,&b_cluster_ENG_BAD_HV_CELLS  ); }
   if ( fChain->FindLeaf("cluster_N_BAD_HV_CELLS"     ) != nullptr ) { m_listOfLeaves["cluster_N_BAD_HV_CELLS"    ] = false; fChain->SetBranchAddress("cluster_N_BAD_HV_CELLS"     ,&cluster_N_BAD_HV_CELLS    ,&b_cluster_N_BAD_HV_CELLS    ); }
   if ( fChain->FindLeaf("cluster_PTD"                ) != nullptr ) { m_listOfLeaves["cluster_PTD"               ] = false; fChain->SetBranchAddress("cluster_PTD"                ,&cluster_PTD               ,&b_cluster_PTD               ); }
   if ( fChain->FindLeaf("cluster_MASS"               ) != nullptr ) { m_listOfLeaves["cluster_MASS"              ] = false; fChain->SetBranchAddress("cluster_MASS"               ,&cluster_MASS              ,&b_cluster_MASS              ); }
   if ( fChain->FindLeaf("cluster_SECOND_TIME"        ) != nullptr ) { m_listOfLeaves["cluster_SECOND_TIME"       ] = false; fChain->SetBranchAddress("cluster_SECOND_TIME"        ,&cluster_SECOND_TIME       ,&b_cluster_SECOND_TIME       ); }
   if ( fChain->FindLeaf("CalibratedE"                ) != nullptr ) { m_listOfLeaves["CalibratedE"               ] = false; fChain->SetBranchAddress("CalibratedE"                ,&CalibratedE               ,&b_CalibratedE               ); }
   if ( fChain->FindLeaf("Delta_Calib_E "             ) != nullptr ) { m_listOfLeaves["Delta_Calib_E "            ] = false; fChain->SetBranchAddress("Delta_Calib_E "             ,&Delta_Calib_E             ,&b_Delta_Calib_E             ); }
   if ( fChain->FindLeaf("Delta_E"                    ) != nullptr ) { m_listOfLeaves["Delta_E"                   ] = false; fChain->SetBranchAddress("Delta_E"                    ,&Delta_E                   ,&b_Delta_E                   ); }

   if ( b_truthE  != nullptr )    { m_isParticle = true; printf("[ClusterPlotterTree::Init()] INFO clusters in particles analysis\n"); }
   if ( b_jetCalE != nullptr )    { m_isJet      = true; printf("[ClusterPlotterTree::Init()] INFO clusters in jets analysis\n"     ); }
   if ( m_isParticle && m_isJet ) {                      printf("[ClusterTreePlotter::Init()] WARN mixed mode!\n"                   ); }
 
   Notify();
}

Bool_t ClusterTreePionPlotter::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.
  std::string kana = m_listOfLeaves.find("jetCalPt") != m_listOfLeaves.end() ? "jet" ? "single particle";
  printf("[ClusterTreePlotter::Init()] INFO booked %zu branches for %s analysis\n",m_listOfLeaves.size(),kana.c_str());
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
