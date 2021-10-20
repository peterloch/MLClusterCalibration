
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>

#include "HistUtils.h"
#include "PlotConfig.h"

#include <string>
#include <map>
#include <tuple>
#include <vector>

#include <cstdio>
#include <cmath>

namespace Data {
  namespace Jet  {
    static const Types::Graph::NameGroupMap knownDists = { 
      { "ResponseEdep", { "EMR_Edep_incl", "LCR_Edep_incl", "MLR_Edep_incl" } },
      { "ResponseEfrc", { "EMR_Efrc_incl", "LCR_Efrc_incl", "MLR_Efrc_incl" } },
      { "Responselamb", { "EMR_lamb_incl", "LCR_lamb_incl", "MLR_lamb_incl" } },
      { "Responselat_", { "EMR_lat__incl", "LCR_lat__incl", "MLR_lat__incl" } },
      { "Responselong", { "EMR_long_incl", "LCR_long_incl", "MLR_long_incl" } },
      { "Responseptd_", { "EMR_ptd__incl", "LCR_ptd__incl", "MLR_ptd__incl" } },
      { "Responserho_", { "EMR_rho__incl", "LCR_rho__incl", "MLR_rho__incl" } },
      { "Responsesign", { "EMR_sign_incl", "LCR_sign_incl", "MLR_sign_incl" } },
      { "Responsetime", { "EMR_time_incl", "LCR_time_incl", "MLR_time_incl" } }
    }; 
  }
  namespace Pion { 
    static const Types::Graph::NameGroupMap knownDists = { 
      { "ResponseEdep", { "EMR_Edep_incl", "LCR_Edep_incl", "MLR_Edep_incl" } },
      { "Responselamb", { "EMR_lamb_incl", "LCR_lamb_incl", "MLR_lamb_incl" } },
      { "Responselat_", { "EMR_lat__incl", "LCR_lat__incl", "MLR_lat__incl" } },
      { "Responselong", { "EMR_long_incl", "LCR_long_incl", "MLR_long_incl" } },
      { "Responseptd_", { "EMR_ptd__incl", "LCR_ptd__incl", "MLR_ptd__incl" } },
      { "Responserho_", { "EMR_rho__incl", "LCR_rho__incl", "MLR_rho__incl" } },
      { "Responsesign", { "EMR_sign_incl", "LCR_sign_incl", "MLR_sign_incl" } },
      { "Responsetime", { "EMR_time_incl", "LCR_time_incl", "MLR_time_incl" } }
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
  HistMap hmap; 
  sortComplete<0>(hmap,std::get<0>(slices)); // EM
  sortComplete<1>(hmap,std::get<1>(slices)); // LC
  sortComplete<2>(hmap,std::get<2>(slices)); // ML
  // analyse map
  auto fmap(hmap.begin());
  while ( fmap != fmap.end() ) { 
    if ( std::get<0>(fmap->second) == nullptr || std::get<1>(fmap->second) == nullptr || std::get<2>(fmap->second) == nullptr ) { fmap = hmap.erase(fmap); } else { ++fmap; }  
  }
  //
  return hmap;
}

void plotResponseHists(const std::string& fileName) { 
  // static memory
  static char _buffer[1024];
  // job parameters
  std::string dirName(File::directory(fileName));
  bool doJets(fileName.find("jet") != std::string::npos);
  const Types::Graph::NameGroupMap& knownDists = doJets ? Data::Jet::knownDists : Data::Pion::knownDists;
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
    printf("[plotResponseSummary(fileName=\042%s\042)] INFO loading distributions for plot series %s\n",fileName.c_str(),key.c_str());
    // loop scales
    Data:::DistTuple distList = { (TH2D*)0, (TH2D*)0, (TH2D*)0 };
    for ( size_t iscale(0); iscale < Types::Graph::knownScales.size(); ++iscale ) { 
      switch ( iscale ) { 
      case 0 : Types::Graph::access<0,DistTuple>(distList) = Types::Graph::loadGraph(inputFile,Types::Graph::findGraph(dists,Types::Graph::knownScales.at(iscale))); break;
      case 1 : Types::Graph::access<1,DistTuple>(distList) = Types::Graph::loadGraph(inputFile,Types::Graph::findGraph(dists,Types::Graph::knownScales.at(iscale))); break;
      case 2 : Types::Graph::access<2,DistTuple>(distList) = Types::Graph::loadGraph(inputFile,Types::Graph::findGraph(dists,Types::Graph::knownScales.at(iscale))); break;
      default: break; 
    } // loop on scales
    plots.insert( { key, distList } );
  } // loop on known distributions
  printf("[plotResponseSummary(fileName=\042%s\042)] INFO found %zu distributions in total\n",fileName.c_str(),plots.size()); 

  /////////////////////////
  // Output: fill slices //
  /////////////////////////

  outputFile->cd();
  int iAxis(2); double minEntries(50.); 
  Data::SliceMap allSlices; TH2D* distPtr = (TH2D*)0; 
  unsignes int islice(0); 
  for ( auto dists : plots ) {
    Data::SliceTuple slices = { Data::Slice(), Data::Slice(), Data::Slice() }; 
    distPtr = std::get<0>(dists.second); if ( distPtr != nullptr ) { sprintf(_buffer,"%s_slice",distPtr->GetName()); std::get<0>(slices) = HistUtils::extract(distPtr,_buffer,iAxis,minEntries); if ( !std::get<0>(slices).empty() ) { ++islice; } } 
    distPtr = std::get<1>(dists.second); if ( distPtr != nullptr ) { sprintf(_buffer,"%s_slice",distPtr->GetName()); std::get<1>(slices) = HistUtils::extract(distPtr,_buffer,iAxis,minEntries); if ( !std::get<1>(slices).empty() ) { ++islice; } } 
    distPtr = std::get<2>(dists.second); if ( distPtr != nullptr ) { sprintf(_buffer,"%s_slice",distPtr->GetName()); std::get<2>(slices) = HistUtils::extract(distPtr,_buffer,iAxis,minEntries); if ( !std::get<2>(slices).empty() ) { ++islice; } } 
    allSlices.insert( { dists.first, slices } ); 
  }
  printf("[plotResponseSummary(fileName=\042%s\042)] INFO extracted %zu slices in %zu categories total\n",fileName.c_str(),islice,allSlices.size()); 

  /////////////////
  // Plot slices //
  /////////////////

  for ( auto& entry : SliceMap ) {
    // actual key and values
    const std::string&      key    = entry.first();
    const Data::SliceTuple& slices = entry.second();
    // find reference distributions for evaluation range
    TH2D* dptr_em = std::get<0>(plots.at(key)); if ( dptr_em == nullptr ) { printf("[plotResponseHists(fileName=\042%s\042)] WARN Key [%s] cannot find reference EM distribution\n",fileName.c_str(),key.c_str()); continue; }
    TH2D* dptr_lc = std::get<1>(plots.at(key)); if ( dptr_lc == nullptr ) { printf("[plotResponseHists(fileName=\042%s\042)] WARN Key [%s] cannot find reference EM distribution\n",fileName.c_str(),key.c_str()); continue; }
    TH2D* dptr_ml = std::get<2>(plots.at(key)); if ( dptr_ml == nullptr ) { printf("[plotResponseHists(fileName=\042%s\042)] WARN Key [%s] cannot find reference EM distribution\n",fileName.c_str(),key.c_str()); continue; }
    // check that slices are all filled
    Data::HistMap hmap = findHists(slices);
    if ( hmap.empty() ) { continue; }
    // global parameters
    std::string dname(dptr_em->GetName());   // distribution name
    std::string cname(key);                  // category name
    std::string atitle(String::extractVariable(Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"x"))));
    std::string utitle(String::extractUnit    (atitle); 
    std::string xtitle(Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"y")));
    std::string ytitle("Entries");
    // loop complete slices
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
      sprintf(_buffer,"Response %s %s < %s < %s %s",lowerLimit.c_str(),utitle.c_str(),atitle.c_str(),upperLimit.c_str(),utitle.c_str());
      double hmax(0.); for ( auto hptr : hists ) { double norm(hists->Integral()); if ( norm != 0. ) { hptr->Scale(1./norm); hptr->SetTitle(_buffer); hptr->GetYaxis()->SetTitle(ytitle.c_str()); hmax = std::max(hmax,hptr->GetMaximum()); } }
      // plotting
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
      cvs->Write();
    }
	    

    




  //   // normalize histograms
  // } 


  // for ( auto& entry : slices ) {
  //   // allocate 2-dim distribution and category
  //   TH2D* dptr = entry.first;
  //   if ( dptr == nullptr ) { continue; }
  //   // category and directories
  //   if ( cname != "" ) { outputFile->mkdir(cname.c_str(),cname.c_str(),true); outputFile->cd(cname.c_str()); }
  //   // plot all slices
  //   TCanvas* cvs = new TCanvas(TString::Format("Canvas%s",dname.c_str()).Data(),dname.c_str());
  //   for ( auto& content : entry.second ) {
  //     TH1D*       hptr  = std::get<0>(content);
  //     int         idx   = std::get<1>(content);   
  //     if ( hptr != nullptr ) { 
  // 	if ( Types::Axis::isLog(std::get<1>(Data::plotAxis.at(dptr->GetName()))) ) { cvs->SetLogx(); }
  // 	if ( Types::Axis::isLog(std::get<0>(Data::plotAxis.at(dptr->GetName()))) ) { cvs->SetLogy(); }
  // 	hptr->GetXaxis()->SetTitle(xtitle.c_str());
  // 	hptr->GetYaxis()->SetTitle(ytitle.c_str());
  // 	std::string lowerLimit(HistUtils::Format::fmtNumber(dptr->GetXaxis()->GetBinLowEdge(idx)));
  // 	std::string upperLimit(HistUtils::Format::fmtNumber(dptr->GetXaxis()->GetBinUpEdge (idx)));
  // 	// double xmin(dptr->GetXaxis()->GetBinLowEdge(idx)); double xmax(dptr->GetXaxis()->GetBinUpEdge(idx)); 
  // 	// new histogram title with boundaries

  // 	hptr->SetTitle(_buffer); 
  // 	// draw and save
  // 	Types::Graph::setDrawStyle<TH1D>(hptr,Data::lineStyles.at
  // 	hptr->DrawCopy("hist");	hptr->Write();
  // 	cvs->Write();
  //     } // is valid histogram
		       //    } // loop histograms in slice
    outputFile->cd();
  } // loop slices
  // finish
  outputFile->Close();
}
