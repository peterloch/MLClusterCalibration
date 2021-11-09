
#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>

#include <string>
#include <vector>

#include <cstdio>
#include <cmath>

#include <iostream>

void binNormalize(TH1* hptr) { 
  for ( int ib(1); ib<=hptr->GetNbinsX(); ++ib ) {
    double xwid(hptr->GetBinWidth(ib));
    if ( xwid > 0. ) {  
      hptr->SetBinContent(ib,hptr->GetBinContent(ib)/xwid); 
      hptr->SetBinError  (ib,hptr->GetBinError  (ib)/xwid);
    }
  }
}

void extractJets(const std::string& inputFileName,const std::string& outputFileName) { 
  // input file
  TFile* infPtr = new TFile(inputFileName.c_str(),"READ");
  if ( infPtr == nullptr ) { printf("[extractJets] ABRT cannot find input file \042%s\042\n",inputFileName.c_str()); return; }
  printf("[extractJets] INFO input file ....: \042%s\042 (opened)\n",infPtr->GetName());
  // output file
  TFile* outfPtr = new TFile(outputFileName.c_str(),"RECREATE");
  if ( outfPtr == nullptr ) { printf("[extractJets] ABRT cannot open output file \042%s\042\n",outputFileName.c_str()); return; }
  printf("[extractJets] INFO output file ...: \042%s\042 (opened)\n",outfPtr->GetName());
  // 
  TTree* inputTree = (TTree*)infPtr->FindObjectAny("ClusterTree");
  if ( inputTree == nullptr ) { printf("[extractJets] ABRT cannot access input tree \042ClusterTree\042\n"); return; }
  // define histograms
  int nbin(100); 
  double xmin(0.020)             ; double xmax(2000.0); 
  double lmin(std::log10(xmin))  ; double lmax(std::log10(xmax)); double lval(lmin); double lstp((lmax-lmin)/((double)nbin));
  std::vector<double> xbin; for ( ; lval <= lmax; lval += lstp ) { xbin.push_back(std::pow(10.,lval)); }
  printf("[extractJets] INFO defined %zu irregular energy bins within [%.2f,%.0f] GeV\n",xbin.size()-1,xbin.front(),xbin.back());
  int mbin(50);
  xmax = 500.; lmax = std::log10(xmax); 
  xmin = 5.0 ; lmin = std::log10(xmin); 
  lval = lmin; lstp = (lmax-lmin)/((double)mbin);
  std::vector<double> pbin; for ( int ib(0); ib<=mbin; ++ib ) { pbin.push_back(std::pow(10.,lval)); lval += lstp; } 
  printf("[extractJets] INFO defined %zu irregular pT bins within [%.2f,%.1f] GeV\n",pbin.size()-1,pbin.front(),pbin.back());
  TH1F* hdepincl    = new TH1F("hdepincl"   ,"E_{clus}^{dep}" ,xbin.size()-1,xbin.data()); hdepincl   ->GetXaxis()->SetTitle("E_{clus}^{dep} [GeV]"   ); hdepincl   ->GetYaxis()->SetTitle("Entries/GeV"          );  
  TH1F* hdep        = new TH1F("hdep"       ,"E_{clus}^{dep}" ,xbin.size()-1,xbin.data()); hdep       ->GetXaxis()->SetTitle("E_{clus}^{dep} [GeV]"   ); hdep       ->GetYaxis()->SetTitle("Entries/GeV"          );  
  TH1F* hjetrapincl = new TH1F("hjetrapincl","y_{jet}^{LCJES}",99,-4.95,4.95            ); hjetrapincl->GetXaxis()->SetTitle("y_{jet}^{LCJES}"        ); hjetrapincl->GetYaxis()->SetTitle("Entries/unit rapidity"); 
  TH1F* hjetrap     = new TH1F("hjetrap"    ,"y_{jet}^{LCJES}",99,-4.95,4.95            ); hjetrap    ->GetXaxis()->SetTitle("y_{jet}^{LCJES}"        ); hjetrap    ->GetYaxis()->SetTitle("Entries/unit rapidity"); 
  TH1F* hjetptincl  = new TH1F("hjetptincl" ,"p_{T,jet}"      ,pbin.size()-1,pbin.data()); hjetptincl ->GetXaxis()->SetTitle("p_{T,jet}^{LCJES} [GeV]"); hjetptincl ->GetYaxis()->SetTitle("Entries/GeV"          );
  TH1F* hjetpt      = new TH1F("hjetpt"     ,"p_{T,jet}"      ,pbin.size()-1,pbin.data()); hjetptincl ->GetXaxis()->SetTitle("p_{T,jet}^{LCJES} [GeV]"); hjetptincl ->GetYaxis()->SetTitle("Entries/GeV"          );
  // fill input histograms
  int inEntries(inputTree->GetEntries());
  inputTree->Draw("cluster_ENG_CALIB_TOT>>hdepincl","","goff"); 
  inputTree->Draw("jetCalEta>>hjetrapincl"         ,"","goff"); 
  inputTree->Draw("jetCalPt>>hjetptincl"           ,"","goff"); 
  printf("[extractJets] INFO filled input cluster energy histogram with %.0f entries\n",hdepincl   ->GetEntries()); 
  printf("[extractJets] INFO filled input jet rapidity histogram with %.0f entries\n"  ,hjetrapincl->GetEntries()); 
  printf("[extractJets] INFO filled input jet pT histogram with %.0f entries\n"        ,hjetptincl ->GetEntries());
  // bin-normalize
  binNormalize(hdepincl   ); 
  binNormalize(hjetrapincl); 
  binNormalize(hjetptincl );
  // for ( int ib(1); ib <= hdepincl->GetNbinsX(); ++ib ) { 
  //   double xwid(hdepincl->GetBinWidth(ib)); 
  //   if ( xwid > 0. ) { 
  //     double yval(hdepincl->GetBinContent(ib)/xwid); 
  //     double yerr(hdepincl->GetBinError(ib)  /xwid);
  //     hdepincl->SetBinContent(ib,yval); 
  //     hdepincl->SetBinError(ib,yerr);
  //   } 
  // }
  // output
  outfPtr->cd(); 
  TTree* outputTree = inputTree->CopyTree("jetCalEta<0.4&&jetCalEta>-0.4&&cluster_ENG_CALIB_TOT>0.3");
  if ( outputTree != nullptr ) {
    outputTree->Write();
    int outEntries(outputTree->GetEntries());
    printf("[extractJets] INFO output tree \042%s\042 filled with %i of %i inputs and written\n",outputTree->GetName(),outEntries,inEntries); 
  }
  //  outfPtr->Close()
  outputTree->Draw("cluster_ENG_CALIB_TOT>>hdep","","goff");
  outputTree->Draw("jetCalEta>>hjetrap"         ,"","goff");
  outputTree->Draw("jetCalPt>>hjetpt"           ,"","goff");
  printf("[extractJets] INFO filled output cluster energy histogram with %.0f entries\n",hdep   ->GetEntries()); 
  printf("[extractJets] INFO filled output jet rapidity histogram with %.0f entries\n"  ,hjetrap->GetEntries()); 
  printf("[extractJets] INFO filled output jet pT histogram with %.0f entries\n"        ,hjetpt ->GetEntries());
  binNormalize(hdep   ); 
  binNormalize(hjetrap); 
  binNormalize(hjetpt );
  // for ( int ib(1); ib <= hdep->GetNbinsX(); ++ib ) { 
  //   double xwid(hdep->GetBinWidth(ib)); 
  //   if ( xwid > 0. ) { 
  //     double yval(hdep->GetBinContent(ib)/xwid); 
  //     double yerr(hdep->GetBinError(ib)  /xwid);
  //     hdep->SetBinContent(ib,yval); 
  //     hdep->SetBinError(ib,yerr);
  //   } 
  // }

  // Edep plot
  TCanvas* cv = new TCanvas("DepositedEnergies","DepositedEnergies"); 
  cv->SetLogx(); cv->SetLogy();
  hdepincl->SetLineColor(kBlue); 
  hdepincl->SetFillColor(kCyan);
  hdepincl->DrawCopy("hist");  
  hdep->SetLineColor(kRed); 
  hdep->SetFillColor(kYellow); 
  hdep->DrawCopy("same hist");
  hdepincl->SetFillColor(0); 
  hdepincl->SetLineStyle(2);
  hdepincl->DrawCopy("same hist");
  cv->RedrawAxis();
  cv->Print("edepfilter.pdf"); 
  cv->Print("edepfilter.png");

  // jet rapidity plot
  TCanvas* jr = new TCanvas("JetRapidity","JetRapidity"); 
  hjetrapincl->SetLineColor(kBlue); 
  hjetrapincl->SetFillColor(kCyan);
  hjetrapincl->DrawCopy("hist");  
  hjetrap->SetLineColor(kRed); 
  hjetrap->SetFillColor(kYellow); 
  hjetrap->DrawCopy("same hist");
  hjetrapincl->SetFillColor(0); 
  hjetrapincl->SetLineStyle(2);
  hjetrapincl->DrawCopy("same hist");
  jr->RedrawAxis();
  jr->Print("jetrapfilter.pdf"); 
  jr->Print("jetrapfilter.png");

  // jet rapidity plot
  TCanvas* jp = new TCanvas("JetPt","JetPt");
  jp->SetLogx(); jp->SetLogy(); 
  hjetptincl->SetLineColor(kBlue); 
  hjetptincl->SetFillColor(kCyan);
  hjetptincl->DrawCopy("hist");  
  hjetpt->SetLineColor(kRed); 
  hjetpt->SetFillColor(kYellow); 
  hjetpt->DrawCopy("same hist");
  hjetptincl->SetFillColor(0); 
  hjetptincl->SetLineStyle(2);
  hjetptincl->DrawCopy("same hist");
  jp->RedrawAxis();
  jp->Print("jetptfilter.pdf"); 
  jp->Print("jetptfilter.png");
}
