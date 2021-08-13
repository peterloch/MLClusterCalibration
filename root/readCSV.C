
#include <TFile.h>
#include <TTree.h>

#include <string>
// #include <map>

// #define ADD( TREE, BRANCH )						\
//   if ( typeMap.find( #BRANCH ) != typeMap.end() ) {			\
//   std::string leaf( #BRANCH );						\
//   leaf += (std::string("/")+typeMap.at( #BRANCH ));			\
//   TREE->Branch( #BRANCH, & BRANCH, leaf.c_str() );			\
//   }

void readCSV(const std::string& csvFileName,const std::string& rootFileName) {

  // int   entry,runNumber,eventNumber;
  // float jetCalE,jetCalPt,jetCalEta,jetCalPhi;
  // float jetRawE,jetRawPt,jetRawEta,jetRawPhi;
  // float truthJetE,truthJetPt,truthJetRap,truthJetPhi;
  // float jetNConst;
  // float truthJetMatchRadius;
  // int   nCluster,clusterIndex,cluster_nCells,cluster_nCells_tot;
  // float clusterECalib,clusterPtCalib,clusterEtaCalib,clusterPhiCalib,cluster_sumCellECalib,cluster_fracECalib,cluster_fracECalib_ref;
  // float clusterE,clusterPt,clusterEta,clusterPhi,cluster_sumCellE,cluster_fracE,cluster_fracE_ref;
  // float cluster_time;
  // float cluster_EM_PROBABILITY,cluster_HAD_WEIGHT,cluster_OOC_WEIGHT,cluster_DM_WEIGHT;
  // float cluster_ENG_CALIB_TOT,cluster_ENG_CALIB_OUT_T,cluster_ENG_CALIB_DEAD_TOT;
  // float cluster_CENTER_MAG,cluster_FIRST_ENG_DENS,cluster_FIRST_PHI,cluster_FIRST_ETA;
  // float cluster_SECOND_R,cluster_SECOND_LAMBDA,cluster_DELTA_PHI,cluster_DELTA_THETA,cluster_DELTA_ALPHA;
  // float cluster_CENTER_X,cluster_CENTER_Y,cluster_CENTER_Z;
  // float cluster_CENTER_LAMBDA,cluster_LATERAL,cluster_LONGITUDINAL;
  // float cluster_ENG_FRAC_EM,cluster_ENG_FRAC_MAX,cluster_ENG_FRAC_CORE;
  // float cluster_SECOND_ENG_DENS,cluster_ISOLATION;
  // float cluster_ENG_BAD_CELLS;
  // int   cluster_N_BAD_CELLS,cluster_N_BAD_CELLS_CORR;
  // float cluster_BAD_CELLS_CORR_E,cluster_BADLARQ_FRAC;
  // float cluster_ENG_POS;
  // float cluster_SIGNIFICANCE,cluster_CELL_SIGNIFICANCE,cluster_CELL_SIG_SAMPLING;
  // float cluster_AVG_LAR_Q,cluster_AVG_TILE_Q,cluster_ENG_BAD_HV_CELLS;
  // int   cluster_N_BAD_HV_CELLS;
  // float cluster_PTD,cluster_MASS,cluster_SECOND_TIME;
  // float CalibratedE,Delta_Calib_E ,Delta_E;

  // std::map<std::string,std::string> typeMap = {
  //   { "entry"                     , "I" },
  //   { "runNumber"                 , "I" },
  //   { "eventNumber"               , "I" },
  //   { "jetCalE"                   , "F" },
  //   { "jetCalPt"                  , "F" },
  //   { "jetCalEta"                 , "F" },
  //   { "jetCalPhi"                 , "F" },
  //   { "jetRawE"                   , "F" },
  //   { "jetRawPt"                  , "F" },
  //   { "jetRawEta"                 , "F" },
  //   { "jetRawPhi"                 , "F" },
  //   { "jetNConst"                 , "I" },
  //   { "truthJetMatchRadius"       , "F" },
  //   { "truthJetE"                 , "F" },
  //   { "truthJetPt"                , "F" },
  //   { "truthJetRap"               , "F" },
  //   { "truthJetPhi"               , "F" },
  //   { "nCluster"                  , "I" },
  //   { "clusterIndex"              , "I" },
  //   { "cluster_nCells"            , "I" },
  //   { "cluster_nCells_tot"        , "I" },
  //   { "clusterECalib"             , "F" },
  //   { "clusterPtCalib"            , "F" },
  //   { "clusterEtaCalib"           , "F" },
  //   { "clusterPhiCalib"           , "F" },
  //   { "cluster_sumCellECalib"     , "F" },
  //   { "cluster_fracECalib"        , "F" },
  //   { "cluster_fracECalib_ref"    , "F" },
  //   { "clusterE"                  , "F" },
  //   { "clusterPt"                 , "F" },
  //   { "clusterEta"                , "F" },
  //   { "clusterPhi"                , "F" },
  //   { "cluster_sumCellE"          , "F" },
  //   { "cluster_time"              , "F" },
  //   { "cluster_fracE"             , "F" },
  //   { "cluster_fracE_ref"         , "F" },
  //   { "cluster_EM_PROBABILITY"    , "F" },
  //   { "cluster_HAD_WEIGHT"        , "F" },
  //   { "cluster_OOC_WEIGHT"        , "F" },
  //   { "cluster_DM_WEIGHT"         , "F" },
  //   { "cluster_ENG_CALIB_TOT"     , "F" },
  //   { "cluster_ENG_CALIB_OUT_T"   , "F" },
  //   { "cluster_ENG_CALIB_DEAD_TOT", "F" },
  //   { "cluster_CENTER_MAG"        , "F" },
  //   { "cluster_FIRST_ENG_DENS"    , "F" },
  //   { "cluster_FIRST_PHI"         , "F" },
  //   { "cluster_FIRST_ETA"         , "F" },
  //   { "cluster_SECOND_R"          , "F" },
  //   { "cluster_SECOND_LAMBDA"     , "F" },
  //   { "cluster_DELTA_PHI"         , "F" },
  //   { "cluster_DELTA_THETA"       , "F" },
  //   { "cluster_DELTA_ALPHA"       , "F" },
  //   { "cluster_CENTER_X"          , "F" },
  //   { "cluster_CENTER_Y"          , "F" },
  //   { "cluster_CENTER_Z"          , "F" },
  //   { "cluster_CENTER_LAMBDA"     , "F" },
  //   { "cluster_LATERAL"           , "F" },
  //   { "cluster_LONGITUDINAL"      , "F" },
  //   { "cluster_ENG_FRAC_EM"       , "F" },
  //   { "cluster_ENG_FRAC_MAX"      , "F" },
  //   { "cluster_ENG_FRAC_CORE"     , "F" },
  //   { "cluster_SECOND_ENG_DENS"   , "F" },
  //   { "cluster_ISOLATION"         , "F" },
  //   { "cluster_ENG_BAD_CELLS"     , "F" },
  //   { "cluster_N_BAD_CELLS"       , "I" },
  //   { "cluster_N_BAD_CELLS_CORR"  , "I" },
  //   { "cluster_BAD_CELLS_CORR_E"  , "F" },
  //   { "cluster_BADLARQ_FRAC"      , "F" },
  //   { "cluster_ENG_POS"           , "F" },
  //   { "cluster_SIGNIFICANCE"      , "F" },
  //   { "cluster_CELL_SIGNIFICANCE" , "F" },
  //   { "cluster_CELL_SIG_SAMPLING" , "F" },
  //   { "cluster_AVG_LAR_Q"         , "F" },
  //   { "cluster_AVG_TILE_Q"        , "F" },
  //   { "cluster_ENG_BAD_HV_CELLS"  , "F" },
  //   { "cluster_N_BAD_HV_CELLS"    , "I" },
  //   { "cluster_PTD"               , "F" },
  //   { "cluster_MASS"              , "F" },
  //   { "cluster_SECOND_TIME"       , "F" },
  //   { "CalibratedE"               , "F" },
  //   { "Delta_Calib_E"             , "F" },
  //   { "Delta_E"                   , "F" }
  // };

  TFile* outf = new TFile(rootFileName.c_str(),"RECREATE"); 
  TTree* tree = new TTree("ClusterTree","ClusterTree"); 
  tree->ReadFile(csvFileName.c_str(),"",','); 
  tree->Write();
  outf->Close();

  // ADD( tree, runNumber                  );
  // ADD( tree, eventNumber                );
  // ADD( tree, jetCalE                    );
  // ADD( tree, jetCalPt                   );
  // ADD( tree, jetCalEta                  );
  // ADD( tree, jetCalPhi                  );
  // ADD( tree, jetRawE                    );
  // ADD( tree, jetRawPt                   );
  // ADD( tree, jetRawEta                  );
  // ADD( tree, jetRawPhi                  );
  // ADD( tree, jetNConst                  );
  // ADD( tree, truthJetMatchRadius        );
  // ADD( tree, truthJetE                  );
  // ADD( tree, truthJetPt                 );
  // ADD( tree, truthJetRap                );
  // ADD( tree, truthJetPhi                );
  // ADD( tree, nCluster                   );
  // ADD( tree, clusterIndex               );
  // ADD( tree, cluster_nCells             );
  // ADD( tree, cluster_nCells_tot         );
  // ADD( tree, clusterECalib              );
  // ADD( tree, clusterPtCalib             );
  // ADD( tree, clusterEtaCalib            );
  // ADD( tree, clusterPhiCalib            );
  // ADD( tree, cluster_sumCellECalib      );
  // ADD( tree, cluster_fracECalib         );
  // ADD( tree, cluster_fracECalib_ref     );
  // ADD( tree, clusterE                   );
  // ADD( tree, clusterPt                  );
  // ADD( tree, clusterEta                 );
  // ADD( tree, clusterPhi                 );
  // ADD( tree, cluster_sumCellE           );
  // ADD( tree, cluster_time               );
  // ADD( tree, cluster_fracE              );
  // ADD( tree, cluster_fracE_ref          );
  // ADD( tree, cluster_EM_PROBABILITY     );
  // ADD( tree, cluster_HAD_WEIGHT         );
  // ADD( tree, cluster_OOC_WEIGHT         );
  // ADD( tree, cluster_DM_WEIGHT          );
  // ADD( tree, cluster_ENG_CALIB_TOT      );
  // ADD( tree, cluster_ENG_CALIB_OUT_T    );
  // ADD( tree, cluster_ENG_CALIB_DEAD_TOT );
  // ADD( tree, cluster_CENTER_MAG         );
  // ADD( tree, cluster_FIRST_ENG_DENS     );
  // ADD( tree, cluster_FIRST_PHI          );
  // ADD( tree, cluster_FIRST_ETA          );
  // ADD( tree, cluster_SECOND_R           );
  // ADD( tree, cluster_SECOND_LAMBDA      );
  // ADD( tree, cluster_DELTA_PHI          );
  // ADD( tree, cluster_DELTA_THETA        );
  // ADD( tree, cluster_DELTA_ALPHA        );
  // ADD( tree, cluster_CENTER_X           );
  // ADD( tree, cluster_CENTER_Y           );
  // ADD( tree, cluster_CENTER_Z           );
  // ADD( tree, cluster_CENTER_LAMBDA      );
  // ADD( tree, cluster_LATERAL            );
  // ADD( tree, cluster_LONGITUDINAL       );
  // ADD( tree, cluster_ENG_FRAC_EM        );
  // ADD( tree, cluster_ENG_FRAC_MAX       );
  // ADD( tree, cluster_ENG_FRAC_CORE      );
  // ADD( tree, cluster_SECOND_ENG_DENS    );
  // ADD( tree, cluster_ISOLATION          );
  // ADD( tree, cluster_ENG_BAD_CELLS      );
  // ADD( tree, cluster_N_BAD_CELLS        );
  // ADD( tree, cluster_N_BAD_CELLS_CORR   );
  // ADD( tree, cluster_BAD_CELLS_CORR_E   );
  // ADD( tree, cluster_BADLARQ_FRAC       );
  // ADD( tree, cluster_ENG_POS            );
  // ADD( tree, cluster_SIGNIFICANCE       );
  // ADD( tree, cluster_CELL_SIGNIFICANCE  );
  // ADD( tree, cluster_CELL_SIG_SAMPLING  );
  // ADD( tree, cluster_AVG_LAR_Q          );
  // ADD( tree, cluster_AVG_TILE_Q         );
  // ADD( tree, cluster_ENG_BAD_HV_CELLS   );
  // ADD( tree, cluster_N_BAD_HV_CELLS     );
  // ADD( tree, cluster_PTD                );
  // ADD( tree, cluster_MASS               );
  // ADD( tree, cluster_SECOND_TIME        );
  // ADD( tree, CalibratedE                );
  // ADD( tree, Delta_Calib_E              );
  // ADD( tree, Delta_E                    );
 
}
