
#include "HistUtils.h"

#include <TString.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>

#include <string>
#include <vector>
#include <map>

#include <cstdio>
#include <cmath>

#define CFG_DATA( N, DATA ) std::get< N >( DATA )

void plotClusterEnergies(const std::string& dirName="jz2_cut_2") {
  // file lookup
  std::map<std::string,std::string> fileDictionary = { 
    { "jz2_cut_2", "JZ2_Cut2_summary.root" },
    { "jz2_cut_3", "JZ2_Cut3_summary.root" },
    { "jz3_cut_2", "JZ2_Cut2_summary.root" },
    { "jz3_cut_3", "JZ2_Cut3_summary.root" }
  }; 
  // histogram names              -------line------- -----fill----- -----key---   line order is (style,size,color,transparency) fill is (style,color,transparency)
  std::map<std::string,std::tuple<int,int,int,double,int,int,double,std::string> > histNames = { 
    { "ClEM__Ene_pt020", { 1, 2, HistUtils::Color::black , 0., 1001, HistUtils::Color::Light::black  , 0. ,"p_{T,jet} > 20 GeV" } },  
    { "ClEM__Ene_pt040", { 1, 2, HistUtils::Color::blue  , 0., 1001, HistUtils::Color::Light::blue   , 0. ,"p_{T,jet} > 40 GeV" } },
    { "ClEM__Ene_pt060", { 1, 2, HistUtils::Color::violet, 0., 1001, HistUtils::Color::Light::magenta, 0. ,"p_{T,jet} > 60 GeV" } },
    { "ClEM__Ene_pt080", { 1, 2, HistUtils::Color::red   , 0., 1001, HistUtils::Color::Light::orange , 0. ,"p_{T,jet} > 80 GeV" } },
    { "ClEM__Ene_pt100", { 1, 2, HistUtils::Color::brown , 0., 1001, HistUtils::Color::Light::brown  , 0. ,"p_{T,jet} > 100 GeV"} },
    { "ClEM__Ene_pt200", { 1, 2, HistUtils::Color::green , 0., 1001, HistUtils::Color::Light::green  , 0. ,"p_{T,jet} > 200 GeV"} } 
  };

  // input
  auto ffile(fileDictionary.find(dirName)); 
  if ( ffile == fileDictionary.end() ) { printf("[plotClusterEnergies] ABRT cannot find histogram file in directory \042%s\042\n",dirName.c_str()); return; } 
  TFile* inFile = new TFile(TString::Format("%s/%s",dirName.c_str(),ffile->second.c_str()).Data(),"READ");
  if ( inFile == nullptr             ) { printf("[plotClusterEnergies] ABRT cannot open file \042%s\042 in directory \042%s\042\n",ffile->second.c_str(),ffile->first.c_str()); return; } 
  // load histograms
  std::vector<TH1D*> hlist;
  double ymax(0.); 
  for ( auto entry : histNames ) { 
    TH1D* hptr = (TH1D*)inFile->FindObjectAny(entry.first.c_str()); 
    if ( hptr != nullptr && hptr->GetEntries() > 0. ) { 
      const auto& cfg = entry.second;
      int    lstyle(CFG_DATA(0,cfg)); int    fstyle(CFG_DATA(4,cfg));
      int    lwidth(CFG_DATA(1,cfg));
      int    lcolor(CFG_DATA(2,cfg)); int    fcolor(CFG_DATA(5,cfg));
      double lalpha(CFG_DATA(3,cfg)); double falpha(CFG_DATA(6,cfg));
      hptr->SetLineStyle(lstyle); hptr->SetLineWidth(lwidth); if ( lalpha == 0. ) { hptr->SetLineColor(lcolor); } else { hptr->SetLineColorAlpha(lcolor,lalpha); }
      if ( fstyle > 0 ) { hptr->SetFillStyle(fstyle); if ( falpha == 0. ) { hptr->SetFillColor(fcolor); } else { hptr->SetFillColorAlpha(fcolor,falpha); } }
      const std::string& key = CFG_DATA(7,cfg); if ( key != "" ) { hptr->SetTitle(key.c_str()); }
      hlist.push_back(hptr); ymax = std::max(ymax,hptr->GetMaximum()); 
    }
  }
  if ( hlist.empty() ) {  printf("[plotClusterEnergies] ABRT cannot find any histograms in file \042%s\042 in directory \042%s\042\n",ffile->second.c_str(),ffile->first.c_str()); return; }
  // canvas
  TCanvas* cvs = new TCanvas("JetClusEem","JetClusEem");
  cvs->SetLogx(); 
  cvs->SetLogy(); 
  
  // double xmin(hlist.front()->GetXaxis()->GetXmin()); double xmax(hlist.front()->GetXaxis()->GetXmax());
  double xmin(0.2 ); double ymin(0.9);    
  double xmax(210.); ymax *= 2.;
  TH1D* _frame = new TH1D("_frame","_frame",100,xmin,xmax);
  _frame->SetMinimum(ymin); 
  _frame->SetMaximum(ymax);
  _frame->GetXaxis()->SetTitle("E_{clus}^{EM} [GeV]"); 
  _frame->GetYaxis()->SetTitle("Entries");
  _frame->DrawCopy("axis");
  TLegend* lptr = new TLegend(0.2,0.5,0.4,0.9); 
  for ( auto hptr : hlist ) { hptr->DrawCopy("same hist"); lptr->AddEntry(hptr,hptr->GetTitle(),"lf"); }
  lptr->Draw("same"); 
  cvs->RedrawAxis(); 
} 
