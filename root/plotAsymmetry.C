
#include <TStyle.h>
#include <TFile.h>
#include <TH1D.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TString.h>
#include <TF1.h>
#include <TFitResultPtr.h>
#include <TLatex.h>

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include <algorithm>

#include <iostream>

#include <cmath>
#include <cstdio>

namespace Asymmetry {
  // quadratic asymmetry
  struct quadratic { 
    double operator()(double rms_up,double rms_down) { double var0(std::pow(rms_up,2)); double var1(std::pow(rms_down,2)); return var0+var1 != 0. ? 2.*(var0-var1)/(var0+var1) : 0.; }
  };
  // linear asymmetry
  struct linear { 
    double operator()(double rms_up,double rms_down) { return rms_up+rms_down != 0. ? 2.*(rms_up-rms_down)/(rms_up+rms_down) : 0.; }
  }; 
  // calculator (template parameter F defines asymmetry function type)
  template<class F>
  std::vector<double> calculate(const std::vector<double>& rms_up,const std::vector<double>& rms_down, F fct) {
    size_t entries(std::min(rms_up.size(),rms_down.size())); 
    std::vector<double> result(entries,0.);
    for ( size_t i(0); i<entries; ++i ) { result[i] = fct(rms_up.at(i),rms_down.at(i)) ; } 
    return result; 
  }
  // fit
  class LogPowerSum { 
  private: 
    int _firstIndex = { 0 };
    int _numParms   = { 0 };
    int _nstep      = { 1 };
  public:
    LogPowerSum() { }
    LogPowerSum(int fIdx,int numParms,int nst=1) 
      : _firstIndex(fIdx)
      , _numParms(numParms)
      , _nstep(nst)
    { } 
    double operator()(double* x,double* p) { 
      double xval(std::log(x[0])); double psum(0.); 
      int idx(_firstIndex); for ( int i(0); i<_numParms; ++i, ++idx ) { psum += p[i]*std::pow(xval,idx); }
      return psum;
    }
    int nPar() { return _numParms; }
  };
  double function(double* x,double* p) { 
    static double _nstep = 1.;
    // parameters:
    double nbeg = p[0];  // sum index (begin)
    double nend = p[1];  // sum index (end)
    // variable
    double xval = std::log(x[0]);
    //
    double sum(0.); int ip(2);
    while ( nbeg <= nend ) { sum += p[ip]*std::pow(xval,nbeg); nbeg += _nstep; ++ip; }
    //
    return sum;
  } 
}

void plotAsymmetry(const std::string& fileName="JZ3_summary.root") {
  std::map<std::string,TGraphAsymmErrors*> knownGraphs = { 
    { "EMR_Eclus_pt020_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Eclus_pt040_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Eclus_pt060_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Eclus_pt080_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Eclus_pt100_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Eclus_pt200_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Fclus_pt020_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Fclus_pt040_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Fclus_pt060_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Fclus_pt080_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Fclus_pt100_graph_mean", (TGraphAsymmErrors*)0 },
    { "EMR_Fclus_pt200_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Eclus_pt020_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Eclus_pt040_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Eclus_pt060_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Eclus_pt080_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Eclus_pt100_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Eclus_pt200_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Fclus_pt020_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Fclus_pt040_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Fclus_pt060_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Fclus_pt080_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Fclus_pt100_graph_mean", (TGraphAsymmErrors*)0 },
    { "LCR_Fclus_pt200_graph_mean", (TGraphAsymmErrors*)0 }
  };
  std::map<std::string,std::tuple<std::string,TGraphAsymmErrors*,TGraphAsymmErrors*> > graphPairs = {
    { "EMR_Eclus_pt020_graph_mean", { "LCR_Eclus_pt020_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Eclus_pt040_graph_mean", { "LCR_Eclus_pt040_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Eclus_pt060_graph_mean", { "LCR_Eclus_pt060_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Eclus_pt080_graph_mean", { "LCR_Eclus_pt080_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Eclus_pt100_graph_mean", { "LCR_Eclus_pt100_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Eclus_pt200_graph_mean", { "LCR_Eclus_pt200_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Fclus_pt020_graph_mean", { "LCR_Fclus_pt020_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Fclus_pt040_graph_mean", { "LCR_Fclus_pt040_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Fclus_pt060_graph_mean", { "LCR_Fclus_pt060_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Fclus_pt080_graph_mean", { "LCR_Fclus_pt080_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Fclus_pt100_graph_mean", { "LCR_Fclus_pt100_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } },
    { "EMR_Fclus_pt200_graph_mean", { "LCR_Fclus_pt200_graph_mean", (TGraphAsymmErrors*)0, (TGraphAsymmErrors*)0 } }
  };
  
  // allocate input file
  TFile* f = new TFile(fileName.c_str(),"READ");
  if ( f == nullptr ) { printf("[plotAsymmetry] ABRT cannot open file \042%s\042 for reading\n",fileName.c_str()); return; }

  // load graphs
  for ( auto& entry : knownGraphs ) { 
    entry.second = (TGraphAsymmErrors*)f->FindObjectAny(entry.first.c_str());
    if ( entry.second == nullptr ) { 
      printf("[plotAsymmetry] WARN cannot find graph \042%s\042\n",entry.first.c_str()); 
    } else { 
      printf("[plotAsymmetry] INFO registered graph \042%s\042 at address %p\n",entry.second->GetName(),(void*)entry.second);
    } 
  }

  // find pairs
  size_t npp(graphPairs.size());
  auto fentry(graphPairs.begin()); 
  while ( fentry != graphPairs.end() ) {
    bool isValid(false);  
    // find EM scale graph object
    auto fgraph(knownGraphs.find(fentry->first)); 
    if ( fgraph != knownGraphs.end() ) {
      auto g0ptr = fgraph->second; 
      if ( g0ptr != nullptr ) { 
	// printf("[plotAsymmetry] INFO found graph \042%s\042 for pairing\n",g0ptr->GetName()); std::cout << std::flush;
	// find LCW scale graph
	auto fpair(knownGraphs.find(std::get<0>(fentry->second)));
	auto g1ptr = fpair->second;
	if ( g1ptr != nullptr && fpair != knownGraphs.end() ) {
	  isValid = g0ptr != nullptr && g1ptr != nullptr; 
	  std::get<1>(fentry->second) = g0ptr;
	  std::get<2>(fentry->second) = g1ptr;
	  printf("[plotAsymmetry] INFO matched graph \042%s\042 with \042%s\042\n",g0ptr->GetName(),g1ptr->GetName()); 
	} // both graphs exist
      } // EM exists
    } // EM graph known
    if ( isValid ) { ++fentry; } else { fentry = graphPairs.erase(fentry); }
  } // loop on graphPairs
  printf("[plotAsymmetry] INFO found %zu of %zu possible graph pairs\n",graphPairs.size(),npp);

  // plotting area parameters
  double defLeft   = gStyle->GetPadLeftMargin()  ; gStyle->SetPadLeftMargin(0.)  ;
  double defBottom = gStyle->GetPadBottomMargin(); gStyle->SetPadBottomMargin(0.);
  double xwleft (gStyle->GetPadLeftMargin());
  double xwright(1.-gStyle->GetPadRightMargin());
  double xwwidth(xwright-xwleft); 
  double ywbottom(defBottom);
  double ywtop   (1.-gStyle->GetPadTopMargin());
  double ywheight(ywtop-ywbottom);
  double plotpfrac(0.4); double ypheight(plotpfrac*ywheight);  
  double ratiofrac(0.2); double yrheight(ratiofrac*ywheight);
  double prightm(0.); 
  double pleftm(defLeft);
  double ptopm(0.);
  double pbottomm(ywbottom); 
  std::vector<std::tuple<std::string,double,double,double,double> > padDescr = { 
    { "EM"   , xwleft,ywtop-ypheight   ,xwright,ywtop             },
    { "LCW"  , xwleft,ywtop-2.*ypheight,xwright,ywtop-ypheight    },
    { "Ratio", xwleft,ywbottom         ,xwright,ywbottom+yrheight }
  };
  std::map<std::string,TPad*> pads;
  // analyze asymmetries
  double* dptr; 
  int     fitFirstIdx(0); 
  int     fitOrderF(5); 
  int     fitOrderE(8); 
  std::vector<double> g0xval; std::vector<double> g1xval;
  std::vector<double> g0dxlo; std::vector<double> g1dxlo;
  std::vector<double> g0dxhi; std::vector<double> g1dxhi;
  std::vector<double> g0yval; std::vector<double> g1yval;
  std::vector<double> g0dylo; std::vector<double> g1dylo;
  std::vector<double> g0dyhi; std::vector<double> g1dyhi;
  std::vector<double> as0sqr; std::vector<double> as1sqr;
  std::vector<double> as0lin; std::vector<double> as1lin;
  double ratioMin(10000.); 
  double ratioMax(-10000.);
  //
  TH1D* _frameF = new TH1D("_frameF","_frameF",100,0.00025,   2.); _frameF->SetMinimum(-1.499); _frameF->SetMaximum(1.499); _frameF->GetXaxis()->SetTitle("Cluster energy fraction in jet"); 
  TH1D* _frameE = new TH1D("_frameE","_frameE",100,0.025  ,500.0); _frameE->SetMinimum(-1.499); _frameE->SetMaximum(1.499); _frameE->GetXaxis()->SetTitle("E_{clus}^{dep} [GeV]"          );
  _frameE->GetXaxis()->SetLabelSize  ( 2.0*_frameE->GetXaxis()->GetLabelSize()  ); _frameF->GetXaxis()->SetLabelSize  ( 2.0*_frameF->GetXaxis()->GetLabelSize()  );
  _frameE->GetXaxis()->SetTitleSize  ( 2.0*_frameE->GetXaxis()->GetTitleSize()  ); _frameF->GetXaxis()->SetTitleSize  ( 2.0*_frameF->GetXaxis()->GetTitleSize()  );
  _frameE->GetYaxis()->SetLabelSize  ( 2.0*_frameE->GetYaxis()->GetLabelSize()  ); _frameF->GetYaxis()->SetLabelSize  ( 2.0*_frameF->GetYaxis()->GetLabelSize()  );
  _frameE->GetYaxis()->SetTitleSize  ( 2.0*_frameE->GetYaxis()->GetTitleSize()  ); _frameF->GetYaxis()->SetTitleSize  ( 2.0*_frameF->GetYaxis()->GetTitleSize()  );
  _frameE->GetYaxis()->SetTitleOffset( 0.3*_frameE->GetYaxis()->GetTitleOffset()); _frameF->GetYaxis()->SetTitleOffset( 0.3*_frameF->GetYaxis()->GetTitleOffset());
  for ( auto entry : graphPairs ) { 
    // allocate graphs
    auto g0ptr = std::get<1>(entry.second) /* EM */; auto g1ptr = std::get<2>(entry.second) /* LCW */; 
    // get number of points 
    int g0npt(g0ptr->GetN()); int g1npt(g1ptr->GetN()); 
    // get central value and errors in x for both distributions (g0 -> EM, g1 -> LCW)
    dptr = g0ptr->GetX()     ; g0xval.clear(); g0xval.insert(g0xval.begin(),dptr,dptr+g0npt); dptr = g1ptr->GetX()     ; g1xval.clear(); g1xval.insert(g1xval.begin(),dptr,dptr+g1npt); 
    dptr = g0ptr->GetEXlow() ; g0dxlo.clear(); g0dxlo.insert(g0dxlo.begin(),dptr,dptr+g0npt); dptr = g1ptr->GetEXlow() ; g1dxlo.clear(); g1dxlo.insert(g1dxlo.begin(),dptr,dptr+g1npt);
    dptr = g0ptr->GetEXhigh(); g0dxhi.clear(); g0dxhi.insert(g0dxhi.begin(),dptr,dptr+g0npt); dptr = g1ptr->GetEXhigh(); g1dxhi.clear(); g1dxhi.insert(g1dxhi.begin(),dptr,dptr+g1npt);
    // get central value and errors in y for both distributions (g0 -> EM, g1 -> LCW)
    dptr = g0ptr->GetY()     ; g0yval.clear(); g0yval.insert(g0yval.begin(),dptr,dptr+g0npt); dptr = g1ptr->GetY()     ; g1yval.clear(); g1yval.insert(g1yval.begin(),dptr,dptr+g1npt);  
    dptr = g0ptr->GetEYlow() ; g0dylo.clear(); g0dylo.insert(g0dylo.begin(),dptr,dptr+g0npt); dptr = g1ptr->GetEYlow() ; g1dylo.clear(); g1dylo.insert(g1dylo.begin(),dptr,dptr+g1npt);
    dptr = g0ptr->GetEYhigh(); g0dyhi.clear(); g0dyhi.insert(g0dyhi.begin(),dptr,dptr+g0npt); dptr = g1ptr->GetEYhigh(); g1dyhi.clear(); g1dyhi.insert(g1dyhi.begin(),dptr,dptr+g1npt);
    // calculate asymmetries
    as0sqr = Asymmetry::calculate(g0dylo,g0dyhi,Asymmetry::quadratic()); as1sqr = Asymmetry::calculate(g1dylo,g1dyhi,Asymmetry::quadratic());
    // as0lin = Asymmetry::calculate(g0dylo,g0dyhi,Asymmetry::linear   ()); as1lin = Asymmetry::calculate(g1dylo,g1dyhi,Asymmetry::linear   ());
    // fill graphs
    std::string t0sqr(g0ptr->GetName()); t0sqr.replace(t0sqr.find("graph_mean"),std::string::npos,"asymmetry_square"   ); std::string t1sqr(g1ptr->GetName()); t1sqr.replace(t1sqr.find("graph_mean"),std::string::npos,"asymmetry_square");
    std::string trsqr(g0ptr->GetName()); trsqr.replace(trsqr.find("graph_mean"),std::string::npos,"asymmetry_fit_ratio");
    // std::string t0lin(g0ptr->GetName()); t0lin.replace(t0lin.find("graph_mean"),std::string::npos,"asymmetry_linear"); std::string t1lin(g1ptr->GetName()); t1lin.replace(t1lin.find("graph_mean"),std::string::npos,"asymmetry_linear");
    TGraph* g0sqr = new TGraph(g0xval.size(),&g0xval.at(0),&as0sqr.at(0)); g0sqr->SetName(t0sqr.c_str()); g0sqr->SetLineColor(kRed) ; g0sqr->SetMarkerColor(kRed) ; g0sqr->SetMarkerStyle(20); g0sqr->SetMarkerSize(0.75); g0sqr->SetLineWidth(2); 
    // TGraph* g0lin = new TGraph(g0xval.size(),&g0xval.at(0),&as0lin.at(0)); g0sqr->SetName(t0lin.c_str()); g0lin->SetLineColor(kRed) ; g0lin->SetMarkerColor(kRed) ; g0lin->SetMarkerStyle(20); g0lin->SetMarkerSize(0.75); g0lin->SetLineWidth(2);
    TGraph* g1sqr = new TGraph(g1xval.size(),&g1xval.at(0),&as1sqr.at(0)); g0sqr->SetName(t1sqr.c_str()); g1sqr->SetLineColor(kBlue); g1sqr->SetMarkerColor(kBlue); g1sqr->SetMarkerStyle(20); g1sqr->SetMarkerSize(0.75); g1sqr->SetLineWidth(2);
    // TGraph* g1lin = new TGraph(g1xval.size(),&g1xval.at(0),&as1lin.at(0)); g0sqr->SetName(t1lin.c_str()); g1lin->SetLineColor(kBlue); g1lin->SetMarkerColor(kBlue); g1lin->SetMarkerStyle(20); g1lin->SetMarkerSize(0.75); g1lin->SetLineWidth(2);
    // extract information
    std::string ptrange(g0ptr->GetName()); ptrange = ptrange.substr(ptrange.find("_pt")+3,3);
    std::string evalvar(g0ptr->GetName()); evalvar = evalvar.substr(evalvar.find_first_of('_')+1,5);
    // set up plotting areas
    TCanvas* csqr = new TCanvas(TString::Format("SquareAsymmetry_%s_%s",evalvar.c_str(),ptrange.c_str()).Data(),TString::Format("SquareAsymmetry_%s_%s",evalvar.c_str(),ptrange.c_str()).Data()); // csqr->Divide(1,2,0.,0.);
    csqr->SetFillStyle(4000);
    // TCanvas* clin = new TCanvas(TString::Format("LinearAsymmetry_%s_%s",evalvar.c_str(),ptrange.c_str()).Data(),TString::Format("LinearAsymmetry_%s_%s",evalvar.c_str(),ptrange.c_str()).Data()); // clin->Divide(1,2,0.,0.);
    csqr->cd(); pads.clear(); 
    for ( auto entry : padDescr ) {
      std::string pname(std::get<0>(entry));
      pads[pname] = new TPad(TString::Format("%s_%s",csqr->GetName(),std::get<0>(entry).c_str()).Data(),std::get<0>(entry).c_str(),std::get<1>(entry),std::get<2>(entry),std::get<3>(entry),std::get<4>(entry));
      pads[pname]->SetLogx(); pads[pname]->SetGridy();
      pads[pname]->SetLeftMargin(pleftm); pads[pname]->SetRightMargin(prightm); pads[pname]->SetTopMargin(ptopm); if ( pname == "Ratio" ) { pads[pname]->SetBottomMargin(2.*pbottomm); } else { pads[pname]->SetBottomMargin(0.); } 
      csqr->cd(); pads[pname]->Draw();
    }
    // csqr->cd(); pads.clear(); 
    // for ( auto entry : padDescr ) {
    //   std::string pname(std::get<0>(entry));
    //   pads[pname] = new TPad(TString::Format("%s_%s",csqr->GetName(),std::get<0>(entry).c_str()).Data(),std::get<0>(entry).c_str(),std::get<1>(entry),std::get<2>(entry),std::get<3>(entry),std::get<4>(entry));
    //   pads[pname]->SetLogx(); pads[pname]->SetGridy();
    //   pads[pname]->SetLeftMargin(pleftm); pads[pname]->SetRightMargin(prightm); pads[pname]->SetTopMargin(ptopm); if ( pname == "Ratio" ) { pads[pname]->SetBottomMargin(pbottomm); } else { pads[pname]->SetBottomMargin(0.); } 
    //   csqr->cd(); pads[pname]->Draw();
    // }
    // csqr->cd(1)->SetLogx(); csqr->cd(1)->SetGridy(); csqr->cd(2)->SetLogx(); csqr->cd(2)->SetGridy();    
    // clin->cd(1)->SetLogx(); clin->cd(1)->SetGridy(); clin->cd(2)->SetLogx(); clin->cd(2)->SetGridy();
    TH1D* _frame = evalvar == "Eclus" ? new TH1D(*_frameE) : new TH1D(*_frameF);
    std::string axt(_frame->GetXaxis()->GetTitle());
    /* csqr->cd(1) */pads["EM"]->cd() ; _frame->GetYaxis()->SetTitle("A_{quadratic}^{EM}" ); _frame->GetXaxis()->SetTitle(""); _frame->DrawCopy("axis"); _frame->DrawCopy("axig same"); g0sqr->Draw("psame"); gPad->RedrawAxis(); 
    /* csqr->cd(2) */pads["LCW"]->cd(); _frame->GetYaxis()->SetTitle("A_{quadratic}^{LCW}"); _frame->GetXaxis()->SetTitle(""); _frame->DrawCopy("axis"); _frame->DrawCopy("axig same"); g1sqr->Draw("psame"); gPad->RedrawAxis();  
    // clin->cd(1); _frame->GetYaxis()->SetTitle("A_{linear}^{EM}"    ); _frame->GetXaxis()->SetTitle("")         ; _frame->DrawCopy("axis"); _frame->DrawCopy("axig same"); g0lin->Draw("psame"); gPad->RedrawAxis(); 
    // clin->cd(2); _frame->GetYaxis()->SetTitle("A_{linear}^{LCW}"   ); _frame->GetXaxis()->SetTitle(axt.c_str()); _frame->DrawCopy("axis"); _frame->DrawCopy("axig same"); g1lin->Draw("psame"); gPad->RedrawAxis();  
    // fit graphs
    Asymmetry::LogPowerSum powerSumE(0,fitOrderE); Asymmetry::LogPowerSum powerSumF(fitFirstIdx,fitOrderF);
    TF1* f0sqr = (TF1*)0; TFitResultPtr r0sqr; // TF1* f0lin = (TF1*)0; TFitResultPtr r0lin;
    TF1* f1sqr = (TF1*)0; TFitResultPtr r1sqr; // TF1* f1lin = (TF1*)0; TFitResultPtr r1lin;
    if ( evalvar == "Eclus" ) { 
      f0sqr = new TF1("f_quadratic_em",powerSumE,g0xval.front(),g0xval.back(),powerSumE.nPar()); f0sqr->SetNpx(5000); f0sqr->SetLineColorAlpha(g0sqr->GetLineColor(),0.5); f0sqr->SetLineWidth(4); f0sqr->SetLineStyle(1);
      // f0lin = new TF1("f_linear_em",   powerSumE,g0xval.front(),g0xval.back(),powerSumE.nPar()); f0lin->SetNpx(5000); f0lin->SetLineColorAlpha(g0lin->GetLineColor(),0.5); f0lin->SetLineWidth(4); f0lin->SetLineStyle(1);
      f1sqr = new TF1("f_quadratic_lc",powerSumE,g1xval.front(),g1xval.back(),powerSumE.nPar()); f1sqr->SetNpx(5000); f1sqr->SetLineColorAlpha(g1sqr->GetLineColor(),0.5); f1sqr->SetLineWidth(4); f1sqr->SetLineStyle(1);  
      // f1lin = new TF1("f_linear_lc",   powerSumE,g1xval.front(),g1xval.back(),powerSumE.nPar()); f1lin->SetNpx(5000); f1lin->SetLineColorAlpha(g1lin->GetLineColor(),0.5); f1lin->SetLineWidth(4); f1lin->SetLineStyle(1);
      /* csqr->cd(1) */pads["EM"]->cd(); r0sqr = g0sqr->Fit(f0sqr,"+R0","l"); f0sqr->Draw("lsame"); /* csqr->cd(2) */pads["LCW"]->cd(); r1sqr = g1sqr->Fit(f1sqr,"+R0","l"); f1sqr->Draw("lsame");
      // clin->cd(1); r0lin = g0lin->Fit(f0lin,"+R0","l"); f0lin->Draw("lsame"); clin->cd(2); r1lin = g1lin->Fit(f1lin,"+R0","l"); f1lin->Draw("lsame"); 
    } else { 
      f0sqr = new TF1("f_quadratic_em",powerSumF,g0xval.front(),g0xval.back(),powerSumF.nPar()); f0sqr->SetNpx(5000); f0sqr->SetLineColorAlpha(g0sqr->GetLineColor(),0.5); f0sqr->SetLineWidth(4); f0sqr->SetLineStyle(1);
      // f0lin = new TF1("f_linear_em",   powerSumF,g0xval.front(),g0xval.back(),powerSumF.nPar()); f0lin->SetNpx(5000); f0lin->SetLineColorAlpha(g0lin->GetLineColor(),0.5); f0lin->SetLineWidth(4); f0lin->SetLineStyle(1);
      f1sqr = new TF1("f_quadratic_lc",powerSumF,g1xval.front(),g1xval.back(),powerSumF.nPar()); f1sqr->SetNpx(5000); f1sqr->SetLineColorAlpha(g1sqr->GetLineColor(),0.5); f1sqr->SetLineWidth(4); f1sqr->SetLineStyle(1);  
      // f1lin = new TF1("f_linear_lc",   powerSumF,g1xval.front(),g1xval.back(),powerSumF.nPar()); f1lin->SetNpx(5000); f1lin->SetLineColorAlpha(g1lin->GetLineColor(),0.5); f1lin->SetLineWidth(4); f1lin->SetLineStyle(1);
      /* csqr->cd(1) */pads["EM"]->cd(); r0sqr = g0sqr->Fit(f0sqr,"+R0","l"); f0sqr->Draw("lsame"); /* csqr->cd(2) */pads["LCW"]->cd(); r1sqr = g1sqr->Fit(f1sqr,"+R0","l"); f1sqr->Draw("lsame");
      // clin->cd(1); r0lin = g0lin->Fit(f0lin,"+R0","l"); f0lin->Draw("lsame"); clin->cd(2); r1lin = g1lin->Fit(f1lin,"+R0","l"); f1lin->Draw("lsame"); 
    }    
    // calculate ratio
    // double x0start(0.); double x1start(0.); 
    // double x0end(0.)  ; double x1end(0.)  ;
    // f0sqr->GetRange(x0start,x0end); f1sqr->GetRange(x1start,x1end);
    std::vector<double> x0values(g0sqr->GetX(),g0sqr->GetX()+g0sqr->GetN());
    std::vector<double> x1values(g1sqr->GetX(),g1sqr->GetX()+g1sqr->GetN());
    double x0start(*(std::minmax_element(x0values.begin(),x0values.end()).first )); double x1start(*(std::minmax_element(x1values.begin(),x1values.end()).first ));
    double x0end  (*(std::minmax_element(x0values.begin(),x0values.end()).second)); double x1end  (*(std::minmax_element(x1values.begin(),x1values.end()).second));
    double xstart(std::max(x0start,x1start)); double xend(std::min(x0end,x1end)); 
    int npts(f0sqr->GetNpx()); 
    printf("[plotAsymmetry] INFO sample %i x-values in [%.3f,%.3f]\n",npts,xstart,xend);
    std::vector<double> xcoord(npts,0.); std::vector<double> ycoord(npts,0.); 
    double xstep((xend-xstart)/((double)npts));
    size_t icoord(0); 
    while ( xstart <= xend ) { 
      double fem(f0sqr->Eval(xstart)); 
      if ( fem != 0. ) { double flcw(f1sqr->Eval(xstart)); xcoord[icoord] = xstart; ycoord[icoord] = flcw-fem; xstart += xstep; ++icoord; }
    } 
    pads["Ratio"]->cd(); 
    TGraph* grsqr = new TGraph(xcoord.size(),&xcoord.at(0),&ycoord.at(0)); grsqr->SetName(trsqr.c_str()); grsqr->SetLineColorAlpha(kBlack,0.5); grsqr->SetLineWidth(4); 
    printf("[plotAsymmetry] INFO Graph \042%s\042 has %i points\n",grsqr->GetName(),grsqr->GetN());
    double yrmax(*(std::minmax_element(ycoord.begin(),ycoord.end()).second)); double yrmin(*(std::minmax_element(ycoord.begin(),ycoord.end()).first));
    ratioMin = std::min(ratioMin,yrmin); ratioMax = std::max(ratioMax,yrmax);
    // double yfmax(0.); while ( std::abs(yrmax) < 1. ) { yrmax *= 10.; ++yfmax; } double grmax(std::round(yrmax)); if ( grmax < std::abs(yrmax) ) { grmax += 1.; } grmax = std::copysign(grmax/std::pow(10.,yfmax),yrmax);
    // double yfmin(0.); while ( std::abs(yrmin) < 1. ) { yrmin *= 10.; ++yfmin; } double grmin(std::round(yrmin)); if ( grmin < std::abs(yrmin) ) { grmin += 1.; } grmin = std::copysign(grmin/std::pow(10.,yfmin),yrmin);
    // printf("[plotAsymmetry] INFO Graph \042%s\042 has min/max %.3f/%.3f\n",grsqr->GetName(),grmin,grmax); 
    printf("[plotAsymmetry] INFO Graph \042%s\042 has min/max %.3f/%.3f\n",grsqr->GetName(),yrmin,yrmax); 
    double textScale(ypheight/yrheight); 
    _frame->SetMinimum(-0.7); _frame->SetMaximum(0.699999999);
    _frame->GetXaxis()->SetLabelSize(_frame->GetXaxis()->GetLabelSize()*textScale); //_frame->GetXaxis()->SetTitleSize(_frame->GetXaxis()->GetTitleSize()*textScale); _frame->GetXaxis()->SetTitle(axt.c_str());
    //    _frame->GetXaxis()->SetTitleOffset(0.75);
    _frame->GetYaxis()->SetLabelSize(_frame->GetYaxis()->GetLabelSize()*textScale); _frame->GetYaxis()->SetTitleSize(_frame->GetYaxis()->GetTitleSize()*textScale); _frame->GetYaxis()->SetTitle("#DeltaA_{LCW-EM}")  ; 
    _frame->GetYaxis()->SetTitleOffset(0.2);      //_frame->GetTitleOffset()/textScale);
    _frame->GetYaxis()->SetNdivisions(504); 
    _frame->DrawCopy("axis"); _frame->DrawCopy("same axig"); grsqr->Draw("lsame"); 
    // 
    for ( auto plot : pads ) { plot.second->cd(); plot.second->Draw(); }
    // x-axis label
    csqr->cd();
    TLatex xlab;
    xlab.SetTextAlign(33); 
    xlab.SetNDC();
    xlab.SetTextSize(_frame->GetXaxis()->GetTitleSize()*ypheight);
    xlab.DrawLatex(xwright,ywbottom,axt.c_str()); 
    // print
    csqr->Print(TString::Format("%s.pdf",csqr->GetName()).Data()); csqr->Print(TString::Format("%s.png",csqr->GetName()).Data());
    // clin->Print(TString::Format("%s.pdf",clin->GetName()).Data()); clin->Print(TString::Format("%s.png",clin->GetName()).Data());
  }
  printf("[plotAsymmetry] INFO min/max ratio %+.3f/%+.3f\n",ratioMin,ratioMax);
}
