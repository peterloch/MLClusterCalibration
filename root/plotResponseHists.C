
#include <TError.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLegendEntry.h>

#include "HistUtils.h"
#include "PlotConfig.h"

#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <iterator>

#include <chrono>

#include <cstdio>
#include <cmath>
#include <ctime>

#include <iostream>
#include <fstream>

namespace Data {
  namespace Jet  {
    static const Types::Graph::NameGroupMap knownDists = { 
      { "ResponseEdep"        , { "EMR_Edep_incl", "LCR_Edep_incl", "MLR_Edep_incl" } },
      { "ResponseEfrc"        , { "EMR_Efrc_incl", "LCR_Efrc_incl", "MLR_Efrc_incl" } },
      { "ResponseLambda"      , { "EMR_lamb_incl", "LCR_lamb_incl", "MLR_lamb_incl" } },
      { "ResponseLateral"     , { "EMR_lat__incl", "LCR_lat__incl", "MLR_lat__incl" } },
      { "ResponseLongitudinal", { "EMR_long_incl", "LCR_long_incl", "MLR_long_incl" } },
      { "ResponsePtD"         , { "EMR_ptd__incl", "LCR_ptd__incl", "MLR_ptd__incl" } },
      { "ResponseRho"         , { "EMR_rho__incl", "LCR_rho__incl", "MLR_rho__incl" } },
      { "ResponseSignificance", { "EMR_sign_incl", "LCR_sign_incl", "MLR_sign_incl" } },
      { "ResponseTime"        , { "EMR_time_incl", "LCR_time_incl", "MLR_time_incl" } }
    }; 
  }
  namespace Pion { 
    static const Types::Graph::NameGroupMap knownDists = { 
      { "ResponseEdep"        , { "EMR_Edep_incl", "LCR_Edep_incl", "MLR_Edep_incl" } },
      { "ResponseLambda"      , { "EMR_lamb_incl", "LCR_lamb_incl", "MLR_lamb_incl" } },
      { "ResponseLateral"     , { "EMR_lat__incl", "LCR_lat__incl", "MLR_lat__incl" } },
      { "ResponseLongitudinal", { "EMR_long_incl", "LCR_long_incl", "MLR_long_incl" } },
      { "ResponsePtD"         , { "EMR_ptd__incl", "LCR_ptd__incl", "MLR_ptd__incl" } },
      { "ResponseRho"         , { "EMR_rho__incl", "LCR_rho__incl", "MLR_rho__incl" } },
      { "ResponseSignificance", { "EMR_sign_incl", "LCR_sign_incl", "MLR_sign_incl" } },
      { "ResponseTime"        , { "EMR_time_incl", "LCR_time_incl", "MLR_time_incl" } }
    }; 
  }
  static const std::map<std::string,std::string> sliceCategories = { 
    { "EMR_Edep_incl", "ResponseEdep"         },
    { "LCR_Edep_incl", "ResponseEdep"         },
    { "MLR_Edep_incl", "ResponseEdep"         },
    { "EMR_Efrc_incl", "ResponseEfrc"         },
    { "LCR_Efrc_incl", "ResponseEfrc"         },
    { "MLR_Efrc_incl", "ResponseEfrc"         },
    { "EMR_lamb_incl", "ResponseLambda"       },
    { "LCR_lamb_incl", "ResponseLambda"       },
    { "MLR_lamb_incl", "ResponseLambda"       },
    { "EMR_lat__incl", "ResponseLateral"      },
    { "LCR_lat__incl", "ResponseLateral"      }, 
    { "MLR_lat__incl", "ResponseLateral"      },
    { "EMR_long_incl", "ResponseLongitudinal" },
    { "LCR_long_incl", "ResponseLongitudinal" }, 
    { "MLR_long_incl", "ResponseLongitudinal" },
    { "EMR_ptd__incl", "ResponsePtD"          },
    { "LCR_ptd__incl", "ResponsePtD"          },
    { "MLR_ptd__incl", "ResponsePtD"          },
    { "EMR_rho__incl", "ResponseRho"          }, 
    { "LCR_rho__incl", "ResponseRho"          }, 
    { "MLR_rho__incl", "ResponseRho"          },
    { "EMR_sign_incl", "ResponseSignificance" }, 
    { "LCR_sign_incl", "ResponseSignificance" }, 
    { "MLR_sign_incl", "ResponseSignificance" },
    { "EMR_time_incl", "ResponseTime"         },
    { "LCR_time_incl", "ResponseTime"         }, 
    { "MLR_time_incl", "ResponseTime"         }
  };
  typedef Types::Axis::Descriptor         axis_t;
  typedef std::tuple<axis_t,axis_t,bool>  axisdescr_t;
  typedef std::string                     axiskey_t; 
  typedef std::map<axiskey_t,axisdescr_t> axismap_t;
  static axismap_t plotAxis = { 
    { "EMR_Edep_incl", { Types::Axis::description(0.1,200.  ,true,"E_{clus}^{dep} [GeV]")                               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}" ),true} },
    { "LCR_Edep_incl", { Types::Axis::description(0.1,200.  ,true,"E_{clus}^{dep} [GeV]")                               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },
    { "MLR_Edep_incl", { Types::Axis::description(0.1,200.  ,true,"E_{clus}^{dep} [GeV]")                               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}" ),true} },
    { "EMR_Efrc_incl", { Types::Axis::description(0.005,1.0 ,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}")               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}" ),true} },
    { "LCR_Efrc_incl", { Types::Axis::description(0.005,1.0 ,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}")               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },
    { "MLR_Efrc_incl", { Types::Axis::description(0.005,1.0 ,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}")               ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}" ),true} },
    { "EMR_lamb_incl", { Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]")                                 ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}" ),true} },
    { "LCR_lamb_incl", { Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]")                                 ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },
    { "MLR_lamb_incl", { Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]")                                 ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}" ),true} },
    { "EMR_lat__incl", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}" ),true} },
    { "LCR_lat__incl", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },  
    { "MLR_lat__incl", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}" ),true} }, 
    { "EMR_long_incl", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT")                                     ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}") ,true} },
    { "LCR_long_incl", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT")                                     ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },
    { "MLR_long_incl", { Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT")                                     ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}") ,true} },
    { "EMR_ptd__incl", {Types::Axis::description(0.,1.,false,"p_{t}D")                                                  ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}") ,true} },  
    { "LCR_ptd__incl", {Types::Axis::description(0.,1.,false,"p_{t}D")                                                  ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },  
    { "MLR_ptd__incl", {Types::Axis::description(0.,1.,false,"p_{t}D")                                                  ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}") ,true} },   
    { "EMR_rho__incl", {Types::Axis::description(std::pow(10.,-8.),std::pow(10.,-3.25),true,"#rho_{clus} [GeV/mm^{3}]") ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}") ,true} },    
    { "LCR_rho__incl", {Types::Axis::description(std::pow(10.,-8.),std::pow(10.,-3.25),true,"#rho_{clus} [GeV/mm^{3}]") ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },
    { "MLR_rho__incl", {Types::Axis::description(std::pow(10.,-8.),std::pow(10.,-3.25),true,"#rho_{clus} [GeV/mm^{3}]") ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}") ,true} },
    { "EMR_sign_incl", {Types::Axis::description(1.,500.,true,"#zeta_{clus}^{em}")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}") ,true} },
    { "LCR_sign_incl", {Types::Axis::description(1.,500.,true,"#zeta_{clus}^{em}")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },
    { "MLR_sign_incl", {Types::Axis::description(1.,500.,true,"#zeta_{clus}^{em}")                                      ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}") ,true} },
    { "EMR_time_incl", {Types::Axis::description(-0.25,7.25,false,"#sigma(^{}t_{cell}) [ns]")                           ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{em}/^{}E_{clus}^{dep}") ,true} },
    { "LCR_time_incl", {Types::Axis::description(-0.25,7.25,false,"#sigma(^{}t_{cell}) [ns]")                           ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{had}/^{}E_{clus}^{dep}"),true} },
    { "MLR_time_incl", {Types::Axis::description(-0.25,7.25,false,"#sigma(^{}t_{cell}) [ns]")                           ,Types::Axis::description(0.505,1.5,false,"E_{clus}^{ml}/^{}E_{clus}^{dep}") ,true} }
  };
  static const std::string&             plotAxisKey  (const axismap_t::value_type& entry)                             { return entry.first;    }
  static const std::string&             plotAxisKey  (axismap_t::const_iterator fentry)                               { return fentry->first;  }
  static const axismap_t::mapped_type&  plotAxisData (const axismap_t::value_type& entry)                             { return entry.second;   }
  static const axismap_t::mapped_type&  plotAxisData (axismap_t::const_iterator fentry)                               { return fentry->second; }
  static const axis_t&                  plotAxisDescr(const axismap_t::value_type& entry,const std::string& axis="x") { return axis == "x" ? std::get<0>(plotAxisData(entry))  : std::get<1>(plotAxisData(entry)) ; }  
  static const axis_t&                  plotAxisDescr(axismap_t::const_iterator fentry,const std::string& axis="x")   { return axis == "x" ? std::get<0>(plotAxisData(fentry)) : std::get<1>(plotAxisData(fentry)); }  

#include "DrawStyles.h"

  // collection types supporting [key,[EM,LC,ML]]_2D -> [key,[EM,LC,ML]]_1D
  typedef Types::Graph::Key                Key;
  typedef std::tuple<TH1D*,TH1D*,TH1D*>    HistTuple;
  typedef std::tuple<TH2D*,TH2D*,TH2D*>    DistTuple;
  typedef HistUtils::vslice_t              Slice;
  typedef std::tuple<Slice,Slice,Slice>    SliceTuple;
  typedef std::map<Key,DistTuple>          DistMap;
  typedef std::map<Key,SliceTuple>         SliceMap;
  typedef std::map<int,HistTuple>          HistMap;         
} // Data

template<int I>
int sortComplete(Data::HistMap& hmap,const Data::Slice& slice) {
  for ( const auto& entry : slice ) { 
    int   hind(std::get<1>(entry));
    TH1D* hptr(std::get<0>(entry));
    if ( hptr != nullptr ) { 
      auto fmap(hmap.find(hind)); if ( fmap == hmap.end() ) { fmap = hmap.insert( fmap, { hind, { (TH1D*)0, (TH1D*)0, (TH1D*)0 } } ); } 
      std::get<I>(fmap->second) = hptr; 
    } 
  }
  return static_cast<int>(hmap.size());
} 

Data::HistMap findHists(const Data::SliceTuple& slices ) { 
  Data::HistMap hmap; 
  sortComplete<0>(hmap,std::get<0>(slices)); // EM
  sortComplete<1>(hmap,std::get<1>(slices)); // LC
  sortComplete<2>(hmap,std::get<2>(slices)); // ML
  // analyse map
  auto fmap(hmap.begin());
  while ( fmap != hmap.end() ) { 
    if ( std::get<0>(fmap->second) == nullptr || std::get<1>(fmap->second) == nullptr || std::get<2>(fmap->second) == nullptr ) { fmap = hmap.erase(fmap); } else { ++fmap; }  
  }
  //
  return hmap;
}

void plotResponseHists(const std::string& fileName,const std::string& dirName,bool isBatch=false) { 
  // static memory
  static char _buffer[1024];
  // job parameters
  // std::string dirName(File::directory(fileName));
  bool doJets(fileName.find("jet") != std::string::npos);
  const Types::Graph::NameGroupMap& knownDists = doJets ? Data::Jet::knownDists : Data::Pion::knownDists;
  gErrorIgnoreLevel = kWarning;
  // open file
  TFile* inputFile = File::open(fileName,File::IO::Read); 
  if ( inputFile == nullptr ) { return; }
  // open output file
  std::string outFileName = File::name(fileName,true)+std::string(".dists.")+File::extension(fileName); 
  TFile* outputFile = File::open(outFileName.c_str(),File::IO::Recreate); 
  if ( outputFile == nullptr ) { return; }

  /////////////////////////////////////////
  // Input: read distributions from file //
  /////////////////////////////////////////

  inputFile->cd(); 
  Data::DistMap plots;
  // retrieve all known distributions
  for ( const auto& entry : knownDists ) {
    // entry
    const std::string&             key   = entry.first;  // name of series (key)
    const Types::Graph::NameGroup& dists = entry.second; // names of distributions (payload)
    printf("[plotResponseHists(fileName=\042%s\042)] INFO loading distributions for plot series %s\n",fileName.c_str(),key.c_str());
    // loop scales
    Data::DistTuple distList = { (TH2D*)0, (TH2D*)0, (TH2D*)0 };
    for ( size_t iscale(0); iscale < Types::Graph::knownScales.size(); ++iscale ) { 
      switch ( iscale ) { 
      case 0 : Types::Graph::access<0,Data::DistTuple>(distList) = Types::Graph::loadGraph<TH2D>(inputFile,Types::Graph::findGraph(dists,Types::Graph::knownScales.at(iscale))); break;
      case 1 : Types::Graph::access<1,Data::DistTuple>(distList) = Types::Graph::loadGraph<TH2D>(inputFile,Types::Graph::findGraph(dists,Types::Graph::knownScales.at(iscale))); break;
      case 2 : Types::Graph::access<2,Data::DistTuple>(distList) = Types::Graph::loadGraph<TH2D>(inputFile,Types::Graph::findGraph(dists,Types::Graph::knownScales.at(iscale))); break;
      default: break; 
      } // scale switches
    } // loop on scales
    plots.insert( { key, distList } );
    printf("[[plotResponseHists(fileName=\042%s\042)] DEBG [%zu] added 2-dim distributions\n",fileName.c_str(),3*plots.size());
  } // loop on know distributions
  printf("[plotResponseHists(fileName=\042%s\042)] INFO found %zu 2-dim distributions in total\n",fileName.c_str(),plots.size());
  std::string invalidPtr = "<null> pointer";
  std::string::size_type lm(invalidPtr.length());
  std::string::size_type lk(0);
  for ( const auto& entry : plots ) { 
    lk = std::max(lk,entry.first.length());
    if ( std::get<0>(entry.second) != nullptr && std::get<1>(entry.second) != nullptr && std::get<2>(entry.second) != nullptr ) { 
      lm = std::max( { lm, std::string(std::get<0>(entry.second)->GetName()).length(),std::string(std::get<1>(entry.second)->GetName()).length(),std::string(std::get<2>(entry.second)->GetName()).length() } );
    } 
  }
  for ( const auto& entry : plots ) { 
    printf("[plotResponseHists(fileName=\042%s\042)] INFO key: %-*.*s - found 2-dim distributions",fileName.c_str(),(int)lk,(int)lk,entry.first.c_str());
    if ( std::get<0>(entry.second) != nullptr ) { printf(" %-*.*s",(int)lm,(int)lm,std::get<0>(entry.second)->GetName()); } else { printf(" %-*.*s",(int)lm,(int)lm,invalidPtr.c_str()); }
    if ( std::get<1>(entry.second) != nullptr ) { printf(" %-*.*s",(int)lm,(int)lm,std::get<1>(entry.second)->GetName()); } else { printf(" %-*.*s",(int)lm,(int)lm,invalidPtr.c_str()); }
    if ( std::get<2>(entry.second) != nullptr ) { printf(" %-*.*s",(int)lm,(int)lm,std::get<2>(entry.second)->GetName()); } else { printf(" %-*.*s",(int)lm,(int)lm,invalidPtr.c_str()); }
    printf("\n"); std::cout << std::flush;
  }

  /////////////////////////
  // Output: fill slices //
  /////////////////////////

  outputFile->cd();
  int iAxis(2); double minEntries(50.); 
  Data::SliceMap allSlices; TH2D* distPtr = (TH2D*)0; 
  unsigned int islice(0); 
  for ( auto dists : plots ) {
    Data::SliceTuple slices = { Data::Slice(), Data::Slice(), Data::Slice() }; 
    distPtr = std::get<0>(dists.second); if ( distPtr != nullptr ) { sprintf(_buffer,"%s_slice",distPtr->GetName()); std::get<0>(slices) = HistUtils::extract(distPtr,_buffer,iAxis,minEntries); if ( !std::get<0>(slices).empty() ) { ++islice; } } 
    distPtr = std::get<1>(dists.second); if ( distPtr != nullptr ) { sprintf(_buffer,"%s_slice",distPtr->GetName()); std::get<1>(slices) = HistUtils::extract(distPtr,_buffer,iAxis,minEntries); if ( !std::get<1>(slices).empty() ) { ++islice; } } 
    distPtr = std::get<2>(dists.second); if ( distPtr != nullptr ) { sprintf(_buffer,"%s_slice",distPtr->GetName()); std::get<2>(slices) = HistUtils::extract(distPtr,_buffer,iAxis,minEntries); if ( !std::get<2>(slices).empty() ) { ++islice; } } 
    allSlices.insert( { dists.first, slices } ); 
  }
  printf("[plotResponseHists(fileName=\042%s\042)] INFO extracted %u slices in %zu categories total\n",fileName.c_str(),islice,allSlices.size()); 

  /////////////////
  // Plot slices //
  /////////////////

  // descriptive text
  TLatex tl;
  double normalSize(tl.GetTextSize()); 
  double titleSize(0.75*normalSize);
  double smallSize(0.50*normalSize); 
  tl.SetTextSize(titleSize);
  tl.SetNDC();
  tl.SetTextAlign(13);
  double tx(gStyle->GetPadLeftMargin()+0.04);
  double ty(1-(gStyle->GetPadTopMargin()+0.04));

  // plot all slices in all categories stored in the map 
  std::vector<std::string> printFiles; printFiles.reserve(100000); 
  for ( auto& entry : allSlices ) {
    // actual key and values
    const std::string&      key    = entry.first;
    const Data::SliceTuple& slices = entry.second;
    // change/create directory
    outputFile->cd();
    auto thisDir = outputFile->mkdir(key.c_str(),key.c_str(),true); thisDir->cd(); 
    printf("[plotResponseHists(fileName=\042%s\042)] INFO changed to directory %s/%s\n",inputFile->GetName(),outputFile->GetName(),thisDir->GetName()); 
    // find reference distributions for evaluation range
    TH2D* dptr_em = std::get<0>(plots.at(key)); if ( dptr_em == nullptr ) { printf("[plotResponseHists(fileName=\042%s\042)] WARN Key [%s] cannot find reference EM distribution\n",fileName.c_str(),key.c_str()); continue; }
    TH2D* dptr_lc = std::get<1>(plots.at(key)); if ( dptr_lc == nullptr ) { printf("[plotResponseHists(fileName=\042%s\042)] WARN Key [%s] cannot find reference EM distribution\n",fileName.c_str(),key.c_str()); continue; }
    TH2D* dptr_ml = std::get<2>(plots.at(key)); if ( dptr_ml == nullptr ) { printf("[plotResponseHists(fileName=\042%s\042)] WARN Key [%s] cannot find reference EM distribution\n",fileName.c_str(),key.c_str()); continue; }
    dptr_em->Write();
    dptr_lc->Write();
    dptr_ml->Write();
    // check that slices are all filled
    Data::HistMap hmap = findHists(slices);
    if ( hmap.empty() ) { continue; }
    // global parameters
    std::string dname(dptr_em->GetName());   // distribution name
    std::string cname(key);                  // category name
    std::string atitle(String::strip(String::extractVariable(Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"x")))));
    std::string utitle(String::strip(String::extractUnit    (Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"x"))))); 
    std::string xtitle(Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"y")));
    std::string ytitle("Entries");
    // plot all complete slices for this category
    for ( auto fmap(hmap.begin()); fmap != hmap.end(); ++fmap ) { 
      // parameters
      std::string lowerLimit(HistUtils::Format::fmtNumber(dptr_em->GetXaxis()->GetBinLowEdge(fmap->first)));
      std::string upperLimit(HistUtils::Format::fmtNumber(dptr_em->GetXaxis()->GetBinUpEdge (fmap->first)));
      // data
      TH1D* hptr_em = std::get<0>(fmap->second); Types::Graph::setDrawStyle<TH1D>(hptr_em,Data::lineStyles.at(Types::Graph::knownScales.at(0))); Types::Graph::setDrawStyle<TH1D>(hptr_em,Data::fillStyles.at(Types::Graph::knownScales.at(0)));  
      TH1D* hptr_lc = std::get<1>(fmap->second); Types::Graph::setDrawStyle<TH1D>(hptr_lc,Data::lineStyles.at(Types::Graph::knownScales.at(1))); Types::Graph::setDrawStyle<TH1D>(hptr_lc,Data::fillStyles.at(Types::Graph::knownScales.at(1)));  
      TH1D* hptr_ml = std::get<2>(fmap->second); Types::Graph::setDrawStyle<TH1D>(hptr_ml,Data::lineStyles.at(Types::Graph::knownScales.at(2))); Types::Graph::setDrawStyle<TH1D>(hptr_ml,Data::fillStyles.at(Types::Graph::knownScales.at(2)));
      std::vector<TH1D*> hists = { hptr_em, hptr_lc, hptr_ml }; 
      // normalizing
      sprintf(_buffer,"%s %s < %s < %s %s",lowerLimit.c_str(),utitle.c_str(),atitle.c_str(),upperLimit.c_str(),utitle.c_str());
      double hmax(0.); for ( auto hptr : hists ) { double norm(hptr->Integral()); if ( norm != 0. ) { hptr->Scale(1./norm); hptr->SetTitle(_buffer); hptr->GetYaxis()->SetTitle(ytitle.c_str()); hmax = std::max(hmax,hptr->GetMaximum()); } }
      // plotting histograms
      sprintf(_buffer,"Category%s_bin_%i",key.c_str(),fmap->first);
      TCanvas* cvs = new TCanvas(_buffer,_buffer);
      TH1D* _frame = new TH1D(*hptr_em); 
      _frame->Reset();
      _frame->SetMinimum(0.);
      _frame->SetMaximum(1.1*hmax);
      _frame->GetXaxis()->SetTitle(xtitle.c_str());
      _frame->GetYaxis()->SetTitle(ytitle.c_str());
      _frame->DrawCopy("axis"); 
      for ( auto hptr : hists ) { hptr->DrawCopy("same hist"); hptr->Write(); }
      // descriptive text
      sprintf(_buffer,"%s",hists.front()->GetTitle());
      tl.SetTextSize(titleSize); tl.DrawLatex(tx,ty     ,"#font[72]{ATLAS} Simulation Internal"              ); 
      tl.SetTextSize(smallSize); tl.DrawLatex(tx,ty-0.06,"Anti-k_{t} R = 0.4 LCTopo jets (MC16d JZ2W)"       );
      tl.SetTextSize(smallSize); tl.DrawLatex(tx,ty-0.10,"p_{T,jet}^{LCJES} > 20 GeV |y_{jet}^{LCJES}| < 0,4");
      tl.SetTextSize(smallSize); tl.DrawLatex(tx,ty-0.15,"Topo-cluster response"                             );
      tl.SetTextSize(smallSize); tl.DrawLatex(tx,ty-0.18,_buffer                                             );
      // legend
      TLegend* lptr = new TLegend(tx,ty-0.25,tx+0.15,ty-0.4,"","NDC");
      lptr->SetBorderSize(0); 
      TLegendEntry* eptr_em = lptr->AddEntry(hptr_em,"EM response" ,"lf"); eptr_em->SetTextFont(42);
      TLegendEntry* eptr_lc = lptr->AddEntry(hptr_lc,"LCW response","lf"); eptr_lc->SetTextFont(42);
      TLegendEntry* eptr_ml = lptr->AddEntry(hptr_ml,"ML response" ,"lf"); eptr_ml->SetTextFont(42);
      lptr->Draw("same");
      // save canvas
      cvs->Write();
      // print canvas
      if ( dirName.length() > 0 ) { sprintf(_buffer,"%s/%s",dirName.c_str(),cvs->GetName()); } else { sprintf(_buffer,"./%s",cvs->GetName()); }
      std::vector<std::string> pfiles = File::print(_buffer,cvs,std::vector<std::string>({"pdf","png"}));
      printFiles.insert(printFiles.end(),pfiles.begin(),pfiles.end());
      // break point
      if ( !isBatch ) { 
	gSystem->ProcessEvents();
	std::cout << "(push key to continue, q/Q -> quit: ";
	int c=getchar();
	if ( c == 'q' || c == 'Q' ) { std::cout << std::endl; outputFile->Close(); return; }
      }
    } // slices
  } // slice map

  ////////////////
  // Finalizing //
  ////////////////

  // get time stamp
  std::time_t tnow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  std::string strNow(ctime(&tnow));
  std::cout << strNow << std::endl;
  strNow =String::strip(String::remove(strNow,{ "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" }),' ');
  // std::cout << strNow << std::endl;
  // strNow = String::replace(strNow,' ','_');
  std::cout << strNow << std::endl;
  // strNow = String::replace(strNow,' ','_');
  std::vector<char> forbidden( { ' ',':',',','!','?','+','-','*','#','@','&','^','%','$' } );
  strNow = String::replace(strNow,forbidden,'_');
  std::cout << strNow << std::endl;
  sprintf(_buffer,"Report.%s.log",strNow.c_str());

  printf("[plotResponseHists(fileName=\042%s\042)] INFO full listof  %zu plots in file \042%s\042\n",fileName.c_str(),printFiles.size(),_buffer);
  std::ofstream messageStream(_buffer);
  std::copy(printFiles.begin(),printFiles.end(),std::ostream_iterator<std::string>(messageStream,"\n")); 
  messageStream.close();
  // finish
  outputFile->Close();
}
