
#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TCanvas.h>

#include "HistUtils.h"
#include "PlotConfig.h"

#include <string>
#include <map>
#include <tuple>

#include <cstdio>

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
} // Data

void plotResponseHists(const std::string& fileName) { 
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
  // read distributions
  inputFile->cd(); 
  std::map<std::string,std::tuple<TH2D*,std::string> > plots;
  for ( const auto& entry : knownDists ) {
    // entry
    const std::string&             name = entry.first;  // name of series (key)
    const Types::Graph::NameGroup& dist = entry.second; // names of distributions (payload)
    printf("[plotResponseSummary(fileName=\042%s\042)] INFO loading distributions for plot series %s\n",fileName.c_str(),name.c_str());
    // loop scales
    for ( const auto& scaleTag : Types::Graph::knownScales ) {
      // get distribution
      Types::Graph::Name distName = Types::Graph::findGraph(dist,scaleTag);             // get name from scale tag 
      TH2D*              distPtr  = Types::Graph::loadGraph<TH2D>(inputFile,distName);  // get distribution
      // store distribution
      if ( distPtr != nullptr ) { plots.insert( { distName, { distPtr, String::extractVariable(Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(std::string(distPtr->GetName())),"y"))) } } ); }
    } // loop in scales
  } // loop on known distributions
  printf("[plotResponseSummary(fileName=\042%s\042)] INFO found %zu distributions in total\n",fileName.c_str(),plots.size()); 
  // prepare slices
  outputFile->cd();
  int iAxis(2); double minEntries(50.); 
  std::map<TH2D*,HistUtils::vslice_t> slices; 
  for ( auto dists : plots ) { 
    TH2D* distPtr = std::get<0>(dists.second); sprintf(_buffer,"%s_slice",distPtr->GetName()); slices[distPtr] = HistUtils::extract(distPtr,_buffer,iAxis,minEntries); 
  }
  printf("[plotResponseSummary(fileName=\042%s\042)] INFO extracted %zu slices in total\n",fileName.c_str(),slices.size()); 
  for ( auto& entry : slices ) {
    // allocate 2-dim distribution and category
    TH2D* dptr = entry.first;
    if ( dptr == nullptr ) { continue; }
    // category and directories
    std::string dname(dptr->GetName()); 
    std::string cname(Data::sliceCategories.at(dname));
    std::string atitle(String::extractVariable(Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"x"))));
    std::string utitle(String::extractUnit    (Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"x")))); 
    std::string xtitle(                        Types::Axis::title(Data::plotAxisDescr(Data::plotAxis.find(dname),"y")) );
    std::string ytitle("Entries");
    if ( cname != "" ) { outputFile->mkdir(cname.c_str(),cname.c_str(),true); outputFile->cd(cname.c_str()); }
    // plot all slices
    TCanvas* cvs = new TCanvas(TString::Format("Canvas%s",dname.c_str()).Data(),dname.c_str());
    for ( auto& content : entry.second ) {
      TH1D*       hptr  = std::get<0>(content);
      int         idx   = std::get<1>(content);   
      if ( hptr != nullptr ) { 
	if ( Types::Axis::isLog(std::get<1>(Data::plotAxis.at(dptr->GetName()))) ) { cvs->SetLogx(); }
	if ( Types::Axis::isLog(std::get<0>(Data::plotAxis.at(dptr->GetName()))) ) { cvs->SetLogy(); }
	hptr->GetXaxis()->SetTitle(xtitle.c_str());
	hptr->GetYaxis()->SetTitle(ytitle.c_str());
	std::string lowerLimit(HistUtils::Format::fmtNumber(dptr->GetXaxis()->GetBinLowEdge(idx)));
	std::string upperLimit(HistUtils::Format::fmtNumber(dptr->GetXaxis()->GetBinUpEdge (idx)));
	// double xmin(dptr->GetXaxis()->GetBinLowEdge(idx)); double xmax(dptr->GetXaxis()->GetBinUpEdge(idx)); 
	// new histogram title with boundaries
	sprintf(_buffer,"Response %s %s < %s < %s %s",lowerLimit.c_str(),utitle.c_str(),atitle.c_str(),upperLimit.c_str(),utitle.c_str());
	hptr->SetTitle(_buffer); 
	// draw and save
	hptr->DrawCopy("hist");	hptr->Write();
	cvs->Write();
      } // is valid histogram
    } // loop histograms in slice
    outputFile->cd();
  } // loop slices
  // finish
  outputFile->Close();
}
