
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TBranch.h>

#include <vector>
#include <string>
#include <tuple>
#include <cstdio>

#include <iostream>
#include <fstream>
#include <iterator>

#include <algorithm>

namespace Data { 
   // Declaration of leaf types
   static Int_t           entry       = { 0 };       
   static Int_t           runNumber   = { 0 };
   static Int_t           eventNumber = { 0 };   
   // particle tuples
   static Float_t         truthE   = { 0. };
   static Float_t         truthPt  = { 0. };
   static Float_t         truthEta = { 0. };
   static Float_t         truthPhi = { 0. }; 
   static Int_t           truthPDG = { 0  };
   // jet tuples		 
   static Float_t         jetCalE                = { 0. };
   static Float_t         jetCalPt		 = { 0. };
   static Float_t         jetCalEta		 = { 0. };
   static Float_t         jetCalPhi		 = { 0. };
   static Float_t         jetRawE		 = { 0. };
   static Float_t         jetRawPt               = { 0. };
   static Float_t         jetRawEta		 = { 0. };
   static Float_t         jetRawPhi		 = { 0. };
   static Int_t           jetNConst		 = { 0  };
   static Float_t         truthJetMatchingRadius = { 0. };
   static Float_t         truthJetE              = { 0. };
   static Float_t         truthJetPt 	         = { 0. };
   static Float_t         truthJetEta 	         = { 0. };
   static Float_t         truthJetPhi 	         = { 0. };
   // cluster data			    
   static Int_t           nCluster                   = { 0  };
   static Int_t           clusterIndex 		     = { 0  };
   static Int_t           cluster_nCells 	     = { 0  };
   static Int_t           cluster_nCells_tot	     = { 0 };
   static Float_t         clusterECalib		     = { 0. };
   static Float_t         clusterPtCalib             = { 0. };
   static Float_t         clusterEtaCalib            = { 0. };
   static Float_t         clusterPhiCalib            = { 0. };
   static Float_t         cluster_sumCellECalib      = { 0. };
   static Float_t         cluster_fracECalib         = { 0. };
   static Float_t         cluster_fracECalib_ref     = { 0. };
   static Float_t         clusterE		     = { 0. };
   static Float_t         clusterPt		     = { 0. };
   static Float_t         clusterEta		     = { 0. };
   static Float_t         clusterPhi		     = { 0. };
   static Float_t         cluster_sumCellE           = { 0. };
   static Float_t         cluster_time 		     = { 0. };
   static Float_t         cluster_fracE		     = { 0. };
   static Float_t         cluster_fracE_ref	     = { 0. };
   static Float_t         cluster_EM_PROBABILITY     = { 0. };
   static Float_t         cluster_HAD_WEIGHT         = { 0. };
   static Float_t         cluster_OOC_WEIGHT	     = { 0. };
   static Float_t         cluster_DM_WEIGHT	     = { 0. };
   static Float_t         cluster_ENG_CALIB_TOT	     = { 0. };
   static Float_t         cluster_ENG_CALIB_OUT_T    = { 0. };
   static Float_t         cluster_ENG_CALIB_DEAD_TOT = { 0. };
   static Float_t         cluster_CENTER_MAG	     = { 0. };
   static Float_t         cluster_FIRST_ENG_DENS     = { 0. };
   static Float_t         cluster_FIRST_PHI	     = { 0. };
   static Float_t         cluster_FIRST_ETA          = { 0. };
   static Float_t         cluster_SECOND_R           = { 0. };
   static Float_t         cluster_SECOND_LAMBDA      = { 0. };
   static Float_t         cluster_DELTA_PHI          = { 0. };
   static Float_t         cluster_DELTA_THETA        = { 0. };
   static Float_t         cluster_DELTA_ALPHA	     = { 0. };
   static Float_t         cluster_CENTER_X           = { 0. };
   static Float_t         cluster_CENTER_Y	     = { 0. };
   static Float_t         cluster_CENTER_Z	     = { 0. };
   static Float_t         cluster_CENTER_LAMBDA	     = { 0. };
   static Float_t         cluster_LATERAL	     = { 0. };
   static Float_t         cluster_LONGITUDINAL       = { 0. };
   static Float_t         cluster_ENG_FRAC_EM	     = { 0. };
   static Float_t         cluster_ENG_FRAC_MAX       = { 0. };
   static Float_t         cluster_ENG_FRAC_CORE	     = { 0. };
   static Float_t         cluster_SECOND_ENG_DENS    = { 0. };
   static Float_t         cluster_ISOLATION          = { 0. };
   static Float_t         cluster_ENG_BAD_CELLS	     = { 0. };
   static Float_t         cluster_N_BAD_CELLS        = { 0. };
   static Float_t         cluster_N_BAD_CELLS_CORR   = { 0. };
   static Float_t         cluster_BAD_CELLS_CORR_E   = { 0. };
   static Float_t         cluster_BADLARQ_FRAC       = { 0. };
   static Float_t         cluster_ENG_POS	     = { 0. };
   static Float_t         cluster_SIGNIFICANCE       = { 0. };
   static Float_t         cluster_CELL_SIGNIFICANCE  = { 0. };
   static Float_t         cluster_CELL_SIG_SAMPLING  = { 0. };
   static Float_t         cluster_AVG_LAR_Q          = { 0. };
   static Float_t         cluster_AVG_TILE_Q	     = { 0. };
   static Float_t         cluster_ENG_BAD_HV_CELLS   = { 0. };
   static Float_t         cluster_N_BAD_HV_CELLS     = { 0. };
   static Float_t         cluster_PTD		     = { 0. };
   static Float_t         cluster_MASS               = { 0. };
   static Float_t         cluster_SECOND_TIME	     = { 0. };
   static Float_t         CalibratedE		     = { 0. };
   static Float_t         Delta_Calib_E 	     = { 0. };
   static Float_t         Delta_E		     = { 0. };
} // Data

namespace Branches {
  // List of branches
  static TBranch* b_entry                       = { (TBranch*)0 }; //!
  static TBranch* b_runNumber		        = { (TBranch*)0 }; //!
  static TBranch* b_eventNumber	                = { (TBranch*)0 }; //!
  // particles			        
  static TBranch* b_truthE                      = { (TBranch*)0 }; //!
  static TBranch* b_truthPt		        = { (TBranch*)0 }; //!
  static TBranch* b_truthEta		        = { (TBranch*)0 }; //!
  static TBranch* b_truthPhi		        = { (TBranch*)0 }; //!
  static TBranch* b_truthPDG		        = { (TBranch*)0 }; //!
   // jets			        
  static TBranch* b_jetCalE                     = { (TBranch*)0 }; //!
  static TBranch* b_jetCalPt		        = { (TBranch*)0 }; //!
  static TBranch* b_jetCalEta		        = { (TBranch*)0 }; //!
  static TBranch* b_jetCalPhi		        = { (TBranch*)0 }; //!
  static TBranch* b_jetRawE		        = { (TBranch*)0 }; //!
  static TBranch* b_jetRawPt                    = { (TBranch*)0 }; //!
  static TBranch* b_jetRawEta		        = { (TBranch*)0 }; //!
  static TBranch* b_jetRawPhi		        = { (TBranch*)0 }; //!
  static TBranch* b_jetNConst		        = { (TBranch*)0 }; //!
  static TBranch* b_truthJetMatchingRadius      = { (TBranch*)0 }; //!
  static TBranch* b_truthJetE                   = { (TBranch*)0 }; //!
  static TBranch* b_truthJetPt   	        = { (TBranch*)0 }; //!
  static TBranch* b_truthJetEta 	        = { (TBranch*)0 }; //!
  static TBranch* b_truthJetPhi       	        = { (TBranch*)0 }; //!
  // clusters			        
  static TBranch* b_nCluster                    = { (TBranch*)0 }; //!
  static TBranch* b_clusterIndex                = { (TBranch*)0 }; //!
  static TBranch* b_cluster_nCells              = { (TBranch*)0 }; //!
  static TBranch* b_cluster_nCells_tot          = { (TBranch*)0 }; //!!
  static TBranch* b_clusterECalib               = { (TBranch*)0 }; //!
  static TBranch* b_clusterPtCalib	        = { (TBranch*)0 }; //!
  static TBranch* b_clusterEtaCalib	        = { (TBranch*)0 }; //!
  static TBranch* b_clusterPhiCalib	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_sumCellECalib       = { (TBranch*)0 }; //!
  static TBranch* b_cluster_fracECalib	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_fracECalib_ref      = { (TBranch*)0 }; //!
  static TBranch* b_clusterE		        = { (TBranch*)0 }; //!
  static TBranch* b_clusterPt                   = { (TBranch*)0 }; //!
  static TBranch* b_clusterEta		        = { (TBranch*)0 }; //!
  static TBranch* b_clusterPhi		        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_sumCellE	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_time                = { (TBranch*)0 }; //!
  static TBranch* b_cluster_fracE	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_fracE_ref	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_EM_PROBABILITY      = { (TBranch*)0 }; //!
  static TBranch* b_cluster_HAD_WEIGHT          = { (TBranch*)0 }; //!
  static TBranch* b_cluster_OOC_WEIGHT	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_DM_WEIGHT	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_CALIB_TOT       = { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_CALIB_OUT_T     = { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_CALIB_DEAD_TOT	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_CENTER_MAG		= { (TBranch*)0 }; //!
  static TBranch* b_cluster_FIRST_ENG_DENS	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_FIRST_PHI           = { (TBranch*)0 }; //!
  static TBranch* b_cluster_FIRST_ETA		= { (TBranch*)0 }; //!
  static TBranch* b_cluster_SECOND_R		= { (TBranch*)0 }; //!
  static TBranch* b_cluster_SECOND_LAMBDA	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_DELTA_PHI           = { (TBranch*)0 }; //!
  static TBranch* b_cluster_DELTA_THETA	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_DELTA_ALPHA	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_CENTER_X		= { (TBranch*)0 }; //!
  static TBranch* b_cluster_CENTER_Y            = { (TBranch*)0 }; //!
  static TBranch* b_cluster_CENTER_Z	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_CENTER_LAMBDA       = { (TBranch*)0 }; //!
  static TBranch* b_cluster_LATERAL	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_LONGITUDINAL        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_FRAC_EM	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_FRAC_MAX	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_FRAC_CORE	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_SECOND_ENG_DENS     = { (TBranch*)0 }; //!
  static TBranch* b_cluster_ISOLATION		= { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_BAD_CELLS	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_N_BAD_CELLS	        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_N_BAD_CELLS_CORR    = { (TBranch*)0 }; //!
  static TBranch* b_cluster_BAD_CELLS_CORR_E	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_BADLARQ_FRAC	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_POS		= { (TBranch*)0 }; //!
  static TBranch* b_cluster_SIGNIFICANCE        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_CELL_SIGNIFICANCE	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_CELL_SIG_SAMPLING	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_AVG_LAR_Q		= { (TBranch*)0 }; //!
  static TBranch* b_cluster_AVG_TILE_Q          = { (TBranch*)0 }; //!
  static TBranch* b_cluster_ENG_BAD_HV_CELLS	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_N_BAD_HV_CELLS	= { (TBranch*)0 }; //!
  static TBranch* b_cluster_PTD		        = { (TBranch*)0 }; //!
  static TBranch* b_cluster_MASS                = { (TBranch*)0 }; //!
  static TBranch* b_cluster_SECOND_TIME	        = { (TBranch*)0 }; //!
  static TBranch* b_CalibratedE		        = { (TBranch*)0 }; //!
  static TBranch* b_Delta_Calib_E 		= { (TBranch*)0 }; //!
  static TBranch* b_Delta_E                     = { (TBranch*)0 }; //!

  static int setAddresses(TTree* tree) {
    int bctr(0); 
    if ( tree->FindLeaf("entry"                      ) != nullptr ) { ++bctr; tree->SetBranchAddress("entry"                      ,&Data::entry                     ,&b_entry                     ); } 
    if ( tree->FindLeaf("runNumber"                  ) != nullptr ) { ++bctr; tree->SetBranchAddress("runNumber"                  ,&Data::runNumber                 ,&b_runNumber                 ); }
    if ( tree->FindLeaf("eventNumber"                ) != nullptr ) { ++bctr; tree->SetBranchAddress("eventNumber"                ,&Data::eventNumber               ,&b_eventNumber               ); }
    if ( tree->FindLeaf("truthE"                     ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthE"                     ,&Data::truthE                    ,&b_truthE                    ); }
    if ( tree->FindLeaf("truthPt"                    ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthPt"                    ,&Data::truthPt                   ,&b_truthPt                   ); }
    if ( tree->FindLeaf("truthEta"                   ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthEta"                   ,&Data::truthEta                  ,&b_truthEta                  ); }
    if ( tree->FindLeaf("truthPhi"                   ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthPhi"                   ,&Data::truthPhi                  ,&b_truthPhi                  ); }
    if ( tree->FindLeaf("truthPDG"                   ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthPDG"                   ,&Data::truthPDG                  ,&b_truthPDG                  ); }
    if ( tree->FindLeaf("jetCalE"                    ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetCalE"                    ,&Data::jetCalE                   ,&b_jetCalE                   ); } 
    if ( tree->FindLeaf("jetCalPt"	             ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetCalPt"                   ,&Data::jetCalPt                  ,&b_jetCalPt                  ); }
    if ( tree->FindLeaf("jetCalEta"	             ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetCalEta"		  ,&Data::jetCalEta                 ,&b_jetCalEta                 ); }
    if ( tree->FindLeaf("jetCalPhi"	             ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetCalPhi"		  ,&Data::jetCalPhi                 ,&b_jetCalPhi                 ); }
    if ( tree->FindLeaf("jetRawE"		     ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetRawE"		          ,&Data::jetRawE                   ,&b_jetRawE                   ); }
    if ( tree->FindLeaf("jetRawPt"                   ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetRawPt"                   ,&Data::jetRawPt                  ,&b_jetRawPt                  ); }
    if ( tree->FindLeaf("jetRawEta"		     ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetRawEta"		  ,&Data::jetRawEta                 ,&b_jetRawEta                 ); }
    if ( tree->FindLeaf("jetRawPhi"		     ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetRawPhi"		  ,&Data::jetRawPhi                 ,&b_jetRawPhi                 ); }
    if ( tree->FindLeaf("jetNConst"		     ) != nullptr ) { ++bctr; tree->SetBranchAddress("jetNConst"		  ,&Data::jetNConst     	    ,&b_jetNConst                 ); }
    if ( tree->FindLeaf("truthJetMatchingRadius"     ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthJetMatchingRadius"     ,&Data::truthJetMatchingRadius    ,&b_truthJetMatchingRadius    ); }
    if ( tree->FindLeaf("truthJetE"                  ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthJetE"                  ,&Data::truthJetE                 ,&b_truthJetE                 ); }
    if ( tree->FindLeaf("truthJetPt" 		     ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthJetPt" 	          ,&Data::truthJetPt 	            ,&b_truthJetPt                ); }
    if ( tree->FindLeaf("truthJetEta" 		     ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthJetEta" 	          ,&Data::truthJetEta 	            ,&b_truthJetEta               ); }
    if ( tree->FindLeaf("truthJetPhi" 		     ) != nullptr ) { ++bctr; tree->SetBranchAddress("truthJetPhi" 	          ,&Data::truthJetPhi 	            ,&b_truthJetPhi               ); }
    if ( tree->FindLeaf("nCluster"                   ) != nullptr ) { ++bctr; tree->SetBranchAddress("nCluster"                   ,&Data::nCluster                  ,&b_nCluster                  ); }
    if ( tree->FindLeaf("clusterIndex"               ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterIndex"               ,&Data::clusterIndex              ,&b_clusterIndex              ); }
    if ( tree->FindLeaf("cluster_nCells"             ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_nCells"             ,&Data::cluster_nCells            ,&b_cluster_nCells            ); }
    if ( tree->FindLeaf("cluster_nCells_tot"         ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_nCells_tot"         ,&Data::cluster_nCells_tot        ,&b_cluster_nCells_tot        ); }
    if ( tree->FindLeaf("clusterECalib"              ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterECalib"              ,&Data::clusterECalib             ,&b_clusterECalib             ); }
    if ( tree->FindLeaf("clusterPtCalib"             ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterPtCalib"             ,&Data::clusterPtCalib            ,&b_clusterPtCalib            ); }
    if ( tree->FindLeaf("clusterEtaCalib"            ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterEtaCalib"            ,&Data::clusterEtaCalib           ,&b_clusterEtaCalib           ); }
    if ( tree->FindLeaf("clusterPhiCalib"            ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterPhiCalib"            ,&Data::clusterPhiCalib           ,&b_clusterPhiCalib           ); }
    if ( tree->FindLeaf("cluster_sumCellECalib"      ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_sumCellECalib"      ,&Data::cluster_sumCellECalib     ,&b_cluster_sumCellECalib     ); }
    if ( tree->FindLeaf("cluster_fracECalib"         ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_fracECalib"         ,&Data::cluster_fracECalib        ,&b_cluster_fracECalib        ); }
    if ( tree->FindLeaf("cluster_fracECalib_ref"     ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_fracECalib_ref"     ,&Data::cluster_fracECalib_ref    ,&b_cluster_fracECalib_ref    ); }
    if ( tree->FindLeaf("clusterE"                   ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterE"                   ,&Data::clusterE                  ,&b_clusterE                  ); }
    if ( tree->FindLeaf("clusterPt"                  ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterPt"                  ,&Data::clusterPt                 ,&b_clusterPt                 ); }
    if ( tree->FindLeaf("clusterEta"                 ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterEta"                 ,&Data::clusterEta                ,&b_clusterEta                ); }
    if ( tree->FindLeaf("clusterPhi"                 ) != nullptr ) { ++bctr; tree->SetBranchAddress("clusterPhi"                 ,&Data::clusterPhi                ,&b_clusterPhi                ); }
    if ( tree->FindLeaf("cluster_sumCellE"           ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_sumCellE"           ,&Data::cluster_sumCellE          ,&b_cluster_sumCellE          ); }
    if ( tree->FindLeaf("cluster_time"               ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_time"               ,&Data::cluster_time              ,&b_cluster_time              ); }
    if ( tree->FindLeaf("cluster_fracE"              ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_fracE"              ,&Data::cluster_fracE             ,&b_cluster_fracE             ); }
    if ( tree->FindLeaf("cluster_fracE_ref"          ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_fracE_ref"          ,&Data::cluster_fracE_ref         ,&b_cluster_fracE_ref         ); }
    if ( tree->FindLeaf("cluster_EM_PROBABILITY"     ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_EM_PROBABILITY"     ,&Data::cluster_EM_PROBABILITY    ,&b_cluster_EM_PROBABILITY    ); }
    if ( tree->FindLeaf("cluster_HAD_WEIGHT"         ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_HAD_WEIGHT"         ,&Data::cluster_HAD_WEIGHT        ,&b_cluster_HAD_WEIGHT        ); }
    if ( tree->FindLeaf("cluster_OOC_WEIGHT"         ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_OOC_WEIGHT"         ,&Data::cluster_OOC_WEIGHT        ,&b_cluster_OOC_WEIGHT        ); }
    if ( tree->FindLeaf("cluster_DM_WEIGHT"          ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_DM_WEIGHT"          ,&Data::cluster_DM_WEIGHT         ,&b_cluster_DM_WEIGHT         ); }
    if ( tree->FindLeaf("cluster_ENG_CALIB_TOT"      ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_CALIB_TOT"      ,&Data::cluster_ENG_CALIB_TOT     ,&b_cluster_ENG_CALIB_TOT     ); }
    if ( tree->FindLeaf("cluster_ENG_CALIB_OUT_T"    ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_CALIB_OUT_T"    ,&Data::cluster_ENG_CALIB_OUT_T   ,&b_cluster_ENG_CALIB_OUT_T   ); }
    if ( tree->FindLeaf("cluster_ENG_CALIB_DEAD_TOT" ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_CALIB_DEAD_TOT" ,&Data::cluster_ENG_CALIB_DEAD_TOT,&b_cluster_ENG_CALIB_DEAD_TOT); }
    if ( tree->FindLeaf("cluster_CENTER_MAG"         ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_CENTER_MAG"         ,&Data::cluster_CENTER_MAG        ,&b_cluster_CENTER_MAG        ); }
    if ( tree->FindLeaf("cluster_FIRST_ENG_DENS"     ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_FIRST_ENG_DENS"     ,&Data::cluster_FIRST_ENG_DENS    ,&b_cluster_FIRST_ENG_DENS    ); }
    if ( tree->FindLeaf("cluster_FIRST_PHI"          ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_FIRST_PHI"          ,&Data::cluster_FIRST_PHI         ,&b_cluster_FIRST_PHI         ); }
    if ( tree->FindLeaf("cluster_FIRST_ETA"          ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_FIRST_ETA"          ,&Data::cluster_FIRST_ETA         ,&b_cluster_FIRST_ETA         ); }
    if ( tree->FindLeaf("cluster_SECOND_R"           ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_SECOND_R"           ,&Data::cluster_SECOND_R          ,&b_cluster_SECOND_R          ); }
    if ( tree->FindLeaf("cluster_SECOND_LAMBDA"      ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_SECOND_LAMBDA"      ,&Data::cluster_SECOND_LAMBDA     ,&b_cluster_SECOND_LAMBDA     ); }
    if ( tree->FindLeaf("cluster_DELTA_PHI"          ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_DELTA_PHI"          ,&Data::cluster_DELTA_PHI         ,&b_cluster_DELTA_PHI         ); }
    if ( tree->FindLeaf("cluster_DELTA_THETA"        ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_DELTA_THETA"        ,&Data::cluster_DELTA_THETA       ,&b_cluster_DELTA_THETA       ); }
    if ( tree->FindLeaf("cluster_DELTA_ALPHA"        ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_DELTA_ALPHA"        ,&Data::cluster_DELTA_ALPHA       ,&b_cluster_DELTA_ALPHA       ); }
    if ( tree->FindLeaf("cluster_CENTER_X"           ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_CENTER_X"           ,&Data::cluster_CENTER_X          ,&b_cluster_CENTER_X          ); }
    if ( tree->FindLeaf("cluster_CENTER_Y"           ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_CENTER_Y"           ,&Data::cluster_CENTER_Y          ,&b_cluster_CENTER_Y          ); }
    if ( tree->FindLeaf("cluster_CENTER_Z"           ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_CENTER_Z"           ,&Data::cluster_CENTER_Z          ,&b_cluster_CENTER_Z          ); }
    if ( tree->FindLeaf("cluster_CENTER_LAMBDA"      ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_CENTER_LAMBDA"      ,&Data::cluster_CENTER_LAMBDA     ,&b_cluster_CENTER_LAMBDA     ); }
    if ( tree->FindLeaf("cluster_LATERAL"            ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_LATERAL"            ,&Data::cluster_LATERAL           ,&b_cluster_LATERAL           ); }
    if ( tree->FindLeaf("cluster_LONGITUDINAL"       ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_LONGITUDINAL"       ,&Data::cluster_LONGITUDINAL      ,&b_cluster_LONGITUDINAL      ); }
    if ( tree->FindLeaf("cluster_ENG_FRAC_EM"        ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_FRAC_EM"        ,&Data::cluster_ENG_FRAC_EM       ,&b_cluster_ENG_FRAC_EM       ); }
    if ( tree->FindLeaf("cluster_ENG_FRAC_MAX"       ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_FRAC_MAX"       ,&Data::cluster_ENG_FRAC_MAX      ,&b_cluster_ENG_FRAC_MAX      ); }
    if ( tree->FindLeaf("cluster_ENG_FRAC_CORE"      ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_FRAC_CORE"      ,&Data::cluster_ENG_FRAC_CORE     ,&b_cluster_ENG_FRAC_CORE     ); }
    if ( tree->FindLeaf("cluster_SECOND_ENG_DENS"    ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_SECOND_ENG_DENS"    ,&Data::cluster_SECOND_ENG_DENS   ,&b_cluster_SECOND_ENG_DENS   ); }
    if ( tree->FindLeaf("cluster_ISOLATION"          ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ISOLATION"          ,&Data::cluster_ISOLATION         ,&b_cluster_ISOLATION         ); }
    if ( tree->FindLeaf("cluster_ENG_BAD_CELLS"      ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_BAD_CELLS"      ,&Data::cluster_ENG_BAD_CELLS     ,&b_cluster_ENG_BAD_CELLS     ); }
    if ( tree->FindLeaf("cluster_N_BAD_CELLS"        ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_N_BAD_CELLS"        ,&Data::cluster_N_BAD_CELLS       ,&b_cluster_N_BAD_CELLS       ); }
    if ( tree->FindLeaf("cluster_N_BAD_CELLS_CORR"   ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_N_BAD_CELLS_CORR"   ,&Data::cluster_N_BAD_CELLS_CORR  ,&b_cluster_N_BAD_CELLS_CORR  ); }
    if ( tree->FindLeaf("cluster_BAD_CELLS_CORR_E"   ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_BAD_CELLS_CORR_E"   ,&Data::cluster_BAD_CELLS_CORR_E  ,&b_cluster_BAD_CELLS_CORR_E  ); }
    if ( tree->FindLeaf("cluster_BADLARQ_FRAC"       ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_BADLARQ_FRAC"       ,&Data::cluster_BADLARQ_FRAC      ,&b_cluster_BADLARQ_FRAC      ); }
    if ( tree->FindLeaf("cluster_ENG_POS"            ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_POS"            ,&Data::cluster_ENG_POS           ,&b_cluster_ENG_POS           ); }
    if ( tree->FindLeaf("cluster_SIGNIFICANCE"       ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_SIGNIFICANCE"       ,&Data::cluster_SIGNIFICANCE      ,&b_cluster_SIGNIFICANCE      ); }
    if ( tree->FindLeaf("cluster_CELL_SIGNIFICANCE"  ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_CELL_SIGNIFICANCE"  ,&Data::cluster_CELL_SIGNIFICANCE ,&b_cluster_CELL_SIGNIFICANCE ); }
    if ( tree->FindLeaf("cluster_CELL_SIG_SAMPLING"  ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_CELL_SIG_SAMPLING"  ,&Data::cluster_CELL_SIG_SAMPLING ,&b_cluster_CELL_SIG_SAMPLING ); }
    if ( tree->FindLeaf("cluster_AVG_LAR_Q"          ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_AVG_LAR_Q"          ,&Data::cluster_AVG_LAR_Q         ,&b_cluster_AVG_LAR_Q         ); }
    if ( tree->FindLeaf("cluster_AVG_TILE_Q"         ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_AVG_TILE_Q"         ,&Data::cluster_AVG_TILE_Q        ,&b_cluster_AVG_TILE_Q        ); }
    if ( tree->FindLeaf("cluster_ENG_BAD_HV_CELLS"   ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_ENG_BAD_HV_CELLS"   ,&Data::cluster_ENG_BAD_HV_CELLS  ,&b_cluster_ENG_BAD_HV_CELLS  ); }
    if ( tree->FindLeaf("cluster_N_BAD_HV_CELLS"     ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_N_BAD_HV_CELLS"     ,&Data::cluster_N_BAD_HV_CELLS    ,&b_cluster_N_BAD_HV_CELLS    ); }
    if ( tree->FindLeaf("cluster_PTD"                ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_PTD"                ,&Data::cluster_PTD               ,&b_cluster_PTD               ); }
    if ( tree->FindLeaf("cluster_MASS"               ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_MASS"               ,&Data::cluster_MASS              ,&b_cluster_MASS              ); }
    if ( tree->FindLeaf("cluster_SECOND_TIME"        ) != nullptr ) { ++bctr; tree->SetBranchAddress("cluster_SECOND_TIME"        ,&Data::cluster_SECOND_TIME       ,&b_cluster_SECOND_TIME       ); }
    if ( tree->FindLeaf("CalibratedE"                ) != nullptr ) { ++bctr; tree->SetBranchAddress("CalibratedE"                ,&Data::CalibratedE               ,&b_CalibratedE               ); }
    if ( tree->FindLeaf("Delta_Calib_E "             ) != nullptr ) { ++bctr; tree->SetBranchAddress("Delta_Calib_E "             ,&Data::Delta_Calib_E             ,&b_Delta_Calib_E             ); }
    if ( tree->FindLeaf("Delta_E"                    ) != nullptr ) { ++bctr; tree->SetBranchAddress("Delta_E"                    ,&Data::Delta_E                   ,&b_Delta_E                   ); }
    return bctr; 
  }
} // Branches

void convertToCSV(const std::string& fileName,const std::string& treeName) { 
  // open file
  TFile* file = new TFile(fileName.c_str(),"READ");
  if ( file == nullptr ) { printf("[convertToCSV(fileName=\042%s\042,treeName=\042%s\042)] ABRT cannot find file\n",fileName.c_str(),treeName.c_str()); return; }
  // find tree
  TTree* tree = (TTree*)file->FindObjectAny(treeName.c_str());
  if ( tree == nullptr ) { printf("[convertToCSV(fileName=\042%s\042,treeName=\042%s\042)] ABRT cannot find tree\n",fileName.c_str(),treeName.c_str()); return; }
  // set branch addresses
  printf("[convertToCSV(fileName=\042%s\042,treeName=\042%s\042)] INFO set %i of branch addresses\n",fileName.c_str(),treeName.c_str(),Branches::setAddresses(tree)); 
  // get list of leaves
  std::vector<std::tuple<std::string,TLeaf*> > mapOfLeaves; 
  TObjArray* lof = tree->GetListOfLeaves();
  int nleaves(lof->GetEntries());
  for ( int i(0); i<nleaves; ++i ) { 
    TObject* pObj = (*lof)[i]; if ( pObj != nullptr ) { mapOfLeaves.push_back( { std::string(pObj->GetName()), tree->GetLeaf(pObj->GetName()) } ); } 
  }
  // get values
  int  nentries(tree->GetEntries());  std::vector<std::vector<double> > data; data.reserve(nentries+1);
  for ( int ientry(0); ientry<nentries; ++ientry ) {
    if ( tree->LoadTree(ientry) < 0 ) { break; } // reached end-of-file/read error
    tree->GetEntry(ientry); 
    data.push_back(std::vector<double>()); data.back().reserve(nleaves); 
    for ( auto leaf : mapOfLeaves ) { data.back().push_back(std::get<1>(leaf)->GetValue()); } 
  }
  //
  printf("[convertToCSV(fileName=\042%s\042,treeName=\042%s\042)] INFO found %zu of %i leaves\n",fileName.c_str(),treeName.c_str(),mapOfLeaves.size(),nleaves);
  // int l = static_cast<int>(std::log10((double)mapOfLeaves.size())+1.); 
  // size_t nl(0); 
  // for ( auto entry : mapOfLeaves ) { printf("[convertToCSV(fileName=\042%s\042,treeName=\042%s\042)] INFO leave %*zu: \042%s\042\n",fileName.c_str(),treeName.c_str(),l,nl++,std::get<0>(entry).c_str()); }
  // pipe the vector to a stream
  auto fext = fileName.find_last_of('.'); 
  auto fileNameCSV = fileName.substr(0,fext) + std::string(".csv");
  printf("[convertToCSV(fileName=\042%s\042,treeName=\042%s\042)] INFO writing column headers to file \042%s\042\n",fileName.c_str(),treeName.c_str(),fileNameCSV.c_str()); 
  std::ofstream outStream(fileNameCSV);
  for ( size_t i(0); i<mapOfLeaves.size(); ++i ) { 
    if ( i < mapOfLeaves.size()-1 ) { outStream << std::get<0>(mapOfLeaves.at(i)) << ","; } else { outStream << std::get<0>(mapOfLeaves.at(i)) << std::endl; } 
  }
  for ( auto entry : data ) { 
    for ( size_t i(0); i<entry.size()-1; ++i ) { outStream << entry.at(i) << ","; }
    outStream << entry.back() << std::endl;
  }

  outStream.close();
}
