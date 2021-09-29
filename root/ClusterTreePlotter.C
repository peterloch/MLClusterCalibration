#define ClusterTreePlotter_cxx
#include "ClusterTreePlotter.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>

#include "HistManager.h"

#include <vector>
#include <cmath>

/////////////////////
// Production mode //
/////////////////////

bool ClusterTreePlotter::hasBookedLeaf(const std::string& lname) { return m_listOfLeaves.find(lname) != m_listOfLeaves.end(); }
bool ClusterTreePlotter::isJet()                                 { return m_isJet;      }
bool ClusterTreePlotter::isParticle()                            { return m_isParticle; }

///////////////////////
// Setting Selectors //
///////////////////////

void ClusterTreePlotter::setParticleEmin  (ParticleScale ps,double e                   ) { key_t key((uint_t)ps); m_selectors[key] = { ValueType::E  , e     , -1.   , false }; }
void ClusterTreePlotter::setParticlePtmin (ParticleScale ps,double pt                  ) { key_t key((uint_t)ps); m_selectors[key] = { ValueType::PT , pt    , -1.   , false }; }
void ClusterTreePlotter::setParticleAbsRap(ParticleScale ps,double rap                 ) { key_t key((uint_t)ps); m_selectors[key] = { ValueType::RAP, rap   , -1.   , true  }; }
void ClusterTreePlotter::setParticleAbsRap(ParticleScale ps,double rapmin,double rapmax) { key_t key((uint_t)ps); m_selectors[key] = { ValueType::RAP, rap   , rapmax, true  }; }
void ClusterTreePlotter::setParticleRap   (ParticleScale ps,double rap                 ) { key_t key((uint_t)ps); m_selectors[key] = { ValueType::RAP, rap   , -1.   , false }; }
void ClusterTreePlotter::setParticleRap   (ParticleScale ps,double rapmin,double rapmax) { key_t key((uint_t)ps); m_selectors[key] = { ValueType::RAP, rapmin, rapmax, false }; }

void ClusterTreePlotter::setClusterEmin  (ClusterScale cs,double e                   ) { key_t key((uint_t)cc); m_selectors[key] = { ValueType::E  , e     , -1.   , false }; }
void ClusterTreePlotter::setClusterPtmin (ClusterScale cs,double pt                  ) { key_t key((uint_t)cc); m_selectors[key] = { ValueType::PT , pt    , -1.   , false }; }
void ClusterTreePlotter::setClusterAbsRap(ClusterScale cs,double rap                 ) { key_t key((uint_t)cc); m_selectors[key] = { ValueType::RAP, rap   , -1.   , true  }; }
void ClusterTreePlotter::setClusterAbsRap(ClusterScale cs,double rapmin,double rapmax) { key_t key((uint_t)cc); m_selectors[key] = { ValueType::RAP, rap   , rapmax, true  }; }
void ClusterTreePlotter::setClusterRap   (ClusterScale cs,double rap                 ) { key_t key((uint_t)cc); m_selectors[key] = { ValueType::RAP, rap   , -1.   , false }; }
void ClusterTreePlotter::setClusterRap   (ClusterScale cs,double rapmin,double rapmax) { key_t key((uint_t)cc); m_selectors[key] = { ValueType::RAP, rapmin, rapmax, false }; }

void ClusterTreePlotter::setJetEMin      (JetScale js,double e                   ) { key_t key((unit_t)js); m_selectors[key] = { ValueType::E  , e     , -1.   , false }; }
void ClusterTreePlotter::setJetPtMin     (JetScale js,double pt                  ) { key_t key((unit_t)js); m_selectors[key] = { ValueType::PT , pt    , -1.   , false }; }
void ClusterTreePlotter::setJetAbsRap    (JetScale js,double rap                 ) { key_t key((unit_t)js); m_selectors[key] = { ValueType::RAP, rap   , -1.   , true  }; }
void ClusterTreePlotter::setJetAbsRap    (JetScale js,double rapmin,double rapmax) { key_t key((unit_t)js); m_selectors[key] = { ValueType::RAP, rap   , rapmax, true  }; }
void ClusterTreePlotter::setJetRap       (JetScale js,double rap                 ) { key_t key((unit_t)js); m_selectors[key] = { ValueType::RAP, rap   , -1.   , false }; }
void ClusterTreePlotter::setJetRap       (JetScale js,double rapmin,double rapmax) { key_t key((unit_t)js); m_selectors[key] = { ValueType::RAP, rapmin, rapmax, false }; }

////////////////////////
// Applying Selectors //
////////////////////////

// -- Clusters
bool ClusterTreePlotter::filter(ClusterScale cs)  { return select((uint_t)cs); }
// -- Jets					    		           
bool ClusterTreePlotter::filter(JetScale js)      { return !isJet()      || select((uint_t)js); }
// -- Particles					    		           
bool ClusterTreePlotter::filter(ParticleScale ps) { return !isParticle() || select((uint_t)ps); }
// -- Filter function 
bool ClusterTreePlotter::select(uint_t key) {
  // find variable to filter - if not found, no filter is applied
  auto fvar = m_selectors.lower_bound(key); if ( fvar == m_selectors.end() ) { return true; }
  // check with value map is needed
  const std::map<vkey_t,vptr_t>& map = isClusterKey<uint_t>(key) ? m_accessCluster : isJetKey<uint_t>(key) ? m_accessJet : isParticleKey<uint_t>(key) ? m_accessParticle : m_accessEmpty;
  if ( map.empty() ) { return true; }   
  // loop all variables
  bool accept(true); 
  while ( fvar != m_selectors.upper_bound(key) && accept ) {
    vkey_t vkey = { std::get<0>(fvar->second), key }; 
    auto fvalue(map.find(vkey)); 
    if ( fvalue != map.end() ) { 
      double value = std::get<3>(fvar->second) ? static_cast<double>(std::abs(*(fvalue->second))) : static_cast<double>(*(fvalue->second)); 
      accept = std::get<2>(fvar->second) > std::get<1>(fvar->second) ? value > std::get<1>(fvar->second) && value < std::get<2>(fvar->second) : value > std::get<1>(fvar->second);
    }
    ++fvar;
  } 
  return accept;
}

///////////////////
// Access values //
///////////////////
 
//   auto fsep(map.find(key)); if ( fsep == map.end() ) { return true; }
//   double e(0.); 
//   switch (cc) {
//   case ClusterCalib::RAW: e = std::get<2>(fsep->second) ? std::abs(clusterE)      : clusterE     ; break;
//   case ClusterCalib::LCW: e = std::get<2>(fsep->second) ? std::abs(clusterECalib) : clusterECalib; break;
//   case ClusterCalib::ML:  e = std::get<2>(fsep->second) ? std::abs(CalibratedE)   : CalibratedE  ; break;
//   case JetCalib::RAW:     e = std::get<2>(fsep->second) ? std::abs(jetRawE)       : jetRawE      ; break;
//   case JetCalib::LCJES:   e = std::get<2>(fsep->second) ? std::abs(jetCalE)       : jetCalE      ; break;
//   default:                                                                                         break;
//   }
//   return std::get<1>(fsep->second) > std::get<0>(fsep->second) ? e > std::get<0>(fsep->second) && e < std::get<1>(fsep->second) : e > std::get<0>(fsep->second); 
// }

void ClusterTreePionPlotter::Loop(double pdgID,bool absVal)
{

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   double xmin(.05); double xmax(2000.);
   double ymin(0.) ; double ymax(2); 
   int    n_bins(100);
   double lxmin(std::log10(xmin)); double lxmax(std::log10(xmax)); 
   double lxwid((lxmax-lxmin)/(double(n_bins)));
   std::vector<double> logEbins(n_bins+1,0.);
   for ( size_t i(0); i<logEbins.size(); ++i ) { logEbins[i] = std::pow(10.,lxmin); lxmin += lxwid; }

   double rmin(std::pow(10.,-8.5)); double rmax(std::pow(10.,-3.5));
   double rxmin(std::log10(rmin)); double rxmax(std::log10(rmax)); 
   double rxwid((rxmax-rxmin)/(double(n_bins)));
   std::vector<double> logRbins(n_bins+1,0.);
   for ( size_t i(0); i<logRbins.size(); ++i ) { logRbins[i] = std::pow(10.,rxmin); rxmin += rxwid; }

   double dmin(10e-03); double dmax(10e+04); 
   double dxmin(std::log10(dmin)); double dxmax(std::log10(dmax));
   double dxwid((dxmax-dxmin)/((double)n_bins));
   std::vector<double> logLbins(n_bins+1,0.); 
   for ( size_t i(0); i<logLbins.size(); ++i ) { logLbins[i] = std::pow(10.,dxmin); dxmin += dxwid; }

   double smin(std::pow(10.,-2.)); double smax(std::pow(10,4.)); 
   double sxmin(std::log10(smin)); double sxmax(std::log10(smax));
   double sxwid((sxmax-sxmin)/((double)n_bins));
   std::vector<double> logSbins(n_bins+1,0.); 
   for ( size_t i(0); i<logSbins.size(); ++i ) { logSbins[i] = std::pow(10.,sxmin); sxmin += sxwid; }
   
   printf("[ClusterTreePionPlotter::Loop()] INFO [%lli] calculated energy binning (%zu bins)\n",nentries,logEbins.size()-1); 

   // -- particle quantities
   TH1D* h_part_e_all_incl   = Hist::book<TH1D>("PartEAllIncl"  ,"Particle energy (inclusive,all particles)"  ,logEbins     ,"E_{part} [GeV]","entries/GeV");
   TH1D* h_part_e_pi0_incl   = Hist::book<TH1D>("PartEPi0Incl"  ,"Particle energy (inclusive,#pi^{0})"        ,logEbins     ,"E_{part} [GeV]","entries/GeV");
   TH1D* h_part_e_pic_incl   = Hist::book<TH1D>("PartEPiCIncl"  ,"Particle energy (inclusive,#pi^{#pm})"      ,logEbins     ,"E_{part} [GeV]","entries/GeV");
   TH1D* h_part_e_all_excl   = Hist::book<TH1D>("PartEAllExcl"  ,"Particle energy (exclusive,all particles)"  ,logEbins     ,"E_{part} [GeV]","entries/GeV");
   TH1D* h_part_e_pi0_excl   = Hist::book<TH1D>("PartEPi0Excl"  ,"Particle energy (exclusive,#pi^{0})"        ,logEbins     ,"E_{part} [GeV]","entries/GeV");
   TH1D* h_part_e_pic_excl   = Hist::book<TH1D>("PartEPiCExcl"  ,"Particle energy (exclusive,#pi^{#pm})"      ,logEbins     ,"E_{part} [GeV]","entries/GeV");
   TH1D* h_part_rap_all_incl = Hist::book<TH1D>("PartRapAllIncl","Particle rapidity (inclusive,all particles)",99,-4.95,4.95,"y_{part}"      ,"entries/0.1");
   TH1D* h_part_rap_pi0_incl = Hist::book<TH1D>("PartRapPi0Incl","Particle rapidity (inclusive,#pi^{0})"      ,99,-4.95,4.95,"y_{part}"      ,"entries/0.1");
   TH1D* h_part_rap_pic_incl = Hist::book<TH1D>("PartRapPiCIncl","Particle rapidity (inclusive,#pi^{#pm})"    ,99,-4.95,4.95,"y_{part}"      ,"entries/0.1");
   TH1D* h_part_rap_all_excl = Hist::book<TH1D>("PartRapAllExcl","Particle rapidity (exclusive,all particles)",99,-4.95,4.95,"y_{part}"      ,"entries/0.1");
   TH1D* h_part_rap_pi0_excl = Hist::book<TH1D>("PartRapPi0Excl","Particle rapidity (exclusive,#pi^{0})"      ,99,-4.95,4.95,"y_{part}"      ,"entries/0.1");
   TH1D* h_part_rap_pic_excl = Hist::book<TH1D>("PartRapPiCExcl","Particle rapidity (exclusive,#pi^{#pm})"    ,99,-4.95,4.95,"y_{part}"      ,"entries/0.1");

   // -- jet quantities
   TH1D* h_jet_cale_incl     = Hist::book<TH1D>("JetECalIncl"    ,"Calibrated jet energy (inclusive)"  ,logEbins     ,"E_{jet}^{LCJES} [GeV]"  ,"entries/GeV" );
   TH1D* h_jet_calpt_incl    = Hist::book<TH1D>("JetPtCalIncl"   ,"Calibrated jet p_{T} (inclusive)"   ,logEbins     ,"p_{T,jet}^{LCJES} [GeV]","entries/GeV" );
   TH1D* h_jet_calrap_incl   = Hist::book<TH1D>("JetRapCalIncl"  ,"Calibrated jet rapidity (inclusive)",99,-4.95,4.95,"y_{jet}^{LCJES}"        ,"entries/0.1" );
   TH1D* h_jet_cale_excl     = Hist::book<TH1D>("JetECalExcl"    ,"Calibrated jet energy (exclusive)"  ,logEbins     ,"E_{jet}^{LCJES} [GeV]"  ,"entries/GeV" );
   TH1D* h_jet_calpt_excl    = Hist::book<TH1D>("JetPtCalExcl"   ,"Calibrated jet p_{T} (exclusive)"   ,logEbins     ,"p_{T,jet}^{LCJES} [GeV]","entries/GeV" );
   TH1D* h_jet_calrap_excl   = Hist::book<TH1D>("JetRapCalExcl"  ,"Calibrated jet rapidity (exclusive)",99,-4.95,4.95,"y_{jet}^{LCJES}"        ,"entries/0.1" );
   TH1D* h_jet_truthe_incl   = Hist::book<TH1D>("JetETruthIncl"  ,"Truth jet energy (inclusive)"       ,logEbins     ,"E_{jet}^{truth} [GeV]"  ,"entries/GeV" );
   TH1D* h_jet_truthpt_incl  = Hist::book<TH1D>("JetPtTruthIncl" ,"Truth jet p_{T} (inclusive)"        ,logEbins     ,"p_{T,jet}^{truth} [GeV]","entries/GeV" );
   TH1D* h_jet_truthrap_incl = Hist::book<TH1D>("JetRapTruthIncl","Truth jet rapidity (inclusive)"     ,99,-4.95,4.95,"y_{jet}^{truth}"        ,"entries/0.1" );
   TH1D* h_jet_truthdR_incl  = Hist::book<TH1D>("JetdRTruthIncl", "Truth jet #Delta R (inclusive)"     ,100,0.,1.    ,"#Delta R"               ,"entries/0.01");
   TH1D* h_jet_truthe_excl   = Hist::book<TH1D>("JetETruthExcl"  ,"Truth jet energy (exclusive)"       ,logEbins     ,"E_{jet}^{truth} [GeV]"  ,"entries/GeV" );
   TH1D* h_jet_truthpt_excl  = Hist::book<TH1D>("JetPtTruthExcl" ,"Truth jet p_{T} (exclusive)"        ,logEbins     ,"p_{T,jet}^{truth} [GeV]","entries/GeV" );
   TH1D* h_jet_truthrap_excl = Hist::book<TH1D>("JetRapTruthExcl","Truth jet rapidity (exclusive)"     ,99,-4.95,4.95,"y_{jet}^{truth}"        ,"entries/0.1" );
   TH1D* h_jet_truthdR_excl  = Hist::book<TH1D>("JetdRTruthExcl", "Truth jet #Delta R (exclusive)"     ,100,0.,1.    ,"#Delta R"               ,"entries/0.01");

   // -- cluster quantities
   TH1D* h_clus_rap_all = Hist::book<TH1D>("ClusRapAll","Cluster rapidity (all clusters)"     ,99,-4.95,4.95,"y_{clus}","entries/0.1");
   TH1D* h_clus_rap_acc = Hist::book<TH1D>("ClusRapAcc","Cluster rapidity (accepted clusters)",99,-4.95,4.95,"y_{clus}","entries/0.1");
   TH1D* h_clus_dep_all = Hist::book<TH1D>("ClusDepAll","Cluster Edep (all clusters)"     ,logEbins,"E_{clus}^{dep} [GeV]","entries/GeV");
   TH1D* h_clus_dep_acc = Hist::book<TH1D>("ClusDepAcc","Cluster Edep (accepted clusters)",logEbins,"E_{clus}^{dep} [GeV]","entries/GeV");
   TH1D* h_clus_eem_all = Hist::book<TH1D>("ClusEemAll","Cluster Eem (all clusters)"     ,logEbins,"E_{clus}^{em} [GeV]","entries/GeV");
   TH1D* h_clus_eem_acc = Hist::book<TH1D>("ClusEemAcc","Cluster Eem (accepted clusters)",logEbins,"E_{clus}^{em} [GeV]","entries/GeV"); 
   TH1D* h_clus_lcw_all = Hist::book<TH1D>("ClusLcwAll","Cluster Elcw (all clusters)"     ,logEbins,"E_{clus}^{had} [GeV]","entries/GeV");
   TH1D* h_clus_lcw_acc = Hist::book<TH1D>("ClusLcwAcc","Cluster Elcw (accepted clusters)",logEbins,"E_{clus}^{had} [GeV]","entries/GeV");
   TH1D* h_clus_eml_all = Hist::book<TH1D>("ClusEmlAll","Cluster Eml (all clusters)"     ,logEbins,"E_{clus}^{ml} [GeV]","entries/GeV");
   TH1D* h_clus_eml_acc = Hist::book<TH1D>("ClusEmlAcc","Cluster Eml (accepted clusters)",logEbins,"E_{clus}^{ml} [GeV]","entries/GeV");

   // -- evaluation scale: deposited energy
   TH2D* d_em_resp_edep_incl = Hist::book<TH2D>("EMR_Edep_incl","EM  response vs EclusDep (inclusive)",logEbins,n_bins,ymin,ymax,"E_{clus}^{dep} [GeV]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_edep_incl = Hist::book<TH2D>("LCR_Edep_incl","LCW response vs EclusDep (inclusive)",logEbins,n_bins,ymin,ymax,"E_{clus}^{dep} [GeV]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_edep_incl = Hist::book<TH2D>("MLR_Edep_incl","ML  response vs EclusDep (inclusive)",logEbins,n_bins,ymin,ymax,"E_{clus}^{dep} [GeV]","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_edep_e300 = Hist::book<TH2D>("EMR_Edep_e300","EM  response vs EclusDep EclusDep>300 MeV",logEbins,n_bins,ymin,ymax,"E_{clus}^{dep} [GeV]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_edep_e300 = Hist::book<TH2D>("LCR_Edep_e300","LCW response vs EclusDep EclusDep>300 MeV",logEbins,n_bins,ymin,ymax,"E_{clus}^{dep} [GeV]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_edep_e300 = Hist::book<TH2D>("MLR_Edep_e300","ML  response vs EclusDep EclusDep>300 MeV",logEbins,n_bins,ymin,ymax,"E_{clus}^{dep} [GeV]","E_{clus}^{ML}/E_{clus}^{dep}" );

   // -- evaluation scale: signal density
   TH2D* d_em_resp_rho__incl = Hist::book<TH2D>("EMR_rho__incl","EM  response vs RhoClus (inclusive)",logRbins,n_bins,ymin,ymax,"\rho_{clus} [GeV/mm^{3}]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_rho__incl = Hist::book<TH2D>("LCR_rho__incl","LCW response vs RhoClus (inclusive)",logRbins,n_bins,ymin,ymax,"\rho_{clus} [GeV/mm^{3}]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_rho__incl = Hist::book<TH2D>("MLR_rho__incl","ML  response vs RhoClus (inclusive)",logRbins,n_bins,ymin,ymax,"\rho_{clus} [GeV/mm^{3}]","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_rho__e300 = Hist::book<TH2D>("EMR_rho__e300","EM  response vs RhoClus EclusDep>300 MeV",logRbins,n_bins,ymin,ymax,"\rho_{clus} [GeV/mm^{3}]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_rho__e300 = Hist::book<TH2D>("LCR_rho__e300","LCW response vs RhoClus EclusDep>300 MeV",logRbins,n_bins,ymin,ymax,"\rho_{clus} [GeV/mm^{3}]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_rho__e300 = Hist::book<TH2D>("MLR_rho__e300","ML  response vs RhoClus EclusDep>300 MeV",logRbins,n_bins,ymin,ymax,"\rho_{clus} [GeV/mm^{3}]","E_{clus}^{ML}/E_{clus}^{dep}" );

   // -- evaluation scale: depth
   TH2D* d_em_resp_lamb_incl = Hist::book<TH2D>("EMR_lamb_incl","EM  response vs MlongClus (inclusive)",logLbins,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_lamb_incl = Hist::book<TH2D>("LCR_lamb_incl","LCW response vs MlongClus (inclusive)",logLbins,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_lamb_incl = Hist::book<TH2D>("MLR_lamb_incl","ML  response vs MlongClus (inclusive)",logLbins,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_lamb_e300 = Hist::book<TH2D>("EMR_lamb_e300","EM  response vs MlongClus EclusDep>300 MeV",logLbins,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_lamb_e300 = Hist::book<TH2D>("LCR_lamb_e300","LCW response vs MlongClus EclusDep>300 MeV",logLbins,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_lamb_e300 = Hist::book<TH2D>("MLR_lamb_e300","ML  response vs MlongClus EclusDep>300 MeV",logLbins,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{ML}/E_{clus}^{dep}" );

   // -- evaluation scale: longitudinal energy dispersion
   TH2D* d_em_resp_long_incl = Hist::book<TH2D>("EMR_long_incl","EM  response vs MlongClus (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_long_incl = Hist::book<TH2D>("LCR_long_incl","LCW response vs MlongClus (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_long_incl = Hist::book<TH2D>("MLR_long_incl","ML  response vs MlongClus (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_long_e300 = Hist::book<TH2D>("EMR_long_e300","EM  response vs MlongClus EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_long_e300 = Hist::book<TH2D>("LCR_long_e300","LCW response vs MlongClus EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_long_e300 = Hist::book<TH2D>("MLR_long_e300","ML  response vs MlongClus EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{long}#GT","E_{clus}^{ML}/E_{clus}^{dep}" );

   // -- evaluation scale: lateral energy dispersion
   TH2D* d_em_resp_lat__incl = Hist::book<TH2D>("EMR_lat__incl","EM  response vs MlatClus (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{lat}#GT","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_lat__incl = Hist::book<TH2D>("LCR_lat__incl","LCW response vs MlatClus (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{lat}#GT","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_lat__incl = Hist::book<TH2D>("MLR_lat__incl","ML  response vs MlatClus (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{lat}#GT","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_lat__e300 = Hist::book<TH2D>("EMR_lat__e300","EM  response vs MlatClus EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{lat}#GT","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_lat__e300 = Hist::book<TH2D>("LCR_lat__e300","LCW response vs MlatClus EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{lat}#GT","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_lat__e300 = Hist::book<TH2D>("MLR_lat__e300","ML  response vs MlatClus EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"#LTm^{2}_{lat}#GT","E_{clus}^{ML}/E_{clus}^{dep}" );

   // -- evaluation scale: signal significance
   TH2D* d_em_resp_sign_incl = Hist::book<TH2D>("EMR_sign_incl","EM  response vs Significance (inclusive)",logSbins,n_bins,ymin,ymax,"#zeta_{clus}^{EM}","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_sign_incl = Hist::book<TH2D>("LCR_sign_incl","LCW response vs Significance (inclusive)",logSbins,n_bins,ymin,ymax,"#zeta_{clus}^{EM}","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_sign_incl = Hist::book<TH2D>("MLR_sign_incl","ML  response vs Significance (inclusive)",logSbins,n_bins,ymin,ymax,"#zeta_{clus}^{EM}","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_sign_e300 = Hist::book<TH2D>("EMR_sign_e300","EM  response vs Significance EclusDep>300 MeV",logSbins,n_bins,ymin,ymax,"#zeta_{clus}^{EM}","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_sign_e300 = Hist::book<TH2D>("LCR_sign_e300","LCW response vs Significance EclusDep>300 MeV",logSbins,n_bins,ymin,ymax,"#zeta_{clus}^{EM}","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_sign_e300 = Hist::book<TH2D>("MLR_sign_e300","ML  response vs Significance EclusDep>300 MeV",logSbins,n_bins,ymin,ymax,"#zeta_{clus}^{EM}","E_{clus}^{ML}/E_{clus}^{dep}" );

   // -- evaluation scale: PtD
   TH2D* d_em_resp_ptd__incl = Hist::book<TH2D>("EMR_ptd__incl","EM  response vs PtD (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"P_{t}D","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_ptd__incl = Hist::book<TH2D>("LCR_ptd__incl","LCW response vs PtD (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"P_{t}D","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_ptd__incl = Hist::book<TH2D>("MLR_ptd__incl","ML  response vs PtD (inclusive)",102,-0.1,1.1,n_bins,ymin,ymax,"P_{t}D","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_ptd__e300 = Hist::book<TH2D>("EMR_ptd__e300","EM  response vs PtD EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"P_{t}D","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_ptd__e300 = Hist::book<TH2D>("LCR_ptd__e300","LCW response vs PtD EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"P_{t}D","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_ptd__e300 = Hist::book<TH2D>("MLR_ptd__e300","ML  response vs PtD EclusDep>300 MeV",102,-0.1,1.1,n_bins,ymin,ymax,"P_{t}D","E_{clus}^{ML}/E_{clus}^{dep}" );

   // -- evaluation scale: second moment of time
   TH2D* d_em_resp_time_incl = Hist::book<TH2D>("EMR_time_incl","EM  response vs SigmaTime2 (inclusive)",500,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_time_incl = Hist::book<TH2D>("LCR_time_incl","LCW response vs SigmaTime2 (inclusive)",500,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_time_incl = Hist::book<TH2D>("MLR_time_incl","ML  response vs SigmaTime2 (inclusive)",500,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_time_e300 = Hist::book<TH2D>("EMR_time_e300","EM  response vs SigmaTime2 EclusDep>300 MeV",500,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_time_e300 = Hist::book<TH2D>("LCR_time_e300","LCW response vs SigmaTime2 EclusDep>300 MeV",500,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_time_e300 = Hist::book<TH2D>("MLR_time_e300","ML  response vs SigmaTime2 EclusDep>300 MeV",500,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{ML}/E_{clus}^{dep}" );

   printf("[ClusterTreePionPlotter::Loop()] INFO looking for PDG ID %.0f\n",pdgID);
   // -- loop tuple
   Long64_t kentry(0); Long64_t lentry(0); 
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry); if (ientry < 0) break;
      fChain->GetEntry(jentry); 
      // particle selection
      // double ppdg = absVal ? std::abs(truthPDG) : truthPDG; 
      // if ( pdgID != 0 && ppdg != pdgID ) { continue; }
      // kentry++;
      fillParticle(false); 
      fillJet(false); 
      // cluster selection by particle or jet
      if ( !filter(ParticleScale::TRUTH) || !filter(JetScale::LCJES) ) { continue; } 
      kentry++;
      fillParticle(true); 
      fillJet(true); 
      // cluster selection by cluster
      if ( !filter(ClusterScale::TRUTH) || !filter(ClusterScale::LCW) ) { continue; }
      lentry++;
      // collect signals
      double eem (clusterE); 
      double elcw(cluster_HAD_WEIGHT*eem); 
      double eml (CalibratedE);
      // evaluation variables
      double rho(cluster_FIRST_ENG_DENS); 
      double lambda(cluster_CENTER_LAMBDA); 
      double ptd(cluster_PTD); 
      double longitudinal(cluster_LONGITUDINAL); 
      double lateral(cluster_LATERAL); 
      double stime(std::sqrt(cluster_SECOND_TIME)); 
      // derived quantities
      double rem (eem /edep); 
      double rlcw(elcw/edep); 
      double rml (eml /edep); 
      // distributions
      h_clus_rap_all->Fill(eta );
      h_clus_dep_all->Fill(edep);
      h_clus_eem_all->Fill(eem );
      h_clus_lcw_all->Fill(elcw);
      h_clus_eml_all->Fill(eml );
      // inclusive plots
      d_em_resp_edep_incl->Fill(edep,rem );
      d_lc_resp_edep_incl->Fill(edep,rlcw);
      d_ml_resp_edep_incl->Fill(edep,rml );
      d_em_resp_rho__incl->Fill(rho,rem );
      d_lc_resp_rho__incl->Fill(rho,rlcw);
      d_ml_resp_rho__incl->Fill(rho,rml );
      d_em_resp_lamb_incl->Fill(lambda,rem );
      d_lc_resp_lamb_incl->Fill(lambda,rlcw);
      d_ml_resp_lamb_incl->Fill(lambda,rml );
      d_em_resp_long_incl->Fill(longitudinal,rem );
      d_lc_resp_long_incl->Fill(longitudinal,rlcw);
      d_ml_resp_long_incl->Fill(longitudinal,rml );
      d_em_resp_lat__incl->Fill(lateral,rem );
      d_lc_resp_lat__incl->Fill(lateral,rlcw);
      d_ml_resp_lat__incl->Fill(lateral,rml );
      d_em_resp_sign_incl->Fill(signif,rem );
      d_lc_resp_sign_incl->Fill(signif,rlcw);
      d_ml_resp_sign_incl->Fill(signif,rml );
      d_em_resp_ptd__incl->Fill(ptd,rem );
      d_lc_resp_ptd__incl->Fill(ptd,rlcw);
      d_ml_resp_ptd__incl->Fill(ptd,rml );
      d_em_resp_time_incl->Fill(stime,rem );
      d_lc_resp_time_incl->Fill(stime,rlcw);
      d_ml_resp_time_incl->Fill(stime,rml );
      // exclusive plots
      if ( edep > 0.3 ) { 
	h_clus_rap_acc->Fill(eta );
	h_clus_dep_acc->Fill(edep);
	h_clus_eem_acc->Fill(eem );
	h_clus_lcw_acc->Fill(elcw);
	h_clus_eml_acc->Fill(eml );
	d_em_resp_edep_e300->Fill(edep,rem );
	d_lc_resp_edep_e300->Fill(edep,rlcw);
	d_ml_resp_edep_e300->Fill(edep,rml );
	d_em_resp_rho__e300->Fill(rho,rem );
	d_lc_resp_rho__e300->Fill(rho,rlcw);
	d_ml_resp_rho__e300->Fill(rho,rml );
	d_em_resp_lamb_e300->Fill(lambda,rem );
	d_lc_resp_lamb_e300->Fill(lambda,rlcw);
	d_ml_resp_lamb_e300->Fill(lambda,rml );
	d_em_resp_long_e300->Fill(longitudinal,rem );
	d_lc_resp_long_e300->Fill(longitudinal,rlcw);
	d_ml_resp_long_e300->Fill(longitudinal,rml );
	d_em_resp_lat__e300->Fill(lateral,rem );
	d_lc_resp_lat__e300->Fill(lateral,rlcw);
	d_ml_resp_lat__e300->Fill(lateral,rml );
	d_em_resp_sign_e300->Fill(signif,rem );
	d_lc_resp_sign_e300->Fill(signif,rlcw);
	d_ml_resp_sign_e300->Fill(signif,rml );
	d_em_resp_ptd__e300->Fill(ptd,rem );
	d_lc_resp_ptd__e300->Fill(ptd,rlcw);
	d_ml_resp_ptd__e300->Fill(ptd,rml );
	d_em_resp_time_e300->Fill(stime,rem );
	d_lc_resp_time_e300->Fill(stime,rlcw);
	d_ml_resp_time_e300->Fill(stime,rml );
      }
   }

   printf("[ClusterTreePionPlotter::Loop()] INFO [%lli] accepted %lli entries and %lli clusters\n",nentries,kentry,lentry); 

   // -- normalize energy distibutions
   binNormalize(h_clus_dep_all);
   binNormalize(h_clus_dep_acc);
   binNormalize(h_clus_eem_all);
   binNormalize(h_clus_eem_acc);
   binNormalize(h_clus_lcw_all);
   binNormalize(h_clus_lcw_acc);
   binNormalize(h_clus_eml_all);
   binNormalize(h_clus_eml_acc);
   binNormalize(h_part_e_all_incl );   
   binNormalize(h_part_e_pi0_incl );   
   binNormalize(h_part_e_pic_incl );   
   binNormalize(h_part_e_all_excl );   
   binNormalize(h_part_e_pi0_excl );   
   binNormalize(h_part_e_pic_excl );   
   binNormalize(h_jet_cale_incl   );  
   binNormalize(h_jet_calpt_incl  );  
   binNormalize(h_jet_cale_excl   );  
   binNormalize(h_jet_calpt_excl  );  
   binNormalize(h_jet_truthe_incl );  
   binNormalize(h_jet_truthpt_incl);  
   binNormalize(h_jet_truthdR_incl);  
   binNormalize(h_jet_truthe_excl );  
   binNormalize(h_jet_truthpt_excl);  

   // -- write 
   TFile* outf = new TFile("ml_pions.hist.root","RECREATE");
   HistManager::instance()->write();
   outf->Close();
}

void ClusterTreePionPlotter::binNormalize(TH1* hptr) {
  double nenOld(hptr->GetEntries());
  if ( nenOld == 0. ) { return; }
  double intOld(0.); 
  double intNew(0.); 
  for ( int i(1); i<=hptr->GetNbinsX(); ++i ) { 
    double xwidth(hptr->GetBinWidth(i));
    double yval(hptr->GetBinContent(i)); intOld += yval;
    double yerr(hptr->GetBinError(i));
    yval /= xwidth; intNew += yval;
    yerr /= xwidth; 
    hptr->SetBinContent(i,yval);
    hptr->SetBinError(i,yerr); 
  }
  printf("[ClusterTreePionPlotter::binNormalize()] INFO entries  (old/new): %.0f/%.3f\n",nenOld,hptr->GetEntries()); 
  printf("[ClusterTreePionPlotter::binNormalize()] INFO integral (old/new): %.3f/%.3f\n",intOld,intNew); 
}

bool ClusterTreePlotter::fillParticle(bool final) {
  if ( !isParticle() || !newObject() ) { return false; }
  int partid(0); 
  bool doParticle(fillValue<int>(ValueType::PDG,ParticleScale::TRUTH,partid));
  bool doNeutral(doParticle && std::abs(partid) == 111);
  bool doCharged(doParticle && std::abs(partid) == 211);
  if ( final ) { 
    double etruth(0.); if ( fillValue<double>(ValueType::E  ,ParticleScale::TRUTH,etruth) ) { h_part_e_all_excl  ->Fill(etruth); if ( doNeutral ) { h_part_e_pi0_excl  ->Fill(etruth); } if ( doCharged ) { h_part_e_pic_excl  ->Fill(etruth); } } 
    double ytruth(0.); if ( fillValue<double>(ValueType::RAP,ParticleScale::TRUTH,ytruth) ) { h_part_rap_all_excl->Fill(ytruth); if ( doNeutral ) { h_part_rap_pi0_excl->Fill(ytruth); } if ( doCharged ) { h_part_rap_pic_excl->Fill(ytruth); } }  
  } else {
    double etruth(0.); if ( fillValue<double>(ValueType::E  ,ParticleScale::TRUTH,etruth) ) { h_part_e_all_incl  ->Fill(etruth); if ( doNeutral ) { h_part_e_pi0_incl  ->Fill(etruth); } if ( doCharged ) { h_part_e_pic_incl  ->Fill(etruth); } } 
    double ytruth(0.); if ( fillValue<double>(ValueType::RAP,ParticleScale::TRUTH,ytruth) ) { h_part_rap_all_incl->Fill(ytruth); if ( doNeutral ) { h_part_rap_pi0_incl->Fill(ytruth); } if ( doCharged ) { h_part_rap_pic_incl->Fill(ytruth); } }  
  } 
  return true;
}

bool ClusterTreePlotter::fillJet(bool final) {
  if ( !isJet() || !newObject() ) { return false; }
  double etruth(0.); double ytruth(0.); double ptruth(0.); double ecalib(0.); double ycalib(0.); double pcalib(0.);
  unsigned int ifill(0); 
  if ( final ) { 
    if ( fillValue<double>(ValueType::E  ,JetScale::TRUTH,etruth) ) { h_jet_truthe_excl  ->Fill(etruth); ++ifill; }      
    if ( fillValue<double>(ValueType::PT ,JetScale::TRUTH,ptruth) ) { h_jet_truthpt_excl ->Fill(ptruth); ++ifill; }
    if ( fillValue<double>(ValueType::RAP,JetScale::TRUTH,ytruth) ) { h_jet_truthrap_excl->Fill(ytruth); ++ifill; }
    h_jet_truthdR_excl->Fill(truthJetMatchingRadius); 
    if ( fillValue<double>(ValueType::E  ,JetScale::LCJES,ecalib) ) { h_jet_cale_excl  ->Fill(ecalib); ++ifill; }
    if ( fillValue<double>(ValueType::PT ,JetScale::LCJES,pcalib) ) { h_jet_calpt_excl ->Fill(pcalib); ++ifill; }
    if ( fillValue<double>(ValueType::RAP,JetScale::LCJES,ycalib) ) { h_jet_calrap_excl->Fill(ycalib); ++ifill; }
  } else {
    if ( fillValue<double>(ValueType::E  ,JetScale::TRUTH,etruth) ) { h_jet_truthe_incl  ->Fill(etruth); ++ifill; }      
    if ( fillValue<double>(ValueType::PT ,JetScale::TRUTH,ptruth) ) { h_jet_truthpt_incl ->Fill(ptruth); ++ifill; }
    if ( fillValue<double>(ValueType::RAP,JetScale::TRUTH,ytruth) ) { h_jet_truthrap_incl->Fill(ytruth); ++ifill; }
    h_jet_truthdR_incl->Fill(truthJetMatchingRadius); 
    if ( fillValue<double>(ValueType::E  ,JetScale::LCJES,ecalib) ) { h_jet_cale_incl  ->Fill(ecalib); ++ifill; }
    if ( fillValue<double>(ValueType::PT ,JetScale::LCJES,pcalib) ) { h_jet_calpt_incl ->Fill(pcalib); ++ifill; }
    if ( fillValue<double>(ValueType::RAP,JetScale::LCJES,ycalib) ) { h_jet_calrap_incl->Fill(ycalib); ++ifill; }
  }
  return ifill>0;
}

bool ClusterTreePlotter::fillObject(ClusterScale /*vscale*/,bool /*final*/) { return true; } 

bool ClusterTreePlotter::newEvent() { 
  if ( runNumber != m_runNumber || eventNumber != m_eventNumber ) { 
    m_runNumber   = runNumber; 
    m_eventNumber = eventNumber;
    return true;
  }
  return false; 
}

bool ClusterTreePlotter::newObject() {
  if ( isParticle() ) { 
    if ( m_truthPDG != truthPDG || m_truthE != truthE ) { 
      m_truthPDG = truthPDG; 
      m_truthE   = truthE;
      return true;
    }
    return false; 
  } else if ( isJet() ) { 
    if ( m_truthJetPt != truthJetPt || m_truthJetEta != truthJetEta ) { 
      m_truthJetPt = truthJetPt;
      m_truthJetEta = truthJetEta;
      return true;
    }
    return false;
  }
}
