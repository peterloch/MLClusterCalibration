// -*- c++ -*-
#ifndef HISTMANAGER_H
#define HISTMANAGER_H

#include <TH1.h>
#include <TDirectory.h>

#include <string>
#include <map>
#include <iostream>

#include <vector>
#include <tuple>

#include <cstdio>

class HistManager {
private:
  static HistManager*        _instance;
public:
  // type definitions
  typedef std::tuple<std::string,std::string> hkey_t;
  typedef std::map<hkey_t,TH1*>               hmap_t; 
  typedef hmap_t::size_type                   hsize_t;
  // key encoding/decoding
  const std::string& directoryName(const hkey_t& key) const { return std::get<0>(key); }
  std::string&       directoryName(hkey_t& key)             { return std::get<0>(key); }
  const std::string& histogramName(const hkey_t& key) const { return std::get<1>(key); }
  std::string&       histogramName(hkey_t& key)             { return std::get<1>(key); }
private:
  hmap_t      _cache;
  int         _nwidth     = { 0    }; // histogram name length (max)
  int         _dwidth     = { 0    }; // directory name length (max)
  static std::string _defDirName;
  // make directory (if needed) and change to it 
  TDirectory*                f_changeDir(TDirectory* baseDir,const std::string& dname) {
    if ( baseDir == nullptr ) { printf("[HistManager::f_changeDir(...)] WARN invalid base directory pointer (%p)",(void*)baseDir); return (TDirectory*)0; }
    TDirectory* pdir = baseDir->mkdir(dname.c_str(),dname.c_str(),true);
    if ( pdir == nullptr )    { printf("[HistManager::f_changeDir(...)] WARN cannot change to/create directory \042%s/%s\042",baseDir->GetName(),dname.c_str()); } else { pdir->cd(); }
    return pdir; 
  }
  TDirectory*                f_changeDir(const std::string& dname) { return f_changeDir(TDirectory::CurrentDirectory(),dname); } 
public:
  // singleton accessor 
  static HistManager* instance() { if ( _instance == nullptr ) { _instance = new HistManager(); } return _instance; }
  // adding a histogram
  template<class H> bool add(H* hptr,const std::string& dname=_defDirName) { 
    if ( hptr == nullptr ) { return false; }
    std::string hname(hptr->GetName());
    hkey_t key = dname != "" ? hkey_t(dname,hname) : hkey_t(_defDirName,hname);  
    if ( _cache.find(key) == _cache.end() || (_cache.find(key) != _cache.end() && _cache.at(key) == nullptr ) ) { 
      _cache[key] = hptr; 
      _nwidth = std::max(_nwidth,(int)hname.length()); 
      _dwidth = std::max(_dwidth,(int)dname.length()); 
      return true; 
    } else { 
      return false;
    } 
  }
  // size of cache
  size_t size()  const { return _cache.size();  }
  // cache empty indicator
  bool   empty() const { return _cache.empty(); }
  // clean up cache (removal of nullptr)
  int    clean() { auto fcache(_cache.begin()); int iclean(0); while ( fcache != _cache.end() ) { if ( fcache->second == nullptr ) { fcache = _cache.erase(fcache); ++iclean; } else { ++fcache; } }; return iclean; }
  // print actual cache content - includes cleanup
  std::ostream& print(std::ostream& ostr) const { 
    static char _buffer[1024];
    ostr << std::endl;
    sprintf(_buffer,"[HistManager][INFO] %zu known distributions:",size()); ostr << _buffer << std::endl;
    int lwid((int)std::log10((double)size())+1);
    int ientry(1);
    int twidth(_dwidth+_nwidth+1);
    std::string listing; 
    for ( auto entry : _cache ) {
      listing  = directoryName(entry.first) != _defDirName
	? directoryName(entry.first)+std::string("/")+histogramName(entry.first)
	: histogramName(entry.first);
      sprintf(_buffer,"[HistManager][INFO][%*i] distribution %-*.*s at %p",lwid,ientry++,twidth,twidth,listing.c_str(),(void*)entry.second); 
      ostr << _buffer << std::endl;
    }
    ostr << std::endl;
    return ostr; 
  }
  // write out histograms in cache
  int write(bool noEmpties=true) {
    // clean up cache (remove nullptr entries) 
    clean(); 
    // prepare write
    TDirectory* basedPtr = TDirectory::CurrentDirectory(); // remember base directory
    int iwrite(0);                                         // reset written histograms counter
    // write only Nentries > 0
    std::string dname; std::string hname;
    TDirectory* actdPtr = (TDirectory*)0;
    if ( noEmpties ) { 
      for ( auto entry : _cache ) {
	dname = directoryName(entry.first); hname = histogramName(entry.first); // unpacking the key 
	auto hptr = entry.second;                                               // accessing the payload (histogram pointer
	if ( hptr->GetEntries() != 0. ) {                                       // check if histogram has entries
	  if ( dname != _defDirName ) {                                         // write only directories that do not have the default (no directory) name
	    actdPtr = f_changeDir(basedPtr,dname);                              // -- create directory in case it does not exist in the path and change to it
	    hptr->Write(); ++iwrite;                                            // -- write the histogram and increase count
	    basedPtr->cd();                                                     // -- return to base directory
	  } else {                                                              // write into current (externally defined) directory
	    hptr->Write(); ++iwrite;                                            // -- write histogram and increase count
	  } // directory management
	} // entries > 0
      } // loop on cache
    } else { 
      for ( auto entry : _cache ) { 
	dname = directoryName(entry.first); hname = histogramName(entry.first); // unpacking the key 
	auto hptr = entry.second;                                               // accessing the payload (histogram pointer
	if ( dname != _defDirName ) {                                           // write only directories that do not have the default (no directory) name
	  actdPtr = f_changeDir(basedPtr,dname);                                // -- create directory in case it does not exist in the path and change to it
	  hptr->Write(); ++iwrite;                                              // -- write the histogram and increase count
	  basedPtr->cd();                                                       // --return to base directory
	} else {                                                                // write into current (externally defined) directory
	  hptr->Write(); ++iwrite;                                              // -- write histogram and increase count
	} // directory management
      } // loop on cache
    } // check on entrie 
    return iwrite; 
  }
};

HistManager* HistManager::_instance = (HistManager*)0; 

std::string HistManager::_defDirName = "UNKNOWN_DIRECTORY";

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
 
  template<class H> bool registerDist(H* hptr,const std::string& dname) { return HistManager::instance()->add(hptr,dname); }
  template<class H> bool registerDist(H* hptr)                          { return HistManager::instance()->add(hptr);       }

  ///////////////////////
  // Booking templates //
  ///////////////////////

  // -- add axis labels
  template<class H> bool addAxisLabels(H* hptr,const std::string& axtitle,const std::string& aytitle="",const std::string& aztitle="") {
    if ( hptr == nullptr ) { return false; }
    bool setFlag(false); 
    if ( axtitle != "" ) { hptr->GetXaxis()->SetTitle(axtitle.c_str()); setFlag = true; }
    if ( aytitle != "" ) { hptr->GetYaxis()->SetTitle(aytitle.c_str()); setFlag = true; }
    if ( aztitle != "" ) { hptr->GetZaxis()->SetTitle(aztitle.c_str()); setFlag = true; }
    return setFlag;
  }

  /////////////////////////
  // 1-dim, no directory //
  /////////////////////////

  // -- equidistant bining 
  template<class H> H* book(const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,const std::string& axtitle="",const std::string& aytitle="") {
    if ( xbin < 1 ) { return (H*)0; }
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle); registerDist(hptr); } 
    return hptr; 
  }
  // -- irregular binning
  template<class H> H* book(const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,const std::string& axtitle="",const std::string& aytitle="") {
    if ( xbins.size() < 2 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0)); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle); registerDist(hptr); } 
    return hptr; 
  }

  ///////////////////////////
  // 1-dim, with directory //
  ///////////////////////////

  // -- equidistant bining 
  template<class H> H* book(const std::string& dname,const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,const std::string& axtitle="",const std::string& aytitle="") {
    if ( xbin < 1 ) { return (H*)0; } 
    auto baseDirPtr = TDirectory::CurrentDirectory();
    auto actDirPtr  = baseDirPtr->mkdir(dname.c_str(),dname.c_str(),true); actDirPtr->cd(); 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle); registerDist(hptr,dname); } 
    baseDirPtr->cd();
    return hptr; 
  }
  // -- irregular binning
  template<class H> H* book(const std::string& dname,const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,const std::string& axtitle="",const std::string& aytitle="") {
    if ( xbins.size() < 2 ) { return (H*)0; }
    auto baseDirPtr = TDirectory::CurrentDirectory(); 
    auto actDirPtr  = baseDirPtr->mkdir(dname.c_str(),dname.c_str(),true); actDirPtr->cd();  
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0)); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle); registerDist(hptr,dname); }
    baseDirPtr->cd(); 
    return hptr; 
  }
  
  /////////////////////////
  // 2-dim, no directory //
  /////////////////////////

  // -- equidistant binning in (x,y)
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,int ybin,double ymin,double ymax,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbin < 1 || ybin < 1 ) { return (H*)0; }
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax,ybin,ymin,ymax); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr); } 
    return hptr; 
  }
  // -- irregular binning in x, equidistant binning in y
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,int ybin,double ymin,double ymax,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbins.size() < 2 || ybin < 1 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0),ybin,ymin,ymax); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr); }
    return hptr; 
  }
  // -- irregular binning in (x,y)
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,const std::vector<double>& ybins,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbins.size() < 2 || ybins.size() < 2 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0),ybins.size()-1,&ybins.at(0)); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr); } 
    return hptr; 
  }
  // -- equidistant binning in x, irregular binning in y
  template<class H>
  H* book(const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,const std::vector<double>& ybins,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbin < 1 || ybins.size() < 2 ) { return (H*)0; } 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax,ybins.size()-1,&ybins.at(0)); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr); } 
    return hptr; 
  }
  
  ///////////////////////////
  // 2-dim, with directory //
  ///////////////////////////

  // -- equidistant binning in (x,y)
  template<class H>
  H* book(const std::string& dname,const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,int ybin,double ymin,double ymax,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbin < 1 || ybin < 1 ) { return (H*)0; }
    auto baseDirPtr = TDirectory::CurrentDirectory();
    auto actDirPtr  = baseDirPtr->mkdir(dname.c_str(),dname.c_str(),true); actDirPtr->cd(); 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax,ybin,ymin,ymax); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr,dname); } 
    baseDirPtr->cd();
    return hptr; 
  }
  // -- irregular binning in x, equidistant binning in y
  template<class H>
  H* book(const std::string& dname,const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,int ybin,double ymin,double ymax,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbins.size() < 2 || ybin < 1 ) { return (H*)0; } 
    auto baseDirPtr = TDirectory::CurrentDirectory();
    auto actDirPtr  = baseDirPtr->mkdir(dname.c_str(),dname.c_str(),true); actDirPtr->cd(); 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0),ybin,ymin,ymax); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr,dname); }
    baseDirPtr->cd();
    return hptr; 
  }
  // -- irregular binning in (x,y)
  template<class H>
  H* book(const std::string& dname,const std::string& hname,const std::string& htitle,const std::vector<double>& xbins,const std::vector<double>& ybins,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbins.size() < 2 || ybins.size() < 2 ) { return (H*)0; } 
    auto baseDirPtr = TDirectory::CurrentDirectory();
    auto actDirPtr  = baseDirPtr->mkdir(dname.c_str(),dname.c_str(),true); actDirPtr->cd(); 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbins.size()-1,&xbins.at(0),ybins.size()-1,&ybins.at(0)); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr,dname); } 
    baseDirPtr->cd();
    return hptr; 
  }
  // -- equidistant binning in x, irregular binning in y
  template<class H>
  H* book(const std::string& dname,const std::string& hname,const std::string& htitle,int xbin,double xmin,double xmax,const std::vector<double>& ybins,const std::string& axtitle="",const std::string& aytitle="",const std::string& aztitle="") { 
    if ( xbin < 1 || ybins.size() < 2 ) { return (H*)0; } 
    auto baseDirPtr = TDirectory::CurrentDirectory();
    auto actDirPtr  = baseDirPtr->mkdir(dname.c_str(),dname.c_str(),true); actDirPtr->cd(); 
    H* hptr = new H(hname.c_str(),htitle.c_str(),xbin,xmin,xmax,ybins.size()-1,&ybins.at(0)); if ( hptr != nullptr ) { hptr->Sumw2(); addAxisLabels(hptr,axtitle,aytitle,aztitle); registerDist(hptr,dname); } 
    baseDirPtr->cd();
    return hptr; 
  }

  ///////////////////
  // Other helpers //
  ///////////////////

  // -- messaging
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
