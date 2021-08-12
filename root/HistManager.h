// -*- c++ -*-
#ifndef HISTMANAGER_H
#define HISTMANAGER_H

#include <string>
#include <map>
#include <iostream>

#include <vector>
#include <tuple>

#include <TH1.h>

#include <cstdio>

class HistManager {
private:
  static HistManager*        _instance;
  std::map<std::string,TH1*> _cache;
  int                        _nwidth = { 0 };
public:
  typedef std::map<std::string,TH1*>::size_type size_type; 
  static HistManager* instance() { if ( _instance == nullptr ) { _instance = new HistManager(); } return _instance; }
  template<class H>
  bool add(H* hptr) { 
    if ( hptr == 0 ) { return false; }
    std::string hname(hptr->GetName());
    if ( _cache.find(hname) == _cache.end() || (_cache.find(hname) != _cache.end() && _cache.at(hname) == nullptr ) ) { _cache[hname] = hptr; _nwidth = std::max(_nwidth,(int)hname.length()); return true; }
    return false; 
  }
  size_t size()  const { return _cache.size();  }
  bool   empty() const { return _cache.empty(); }
  int    clean() { auto fcache(_cache.begin()); int iclean(0); while ( fcache != _cache.end() ) { if ( fcache->second == nullptr ) { fcache = _cache.erase(fcache); ++iclean; } else { ++fcache; } }; return iclean; }
  std::ostream& print(std::ostream& ostr) const { 
    static char _buffer[1024];
    ostr << std::endl;
    sprintf(_buffer,"[HistManager][INFO] %zu known distributions:",size()); ostr << _buffer << std::endl;
    int lwid((int)std::log10((double)size())+1);
    int ientry(1);
    for ( auto entry : _cache ) { 
      sprintf(_buffer,"[HistManager][INFO][%*i] distribution %-*.*s at %p",lwid,ientry++,_nwidth,_nwidth,entry.first.c_str(),(void*)entry.second); ostr << _buffer << std::endl;
    }
    ostr << std::endl;
    return ostr; 
  }
  int write(bool noEmpties=true) { 
    clean(); 
    int iwrite(0); 
    if ( noEmpties ) { 
      for ( auto entry : _cache ) { if ( entry.second->GetEntries() != 0. ) {  entry.second->Write(); ++iwrite; } }
    } else { 
      for ( auto entry : _cache ) { entry.second->Write(); ++iwrite; }
    }
    return iwrite; 
  }
};

HistManager* HistManager::_instance = (HistManager*)0; 

std::ostream& operator<<(std::ostream& ostr,const HistManager& hmgr) { return hmgr.print(ostr); }

namespace Hist {
  //                   +------------------------------------------- entry <0> EM  response vs cluster energy   
  //                   |     +------------------------------------- entry <1> LCW response vs cluster energy
  //                   |     |     +------------------------------- entry <2> MLC response vs cluster energy
  //                   |     |     |     +------------------------- entry <3> EM  response vs energy fraction of cluster in jet
  //                   |     |     |     |     +------------------- entry <4> LCW response vs energy fraction of cluster in jet
  //                   |     |     |     |     |     +------------- entry <5> MLC response vs energy fraction of cluster in jet
  //                   |     |     |     |     |     |     +------- entry <6> LCW rapidity of cluster
  //                   |     |     |     |     |     |     |     +- entry <7> EM energy of cluster
  //                   |     |     |     |     |     |     |     |
  typedef std::tuple<TH2D*,TH2D*,TH2D*,TH2D*,TH2D*,TH2D*,TH1D*,TH1D*> DistributionList;

  // fill distributions in list
  // static void fill(DistributionList& dlist,int ipos,double xval,double yval,double weight=1.) {
  //   switch ( ipos ) {
  //   case 0:  std::get<0>(dlist)->Fill(xval,yval,weight); break;
  //   case 1:  std::get<1>(dlist)->Fill(xval,yval,weight); break;
  //   case 2:  std::get<2>(dlist)->Fill(xval,yval,weight); break;
  //   case 3:  std::get<3>(dlist)->Fill(xval,yval,weight); break;
  //   case 4:  std::get<4>(dlist)->Fill(xval,yval,weight); break;
  //   case 5:  std::get<5>(dlist)->Fill(xval,yval,weight); break;
  //   case 6:  std::get<6>(dlist)->Fill(xval,     weight); break;
  //   case 7:  std::get<7>(dlist)->Fill(xval,     weight); break;
  //   default: break;
  //   }
  // }

  // // specialization
  // static void fill1d(DistributionList& dlist,double xval,double weight=1.) {
  //   switch ( ipos ) { 
  //   case 6: std::get<6>(dlist)->Fill(xval,weight); break;
  //   case 7: std::get<7>(dlist)->Fill(xval,weight); break;
  //   default: break;
  //   }
  // }

  // fill templates
  template<int N> static void fill1d(DistributionList& dlist,double xval,            double weight=1.) { std::get<N>(dlist)->Fill(xval,     weight); }
  template<int N> static void fill2d(DistributionList& dlist,double xval,double yval,double weight=1.) { std::get<N>(dlist)->Fill(xval,yval,weight); }
  // specialization for 1-dim histograms
  // template<> static void fill<6>(DistributionList& dlist,double xval,double weight=1.) { std::get<6>(dlist)->Fill(xval,weight); }
  // template<> static void fill<7>(DistributionList& dlist,double xval,double weight=1.) { std::get<7>(dlist)->Fill(xval,weight); }

  HistManager* mgr() { return HistManager::instance(); }
 
  template<class H> bool registerDist(H* hptr) { return HistManager::instance()->add(hptr); }
  template<class H> bool addAxisLabels(H* hptr,const std::string& axtitle,const std::string& aytitle="",const std::string& aztitle="") {
    if ( hptr == nullptr ) { return false; }
    bool setFlag(false); 
    if ( axtitle != "" ) { hptr->GetXaxis()->SetTitle(axtitle.c_str()); setFlag = true; }
    if ( aytitle != "" ) { hptr->GetYaxis()->SetTitle(aytitle.c_str()); setFlag = true; }
    if ( aztitle != "" ) { hptr->GetZaxis()->SetTitle(aztitle.c_str()); setFlag = true; }
    return setFlag;
  }
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,const std::string& axtitle="",const std::string& aytitle="") {
    if ( xbin < 1 ) { return (H*)0; }
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax); if ( hptr == nullptr ) { return hptr; }
    hptr->Sumw2(); 
    addAxisLabels(hptr,axtitle,aytitle); 
    registerDist(hptr); 
    return hptr; 
  }
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,const std::string& axtitle="",const std::string& aytitle="") {
    if ( xbins.size() < 2 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0)); if ( hptr == nullptr ) { return hptr; }
    hptr->Sumw2(); 
    addAxisLabels(hptr,axtitle,aytitle); 
    registerDist(hptr); 
    return hptr; 
  }
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,int ybin,double ymin,double ymax,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbin < 1 || ybin < 1 ) { return (H*)0; }
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax,ybin,ymin,ymax); if ( hptr == nullptr ) { return hptr; }
    hptr->Sumw2(); 
    addAxisLabels(hptr,axtitle,aytitle,aztitle); 
    registerDist(hptr); 
    return hptr; 
  }
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,int ybin,double ymin,double ymax,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbins.size() < 2 || ybin < 1 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0),ybin,ymin,ymax); if ( hptr == nullptr ) { return hptr; }
    hptr->Sumw2(); 
    addAxisLabels(hptr,axtitle,aytitle,aztitle); 
    registerDist(hptr); 
    return hptr; 
  }
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,const std::vector<double>& ybins,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbins.size() < 2 || ybins.size() < 2 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0),ybins.size()-1,&ybins.at(0)); if ( hptr == nullptr ) { return hptr; }
    hptr->Sumw2(); 
    addAxisLabels(hptr,axtitle,aytitle,aztitle); 
    registerDist(hptr); 
    return hptr; 
  }
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,const std::vector<double>& ybins,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbin < 1 || ybins.size() < 2 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax,ybins.size()-1,&ybins.at(0)); if ( hptr == nullptr ) { return hptr; }
    hptr->Sumw2(); 
    addAxisLabels(hptr,axtitle,aytitle,aztitle); 
    registerDist(hptr); 
    return hptr; 
  }
  template<class I>
  bool printStats(I ientry,I nentry,int ievt,int lwid,const std::string& fmtBuffer) {
    I istep = 
      ientry < 10    ? 1    :
      ientry < 100   ? 10   :
      ientry < 1000  ? 100  :
      ientry < 10000 ? 1000 :
      2000; 
    if ( ientry == 1 || ientry % istep == 0 ) { printf(fmtBuffer.c_str(),(double)(ientry)/(double)nentry*100.,ievt,lwid,ientry,lwid,nentry); return true;}
    return false;
  } 
} // Hist
#endif
