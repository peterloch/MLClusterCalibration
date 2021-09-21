#define ClusterTreeDemo_cxx
#include "ClusterTreeDemo.h"

#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>

#include <vector>
#include <tuple>
#include <map>

#include <cmath>
#include <cstdio>

#include "HistManager.h"

#ifndef M_PI 
#define MPI 3.14159265358979323846
#endif

void ClusterTreeDemo::Loop(const std::string& outFile,Long64_t kentries) {

  printf("[ClusterTreeDemo::Loop(\042%s\042,%lli)] INFO called\n",outFile.c_str(),kentries); 
  // invalid setup 
  if (fChain == 0) { printf("[ClusterTreeDemo::Loop(\042%s\042,%lli)] ABRT invalid pointer %p to tree\n",outFile.c_str(),kentries,(void*)fChain); return; }

  /////////////////////////////////
  // Determine number of entries //
  /////////////////////////////////

  Long64_t nentries = kentries <= 0 ? fChain->GetEntriesFast() : std::min(fChain->GetEntriesFast(),kentries);
  printf("[ClusterTreeDemo::Loop(\042%s\042,%lli)] INFO process %lli entries of %lli in tree \042%s\042\n",
	 outFile.c_str(),kentries,nentries,fChain->GetEntriesFast(),fChain->GetName()); 

  ///////////////////////////
  // Book histograms: jets //
  ///////////////////////////

  // -- 1-dim jet distributions
  TH1D* h_njets = Hist::book<TH1D>("N__Jets","N_{jets}"        ,100,-0.5, 99.5,"N_{jets}"              ,"Entries"); // number of jets/event                            
  TH1D* h_ptjes = Hist::book<TH1D>("Pt_JJES","p_{T,jet}^{JES}" ,100,10.0,490.0,"p_{T,jet}^{JES}"       ,"Entries"); // jet transverse momentum (pT) at calibrated scale
  TH1D* h_rajes = Hist::book<TH1D>("RapJJES","y_{jet}^{JES}"   , 16,-0.8,  0.8,"y_{jet}^{JES}"         ,"Entries"); // jet rapidity (y) at calibrated scale             
  TH1D* h_azjes = Hist::book<TH1D>("AziJJES","#phi_{jet}^{JES}", 64,-3.2,  3.2,"#phi_{jet}^{JES} [rad]","Entries"); // jet azimuth (phi) at calibrated scale           
  TH1D* h_ptjcs = Hist::book<TH1D>("Pt_JEMS","p_{T,jet}^{csc}" ,100,10.0,490.0,"p_{T,jet}^{csc}"       ,"Entries"); // jet transverse momentum (pT) at constituent scale 
  TH1D* h_rajcs = Hist::book<TH1D>("RapJEMS","y_{jet}^{csc}"   , 16,-0.8,  0.8,"y_{jet}^{csc}"         ,"Entries"); // jet rapidity (y) at constituent scale            
  TH1D* h_azjcs = Hist::book<TH1D>("AziJEMS","#phi_{jet}^{csc}", 64,-3.2,  3.2,"#phi_{jet}^{csc} [rad]","Entries"); // jet azimuth (phi) at constituent scale           
  TH1D* h_ncjet = Hist::book<TH1D>("NconJet","N_{const}^{jet}" ,100,-0.5, 99.5,"N_{const}^{jet}"       ,"Entries"); // number of constituents in jet                     
  // -- 2-dim jet distribution  
  TH2D* d_nc_ptjet = Hist::book<TH2D>("NcoPt_Jet","N_{const}^{jet} vs p_{T,jet}^{JES}",
				      h_ptjes->GetNbinsX(),h_ptjes->GetXaxis()->GetXmin(),h_ptjes->GetXaxis()->GetXmax(),
				      h_ncjet->GetNbinsX(),h_ncjet->GetXaxis()->GetXmin(),h_ncjet->GetXaxis()->GetXmax(),
				      h_ptjes->GetXaxis()->GetTitle(),
				      h_ncjet->GetXaxis()->GetTitle());
  printf("[ClusterTreeDemo::Loop(\042%s\042,%lli)] INFO booked %zu distributions so far\n",outFile.c_str(),kentries,Hist::mgr()->size()); 

  // cluster energy bins
  double xmin(.05); double xmax(2000.);
  double ymin(0.) ; double ymax(2); 
  int    n_bins(100);
  double lxmin(std::log10(xmin)); double lxmax(std::log10(xmax)); 
  double lxwid((lxmax-lxmin)/(double(n_bins)));
  std::vector<double> logBins(n_bins+1,0.);
  for ( size_t i(0); i<logBins.size(); ++i ) { logBins[i] = std::pow(10.,lxmin); lxmin += lxwid; }
  printf("[ClusterTreeDemo::Loop(\042%s\042,%lli)] INFO calculated energy binning (%zu bins)\n",outFile.c_str(),kentries,logBins.size()-1); 
  double fmin(0.0001); 
  double fmax(1.5000);
  int    fbin(200); 
  double lfmin(std::log10(fmin)); double lfmax(std::log10(fmax));
  double lfwid((lfmax-lfmin)/(double(fbin)));
  std::vector<double> logFbin(fbin+1,0.); 
  for ( size_t i(0); i<logFbin.size(); ++i ) { logFbin[i] = std::pow(10.,lfmin); lfmin += lfwid; }
  printf("[ClusterTreeDemo::Loop(\042%s\042,%lli)] INFO calculated fractional signal binning (%zu bins)\n",outFile.c_str(),kentries,logFbin.size()-1); 
  

  // book histograms: cluster EM response
  //    pTthreshold     +------------------------------------- entry <0> EM  response vs cluster energy   
  //         |          | +----------------------------------- entry <1> LCW response vs cluster energy
  //         |          | | +--------------------------------- entry <2> MLC response vs cluster energy
  //         |          | | | +------------------------------- entry <3> EM  response vs energy fraction of cluster in jet
  //         |          | | | | +----------------------------- entry <4> LCW response vs energy fraction of cluster in jet
  //         |          | | | | | +--------------------------- entry <5> MLC response vs energy fraction of cluster in jet
  //         |          | | | | | | +------------------------- entry <6> LCW rapidity of cluster
  //         |          | | | | | | | +----------------------- entry <7> EM energy of cluster
  //         |          | | | | | | | |
  std::map<double,Hist::DistributionList> plotPtJet = {
    {  20., { Hist::book<TH2D>("EMR_Eclus_pt020","EM  response vs EclusDep p_{T,jet}^{JES} > 20 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{EM}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("LCR_Eclus_pt020","LCW response vs EclusDep p_{T,jet}^{JES} > 20 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{LCW}/E_{clus}^{dep}"),    
	      Hist::book<TH2D>("MLR_Eclus_pt020","ML  response vs EclusDep p_{T,jet}^{JES} > 20 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{ML}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("EMR_Fclus_pt020","EM  response vs FclusJet p_{T,jet}^{JES} > 20 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{EM}/E_{clus}^{dep}" ),
	      Hist::book<TH2D>("LCR_Fclus_pt020","LCW response vs FclusJet p_{T,jet}^{JES} > 20 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{LCW}/E_{clus}^{dep}"),
	      Hist::book<TH2D>("MLR_Fclus_pt020","ML  response vs FclusJet p_{T,jet}^{JES} > 20 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{ML}/E_{clus}^{dep}" ),
	      Hist::book<TH1D>("ClLCW_Rap_pt020","LCW cluster rapidity p_{T,jet}^{JES} > 20 GeV"     ,99,-4.95,4.95           ,"y_{clus}^{LCW}"              ,"Entries"                      ),
	      Hist::book<TH1D>("ClEM__Ene_pt020","EM  cluster energy p_{T,jet}^{JES} > 20 GeV"       ,logBins                 ,"E_{clus}^{EM} [GeV]"         ,"Entries"                      ) } },
    {  40., { Hist::book<TH2D>("EMR_Eclus_pt040","EM  response vs EclusDep p_{T,jet}^{JES} > 40 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{EM}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("LCR_Eclus_pt040","LCW response vs EclusDep p_{T,jet}^{JES} > 40 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{LCW}/E_{clus}^{dep}"),    
	      Hist::book<TH2D>("MLR_Eclus_pt040","ML  response vs EclusDep p_{T,jet}^{JES} > 40 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{ML}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("EMR_Fclus_pt040","EM  response vs FclusJet p_{T,jet}^{JES} > 40 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{EM}/E_{clus}^{dep}" ),
	      Hist::book<TH2D>("LCR_Fclus_pt040","LCW response vs FclusJet p_{T,jet}^{JES} > 40 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{LCW}/E_{clus}^{dep}"),
	      Hist::book<TH2D>("MLR_Fclus_pt040","ML  response vs FclusJet p_{T,jet}^{JES} > 40 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{ML}/E_{clus}^{dep}" ),
	      Hist::book<TH1D>("ClLCW_Rap_pt040","LCW cluster rapidity p_{T,jet}^{JES} > 40 GeV"     ,99,-4.95,4.95,           "y_{clus}^{LCW}"              ,"Entries"                      ),
	      Hist::book<TH1D>("ClEM__Ene_pt040","EM  cluster energy p_{T,jet}^{JES} > 40 GeV"       ,logBins                 ,"E_{clus}^{EM} [GeV]"         ,"Entries"                      ) } },
    {  60., { Hist::book<TH2D>("EMR_Eclus_pt060","EM  response vs EclusDep p_{T,jet}^{JES} > 60 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{EM}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("LCR_Eclus_pt060","LCW response vs EclusDep p_{T,jet}^{JES} > 60 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{LCW}/E_{clus}^{dep}"),    
	      Hist::book<TH2D>("MLR_Eclus_pt060","ML  response vs EclusDep p_{T,jet}^{JES} > 60 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{ML}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("EMR_Fclus_pt060","EM  response vs FclusJet p_{T,jet}^{JES} > 60 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{EM}/E_{clus}^{dep}" ),
	      Hist::book<TH2D>("LCR_Fclus_pt060","LCW response vs FclusJet p_{T,jet}^{JES} > 60 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{LCW}/E_{clus}^{dep}"),
	      Hist::book<TH2D>("MLR_Fclus_pt060","ML  response vs FclusJet p_{T,jet}^{JES} > 60 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{ML}/E_{clus}^{dep}" ),
	      Hist::book<TH1D>("ClLCW_Rap_pt060","LCW cluster rapidity p_{T,jet}^{JES} > 60 GeV"     ,99,-4.95,4.95,           "y_{clus}^{LCW}"              ,"Entries"                      ),
	      Hist::book<TH1D>("ClEM__Ene_pt060","EM  cluster energy p_{T,jet}^{JES} > 60 GeV"       ,logBins                 ,"E_{clus}^{EM} [GeV]"         ,"Entries"                      ) } },
    {  80., { Hist::book<TH2D>("EMR_Eclus_pt080","EM  response vs EclusDep p_{T,jet}^{JES} > 80 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{EM}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("LCR_Eclus_pt080","LCW response vs EclusDep p_{T,jet}^{JES} > 80 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{LCW}/E_{clus}^{dep}"),    
	      Hist::book<TH2D>("MLR_Eclus_pt080","ML  response vs EclusDep p_{T,jet}^{JES} > 80 GeV" ,logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{ML}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("EMR_Fclus_pt080","EM  response vs FclusJet p_{T,jet}^{JES} > 80 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{EM}/E_{clus}^{dep}" ),
	      Hist::book<TH2D>("LCR_Fclus_pt080","LCW response vs FclusJet p_{T,jet}^{JES} > 80 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{LCW}/E_{clus}^{dep}"),
	      Hist::book<TH2D>("MLR_Fclus_pt080","ML  response vs FclusJet p_{T,jet}^{JES} > 80 GeV" ,logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{ML}/E_{clus}^{dep}" ),
	      Hist::book<TH1D>("ClLCW_Rap_pt080","LCW cluster rapidity p_{T,jet}^{JES} > 80 GeV"     ,99,-4.95,4.95,           "y_{clus}^{LCW}"              ,"Entries"                      ),
	      Hist::book<TH1D>("ClEM__Ene_pt080","EM  cluster energy p_{T,jet}^{JES} > 80 GeV"       ,logBins                 ,"E_{clus}^{EM} [GeV]"         ,"Entries"                      ) } },
    { 100., { Hist::book<TH2D>("EMR_Eclus_pt100","EM  response vs EclusDep p_{T,jet}^{JES} > 100 GeV",logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{EM}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("LCR_Eclus_pt100","LCW response vs EclusDep p_{T,jet}^{JES} > 100 GeV",logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{LCW}/E_{clus}^{dep}"),    
	      Hist::book<TH2D>("MLR_Eclus_pt100","ML  response vs EclusDep p_{T,jet}^{JES} > 100 GeV",logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{ML}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("EMR_Fclus_pt100","EM  response vs FclusJet p_{T,jet}^{JES} > 100 GeV",logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{EM}/E_{clus}^{dep}" ),
	      Hist::book<TH2D>("LCR_Fclus_pt100","LCW response vs FclusJet p_{T,jet}^{JES} > 100 GeV",logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{LCW}/E_{clus}^{dep}"),
	      Hist::book<TH2D>("MLR_Fclus_pt100","ML  response vs FclusJet p_{T,jet}^{JES} > 100 GeV",logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{ML}/E_{clus}^{dep}" ),
	      Hist::book<TH1D>("ClLCW_Rap_pt100","LCW cluster rapidity p_{T,jet}^{JES} > 100 GeV"    ,99,-4.95,4.95,           "y_{clus}^{LCW}"              ,"Entries"                      ),
	      Hist::book<TH1D>("ClEM__Ene_pt100","EM  cluster energy p_{T,jet}^{JES} > 100 GeV"      ,logBins                 ,"E_{clus}^{EM} [GeV]"         ,"Entries"                      ) } },
    { 200., { Hist::book<TH2D>("EMR_Eclus_pt200","EM  response vs EclusDep p_{T,jet}^{JES} > 200 GeV",logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{EM}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("LCR_Eclus_pt200","LCW response vs EclusDep p_{T,jet}^{JES} > 200 GeV",logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{LCW}/E_{clus}^{dep}"),    
	      Hist::book<TH2D>("MLR_Eclus_pt200","ML  response vs EclusDep p_{T,jet}^{JES} > 200 GeV",logBins       ,100,0.,2.,"E_{clus}^{dep} [GeV]"        ,"E_{clus}^{ML}/E_{clus}^{dep}" ),    
	      Hist::book<TH2D>("EMR_Fclus_pt200","EM  response vs FclusJet p_{T,jet}^{JES} > 200 GeV",logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{EM}/E_{clus}^{dep}" ),
	      Hist::book<TH2D>("LCR_Fclus_pt200","LCW response vs FclusJet p_{T,jet}^{JES} > 200 GeV",logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{LCW}/E_{clus}^{dep}"),
	      Hist::book<TH2D>("MLR_Fclus_pt200","ML  response vs FclusJet p_{T,jet}^{JES} > 200 GeV",logFbin       ,100,0.,2.,"E_{clus}^{LCW}/E_{jet}^{CSC}","E_{clus}^{ML}/E_{clus}^{dep}" ),
	      Hist::book<TH1D>("ClLCW_Rap_pt200","LCW cluster rapidity p_{T,jet}^{JES} > 200 GeV"    ,99,-4.95,4.95,           "y_{clus}^{LCW}"              ,"Entries"                      ),
	      Hist::book<TH1D>("ClEM__Ene_pt200","EM  cluster energy p_{T,jet}^{JES} > 200 GeV"      ,logBins                 ,"E_{clus}^{EM} [GeV]"         ,"Entries"                      ) } },
  };
  printf("[ClusterTreeDemo::Loop(\042%s\042,%lli)] INFO added %zu sets of distributions at jet pT thresholds, new total number of distributions %zu\n",outFile.c_str(),kentries,plotPtJet.size(),Hist::mgr()->size()); 

  double ptJet(0.); double rapJet(0.); double phiJet(0.); double ncoJet(0.); double nJet(0.);
  int evtNumber(-1); 
  int ievt(0); 
  int ijet(0); 
  int fwid((int)std::log10((double)nentries)+1); 
  char mbuffer[1024];
  std::vector<Hist::DistributionList> dlist;
  sprintf(mbuffer,"[ClusterTreeDemo::Loop(\042%s\042,%lli)] INFO [%s] processed event [%s] - clusters %s/%s\n",outFile.c_str(),kentries,"%5.1f%%","%07i","%*lli","%*lli");
  std::string fmtString(mbuffer);
  bool jetVeto(false);
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    // next entry
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    fChain->GetEntry(jentry);
    // new event
    if ( newEvent() ) { 
      if ( evtNumber > 0 ) { h_njets->Fill(nJet); nJet = 0.; } else { evtNumber = 0; }
      ++evtNumber; ++ievt;
      Hist::printStats<Long64_t>(jentry+1,nentries,ievt,fwid,fmtString);
    }
    // new jet
    if ( newJet() ) {
      // fix rapdity range (uses jetCalEta in production -> some clusters beyond |y|=0.8 may slip in)
      jetVeto = std::abs(jetRawEta) > 0.4; 
      if ( !jetVeto ) { 
	++nJet; 
	h_ptjes->Fill(jetCalE); h_ptjes->Fill(jetCalPt); h_rajes->Fill(jetCalEta); h_azjes->Fill(stdPhi(jetCalPhi));
	h_ptjcs->Fill(jetRawE); h_ptjcs->Fill(jetRawPt); h_rajcs->Fill(jetRawEta); h_azjcs->Fill(stdPhi(jetRawPhi));
	h_ncjet->Fill((double)jetNConst);
	d_nc_ptjet->Fill(jetCalPt,(double)jetNConst);
	dlist.clear(); 
	for ( auto fmap(plotPtJet.begin()); fmap != plotPtJet.end(); ++fmap ) { 
	  if ( jetCalPt > fmap->first ) { dlist.push_back(fmap->second); }
	}
      }
    }
    // cluster stuff
    if ( !jetVeto ) { 
      double elcw(clusterECalib); double eemc(clusterE); double emlc(CalibratedE);
      double whad(cluster_HAD_WEIGHT);
      double ehad(whad*eemc); 
      double edep(cluster_ENG_CALIB_TOT); 
      double flcw(elcw/jetRawE);
      double ylcw(clusterEtaCalib); 
      if ( edep != 0. ) { 
	double rlcw(ehad/edep); double remc(eemc/edep); double rmlc(emlc/edep); 
	for ( auto entry : dlist  ) { 
	  Hist::fill2d<0>(entry,edep,remc); 
	  Hist::fill2d<1>(entry,edep,rlcw); 
	  Hist::fill2d<3>(entry,flcw,remc); 
	  Hist::fill2d<4>(entry,flcw,rlcw); 
	  Hist::fill1d<6>(entry,ylcw     ); // 1-dim
	  Hist::fill1d<7>(entry,eemc     ); // 1-dim
	  if ( b_CalibratedE != nullptr ) { Hist::fill2d<2>(entry,edep,rmlc); Hist::fill2d<5>(entry,flcw,rmlc); }
	}
      }
    }
  } // cluster loop

  std::cout << *Hist::mgr() << std::endl;

  TFile* outf = new TFile(outFile.c_str(),"RECREATE"); 
  if ( outf != nullptr ) { Hist::mgr()->write(); outf->Close(); } 
}

bool ClusterTreeDemo::newEvent() {
  if ( runNumber != m_runNumber || eventNumber != m_eventNumber ) { m_runNumber = runNumber; m_eventNumber = eventNumber; return true; }
  return false; 
}

bool ClusterTreeDemo::newJet() { 
  if ( jetCalE != m_jetCalE ) { m_jetCalE = jetCalE; return true; }
  return false;
}

double ClusterTreeDemo::stdPhi(double phi) { 
  while ( phi >  M_PI ) { phi -= 2.*M_PI; }
  while ( phi < -M_PI ) { phi += 2.*M_PI; }
  return phi;
}
