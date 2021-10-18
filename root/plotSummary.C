
#include <TStyle.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TLine.h>
#include <TPad.h>

#include "PlotConfig.h"

#include <string>
#include <tuple>
#include <map>
#include <vector>

namespace Data {
  // data for jets
  namespace Jet {  
    static const Types::Graph::NameGroupMap knownGraphsRMS = { 
      { "ResponseEdepRMS", { "EMR_Edep_incl_graph_mean_rms", "LCR_Edep_incl_graph_mean_rms", "MLR_Edep_incl_graph_mean_rms" } },
      { "ResponseEfrcRMS", { "EMR_Efrc_incl_graph_mean_rms", "LCR_Efrc_incl_graph_mean_rms", "MLR_Efrc_incl_graph_mean_rms" } },
      { "ResponselambRMS", { "EMR_lamb_incl_graph_mean_rms", "LCR_lamb_incl_graph_mean_rms", "MLR_lamb_incl_graph_mean_rms" } },
      { "Responselat_RMS", { "EMR_lat__incl_graph_mean_rms", "LCR_lat__incl_graph_mean_rms", "MLR_lat__incl_graph_mean_rms" } },
      { "ResponselongRMS", { "EMR_long_incl_graph_mean_rms", "LCR_long_incl_graph_mean_rms", "MLR_long_incl_graph_mean_rms" } },
      { "Responseptd_RMS", { "EMR_ptd__incl_graph_mean_rms", "LCR_ptd__incl_graph_mean_rms", "MLR_ptd__incl_graph_mean_rms" } },
      { "Responserho_RMS", { "EMR_rho__incl_graph_mean_rms", "LCR_rho__incl_graph_mean_rms", "MLR_rho__incl_graph_mean_rms" } },
      { "ResponsesignRMS", { "EMR_sign_incl_graph_mean_rms", "LCR_sign_incl_graph_mean_rms", "MLR_sign_incl_graph_mean_rms" } },
      { "ResponsetimeRMS", { "EMR_time_incl_graph_mean_rms", "LCR_time_incl_graph_mean_rms", "MLR_time_incl_graph_mean_rms" } }
    }; 
    static const Types::Graph::NameGroupMap knownGraphsERR = { 
      { "ResponseEdepERR", { "EMR_Edep_incl_graph_mean_err", "LCR_Edep_incl_graph_mean_err", "MLR_Edep_incl_graph_mean_err" } },
      { "ResponseEfrcERR", { "EMR_Efrc_incl_graph_mean_err", "LCR_Efrc_incl_graph_mean_err", "MLR_Efrc_incl_graph_mean_err" } },
      { "ResponselambERR", { "EMR_lamb_incl_graph_mean_err", "LCR_lamb_incl_graph_mean_err", "MLR_lamb_incl_graph_mean_err" } },
      { "Responselat_ERR", { "EMR_lat__incl_graph_mean_err", "LCR_lat__incl_graph_mean_err", "MLR_lat__incl_graph_mean_err" } },
      { "ResponselongERR", { "EMR_long_incl_graph_mean_err", "LCR_long_incl_graph_mean_err", "MLR_long_incl_graph_mean_err" } },
      { "Responseptd_ERR", { "EMR_ptd__incl_graph_mean_err", "LCR_ptd__incl_graph_mean_err", "MLR_ptd__incl_graph_mean_err" } },
      { "Responserho_ERR", { "EMR_rho__incl_graph_mean_err", "LCR_rho__incl_graph_mean_err", "MLR_rho__incl_graph_mean_err" } },
      { "ResponsesignERR", { "EMR_sign_incl_graph_mean_err", "LCR_sign_incl_graph_mean_err", "MLR_sign_incl_graph_mean_err" } },
      { "ResponsetimeERR", { "EMR_time_incl_graph_mean_err", "LCR_time_incl_graph_mean_err", "MLR_time_incl_graph_mean_err" } }
    }; 
  }
  // data for pions
  namespace Pion { 
    static const Types::Graph::NameGroupMap knownGraphs = { 
      { "ResponseEdepRMS", { "EMR_Edep_incl_graph_mean", "LCR_Edep_incl_graph_mean", "MLR_Edep_incl_graph_mean" } },
      // { "ResponseEfrcRMS", { "EMR_Efrc_incl_graph_mean", "LCR_Efrc_incl_graph_mean", "MLR_Efrc_incl_graph_mean" } },
      { "ResponselambRMS", { "EMR_lamb_incl_graph_mean", "LCR_lamb_incl_graph_mean", "MLR_lamb_incl_graph_mean" } },
      { "Responselat_RMS", { "EMR_lat__incl_graph_mean", "LCR_lat__incl_graph_mean", "MLR_lat__incl_graph_mean" } },
      { "ResponselongRMS", { "EMR_long_incl_graph_mean", "LCR_long_incl_graph_mean", "MLR_long_incl_graph_mean" } },
      { "Responseptd_RMS", { "EMR_ptd__incl_graph_mean", "LCR_ptd__incl_graph_mean", "MLR_ptd__incl_graph_mean" } },
      { "Responserho_RMS", { "EMR_rho__incl_graph_mean", "LCR_rho__incl_graph_mean", "MLR_rho__incl_graph_mean" } },
      { "ResponsesignRMS", { "EMR_sign_incl_graph_mean", "LCR_sign_incl_graph_mean", "MLR_sign_incl_graph_mean" } },
      { "ResponsetimeRMS", { "EMR_time_incl_graph_mean", "LCR_time_incl_graph_mean", "MLR_time_incl_graph_mean" } }
    }; 
  }
  static const std::map<Types::Graph::ScaleTag,Types::Graph::LineDescriptor> lineStyles = { 
    { Types::Graph::knownScales.at(0), Types::Graph::DescriptionFactory::Line((int)kRed     ,1,2,0.90) },  // EM red
    { Types::Graph::knownScales.at(1), Types::Graph::DescriptionFactory::Line((int)kBlue    ,1,2,0.90) },  // LC blue
    { Types::Graph::knownScales.at(2), Types::Graph::DescriptionFactory::Line((int)kOrange+3,1,2,0.90) }   // ML brown 
  };
  static const std::map<Types::Graph::ScaleTag,Types::Graph::MarkerDescriptor> markerStyles = { 
    { Types::Graph::knownScales.at(0), Types::Graph::DescriptionFactory::Marker((int)kRed     ,20,0.75,0.) },  // EM red
    { Types::Graph::knownScales.at(1), Types::Graph::DescriptionFactory::Marker((int)kBlue    ,20,0.75,0.) },  // LC blue
    { Types::Graph::knownScales.at(2), Types::Graph::DescriptionFactory::Marker((int)kOrange+3,20,0.75,0.) }   // ML brown 
  };
  static const std::map<Types::Graph::ScaleTag,Types::Graph::FillDescriptor> fillStyles = { 
    { Types::Graph::knownScales.at(0), Types::Graph::DescriptionFactory::Fill((int)kRed-9   ,1001,200,0.90) },  // EM red
    { Types::Graph::knownScales.at(1), Types::Graph::DescriptionFactory::Fill((int)kBlue-9  ,1001,200,0.90) },  // LC blue
    { Types::Graph::knownScales.at(2), Types::Graph::DescriptionFactory::Fill((int)kOrange-9,1001,200,0.90) }   // ML brown 
  };
  static const std::map<Types::Graph::Name,std::tuple<Types::Axis::Descriptor,Types::Axis::Descriptor,bool> > drawFrames = {
    { "ResponseEdepRMS", { Types::Axis::description(0.1,200.  ,true,"E_{clus}^{dep} [GeV]")                               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "ResponseEdepERR", { Types::Axis::description(0.1,200.  ,true,"E_{clus}^{dep} [GeV]")                               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "ResponseEfrcRMS", { Types::Axis::description(0.005,1.0 ,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}")               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "ResponseEfrcERR", { Types::Axis::description(0.005,1.0 ,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}")               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "Responserho_RMS", { Types::Axis::description(std::pow(10.,-8.),std::pow(10.,-3.25),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "Responserho_ERR", { Types::Axis::description(std::pow(10.,-8.),std::pow(10.,-3.25),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "ResponselambRMS", { Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]")                                 ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "ResponselambERR", { Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]")                                 ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "ResponselongRMS", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT")                                     ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},
    { "ResponselongERR", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT")                                     ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},
    { "Responselat_RMS", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "Responselat_ERR", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}}, 
    { "ResponsesignRMS", { Types::Axis::description(1.,500.,true,"#zeta_{clus}^{em}")                                     ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},
    { "ResponsesignERR", { Types::Axis::description(1.,500.,true,"#zeta_{clus}^{em}")                                     ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},
    { "Responseptd_RMS", { Types::Axis::description(0.,1.,false,"p_{t}D")                                                 ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},
    { "Responseptd_ERR", { Types::Axis::description(0.,1.,false,"p_{t}D")                                                 ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},
    { "ResponsetimeRMS", { Types::Axis::description(-0.25,7.25,false,"#sigma(^{}t_{cell}) [ns]")                          ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}},  
    { "ResponsetimeERR", { Types::Axis::description(-0.25,7.25,false,"#sigma(^{}t_{cell}) [ns]")                          ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em/had/ml}/^{}E_{clus}^{dep}"),true}}
  };
  // dictionary
  static const std::map<bool,std::string> sourceType = { 
    { true , "Jets"  },
    { false, "Pions" }
  };
} // Data

void plotSummary(const std::string& fileName,const std::string& barOpt="RMS") {
  // open file
  TFile* dataFile = new TFile(fileName.c_str(),"READ"); 
  if ( dataFile == nullptr ) { printf("[plotSummary(fileName=\042%s\042)] ABRT cannot find input file\n",fileName.c_str()); return; }
  // find source of input data
  bool haveJets(fileName.find("jets") != std::string::npos);
  printf("[plotSummary(fileName=\042%s\042)] INFO produce plots for %s\n",fileName.c_str(),Data::sourceType.at(haveJets).c_str());
  // read graphs for three different response scales (RMS)
  Types::Graph::PointerGroupMap   graphs;
  std::vector<Types::Graph::Name> gnames;
  // for jets 
  if ( haveJets ) { 
    if ( barOpt == "RMS" ) {
      // RMS bar option 
      for ( auto plot : Data::Jet::knownGraphsRMS ) { 
	// load plots
	graphs[plot.first] = { (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<0>(plot.second)), 
			       (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<1>(plot.second)),  
			       (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<2>(plot.second)) };
	gnames.push_back(plot.first);
      }
    } else if ( barOpt == "ERR" ) {
      // error bar option
      for ( auto plot : Data::Jet::knownGraphsERR ) { 
	// load plots
	graphs[plot.first] = { (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<0>(plot.second)), 
			       (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<1>(plot.second)),  
			       (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<2>(plot.second)) };
	gnames.push_back(plot.first);
      }
    } else {
      printf("[plotSummary(fileName=\042%s\042)] ABRT bar option %s unknown\n",fileName.c_str(),barOpt.c_str()); return;
    }
  } else { 
    // RMS bar option only  
    for ( auto plot : Data::Pion::knownGraphs ) { 
      // load plots
      graphs[plot.first] = { (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<0>(plot.second)), 
			     (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<1>(plot.second)),  
			     (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(dataFile,std::get<2>(plot.second)) };
      gnames.push_back(plot.first);
    }
  }
  // directory for plots
  std::string plotDir = fileName.substr(0,fileName.find_last_of('/'))+std::string("/plots");
  printf("[plotSummary(fileName=\042%s\042)] INFO bar option %s plots will be stored in \042%s\042\n",fileName.c_str(),barOpt.c_str(),plotDir.c_str());

  //////////////
  // Plotting //
  //////////////

  // overall style
  // printf("[plotSummary(fileName=\042%s\042)] INFO default x-error bar width %12.3g changed to ",fileName.c_str(),gStyle->GetErrorX());
  // gStyle->SetErrorX(0.05); 
  // printf("%12.3g",gStyle->GetErrorX());

  double wwidth (1.-(gStyle->GetPadLeftMargin()+gStyle->GetPadRightMargin()));
  double wheight(1.-(gStyle->GetPadTopMargin()+gStyle->GetPadBottomMargin()));

  double dmin(10000.); double dmax(-dmin); 

  std::vector<TGraphAsymmErrors*> graphCache;
  for ( const auto& pname : gnames ) {
    // axis descriptions
    const Types::Axis::Descriptor& xaxisD = std::get<0>(Data::drawFrames.at(pname));
    const Types::Axis::Descriptor& yaxisD = std::get<1>(Data::drawFrames.at(pname));
    bool  drawLines(std::get<2>(Data::drawFrames.at(pname)));
    // canvas
    std::string cname(TString::Format("Canvas%s",pname.c_str()).Data());
    TCanvas* _canvas = new TCanvas(cname.c_str(),pname.c_str());
    _canvas->SetBottomMargin(0.); 
    _canvas->SetLeftMargin(0.);
    _canvas->SetRightMargin(0.);
    _canvas->SetTopMargin(0.);
    // pads
    _canvas->cd(); TPad* upper = new TPad(TString::Format("%s_upper_pad",_canvas->GetName()).Data(),"Response",0.0,0.3,1.0,1.0); upper->SetBottomMargin(0.001); upper->SetGridx(); upper->Draw();
    _canvas->cd(); TPad* lower = new TPad(TString::Format("%s_lower_pad",_canvas->GetName()).Data(),"Symmetry",0.0,0.0,1.0,0.3); lower->SetBottomMargin(0.350); lower->SetTopMargin(0.001); lower->SetGrid(); lower->Draw();
    _canvas->cd();
    if ( Types::Axis::isLog(xaxisD) ) { upper->SetLogx(); lower->SetLogx(); }
    if ( Types::Axis::isLog(yaxisD) ) { upper->SetLogy(); }
    // frame in upper plot
    std::string hname(TString::Format("Frame%s",pname.c_str()).Data());
    TH1D* _frame  = new TH1D(hname.c_str(),hname.c_str(),100,Types::Axis::xmin(xaxisD),Types::Axis::xmax(xaxisD));
    _frame->SetMinimum(Types::Axis::xmin(yaxisD));
    _frame->SetMaximum(Types::Axis::xmax(yaxisD));
    _frame->GetYaxis()->SetTitle(Types::Axis::title(yaxisD).c_str());
    upper->cd(); _frame->DrawCopy("axis");
    // frame in lower plot
    TH1D* frame_ = new TH1D(*_frame); 
    frame_->GetXaxis()->SetTitle(Types::Axis::title(xaxisD).c_str());
    //    frame_->GetYaxis()->SetTitle("#frac{#sigma_{#uparrow}^{2}#minus#sigma_{#downarrow}^{2}}{^{}#sigma_{#uparrow}^{2}#plus^{}#sigma_{#downarrow}^{2}}");
    frame_->GetYaxis()->SetTitle("#sigma_{#uparrow}^{2}#minus#sigma_{#downarrow}^{2}");
    frame_->SetMinimum(-0.05); frame_->SetMaximum(0.135);
    frame_->GetXaxis()->SetTitleSize  (frame_->GetXaxis()->GetTitleSize()  *2.25);
    frame_->GetXaxis()->SetTitleOffset(frame_->GetXaxis()->GetTitleOffset()*0.85);
    frame_->GetXaxis()->SetLabelSize  (frame_->GetXaxis()->GetLabelSize()  *2.25);
    frame_->GetYaxis()->SetTitleSize  (frame_->GetYaxis()->GetTitleSize()  *2.25);
    frame_->GetYaxis()->SetTitleOffset(frame_->GetYaxis()->GetTitleOffset()*0.40);
    frame_->GetYaxis()->SetLabelSize  (frame_->GetYaxis()->GetLabelSize()  *2.25);
    frame_->GetYaxis()->SetNdivisions(209);
    lower->cd(); frame_->DrawCopy("axis"); frame_->DrawCopy("axig same");
    // graphs
    graphCache.clear();
    for ( const auto& scaleTag : Types::Graph::knownScales ) { 
      TGraphAsymmErrors* gptr = Types::Graph::findGraph<TGraphAsymmErrors>(graphs.at(pname),scaleTag); 
      if ( gptr != nullptr ) { 
	// configure drawing style and draw
	Types::Graph::setDrawStyle(gptr,Data::lineStyles.at(scaleTag),Data::fillStyles.at(scaleTag),Data::markerStyles.at(scaleTag)); upper->cd(); gptr->Draw("2same"); graphCache.push_back(gptr);
	// get data for RMS (up/down)
	TGraph* gdptr = new TGraph((const TGraph&)*gptr);
	for ( int ipt(0); ipt<gptr->GetN(); ++ipt ) { 
	  double dylo(std::pow(gptr->GetErrorYlow(ipt),2)); double dyhi(std::pow(gptr->GetErrorYhigh(ipt),2));
	  //	  double dasy(2.*(dyhi-dylo)/(dyhi+dylo));
	  double dasy(dyhi-dylo);
	  gdptr->SetPointY(ipt,dasy);
	  //	  printf("[plotSummary(fileName=\042%s\042)] DEBG point (%12.3g,%12.3g) added\n",fileName.c_str(),gdptr->GetPointX(ipt),gdptr->GetPointY(ipt));
	  dmin = std::min(dmin,gdptr->GetPointY(ipt));
	  dmax = std::max(dmax,gdptr->GetPointY(ipt));  
	  lower->cd(); gdptr->SetLineWidth(2); gdptr->SetLineColorAlpha(gdptr->GetLineColor(),0.50); gdptr->SetFillStyle(0); gdptr->Draw("lsame"); 
	}
      }
    }
    upper->cd(); for ( auto gptr : graphCache ) { TGraphAsymmErrors* cgptr = new TGraphAsymmErrors(*gptr); cgptr->SetFillStyle(0); cgptr->Draw("pxsame"); }
    // draw lines and text
    if ( drawLines ) { 
      TLine* lptr = new TLine(_frame->GetXaxis()->GetXmin(),1.0,_frame->GetXaxis()->GetXmax(),1.0); lptr->SetLineWidth(1); lptr->SetLineStyle(1); lptr->SetLineColor(kGray+3); lptr->Draw("same");  
      TLine* uptr = new TLine(_frame->GetXaxis()->GetXmin(),0.9,_frame->GetXaxis()->GetXmax(),0.9); uptr->SetLineWidth(1); uptr->SetLineStyle(2); uptr->SetLineColor(kGray+3); uptr->Draw("same");  
      TLine* dptr = new TLine(_frame->GetXaxis()->GetXmin(),1.1,_frame->GetXaxis()->GetXmax(),1.1); dptr->SetLineWidth(1); dptr->SetLineStyle(2); dptr->SetLineColor(kGray+3); dptr->Draw("same");  
    }
    _frame->DrawCopy("axig same");
    // finish
    // upper->Draw();
    // lower->Draw();
    _canvas->RedrawAxis();
    // print
    _canvas->Print(TString::Format("%s/%s.pdf",plotDir.c_str(),pname.c_str()).Data()); 
    _canvas->Print(TString::Format("%s/%s.png",plotDir.c_str(),pname.c_str()).Data()); 
  }
  printf("[plotSummary(fileName=\042%s\042)] INFO asymmetry range (%12.3g,%12.3g)\n",fileName.c_str(),dmin,dmax);
}
