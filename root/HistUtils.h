// -*- c++ -*-
#ifndef HISTUTILS_H
#define HISTUTILS_H

#include <iostream>
#include <cstdio>

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <algorithm>

#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TLine.h>
#include <TBox.h>
#include <TLatex.h>
#include <TMath.h>
#include <TColor.h>
#include <TString.h>
#include <TFile.h>

//#include "AnalysisUtils.h"

//////////////////////////////////
// Histogram Analysis Utilities //
////////////////////////////////// 

namespace HistUtils {
  
  //////////////////////////////////////////////
  // Enumerator indicating requested variable //
  //////////////////////////////////////////////

  enum Stats { Mean=0x11, Median=0x12, RMS=0x21, Unknown=0x00 };

  /////////////////////////////////
  // Cache for enumerator lookup //
  /////////////////////////////////

  static std::map<int,std::string> stats_lu = std::map<int,std::string>();
  static const std::map<int,std::string>& fstats() {
    if ( stats_lu.empty() ) { 
      stats_lu[(int)Mean]    = "Mean";
      stats_lu[(int)Median]  = "Median";
      stats_lu[(int)RMS]     = "RMS";
      stats_lu[(int)Unknown] = "Unknown";
    }
    return stats_lu;
  }

  ///////////////////////////////
  // Lookup enumerator -> name //
  ///////////////////////////////

  // returns "Unknown" if numerator value not found (casted as integer)
  static const std::string& lookupStats(Stats s) {
    const std::map<int,std::string>& lmap = fstats();
    std::map<int,std::string>::const_iterator fmap(lmap.find((int)s));
    if ( fmap == fstats().end() ) { fmap = lmap.find((int)Unknown); }
    return fmap->second;
  }

  ///////////////////////////////////////////////////
  // Get mean, median, or rms with symmetric error //
  ///////////////////////////////////////////////////

  // Calculates the requested variable and the associated statistical uncertainty.
  // Default calculation is "Mean".
  // Returns "true" if everything is ok, together with the requested value in "m" and error in "dm".
  static bool stats(TH1D* h,double& m,double& dm,Stats s=Mean)
  {
    bool rf(false);
    double w(0.);
    double prob(0.5);
    //
    switch (s) 
      {
      case Mean:
	m  = h->GetMean();
	dm = h->GetMeanError();
	rf = true;
	break;
      case Median:
	h->ComputeIntegral();
	h->GetQuantiles(1,&m,&prob);
	dm = 0.;
	for ( int i(1); i<=h->GetNbinsX(); ++i ) { 
	  double x(h->GetBinCenter(i));
	  double y(h->GetBinContent(i));
	  dm += y*(x-m)*(x-m);
	  w  += y;
	}
	rf = w > 0.;
	dm = rf ? sqrt(dm/w) : 0.;
	break;
      case RMS:
	m  = h->GetRMS();
	dm = h->GetRMSError();
	rf = true;
	break;
      default:
	break;
      }
    return rf;
  }

  ////////////////////////////////////////////////
  // Get mean and median with asymmetric errors //
  ////////////////////////////////////////////////

  // Calculates the requested variable and the associated statistical uncertainty.
  // Only implemented calculations are "Median" and "Mean", with default "Mean".
  // Returns "true" if everything is ok, together with the requested value in "m", the down error in "dl", and the up error in "dh".
  static bool stats(TH1D* h,double& m,double& dl,double& dh,Stats s=Mean,const std::string& opt="RMS")
  {
    static const std::vector<std::string> _knownOpts = { "ERROR", "RMS" };
    // check options
    if ( std::find(_knownOpts.begin(),_knownOpts.end(),opt) == _knownOpts.end() ) { 
      printf("[HistUtils::stats(...)] ERROR unknown option \042%s\042, use \042ERROR\042 or \042RMS\042\n",opt.c_str());
      return false;
    }
    bool rf(false);
    double prob(0.5);
    switch (s)
      {
      case Mean:
	m  = h->GetMean();
	rf = true;
	break;
      case Median:
	h->ComputeIntegral();
	h->GetQuantiles(1,&m,&prob);
	rf = true;
	break;
      default:
	break;
      }
    // 
    if ( rf ) { 
      dl = 0.;
      dh = 0.;
      double wl(0.);
      double wh(0.);
      for ( int ib(1); ib<=h->GetNbinsX(); ++ib ) {
	double x(h->GetBinCenter(ib));
	double dx(x-m);
	double y(h->GetBinContent(ib));
	if ( x < m ) { 
	  dl += y*dx*dx; wl += y; 
	} else {
	  dh += y*dx*dx; wh += y; 
	}
      }
      if ( wl > 0. ) { 
	dl = TMath::Sqrt(TMath::Abs(dl)/wl);
	if ( opt == "ERROR" ) { dl /= TMath::Sqrt(wl); }
      } else { 
	dl = 0.; 
      }
      if ( wh > 0. ) { 
	dh = TMath::Sqrt(TMath::Abs(dh)/wh);
	if ( opt == "ERROR" ) { dh /= TMath::Sqrt(wh); }
      } else { 
	dh = 0.; 
      }
    }
    return rf;      
  }

  ///////////////////////////////////////////////////////////
  // Get list of projections (as list of 1-dim histograms) //
  ///////////////////////////////////////////////////////////

  // Returns vector filled with valid pointers to TH1D histogram objects. 
  // Needs a name and an axis indicator (1 - x,2 - y) for the projections.
  typedef std::tuple<TH1D*,int> slice_t;
  typedef std::vector<slice_t>  vslice_t;
  static vslice_t extract(TH2D* d,const std::string& name,int alongAxis,double minEntries=-1.)
  {
    vslice_t hists;
    // projection along x axis 
    if ( alongAxis == 1 ) {
      //     printf("HistUtils::extract() loop %i projections\n",d->GetNbinsY());
      for ( int ib(1); ib<=d->GetNbinsY(); ++ib ) {
	TH1D* hptr = d->ProjectionX(TString::Format("%s_%04i",name.c_str(),ib).Data(),ib,ib,"e");
	if ( hptr->GetEntries() > minEntries ) { hists.push_back( { hptr, ib } ); }
      }
      return hists;
    }
    // distribution along y axis
    if ( alongAxis == 2 ) {
      //      printf("HistUtils::extract() loop %i projections\n",d->GetNbinsX());
      for ( int ib(1); ib<=d->GetNbinsX(); ++ib ) { 
	TH1D* hptr = d->ProjectionY(TString::Format("%s_%04i",name.c_str(),ib).Data(),ib,ib,"e");
	if ( hptr->GetEntries() > minEntries ) { hists.push_back( { hptr, ib } ); }
      }
      return hists;
    }
    // 
    return hists;  
  }

  //////////////////////////////////////
  // Collect data points into a graph //
  //////////////////////////////////////

  // Projects along the given axis (1 - x, 2 - y) and extracts requested variable and associated asymmetric errors
  // Returns a TGraphAsymmErrors object holding the graph and the up/down and left/right errors for each point.
  static TGraphAsymmErrors* graph(TH2D* d,const std::string& name,int alongAxis,Stats s=Mean,const std::string& opt="RMS",double minEntries=-1.)
  {
    printf("graph(...) enter with TH2D* = %p, name = \042%s\042, axis = %i, Stats = %s",
	   (void*)d,name.c_str(),alongAxis,lookupStats(s).c_str());
    std::vector<std::tuple<TH1D*,int> > hists = extract(d,name,alongAxis,minEntries);
    if ( hists.empty() ) { 
      printf(" - failed, no projections with at least %.1f entries found\n",minEntries); return (TGraphAsymmErrors*)0; 
    } else { 
      printf(" - succeeded, found %zu projections with at least %.1f entries\n",hists.size(),minEntries); 
    } 
    //printf("graph(...) extracted %i projections...\n",(int)hists.size());
    TGraphAsymmErrors* gptr = 0;
    if ( hists.empty() ) { return gptr; }
    //
    int nb(0);
    std::vector<double> x  (hists.size(),0.);   
    std::vector<double> dxl(hists.size(),0.);   
    std::vector<double> dxh(hists.size(),0.);   
    std::vector<double> y  (hists.size(),0.);   
    std::vector<double> dyl(hists.size(),0.);   
    std::vector<double> dyh(hists.size(),0.);    
    switch ( alongAxis )
      {
      case 1:
	// nb = d->GetNbinsY();
	// for ( int i(1); i<=nb; ++i ) { 
	//   stats(hists.at(i-1),y[i-1],dyl[i-1],dyh[i-1],s,opt);
	//   x[i-1]   = d->GetYaxis()->GetBinCenter(i);
	//   dxl[i-1] = d->GetYaxis()->GetBinWidth(i)/2.;
	//   dxh[i-1] = dxl[i-1];
	// } 
	for ( size_t i(0); i<hists.size(); ++i ) { 
	  stats(std::get<0>(hists.at(i)),y[i],dyl[i],dyh[i],s,opt);
	  x[i]   = d->GetYaxis()->GetBinCenter(std::get<1>(hists.at(i)));
	  dxl[i] = d->GetYaxis()->GetBinWidth (std::get<1>(hists.at(i)))/2.;
	  dxh[i] = dxl[i];
	} 
	gptr = new TGraphAsymmErrors((int)hists.size(),&x[0],&y[0],&dxl[0],&dxh[0],&dyl[0],&dyh[0]);
	break;
      case 2:
	// nb  = d->GetNbinsX();
	// for ( int i(1); i<=nb; ++i ) { 
	//   stats(hists.at(i-1),y[i-1],dyl[i-1],dyh[i-1],s,opt);
	//   x[i-1]   = d->GetXaxis()->GetBinCenter(i);
	//   dxl[i-1] = d->GetXaxis()->GetBinWidth(i)/2.;
	//   dxh[i-1] = dxl[i-1];
	// } 
	for ( size_t i(0); i<hists.size(); ++i ) { 
	  stats(std::get<0>(hists.at(i)),y[i],dyl[i],dyh[i],s,opt);
	  x[i]   = d->GetXaxis()->GetBinCenter(std::get<1>(hists.at(i)));
	  dxl[i] = d->GetXaxis()->GetBinWidth (std::get<1>(hists.at(i)))/2.;
	  dxh[i] = dxl[i];
	} 
	gptr = new TGraphAsymmErrors((int)hists.size(),&x[0],&y[0],&dxl[0],&dxh[0],&dyl[0],&dyh[0]);
	break;
      default:
	break;
      }
    return gptr;
  }

  ///////////////////
  // File handling //
  ///////////////////

  static TFile* rootFile = (TFile*)0;

  static TFile*      getFile() { return rootFile; }
  static std::string getFileName() { return rootFile == 0 ? std::string("<file_not_open>") : std::string(rootFile->GetName()); }
  static bool        fileOpen() { return getFile() != 0; }

  static TFile* openFile(const std::string& fname,const std::string& opt="RECREATE") {
    static std::string _mname = "HistUtils::openFile";
    std::string fn = fname.find(".root") == std::string::npos ? fname + ".root" : fname; 
    if ( fileOpen() ) { 
      std::string stat("UNKNOWN");
      if ( opt == "RECREATE" || opt == "recreate" || 
	   opt == "WRITE"    || opt == "write"    ||
	   opt == "READ"     || opt == "read"      ) { stat = opt; }
      printf("[%s] WARNING attempt to open file \042%s\042 with status <%s> failed - file \042%s\042 already assigned",_mname.c_str(),fn.c_str(),stat.c_str(),rootFile->GetName());
      return (TFile*)0;
    } 
    rootFile = new TFile(fn.c_str(),opt.c_str());
    std::string frame;
    for ( size_t i(0); i<fn.length(); ++i ) { frame += "#"; }
    if ( rootFile != 0 ) { 
      //                    File "  " opened for output #
      printf("[%s] INFO ########%s#####################"      ,_mname.c_str(),frame.c_str());
      printf("[%s] INFO # File \042%s\042 opened for output #",_mname.c_str(),fn.c_str());
      printf("[%s] INFO ########%s#####################"      ,_mname.c_str(),frame.c_str());
    } else {
      //                     File "  " could not be opend for output #"
      printf("[%s] ERROR ########%s#################################"       ,_mname.c_str(),frame.c_str());
      printf("[%s] ERROR # File \042%s\042 could not be opened for output #",_mname.c_str(),fn.c_str());
      printf("[%s] ERROR ########%s#################################"       ,_mname.c_str(),frame.c_str());
    }
    return rootFile;
  }

  static bool closeFile() {
    static std::string _mname = "HistUtils::closeFile";
    if ( rootFile != 0 ) { 
      printf("[%s] INFO file \042%s\042 closing",_mname.c_str(),getFileName().c_str());
      rootFile->Close(); delete rootFile; rootFile = (TFile*)0; return true; 
    } else {
      printf("[%s] WARNING closing file request without any file open",_mname.c_str());
      return false;
    }
  }

  ////////////////////////////
  // Integrate/scale 2-dims //
  ////////////////////////////

  // Scales entries in 2-dim histogram by factor given in "scale" 
  static bool scale2D(TH2D* h,double scale)
  {
    for ( int i(1); i<h->GetNbinsX(); ++i ) { 
      for ( int j(1); j<h->GetNbinsY(); ++j ) {
	int k = h->GetBin(i,j);
	double y(h->GetBinContent(k));
	double dy(h->GetBinError(k));
	y *= scale; dy *= scale;
	h->SetBinContent(k,y);
	h->SetBinError(k,dy);
      }
    }
    return true;
  } 

  //
  static const std::string printDir = "./pdf";
  static const std::string printExt = "pdf";
  static std::string printFile(const std::string& pre,const std::string& post,const std::string& ext=printExt)
  { return printDir+"/"+pre+"_"+post+"."+ext; }
  //
  static double mean(TGraph* gr,double xmin,double xmax)
  {
    if ( gr == 0 )  { return 0.; }
    double* xval = gr->GetX();
    double* yval = gr->GetY();
    double mean(0.); int nctr(0);
    for ( int i(0); i<gr->GetN(); ++i ) {
      if ( xval[i]>xmin && xval[i]<xmax ) { mean += yval[i]; ++nctr; }
    }
    return nctr > 0 ? mean/((double)nctr) : 0.;
  }
  //
  static std::string formStr(const std::string& dirn,const std::string& pref,const std::string& tag)
  { return dirn != "" 
      ? std::string(TString::Format("%s/%s_%s",dirn.c_str(),pref.c_str(),tag.c_str()).Data())
      :  std::string(TString::Format("%s_%s",pref.c_str(),tag.c_str()).Data()); }
  static std::string formStr(const std::string& dirn,const std::string& pref,const std::string& tag,const std::string& postf)
  { return std::string(TString::Format("%s_%s",formStr(dirn,pref,tag).c_str(),postf.c_str()).Data()); }
  //
  static void drawCaloBounds(double ymin,double ymax,int ndc) 
  {
    static std::vector<double>      _bounds  = { -4.9, -3.2, -2.5, -1.475, 1.475, 2.5, 3.2, 4.9 };
    static std::vector<std::string> _calos   = { "FCal", "EC coarse", "EC fine", "Central fine", "EC fine", "EC coarse", "FCal" };
    static std::vector<int>         _bgcolor = { kYellow-10, kGreen-10, kCyan-10, kWhite, kCyan-10, kGreen-10, kYellow-10 };  
    static std::vector<int>         _txcolor = { kRed,       kGreen+3,  kBlue,    kBlack, kBlue,    kGreen+3,  kRed       };  
    static int                     _palette[100];
    static double                  _r[] = { 0.00, 0.00, 0.50, 1.00 };
    static double                  _g[] = { 1.00, 0.50, 0.00, 0.00 };
    static double                  _b[] = { 0.00, 0.50, 0.50, 0.00 };
    static double                  _s[] = { 0.00, 0.33, 0.66, 1.00 };

    int fi = TColor::CreateGradientColorTable(4,_s,_r,_g,_b,4);
    for ( int k(0); k<4;++k )
      {}

    for ( size_t i(1); i<_bounds.size(); ++i ) {
      // draw the boundary
      //      if ( i < _bounds.size() ) { 
	// TLine* l = new TLine(_bounds.at(i),ymin,_bounds.at(i),ymax);
	// l->SetLineWidth(2);
	// l->SetLineStyle(1);
	// l->SetLineColor(kGray);
	// l->Draw("same");
	TBox* b = new TBox(_bounds.at(i-1),ymin,_bounds.at(i),ymax);
	b->SetFillColor(_bgcolor.at(i-1));
	b->SetLineColor(0);
	b->SetLineWidth(0);
	b->Draw("same");
	//	printf("HistUtils::drawCaloBounds - boundary of calo \042%s\042: (%5.2f,%5.2f)-(%5.2f,%5.2f), color code %i\n",_calos.at(i-1).c_str(),_bounds.at(i-1),ymin,_bounds.at(i),ymax,_bgcolor.at(i-1));
	//      }
    }

    TLatex tl;
    tl.SetTextAlign(23);
    tl.SetTextSize(0.65*tl.GetTextSize());
    double yt(0.925*ymax);
    double ty(0.85*ymax);
    for ( size_t i(1); i<_bounds.size(); ++i ) { 
      // 
      double xt((_bounds.at(i-1)+_bounds.at(i))/2.);
      //      printf("HistUtils::drawCaloBounds - boundary of calo \042%s\042: (%5.2f,%5.2f)-(%5.2f,%5.2f), center (%5.2f,%5.2f)\n",_calos.at(i-1).c_str(),_bounds.at(i-1),ymin,_bounds.at(i),ymax,xt,yt);
      tl.SetTextColor(_txcolor.at(i-1));
      if ( i % 2 == 0 ) { tl.DrawLatex(xt,yt,_calos.at(i-1).c_str()); } else { tl.DrawLatex(xt,ty,_calos.at(i-1).c_str()); }
    }
  }

  ////////////
  // Colors //
  ////////////

  namespace Color {
    constexpr int blue    = kBlue; 
    constexpr int red     = kRed; 
    constexpr int green   = kGreen;
    constexpr int black   = kBlack;
    constexpr int white   = kWhite;
    constexpr int grey    = kGray; 
    constexpr int pink    = kPink; 
    constexpr int magenta = kMagenta;
    constexpr int violet  = kViolet; 
    constexpr int orange  = kOrange; 
    constexpr int spring  = kSpring; 
    constexpr int teal    = kTeal;
    constexpr int cyan    = kCyan; 
    constexpr int azure   = kAzure; 
    constexpr int yellow  = kYellow; 
    constexpr int brown   = red+4; 
    namespace Light { 
      constexpr int blue    = kBlue-10; 
      constexpr int red     = kRed-10; 
      constexpr int green   = kGreen-10;
      constexpr int black   = kGray;
      constexpr int white   = kWhite;
      constexpr int grey    = kGray; 
      constexpr int pink    = kPink; 
      constexpr int magenta = kMagenta-10;
      constexpr int violet  = kViolet-9; 
      constexpr int orange  = kOrange-9; 
      constexpr int spring  = kSpring+10; 
      constexpr int teal    = kTeal-4;
      constexpr int cyan    = kCyan-10; 
      constexpr int azure   = kAzure-9; 
      constexpr int yellow  = kYellow-10; 
      constexpr int brown   = red-5; 
    } //HistUtils::Color::Light
  } // HistUtils::Color
  namespace Format {
    static std::string fmtEng(double value,int ndigits,int nval,bool numeric=true) {
#define MICRO "µ"
#define PREFIX_START (-24) // Smallest power of ten for which there is a prefix defined. If the set of prefixes will be extended, change this constant and update the table "prefix".
      static std::vector<std::string> prefix = { "y", "z", "a", "f", "p", "n", MICRO, "m", "", "k", "M", "G", "T", "P", "E", "Z", "Y" }; 
#define PREFIX_END PREFIX_START+(prefix.size()*3)
      static char result[512];
      int expof10;
      // trivial return
      if (value == 0.) { return std::string("0.0"); }
      // negative number
      std::string rstr;
      if ( value < 0. ) { rstr += std::string("-"); value = std::abs(value); }
      //
      // log10(value)     expof10    log10(value)   expof10
      //      1              0          -1           -3       
      //      2              0          -2           -3
      //      3              3          -3           -6
      //      4              3          -4           -6
      //      5              3          -5           -6
      //      6              6          -6           -9        
      //     ...            ...         ...          ...   
      expof10  =  (int)std::log10(value); if( expof10 > 0 ) { expof10 = (expof10/3)*3; } else if ( expof10 < 0 ) { expof10 = (-expof10+3)/3*(-3); } 
      if ( expof10 != 0 ) { value   *= std::pow(10,-expof10); } // DIVISION - expof10 may be negative!
      // reduce to smallest decade
      while ( value >= 1000. ) { value /= 1000.; expof10 += 3; }
      // construct final string 
      if ( numeric || (expof10 < static_cast<int>(PREFIX_START) ) || (expof10 > static_cast<int>(PREFIX_END)) ) {
	if ( expof10 > 0 ) {  
	  sprintf(result, "%*.*fe+%02i",nval+ndigits+1,ndigits,value,std::abs(expof10));
	} else if ( expof10 < 0 ) { 
	  sprintf(result, "%*.*fe-%02i",nval+ndigits+1,ndigits,value,std::abs(expof10));
	} else {
	  sprintf(result, "%*.*f",nval+ndigits+1,ndigits,value);
	}
      } else {
	size_t idx((expof10-PREFIX_START)/3);
	if ( idx < prefix.size() ) { 
	  sprintf(result, "%*.*f %s", nval+ndigits+1, ndigits, value, prefix.at(idx).c_str());
	} else { 
	  sprintf(result, "%*.*f [UNKNOWN]", nval+ndigits+1, ndigits, value);
	}
      }
      rstr += std::string(result); 
      return rstr;
    }
    static std::string fmtNumber(double value) { return fmtEng(value,3,3); } 
  } // HistUtils::Format
} // HistUtils
#endif
