
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TFile.h>

#include "PlotConfig.h"

#include <string>
#include <tuple>
#include <map>
#include <vector>

namespace Data {
  // data 
  static const Types::Graph::NameGroupMap knownGraphsRMS = { 
    { "ResponseEdepRMS", { "EMR_Edep_incl_graph_mean_rms", "LCR_Edep_incl_graph_mean_rms", "MLR_Edep_incl_graph_mean_rms" } },
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
    { "ResponselambERR", { "EMR_lamb_incl_graph_mean_err", "LCR_lamb_incl_graph_mean_err", "MLR_lamb_incl_graph_mean_err" } },
    { "Responselat_ERR", { "EMR_lat__incl_graph_mean_err", "LCR_lat__incl_graph_mean_err", "MLR_lat__incl_graph_mean_err" } },
    { "ResponselongERR", { "EMR_long_incl_graph_mean_err", "LCR_long_incl_graph_mean_err", "MLR_long_incl_graph_mean_err" } },
    { "Responseptd_ERR", { "EMR_ptd__incl_graph_mean_err", "LCR_ptd__incl_graph_mean_err", "MLR_ptd__incl_graph_mean_err" } },
    { "Responserho_ERR", { "EMR_rho__incl_graph_mean_err", "LCR_rho__incl_graph_mean_err", "MLR_rho__incl_graph_mean_err" } },
    { "ResponsesignERR", { "EMR_sign_incl_graph_mean_err", "LCR_sign_incl_graph_mean_err", "MLR_sign_incl_graph_mean_err" } },
    { "ResponsetimeERR", { "EMR_time_incl_graph_mean_err", "LCR_time_incl_graph_mean_err", "MLR_time_incl_graph_mean_err" } }
  }; 
  static const std::map<Types::Graph::ScaleTag,Types::Graph::LineDescriptor> lineStyles = { 
    { knownScales.at(0), { (int)kRed     ,1,2,0.75 } },  // EM red
    { knownScales.at(1), { (int)kBlue    ,1,2,0.75 } },  // LCW blue
    { knownScales.at(2), { (int)kOrange+3,1,2,0.75 } }   // ML brown 
  };
} // Data

void plotSummary(const std::string& fileName,const std::string& barOpt="RMS") {
  // open file
  TFile* dataFile = new TFile(fileName.c_str(),"READ"); 
  if ( dataFile == nullptr ) { printf("[plotSummary(fileName=\042%s\042)] ABRT cannot find input file\n",fileName.c_str()); return; }
  // read graphs for three different response scales
  Types::Graph::PointerGroupMap plotsRMS;
  for ( auto plot : Graphs::knownGraphsRMS ) { 
    // load plots
    plotsRMS[plot.first] = { (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(std::get<0>(plot.second)), 
			     (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(std::get<1>(plot.second)),  
			     (TGraph*)Types::Graph::loadGraph<TGraphAsymmErrors>(std::get<2>(plot.second)) };
    // configure plots
    for ( const Types::Graph::ScaleTag& scaleTag : Types::Graph::knownScales ) { 
      TGraph* gptr = Types::Graph::findGraph(plotsRMS.at(plots.first),scaleTag);
      if ( gptr != nullptr ) {
	Types::Graph::setDrawStyle<Types::Graph::LineDescriptor>  (gptr,Data::lineStyles.at  (scaleTag)); 
	Types::Graph::setDrawStyle<Types::Graph::MarkerDescriptor>(gptr,Data::markerStyles.at(scaleTag)); 
      } 
    }
  }
  
}
