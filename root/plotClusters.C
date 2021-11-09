
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h> 
#include <TCanvas.h>
#include <TLatex.h>
#include <TString.h>

#include "HistUtils.h"
#include "PlotConfig.h"

#include <string>
#include <map>
#include <vector>

#include <cstdio>

void plotClusters(const std::string& fileName="ml_pions.hist.root",const std::string& fdir="plots",double minEntries=50.) {
  // particle type lookup
  static const std::map<std::string,std::string> directoryToParticle = {
    { "pi"  , "#pi"          },
    { "pi-" , "#pi^{#minus}" },
    { "pi+" , "#pi^{#plus}"  },
    { "pi+-", "#pi^{#pm}"    },
    { "pi-+", "#pi^{#mp}"    },
    { "pi0" , "#pi^{0}"      },
    { "jet" , "jet"          }
  };
  // known histogram identifiers
  static const std::vector<Types::Hist::Identifier> knownHists = { 
   /* 00 */ Types::Hist::identify("ClusRapAll","TH1D","CLU",Types::Axis::description(1.,-1.,false,"y_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"entries/0.1")),
   /* 01 */ Types::Hist::identify("ClusRapAcc","TH1D","CLU",Types::Axis::description(1.,-1.,false,"y_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"entries/0.1")),
   /* 02 */ Types::Hist::identify("ClusDepAll","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 03 */ Types::Hist::identify("ClusDepAcc","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 04 */ Types::Hist::identify("ClusEemAll","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{em} [GeV]" ),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 05 */ Types::Hist::identify("ClusEemAcc","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{em} [GeV]" ),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 06 */ Types::Hist::identify("ClusLcwAll","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{had} [GeV]"),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 07 */ Types::Hist::identify("ClusLcwAcc","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{had} [GeV]"),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 08 */ Types::Hist::identify("ClusEmlAll","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{ml} [GeV]" ),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 09 */ Types::Hist::identify("ClusEmlAcc","TH1D","CLU",Types::Axis::description(0.05,2000.,true,"E_{clus}^{ml} [GeV]" ),Types::Axis::description(1.,-1.,false,"entries/GeV" )),  
   /* 10 */ Types::Hist::identify("EMR_Edep_incl","TH2D","RES",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 11 */ Types::Hist::identify("LCR_Edep_incl","TH2D","RES",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 12 */ Types::Hist::identify("MLR_Edep_incl","TH2D","RES",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 13 */ Types::Hist::identify("EMR_Edep_e300","TH2D","RES",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),
   /* 14 */ Types::Hist::identify("LCR_Edep_e300","TH2D","RES",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 15 */ Types::Hist::identify("MLR_Edep_e300","TH2D","RES",Types::Axis::description(0.05,2000.,true,"E_{clus}^{dep} [GeV]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 16 */ Types::Hist::identify("EMR_Efrc_incl","TH2D","RES",Types::Axis::description(0.005,1.0,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 17 */ Types::Hist::identify("LCR_Efrc_incl","TH2D","RES",Types::Axis::description(0.005,1.0,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 18 */ Types::Hist::identify("MLR_Efrc_incl","TH2D","RES",Types::Axis::description(0.005,1.0,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 19 */ Types::Hist::identify("EMR_Efrc_e300","TH2D","RES",Types::Axis::description(0.005,1.0,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),
   /* 20 */ Types::Hist::identify("LCR_Efrc_e300","TH2D","RES",Types::Axis::description(0.005,1.0,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 21 */ Types::Hist::identify("MLR_Efrc_e300","TH2D","RES",Types::Axis::description(0.005,1.0,true,"E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 22 */ Types::Hist::identify("EMR_rho__incl","TH2D","RES",Types::Axis::description(std::pow(10.,-8.5),std::pow(10.,-3.5),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 23 */ Types::Hist::identify("LCR_rho__incl","TH2D","RES",Types::Axis::description(std::pow(10.,-8.5),std::pow(10.,-3.5),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 24 */ Types::Hist::identify("MLR_rho__incl","TH2D","RES",Types::Axis::description(std::pow(10.,-8.5),std::pow(10.,-3.5),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 25 */ Types::Hist::identify("EMR_rho__e300","TH2D","RES",Types::Axis::description(std::pow(10.,-8.5),std::pow(10.,-3.5),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 26 */ Types::Hist::identify("LCR_rho__e300","TH2D","RES",Types::Axis::description(std::pow(10.,-8.5),std::pow(10.,-3.5),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 27 */ Types::Hist::identify("MLR_rho__e300","TH2D","RES",Types::Axis::description(std::pow(10.,-8.5),std::pow(10.,-3.5),true,"#rho_{clus} [GeV/mm^{3}]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 28 */ Types::Hist::identify("EMR_lamb_incl","TH2D","RES",Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 29 */ Types::Hist::identify("LCR_lamb_incl","TH2D","RES",Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 30 */ Types::Hist::identify("MLR_lamb_incl","TH2D","RES",Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 31 */ Types::Hist::identify("EMR_lamb_e300","TH2D","RES",Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 32 */ Types::Hist::identify("LCR_lamb_e300","TH2D","RES",Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 33 */ Types::Hist::identify("MLR_lamb_e300","TH2D","RES",Types::Axis::description(10.,5000.,true,"#lambda_{clus} [mm]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 34 */ Types::Hist::identify("EMR_long_incl","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),
   /* 35 */ Types::Hist::identify("LCR_long_incl","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),
   /* 36 */ Types::Hist::identify("MLR_long_incl","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),
   /* 37 */ Types::Hist::identify("EMR_long_e300","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 38 */ Types::Hist::identify("LCR_long_e300","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 39 */ Types::Hist::identify("MLR_long_e300","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{long}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 40 */ Types::Hist::identify("EMR_lat__incl","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 41 */ Types::Hist::identify("LCR_lat__incl","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 42 */ Types::Hist::identify("MLR_lat__incl","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 43 */ Types::Hist::identify("EMR_lat__e300","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 44 */ Types::Hist::identify("LCR_lat__e300","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 45 */ Types::Hist::identify("MLR_lat__e300","TH2D","RES",Types::Axis::description(0.,1.,false,"#LTm^{2}_{lat}#GT"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 46 */ Types::Hist::identify("EMR_sign_incl","TH2D","RES",Types::Axis::description(1.,2500.,true,"#zeta_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),
   /* 47 */ Types::Hist::identify("LCR_sign_incl","TH2D","RES",Types::Axis::description(1.,2500.,true,"#zeta_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),
   /* 48 */ Types::Hist::identify("MLR_sign_incl","TH2D","RES",Types::Axis::description(1.,2500.,true,"#zeta_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),
   /* 49 */ Types::Hist::identify("EMR_sign_e300","TH2D","RES",Types::Axis::description(1.,2500.,true,"#zeta_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),
   /* 50 */ Types::Hist::identify("LCR_sign_e300","TH2D","RES",Types::Axis::description(1.,2500.,true,"#zeta_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),
   /* 51 */ Types::Hist::identify("MLR_sign_e300","TH2D","RES",Types::Axis::description(1.,2500.,true,"#zeta_{clus}^{em}"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),
   /* 52 */ Types::Hist::identify("EMR_ptd__incl","TH2D","RES",Types::Axis::description(0.,1.,false,"p_{t}D"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),
   /* 53 */ Types::Hist::identify("LCR_ptd__incl","TH2D","RES",Types::Axis::description(0.,1.,false,"p_{t}D"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),
   /* 54 */ Types::Hist::identify("MLR_ptd__incl","TH2D","RES",Types::Axis::description(0.,1.,false,"p_{t}D"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),
   /* 55 */ Types::Hist::identify("EMR_ptd__e300","TH2D","RES",Types::Axis::description(0.,1.,false,"p_{t}D"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),
   /* 56 */ Types::Hist::identify("LCR_ptd__e300","TH2D","RES",Types::Axis::description(0.,1.,false,"p_{t}D"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 57 */ Types::Hist::identify("MLR_ptd__e300","TH2D","RES",Types::Axis::description(0.,1.,false,"p_{t}D"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 58 */ Types::Hist::identify("EMR_time_incl","TH2D","RES",Types::Axis::description(0.,5.,false,"#sigma_{t} [ns]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 59 */ Types::Hist::identify("LCR_time_incl","TH2D","RES",Types::Axis::description(0.,5.,false,"#sigma_{t} [ns]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 60 */ Types::Hist::identify("MLR_time_incl","TH2D","RES",Types::Axis::description(0.,5.,false,"#sigma_{t} [ns]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  )),  
   /* 61 */ Types::Hist::identify("EMR_time_e300","TH2D","RES",Types::Axis::description(0.,5.,false,"#sigma_{t} [ns]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{em}/E_{clus}^{dep}"  )),  
   /* 62 */ Types::Hist::identify("LCR_time_e300","TH2D","RES",Types::Axis::description(0.,5.,false,"#sigma_{t} [ns]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{had}/E_{clus}^{dep}" )),  
   /* 63 */ Types::Hist::identify("MLR_time_e300","TH2D","RES",Types::Axis::description(0.,5.,false,"#sigma_{t} [ns]"),Types::Axis::description(1.,-1.,false,"E_{clus}^{ml}/E_{clus}^{dep}"  ))  
  };   
       
  // plot title lookup 
  static const std::map<std::string,std::string> knownPlots = {
   /* 00 */ { "ClusRapAll","y_{clus}^{em} (all clusters)"              },          
   /* 01 */ { "ClusRapAcc","y_{clus}^{em} (E_{clus}^{dep} > 300 MeV)"  },          
   /* 02 */ { "ClusDepAll","E_{clus}^{dep} (all clusters)"             },  
   /* 03 */ { "ClusDepAcc","E_{clus}^{dep} (E_{clus}^{dep} > 300 MeV)" },  
   /* 04 */ { "ClusEemAll","E_{clus}^{em} (all clusters)"              },  
   /* 05 */ { "ClusEemAcc","E_{clus}^{em} (E_{clus}^{dep} > 300 MeV)"  },  
   /* 06 */ { "ClusLcwAll","E_{clus}^{had} (all clusters)"             },  
   /* 07 */ { "ClusLcwAcc","E_{clus}^{had} (E_{clus}^{dep} > 300 MeV)" },  
   /* 08 */ { "ClusEmlAll","E_{clus}^{ml} (all clusters)"              },  
   /* 09 */ { "ClusEmlAcc","E_{clus}^{ml} (E_{clus}^{dep} > 300 MeV)"  },  
   /* 10 */ { "EMR_Edep_incl","E_{clus}^{em}/E_{clus}^{dep}(E_{clus}^{dep})"  },  
   /* 11 */ { "LCR_Edep_incl","E_{clus}^{had}/E_{clus}^{dep}(E_{clus}^{dep})" },  
   /* 12 */ { "MLR_Edep_incl","E_{clus}^{ml}/E_{clus}^{dep}(E_{clus}^{dep})"  },  
   /* 13 */ { "EMR_Edep_e300","E_{clus}^{em}/E_{clus}^{dep}(E_{clus}^{dep}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 14 */ { "LCR_Edep_e300","E_{clus}^{had}/E_{clus}^{dep}(E_{clus}^{dep}) (E_{clus}^{dep} > 300 MeV)" },
   /* 15 */ { "MLR_Edep_e300","E_{clus}^{ml}/E_{clus}^{dep}(E_{clus}^{dep}) (E_{clus}^{dep} > 300 MeV)"  },
   /* 16 */ { "EMR_Efrc_incl","E_{clus}^{em}/E_{clus}^{dep} (E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM})"  },  
   /* 17 */ { "LCR_Efrc_incl","E_{clus}^{had}/E_{clus}^{dep}(E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM})" },  
   /* 18 */ { "MLR_Efrc_incl","E_{clus}^{ml}/E_{clus}^{dep} (E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM})"  },  
   /* 19 */ { "EMR_Efrc_e300","E_{clus}^{em}/E_{clus}^{dep} (E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 20 */ { "LCR_Efrc_e300","E_{clus}^{had}/E_{clus}^{dep}(E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}) (E_{clus}^{dep} > 300 MeV)" },
   /* 21 */ { "MLR_Efrc_e300","E_{clus}^{ml}/E_{clus}^{dep} (E_{clus}^{EM}/#sum^{}E_{clus,i}^{EM}) (E_{clus}^{dep} > 300 MeV)"  },
   /* 22 */ { "EMR_rho__incl","E_{clus}^{em}/E_{clus}^{dep}(#rho_{clus})"  },  
   /* 23 */ { "LCR_rho__incl","E_{clus}^{had}/E_{clus}^{dep}(#rho_{clus})" },  
   /* 24 */ { "MLR_rho__incl","E_{clus}^{ml}/E_{clus}^{dep}(#rho_{clus})"  },  
   /* 25 */ { "EMR_rho__e300","E_{clus}^{em}/E_{clus}^{dep}(#rho_{clus}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 26 */ { "LCR_rho__e300","E_{clus}^{had}/E_{clus}^{dep}(#rho_{clus}) (E_{clus}^{dep} > 300 MeV)" },  
   /* 27 */ { "MLR_rho__e300","E_{clus}^{ml}/E_{clus}^{dep}(#rho_{clus}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 28 */ { "EMR_lamb_incl","E_{clus}^{em}/E_{clus}^{dep}(#lambda_{clus}) " },  
   /* 29 */ { "LCR_lamb_incl","E_{clus}^{had}/E_{clus}^{dep}(#lambda_{clus})" },  
   /* 30 */ { "MLR_lamb_incl","E_{clus}^{ml}/E_{clus}^{dep}(#lambda_{clus}) " },  
   /* 31 */ { "EMR_lamb_e300","E_{clus}^{em}/E_{clus}^{dep}(#lambda_{clus}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 32 */ { "LCR_lamb_e300","E_{clus}^{had}/E_{clus}^{dep}(#lambda_{clus}) (E_{clus}^{dep} > 300 MeV)" },  
   /* 33 */ { "MLR_lamb_e300","E_{clus}^{ml}/E_{clus}^{dep}(#lambda_{clus}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 34 */ { "EMR_long_incl","E_{clus}^{em}/E_{clus}^{dep}(#LTm^{2}_{long}#GT)"  },  
   /* 35 */ { "LCR_long_incl","E_{clus}^{had}/E_{clus}^{dep}(#LTm^{2}_{long}#GT)" },
   /* 36 */ { "MLR_long_incl","E_{clus}^{ml}/E_{clus}^{dep}(#LTm^{2}_{long}#GT)"  },  
   /* 37 */ { "EMR_long_e300","E_{clus}^{em}/E_{clus}^{dep}(#LTm^{2}_{long}#GT) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 38 */ { "LCR_long_e300","E_{clus}^{had}/E_{clus}^{dep}(#LTm^{2}_{long}#GT) (E_{clus}^{dep} > 300 MeV)" },  
   /* 39 */ { "MLR_long_e300","E_{clus}^{ml}/E_{clus}^{dep}(#LTm^{2}_{long}#GT) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 40 */ { "EMR_lat__incl","E_{clus}^{em}/E_{clus}^{dep}(#LTm^{2}_{lat}#GT)"  },  
   /* 41 */ { "LCR_lat__incl","E_{clus}^{had}/E_{clus}^{dep}(#LTm^{2}_{lat}#GT)" },  
   /* 42 */ { "MLR_lat__incl","E_{clus}^{ml}/E_{clus}^{dep}(#LTm^{2}_{lat}#GT)"  },  
   /* 43 */ { "EMR_lat__e300","E_{clus}^{em}/E_{clus}^{dep}(#LTm^{2}_{lat}#GT) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 44 */ { "LCR_lat__e300","E_{clus}^{had}/E_{clus}^{dep}(#LTm^{2}_{lat}#GT) (E_{clus}^{dep} > 300 MeV)" },  
   /* 45 */ { "MLR_lat__e300","E_{clus}^{ml}/E_{clus}^{dep}(#LTm^{2}_{lat}#GT) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 46 */ { "EMR_sign_incl","E_{clus}^{em}/E_{clus}^{dep}(#zeta_{clus}^{em})"  },  
   /* 47 */ { "LCR_sign_incl","E_{clus}^{had}/E_{clus}^{dep}(#zeta_{clus}^{em})" },
   /* 48 */ { "MLR_sign_incl","E_{clus}^{ml}/E_{clus}^{dep}(#zeta_{clus}^{em})"  },  
   /* 49 */ { "EMR_sign_e300","E_{clus}^{em}/E_{clus}^{dep}(#zeta_{clus}^{em}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 50 */ { "LCR_sign_e300","E_{clus}^{had}/E_{clus}^{dep}(#zeta_{clus}^{em}) (E_{clus}^{dep} > 300 MeV)" },          
   /* 51 */ { "MLR_sign_e300","E_{clus}^{ml}/E_{clus}^{dep}(#zeta_{clus}^{em}) (E_{clus}^{dep} > 300 MeV)"  },          
   /* 52 */ { "EMR_ptd__incl","E_{clus}^{em}/E_{clus}^{dep}(p_{T}D)"  },        
   /* 53 */ { "LCR_ptd__incl","E_{clus}^{had}/E_{clus}^{dep} p_{T}D)" },          
   /* 54 */ { "MLR_ptd__incl","E_{clus}^{ml}/E_{clus}^{dep}(p_{T}D)"  },          
   /* 55 */ { "EMR_ptd__e300","E_{clus}^{em}/E_{clus}^{dep}(p_{T}D) (E_{clus}^{dep} > 300 MeV)"  },          
   /* 56 */ { "LCR_ptd__e300","E_{clus}^{had}/E_{clus}^{dep} p_{T}D) (E_{clus}^{dep} > 300 MeV)" },
   /* 57 */ { "MLR_ptd__e300","E_{clus}^{ml}/E_{clus}^{dep}(p_{T}D) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 58 */ { "EMR_time_incl","E_{clus}^{em}/E_{clus}^{dep}(#sigma_{t})"  },  
   /* 59 */ { "LCR_time_incl","E_{clus}^{had}/E_{clus}^{dep}(#sigma_{t})" },  
   /* 60 */ { "MLR_time_incl","E_{clus}^{ml}/E_{clus}^{dep}(#sigma_{t})"  },  
   /* 61 */ { "EMR_time_e300","E_{clus}^{em}/E_{clus}^{dep}(#sigma_{t}) (E_{clus}^{dep} > 300 MeV)"  },  
   /* 62 */ { "LCR_time_e300","E_{clus}^{had}/E_{clus}^{dep}(#sigma_{t}) (E_{clus}^{dep} > 300 MeV)" },  
   /* 63 */ { "MLR_time_e300","E_{clus}^{ml}/E_{clus}^{dep}(#sigma_{t}) (E_{clus}^{dep} > 300 MeV)"  }
  }; 


  // Canvas descriptor lookup
  std::map<std::string,Types::Canvas::Identifier>  knownCanvas = {
   { Types::Hist::name(knownHists.at( 0)), { "ClusterRapidityAll",         "cluster_rapidity_em_all"        } },          
   { Types::Hist::name(knownHists.at( 1)), { "ClusterRapidityAcc",         "cluster_rapidity_em_acc"        } },          
   { Types::Hist::name(knownHists.at( 2)), { "ClusterEnergyDepAll",        "cluster_energy_dep_all"         } },  
   { Types::Hist::name(knownHists.at( 3)), { "ClusterEnergyDepAcc",        "cluster_energy_dep_acc"         } },  
   { Types::Hist::name(knownHists.at( 4)), { "ClusterEnergyEemAll",        "cluster_energy_em_all"          } },  
   { Types::Hist::name(knownHists.at( 5)), { "ClusterEnergyEemAcc",        "cluster_energy_em_acc"          } },  
   { Types::Hist::name(knownHists.at( 6)), { "ClusterEnergyLcwAll",        "cluster_energy_dep_all"         } },  
   { Types::Hist::name(knownHists.at( 7)), { "ClusterEnergyLcwAcc",        "cluster_energy_dep_acc"         } },  
   { Types::Hist::name(knownHists.at( 8)), { "ClusterEnergyEmlAll",        "cluster_energy_ml_all"          } },  
   { Types::Hist::name(knownHists.at( 9)), { "ClusterEnergyEmlAcc",        "cluster_energy_ml_acc"          } },  
   { Types::Hist::name(knownHists.at(10)), { "ClusterResponseEMvsEdepIncl","cluster_em_response_eclus_incl" } },  
   { Types::Hist::name(knownHists.at(11)), { "ClusterResponseLCvsEdepIncl","cluster_lc_response_eclus_incl" } },  
   { Types::Hist::name(knownHists.at(12)), { "ClusterResponseMLvsEdepIncl","cluster_ml_response_eclus_incl" } },  
   { Types::Hist::name(knownHists.at(13)), { "ClusterResponseEMvsEdepHigh","cluster_em_response_eclus_e300" } },  
   { Types::Hist::name(knownHists.at(14)), { "ClusterResponseLCvsEdepHigh","cluster_lc_response_eclus_e300" } },
   { Types::Hist::name(knownHists.at(15)), { "ClusterResponseMLvsEdepHigh","cluster_ml_response_eclus_e300" } },  
   { Types::Hist::name(knownHists.at(16)), { "ClusterResponseEMvsEfrcIncl","cluster_em_response_efrac_incl" } },  
   { Types::Hist::name(knownHists.at(17)), { "ClusterResponseLCvsEfrcIncl","cluster_lc_response_efrac_incl" } },  
   { Types::Hist::name(knownHists.at(18)), { "ClusterResponseMLvsEfrcIncl","cluster_ml_response_efrac_incl" } },  
   { Types::Hist::name(knownHists.at(19)), { "ClusterResponseEMvsEfrcHigh","cluster_em_response_efrac_e300" } },  
   { Types::Hist::name(knownHists.at(20)), { "ClusterResponseLCvsEfrcHigh","cluster_lc_response_efrac_e300" } },
   { Types::Hist::name(knownHists.at(21)), { "ClusterResponseMLvsEfrcHigh","cluster_ml_response_efrac_e300" } },  
   { Types::Hist::name(knownHists.at(22)), { "ClusterResponseEMvsRhoIncl", "cluster_em_response_rho_incl"   } },  
   { Types::Hist::name(knownHists.at(23)), { "ClusterResponseLCvsRhoIncl", "cluster_lc_response_rho_incl"   } },  
   { Types::Hist::name(knownHists.at(24)), { "ClusterResponseMLvsRhoIncl", "cluster_ml_response_rho_incl"   } },  
   { Types::Hist::name(knownHists.at(25)), { "ClusterResponseEMvsRhoHigh", "cluster_em_response_rho_e300"   } },  
   { Types::Hist::name(knownHists.at(26)), { "ClusterResponseLCvsRhoHigh", "cluster_lc_response_rho_e300"   } },  
   { Types::Hist::name(knownHists.at(27)), { "ClusterResponseMLvsRhoHigh", "cluster_ml_response_rho_e300"   } },
   { Types::Hist::name(knownHists.at(28)), { "ClusterResponseEMvsLamIncl", "cluster_em_response_lam_incl"   } },  
   { Types::Hist::name(knownHists.at(29)), { "ClusterResponseLCvsLamIncl", "cluster_lc_response_lam_incl"   } },  
   { Types::Hist::name(knownHists.at(30)), { "ClusterResponseMLvsLamIncl", "cluster_ml_response_lam_incl"   } },  
   { Types::Hist::name(knownHists.at(31)), { "ClusterResponseEMvsLamHigh", "cluster_em_response_lam_e300"   } },  
   { Types::Hist::name(knownHists.at(32)), { "ClusterResponseLCvsLamHigh", "cluster_lc_response_lam_e300"   } },  
   { Types::Hist::name(knownHists.at(33)), { "ClusterResponseMLvsLamHigh", "cluster_ml_response_lam_e300"   } },  
   { Types::Hist::name(knownHists.at(34)), { "ClusterResponseEMvsLongIncl","cluster_em_response_long_incl"  } },  
   { Types::Hist::name(knownHists.at(35)), { "ClusterResponseLCvsLongIncl","cluster_lc_response_long_incl"  } },
   { Types::Hist::name(knownHists.at(36)), { "ClusterResponseMLvsLongIncl","cluster_ml_response_long_incl"  } },  
   { Types::Hist::name(knownHists.at(37)), { "ClusterResponseEMvsLongHigh","cluster_em_response_long_e300"  } },  
   { Types::Hist::name(knownHists.at(38)), { "ClusterResponseLCvsLongHigh","cluster_lc_response_long_e300"  } },  
   { Types::Hist::name(knownHists.at(39)), { "ClusterResponseMLvsLongHigh","cluster_ml_response_long_e300"  } },  
   { Types::Hist::name(knownHists.at(40)), { "ClusterResponseEMvsLatIncl", "cluster_em_response_lat_incl"   } },  
   { Types::Hist::name(knownHists.at(41)), { "ClusterResponseLCvsLatIncl", "cluster_lc_response_lat_incl"   } },  
   { Types::Hist::name(knownHists.at(42)), { "ClusterResponseMLvsLatIncl", "cluster_ml_response_lat_incl"   } },  
   { Types::Hist::name(knownHists.at(43)), { "ClusterResponseEMvsLatHigh", "cluster_em_response_lat_e300"   } },  
   { Types::Hist::name(knownHists.at(44)), { "ClusterResponseLCvsLatHigh", "cluster_lc_response_lat_e300"   } },  
   { Types::Hist::name(knownHists.at(45)), { "ClusterResponseMLvsLatHigh", "cluster_ml_response_lat_e300"   } },  
   { Types::Hist::name(knownHists.at(46)), { "ClusterResponseEMvsSignIncl","cluster_em_response_sign_incl"  } },  
   { Types::Hist::name(knownHists.at(47)), { "ClusterResponseLCvsSignIncl","cluster_lc_response_sign_incl"  } },
   { Types::Hist::name(knownHists.at(48)), { "ClusterResponseMLvsSignIncl","cluster_ml_response_sign_incl"  } },  
   { Types::Hist::name(knownHists.at(49)), { "ClusterResponseEMvsSignHigh","cluster_em_response_sign_e300"  } },  
   { Types::Hist::name(knownHists.at(50)), { "ClusterResponseLCvsSignHigh","cluster_lc_response_sign_e300"  } },
   { Types::Hist::name(knownHists.at(51)), { "ClusterResponseMLvsSignHigh","cluster_ml_response_sign_e300"  } },
   { Types::Hist::name(knownHists.at(52)), { "ClusterResponseEMvsPtDIncl", "cluster_em_response_ptd_incl"   } },        
   { Types::Hist::name(knownHists.at(53)), { "ClusterResponseLCvsPtDIncl", "cluster_lc_response_ptd_incl"   } },          
   { Types::Hist::name(knownHists.at(54)), { "ClusterResponseMLvsPtDIncl", "cluster_ml_response_ptd_incl"   } },          
   { Types::Hist::name(knownHists.at(55)), { "ClusterResponseEMvsPtDHigh", "cluster_em_response_ptd_e300"   } },          
   { Types::Hist::name(knownHists.at(56)), { "ClusterResponseLCvsPtDHigh", "cluster_lc_response_ptd_e300"   } },
   { Types::Hist::name(knownHists.at(57)), { "ClusterResponseMLvsPtDHigh", "cluster_ml_response_ptd_e300"   } },  
   { Types::Hist::name(knownHists.at(58)), { "ClusterResponseEMvsTimeIncl","cluster_em_response_time_incl"  } },  
   { Types::Hist::name(knownHists.at(59)), { "ClusterResponseLCvsTimeIncl","cluster_lc_response_time_incl"  } },  
   { Types::Hist::name(knownHists.at(60)), { "ClusterResponseMLvsTimeIncl","cluster_ml_response_time_incl"  } },  
   { Types::Hist::name(knownHists.at(61)), { "ClusterResponseEMvsTimeHigh","cluster_em_response_time_e300"  } },  
   { Types::Hist::name(knownHists.at(62)), { "ClusterResponseLCvsTimeHigh","cluster_lc_response_time_e300"  } },
   { Types::Hist::name(knownHists.at(63)), { "ClusterResponseMLvsTimeHigh","cluster_ml_response_time_e300"  } }
  };

  // specialities
  std::map<std::string,bool> doResponseLines = { 
   /* 00 */ { "ClusRapAll", false },          
   /* 01 */ { "ClusRapAcc", false },          
   /* 02 */ { "ClusDepAll", false },  
   /* 03 */ { "ClusDepAcc", false },  
   /* 04 */ { "ClusEemAll", false },  
   /* 05 */ { "ClusEemAcc", false },  
   /* 06 */ { "ClusLcwAll", false },  
   /* 07 */ { "ClusLcwAcc", false },  
   /* 08 */ { "ClusEmlAll", false },  
   /* 09 */ { "ClusEmlAcc", false },  
   /* 10 */ { "EMR_Edep_incl", true  },  
   /* 11 */ { "LCR_Edep_incl", true  },  
   /* 12 */ { "MLR_Edep_incl", true  },  
   /* 13 */ { "EMR_Edep_e300", true  },  
   /* 14 */ { "LCR_Edep_e300", true  },
   /* 15 */ { "MLR_Edep_e300", true  },  
   /* 16 */ { "EMR_Efrc_incl", true  },  
   /* 17 */ { "LCR_Efrc_incl", true  },  
   /* 18 */ { "MLR_Efrc_incl", true  },  
   /* 19 */ { "EMR_Efrc_e300", true  },  
   /* 20 */ { "LCR_Efrc_e300", true  },
   /* 21 */ { "MLR_Efrc_e300", true  },  
   /* 22 */ { "EMR_rho__incl", true  },  
   /* 23 */ { "LCR_rho__incl", true  },  
   /* 24 */ { "MLR_rho__incl", true  },  
   /* 25 */ { "EMR_rho__e300", true  },  
   /* 26 */ { "LCR_rho__e300", true  },  
   /* 27 */ { "MLR_rho__e300", true  },  
   /* 28 */ { "EMR_lamb_incl", true  },  
   /* 29 */ { "LCR_lamb_incl", true  },  
   /* 30 */ { "MLR_lamb_incl", true  },  
   /* 31 */ { "EMR_lamb_e300", true  },  
   /* 32 */ { "LCR_lamb_e300", true  },  
   /* 33 */ { "MLR_lamb_e300", true  },  
   /* 34 */ { "EMR_long_incl", true  },  
   /* 35 */ { "LCR_long_incl", true  },
   /* 36 */ { "MLR_long_incl", true  },  
   /* 37 */ { "EMR_long_e300", true  },  
   /* 38 */ { "LCR_long_e300", true  },  
   /* 39 */ { "MLR_long_e300", true  },  
   /* 40 */ { "EMR_lat__incl", true  },  
   /* 41 */ { "LCR_lat__incl", true  },  
   /* 42 */ { "MLR_lat__incl", true  },  
   /* 43 */ { "EMR_lat__e300", true  },  
   /* 44 */ { "LCR_lat__e300", true  },  
   /* 45 */ { "MLR_lat__e300", true  },  
   /* 46 */ { "EMR_sign_incl", true  },  
   /* 47 */ { "LCR_sign_incl", true  },
   /* 48 */ { "MLR_sign_incl", true  },  
   /* 49 */ { "EMR_sign_e300", true  },  
   /* 50 */ { "LCR_sign_e300", true  },          
   /* 51 */ { "MLR_sign_e300", true  },          
   /* 52 */ { "EMR_ptd__incl", true  },        
   /* 53 */ { "LCR_ptd__incl", true  },          
   /* 54 */ { "MLR_ptd__incl", true  },          
   /* 55 */ { "EMR_ptd__e300", true  },          
   /* 56 */ { "LCR_ptd__e300", true  },
   /* 57 */ { "MLR_ptd__e300", true  },  
   /* 58 */ { "EMR_time_incl", true  },  
   /* 59 */ { "LCR_time_incl", true  },  
   /* 60 */ { "MLR_time_incl", true  },  
   /* 61 */ { "EMR_time_e300", true  },  
   /* 62 */ { "LCR_time_e300", true  },  
   /* 63 */ { "MLR_time_e300", true  }  
  }; 
  
  //////////////
  // Plotting //
  //////////////

  // general settings
  // gStyle->SetTitleSize(0.75*gStyle->GetTitleSize("x"),"x");
  // gStyle->SetTitleSize(0.75*gStyle->GetTitleSize("y"),"y");
  // gStyle->SetTitleOffset(1.25*gStyle->GetTitleOffset("x"),"x");

  // plotting cache
  std::map<std::string,Types::Plot::Content> plotLookup; 
  // set plot frame
  double prw(gStyle->GetPadRightMargin());                // remember old style right frame
  gStyle->SetPadRightMargin(gStyle->GetPadLeftMargin());  // set left and right frame to same width
  // get directory name
  std::string dname("./");
  auto floc = fdir.find_last_of('/'); 
  if ( floc != std::string::npos ) { dname = fdir.substr(0,floc); }
  // open file
  TFile* fptr = new TFile(fileName.c_str(),"READ");
  if ( fptr == nullptr ) { printf("[plotClusters] ABRT cannot allocate file \042%s\042\n",fileName.c_str()); return; }
  // allocate all plots 
  for ( auto pdescr : knownHists ) {
    const std::string& rname = Types::Hist::name(pdescr); 
    const std::string& rtype = Types::Hist::type(pdescr);
    auto fplot(knownPlots.find(rname));
    std::string ptitle = fplot != knownPlots.end() ? fplot->second : ""; 
    // printf("[plotClusters] INFO access histogram type %s\n",rtype.c_str());
    if ( rtype == "TH1D" ) { 
      TH1D* hptr = (TH1D*)fptr->FindObjectAny(rname.c_str()); 
      if ( hptr != nullptr ) { 
	printf("[plotClusters] INFO booked %s at %p name = \042%s\042\n",rtype.c_str(),(void*)hptr,hptr->GetName());
	plotLookup[rname] = { pdescr, hptr, false, (TGraph*)0, (TGraph*)0, ptitle };
      }
    } else if ( rtype == "TH2D" ) { 
      TH2D* hptr = (TH2D*)fptr->FindObjectAny(rname.c_str()); 
      if ( hptr != nullptr ) {
 	printf("[plotClusters] INFO booked %s at %p name = \042%s\042 => ",rtype.c_str(),(void*)hptr,hptr->GetName());
	plotLookup[rname] = { pdescr, hptr, true, (TGraph*)HistUtils::graph(hptr,"response_rms",2,HistUtils::Mean,"RMS",minEntries), (TGraph*)HistUtils::graph(hptr,"response_err",2,HistUtils::Mean,"ERROR",minEntries), ptitle }; 
      }
    }
  }
  // open output file
  //  std::string prefix = fileName.front() == 'J' ? fileName.substr(0,fileName.find_first_of('.')) : fileName.substr(0,fileName.find_first_of('_'));
  if ( (floc = dname.find_last_of('/')) != std::string::npos ) { dname = dname.substr(floc+1); }
  auto fpart = directoryToParticle.find(dname); 
  std::string prefix = fpart == directoryToParticle.end() ? fileName.substr(0,fileName.find_first_of('.')) : fpart->second;
  TFile* outFile = new TFile(TString::Format("%s_summary.root",fileName.substr(0,fileName.find_first_of('.')).c_str()).Data(),"RECREATE"); 
  // get the graphs for all plots
  printf("[plotClusters] INFO found %zu distributions\n",plotLookup.size());
  for ( auto entry : plotLookup ) {
    // get configurations for canvas
    const std::string&          rname = entry.first;
    const std::string&          cname = Types::Canvas::name(knownCanvas.at(rname));
    const Types::Plot::Content& pcont = entry.second;  
    // pick up plots
    TH1* hptr = Types::Plot::distribution(pcont); 
    if ( hptr == nullptr ) { continue; }      // no valid figure to plot 
    // create new canvas and set up plot
    TCanvas* cv = new TCanvas(cname.c_str(),cname.c_str());
    const Types::Hist::Identifier& hid = Types::Plot::histogram(pcont);  
    Types::Axis::Descriptor xdescr = Types::Hist::xAxis(hid); double xmin = Types::Axis::xmin(xdescr); double xmax = Types::Axis::xmax(xdescr); const std::string& axt = Types::Axis::title(xdescr); // x-axis
    Types::Axis::Descriptor ydescr = Types::Hist::yAxis(hid); double ymin = Types::Axis::xmin(ydescr); double ymax = Types::Axis::xmax(ydescr); const std::string& ayt = Types::Axis::title(ydescr); // x-axis 
    if ( Types::Axis::isLog(xdescr) ) { cv->SetLogx(); }
    if ( Types::Axis::isLog(ydescr) ) { cv->SetLogy(); }
    // setting up plot
    std::string opts("hist");
    const std::string& ptitle = Types::Plot::title(pcont);
    if ( Types::Hist::type(hid) == "TH2D" ) { cv->SetLogz(); opts="colz"; } else { hptr->SetFillColor(kCyan); hptr->SetLineColor(kBlue); }
    if ( xmax > xmin ) { hptr->GetXaxis()->SetRangeUser(xmin,xmax); } else { xmin = hptr->GetXaxis()->GetXmin(); xmax = hptr->GetXaxis()->GetXmax(); } 
    if ( axt != "" ) { hptr->GetXaxis()->SetTitle(axt.c_str())  ; } 
    if ( ymax > ymin ) { hptr->GetYaxis()->SetRangeUser(ymin,ymax); } else { ymin = hptr->GetYaxis()->GetXmin(); ymax = hptr->GetYaxis()->GetXmax(); } 
    if ( ayt != "" ) { hptr->GetYaxis()->SetTitle(ayt.c_str())  ; }
    // plot
    hptr->Draw(opts.c_str());
    if ( Types::Plot::doGraph(pcont) ) { 
      TGraphAsymmErrors* grptr = (TGraphAsymmErrors*)Types::Plot::graph(pcont,"RMS"  );
      TGraphAsymmErrors* geptr = (TGraphAsymmErrors*)Types::Plot::graph(pcont,"ERROR");
      if ( grptr != nullptr ) { 
	grptr->SetLineStyle(1)   ; grptr->SetLineColorAlpha(kRed,0.25) ; grptr->SetLineWidth(2)   ;/* gptr->SetFillColorAlpha(kGreen,0.75); */ 
	grptr->SetMarkerStyle(20); grptr->SetMarkerColor(kRed)         ; grptr->SetMarkerSize(0.5); 
	grptr->Draw("same p");
	grptr->SetName(TString::Format("%s_graph_mean_rms",hptr->GetName()).Data()); 
	grptr->Write();
	if ( doResponseLines.at(rname) ) {
	  TLine* cl = new TLine(xmin,1.0,xmax,1.0); cl->SetLineWidth(1); cl->SetLineStyle(9); cl->Draw("lsame");
	  TLine* ul = new TLine(xmin,1.1,xmax,1.1); ul->SetLineWidth(1); ul->SetLineStyle(7); ul->Draw("lsame");
	  TLine* dl = new TLine(xmin,0.9,xmax,0.9); dl->SetLineWidth(1); dl->SetLineStyle(7); dl->Draw("lsame");
	  TLine* hl = new TLine(xmin,1.2,xmax,1.2); hl->SetLineWidth(1); hl->SetLineStyle(2); hl->Draw("lsame");
	  TLine* ll = new TLine(xmin,0.8,xmax,0.8); ll->SetLineWidth(1); ll->SetLineStyle(2); ll->Draw("lsame");
	}
      }
      if ( geptr != nullptr ) { 
	geptr->SetName(TString::Format("%s_graph_mean_err",hptr->GetName()).Data()); 
	geptr->Write();
      } 
    }
    // title
    if ( ptitle != "" ) { 
      double xtit(1.-gStyle->GetPadRightMargin());
      double ytit(1.-gStyle->GetPadTopMargin()/2.);
      TLatex* tlat = new TLatex(); tlat->SetNDC(); tlat->SetTextSize(0.5*tlat->GetTextSize()); tlat->SetTextAlign(32); 
      tlat->DrawLatex(xtit,ytit,TString::Format("[ATLAS %s topo-cluster |y_{clus}| < 0.8]: %s",prefix.c_str(),ptitle.c_str()).Data());
    }
    // print 
    cv->RedrawAxis();
    Types::Canvas::print(cv,knownCanvas.at(rname),fdir,true,true);
    // save
    cv->Write(); 
    hptr->Write();
    printf("[plotClusters] INFO canvas \042%s\042 with histogram %s written to file \042%s\042\n",cv->GetName(),hptr->GetName(),outFile->GetName());
  }
  outFile->Close();
}
