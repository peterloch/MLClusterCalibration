#define ClusterTreePionPlotter_cxx
#include "ClusterTreePionPlotter.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>

#include "HistManager.h"

#include <vector>
#include <cmath>

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

   double rmin(10e-9); double rmax(10e-3);
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
   TH2D* d_em_resp_time_incl = Hist::book<TH2D>("EMR_time_incl","EM  response vs SigmaTime2 (inclusive)",200,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_time_incl = Hist::book<TH2D>("LCR_time_incl","LCW response vs SigmaTime2 (inclusive)",200,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_time_incl = Hist::book<TH2D>("MLR_time_incl","ML  response vs SigmaTime2 (inclusive)",200,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{ML}/E_{clus}^{dep}" );
   TH2D* d_em_resp_time_e300 = Hist::book<TH2D>("EMR_time_e300","EM  response vs SigmaTime2 EclusDep>300 MeV",200,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{EM}/E_{clus}^{dep}" );
   TH2D* d_lc_resp_time_e300 = Hist::book<TH2D>("LCR_time_e300","LCW response vs SigmaTime2 EclusDep>300 MeV",200,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{LCW}/E_{clus}^{dep}");
   TH2D* d_ml_resp_time_e300 = Hist::book<TH2D>("MLR_time_e300","ML  response vs SigmaTime2 EclusDep>300 MeV",200,-0.025,9.975,n_bins,ymin,ymax,"#sigma_{t}^{2} [ns]","E_{clus}^{ML}/E_{clus}^{dep}" );

   printf("[ClusterTreePionPlotter::Loop()] INFO looking for PDG ID %.0f\n",pdgID);
   // -- loop tuple
   Long64_t kentry(0); Long64_t lentry(0); 
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry); if (ientry < 0) break;
      fChain->GetEntry(jentry); 
      // particle selection
      double ppdg = absVal ? std::abs(truthPDG) : truthPDG; 
      if ( pdgID != 0 && ppdg != pdgID ) { continue; }
      kentry++;
      // cluster selection
      double edep(cluster_ENG_CALIB_TOT); double eta(clusterEta); double signif(cluster_SIGNIFICANCE); 
      if ( edep <= 0. || std::abs(eta) > 0.8 || signif < 0. ) { continue; }
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
   // -- write 
   TFile* outf = new TFile("ml_pions.hist.root","RECREATE");
   HistManager::instance()->write();
   outf->Close();
}

void ClusterTreePionPlotter::binNormalize(TH1* hptr) {
  double intOld(0.); 
  double intNew(0.); 
  double nenOld(hptr->GetEntries());
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
