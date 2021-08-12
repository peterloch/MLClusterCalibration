
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h> 
#include <TCanvas.h>
#include <TLatex.h>
#include <TString.h>

#include "HistUtils.h"

#include <string>
#include <vector>
#include <tuple>
#include <map>

#include <cstdio>

namespace Types {

  /////////////////////
  // Axis descriptor //
  /////////////////////
  namespace Axis {
    // Position   Content
    //    0       log(value) if true (default false)
    //    1       xmin (default 1.)
    //    2       xmax (default -1.)
    //    3       title
    //
    // xmin > xmax => automatic axis range
    typedef std::tuple<bool,double,double,std::string> Descriptor;
    // accessors
    static bool               isLog(const Descriptor& descr) { return std::get<0>(descr); }
    static double             xmin (const Descriptor& descr) { return std::get<1>(descr); } 
    static double             xmax (const Descriptor& descr) { return std::get<2>(descr); } 
    static const std::string& title(const Descriptor& descr) { return std::get<3>(descr); } 
    // helpers
    static Descriptor description(double axmin=1.,double axmax =-1.,bool aIsLog=false,const std::string& atitle="") { return { aIsLog, axmin, axmax, atitle }; } 
  }

  //////////////////////////
  // Histogram identifier //
  //////////////////////////
   namespace Hist { 
     // Position   Content
     //    0       name of histogram
     //    1       type of histogram 
     //    2       category of histogram
     //    3       x-axis descriptor
     //    4       y-axis descriptor
     typedef std::tuple<std::string,std::string,std::string,Axis::Descriptor,Axis::Descriptor>  Identifier;
     // accessors
     static const std::string& name      (const Identifier& id) { return std::get<0>(id); }
     static const std::string& type      (const Identifier& id) { return std::get<1>(id); }
     static const std::string& category  (const Identifier& id) { return std::get<2>(id); }
     static const Axis::Descriptor& xAxis(const Identifier& id) { return std::get<3>(id); }
     static const Axis::Descriptor& yAxis(const Identifier& id) { return std::get<4>(id); }
     // helpers
     static Identifier identify(const std::string& hname,const std::string& htitle,const std::string& hcategory,const Axis::Descriptor& hxaxis,const Axis::Descriptor& hyaxis) {
       return { hname, htitle, hcategory, hxaxis, hyaxis };
     }
   }

  //////////////////
  // Plotter type //
  //////////////////
  namespace Plot { 
    // Position   Content
    //    0       histogram identifier
    //    1       pointer to distribution object
    //    2       true/false flag indicating a graph should be calculated for distribution
    //    3       pointer to graph object
    //    4       plot title
    typedef std::tuple<Hist::Identifier,TH1*,bool,TGraph*,std::string> Content;
    // accessors
    static const Hist::Identifier& histogram   (const Content& pcont) { return std::get<0>(pcont); }
    static       TH1*              distribution(const Content& pcont) { return std::get<1>(pcont); }
    static       bool              doGraph     (const Content& pcont) { return std::get<2>(pcont); }
    static       TGraph*           graph       (const Content& pcont) { return std::get<3>(pcont); }
    static const std::string&      title       (const Content& pcont) { return std::get<4>(pcont); } 
    // helpers
    static Content content(const Hist::Identifier& phid,TH1* phptr=(TH1*)0,bool pdograph=false,TGraph* pgptr=(TGraph*)0,const std::string& ptitle="") { 
      return { phid, phptr, pdograph, pgptr, ptitle };
    } 
  }

  ///////////////////////
  // Canvas identifier //
  ///////////////////////
  namespace Canvas {
    // Position   Content
    //    0       canvas name and title
    //    1       file name for plots 
    typedef std::tuple<std::string,std::string> Identifier;
    // accessors
    static const std::string& name(const Identifier& id) { return std::get<0>(id); }
    static const std::string& file(const Identifier& id) { return std::get<1>(id); }
    // helpers
    static void print(TCanvas* pcvs,const Identifier& id,const std::string& fdir="plots",bool pdfFile=true,bool pngFile=true) {
      static char _buffer[1024]; 
      if ( pcvs == nullptr ) { return; } 
      if ( pdfFile ) { sprintf(_buffer,"%s/%s.pdf",fdir.c_str(),file(id).c_str()); pcvs->Print(_buffer); }
      if ( pngFile ) { sprintf(_buffer,"%s/%s.png",fdir.c_str(),file(id).c_str()); pcvs->Print(_buffer); }
    }  
    static Identifier identify(const std::string& cname,const std::string& cfile="") { return { cname, cfile }; }
  }
}

void plotClusterJet(const std::string& fileName="JZ3.full.topo-cluster.hist.root",const std::string& fdir="plots",double minEntries=50.) {
              
  // known histogram identifiers
  static const std::vector<Types::Hist::Identifier> knownHists = { 
   /* 00 */ Types::Hist::identify("AziJEMS"        ,"TH1D","JET",Types::Axis::description(   1.,  -1.,false,"#phi_{jet}^{ConstScale} [rad]"                       ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 01 */ Types::Hist::identify("AziJJES"        ,"TH1D","JET",Types::Axis::description(   1.,  -1.,false,"#phi_{jet}^{JES} [rad]"                              ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 02 */ Types::Hist::identify("ClLCW_Rap_pt020","TH1D","CLU",Types::Axis::description(   1.,  -1.,false,"y_{clus}^{LCW}"                                      ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 03 */ Types::Hist::identify("ClLCW_Rap_pt040","TH1D","CLU",Types::Axis::description(   1.,  -1.,false,"y_{clus}^{LCW}"                                      ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 04 */ Types::Hist::identify("ClLCW_Rap_pt060","TH1D","CLU",Types::Axis::description(   1.,  -1.,false,"y_{clus}^{LCW}"                                      ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 05 */ Types::Hist::identify("ClLCW_Rap_pt080","TH1D","CLU",Types::Axis::description(   1.,  -1.,false,"y_{clus}^{LCW}"                                      ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 06 */ Types::Hist::identify("ClLCW_Rap_pt100","TH1D","CLU",Types::Axis::description(   1.,  -1.,false,"y_{clus}^{LCW}"                                      ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 07 */ Types::Hist::identify("ClLCW_Rap_pt200","TH1D","CLU",Types::Axis::description(   1.,  -1.,false,"y_{clus}^{LCW}"                                      ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 08 */ Types::Hist::identify("EMR_Eclus_pt020","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 09 */ Types::Hist::identify("EMR_Eclus_pt040","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 10 */ Types::Hist::identify("EMR_Eclus_pt060","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 11 */ Types::Hist::identify("EMR_Eclus_pt080","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 12 */ Types::Hist::identify("EMR_Eclus_pt100","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 13 */ Types::Hist::identify("EMR_Eclus_pt200","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 14 */ Types::Hist::identify("EMR_Fclus_pt020","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),
   /* 15 */ Types::Hist::identify("EMR_Fclus_pt040","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 16 */ Types::Hist::identify("EMR_Fclus_pt060","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 17 */ Types::Hist::identify("EMR_Fclus_pt080","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 18 */ Types::Hist::identify("EMR_Fclus_pt100","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 19 */ Types::Hist::identify("EMR_Fclus_pt200","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{EM}/E_{clus}^{dep}" )),  
   /* 20 */ Types::Hist::identify("LCR_Eclus_pt020","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 21 */ Types::Hist::identify("LCR_Eclus_pt040","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 22 */ Types::Hist::identify("LCR_Eclus_pt060","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 23 */ Types::Hist::identify("LCR_Eclus_pt080","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 24 */ Types::Hist::identify("LCR_Eclus_pt100","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 25 */ Types::Hist::identify("LCR_Eclus_pt200","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 26 */ Types::Hist::identify("LCR_Fclus_pt020","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 27 */ Types::Hist::identify("LCR_Fclus_pt040","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 28 */ Types::Hist::identify("LCR_Fclus_pt060","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),  
   /* 29 */ Types::Hist::identify("LCR_Fclus_pt080","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),
   /* 30 */ Types::Hist::identify("LCR_Fclus_pt100","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),
   /* 31 */ Types::Hist::identify("LCR_Fclus_pt200","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{LCW}/E_{clus}^{dep}")),
   /* 32 */ Types::Hist::identify("MLR_Eclus_pt020","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 33 */ Types::Hist::identify("MLR_Eclus_pt040","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 34 */ Types::Hist::identify("MLR_Eclus_pt060","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 35 */ Types::Hist::identify("MLR_Eclus_pt080","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 36 */ Types::Hist::identify("MLR_Eclus_pt100","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 37 */ Types::Hist::identify("MLR_Eclus_pt200","TH2D","RES",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{dep} [GeV]"                                ),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 38 */ Types::Hist::identify("MLR_Fclus_pt020","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 39 */ Types::Hist::identify("MLR_Fclus_pt040","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 40 */ Types::Hist::identify("MLR_Fclus_pt060","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),  
   /* 41 */ Types::Hist::identify("MLR_Fclus_pt080","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),
   /* 42 */ Types::Hist::identify("MLR_Fclus_pt100","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),
   /* 43 */ Types::Hist::identify("MLR_Fclus_pt200","TH2D","RES",Types::Axis::description(0.001,   1.,true ,"E_{clus}^{LCW}/#sum_{clusters in jet} E_{clus}^{LCW}"),Types::Axis::description(  1., -1.,false,"E_{clus}^{ML}/E_{clus}^{dep}" )),
   /* 44 */ Types::Hist::identify("N__Jets"        ,"TH1D","JET",Types::Axis::description( -0.5, 14.5,false,"N_{jet} "                                            ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 45 */ Types::Hist::identify("NconJet"        ,"TH1D","JET",Types::Axis::description( -0.5, 49.5,false,"N_{jet}^{const}"                                     ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 46 */ Types::Hist::identify("NcoPt_Jet"      ,"TH2D","JET",Types::Axis::description(   0., 400.,false,"p_{T,jet}^{JES} [GeV]"                               ),Types::Axis::description(-0.5,49.5,false,"N_{jet}^{const}"              )),
   /* 47 */ Types::Hist::identify("Pt_JEMS"        ,"TH1D","JET",Types::Axis::description(   0., 400.,false,"p_{T,jet}^{ConstScale} [GeV]"                        ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 48 */ Types::Hist::identify("Pt_JJES"        ,"TH1D","JET",Types::Axis::description(   0., 400.,false,"p_{T,jet}^{JES} [GeV]"                               ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 49 */ Types::Hist::identify("RapJEMS"        ,"TH1D","JET",Types::Axis::description(   1.,  -1.,false,"y_{jet}^{ConstScale}"                                ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 50 */ Types::Hist::identify("RapJJES"        ,"TH1D","JET",Types::Axis::description(   1.,  -1.,false,"y_{jet}^{JES}"                                       ),Types::Axis::description(  1., -1.,false,"Entries"                      )),
   /* 51 */ Types::Hist::identify("ClEM__Rap_pt020","TH1D","CLU",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{EM} [GeV]"                                 ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 52 */ Types::Hist::identify("ClEM__Rap_pt040","TH1D","CLU",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{EM} [GeV]"                                 ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 53 */ Types::Hist::identify("ClEM__Rap_pt060","TH1D","CLU",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{EM} [GeV]"                                 ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 54 */ Types::Hist::identify("ClEM__Rap_pt080","TH1D","CLU",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{EM} [GeV]"                                 ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 55 */ Types::Hist::identify("ClEM__Rap_pt100","TH1D","CLU",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{EM} [GeV]"                                 ),Types::Axis::description(  1., -1.,false,"Entries"                      )),  
   /* 56 */ Types::Hist::identify("ClEM__Rap_pt200","TH1D","CLU",Types::Axis::description( 0.05,2000.,true ,"E_{clus}^{EM} [GeV]"                                 ),Types::Axis::description(  1., -1.,false,"Entries"                      ))  
  };

  // plot title lookup 
  static const std::map<std::string,std::string> knownPlots = {
   /* 00 */ { "AziJEMS"        ,"Jet azimuth #phi_{jet}^{LCW} (constituent scale)"                                               },          
   /* 01 */ { "AziJJES"        ,"Jet azimuth #phi_{jet}^{JES} (fully calibrated)"                                                },          
   /* 02 */ { "ClLCW_Rap_pt020","Cluster rapidity y_{clus}^{LCW} for p_{T,jet}^{JES} > 20 GeV"                                   },  
   /* 03 */ { "ClLCW_Rap_pt040","Cluster rapidity y_{clus}^{LCW} for p_{T,jet}^{JES} > 40 GeV"                                   },  
   /* 04 */ { "ClLCW_Rap_pt060","Cluster rapidity y_{clus}^{LCW} for p_{T,jet}^{JES} > 60 GeV"                                   },  
   /* 05 */ { "ClLCW_Rap_pt080","Cluster rapidity y_{clus}^{LCW} for p_{T,jet}^{JES} > 80 GeV"                                   },  
   /* 06 */ { "ClLCW_Rap_pt100","Cluster rapidity y_{clus}^{LCW} for p_{T,jet}^{JES} > 100 GeV"                                  },  
   /* 07 */ { "ClLCW_Rap_pt200","Cluster rapidity y_{clus}^{LCW} for p_{T,jet}^{JES} > 200 GeV"                                  },  
   /* 08 */ { "EMR_Eclus_pt020","EM cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 20 GeV"                         },  
   /* 09 */ { "EMR_Eclus_pt040","EM cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 40 GeV"                         },  
   /* 10 */ { "EMR_Eclus_pt060","EM cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 60 GeV"                         },  
   /* 11 */ { "EMR_Eclus_pt080","EM cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 80 GeV"                         },  
   /* 12 */ { "EMR_Eclus_pt100","EM cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 100 GeV"                        },  
   /* 13 */ { "EMR_Eclus_pt200","EM cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 200 GeV"                        },  
   /* 14 */ { "EMR_Fclus_pt020","EM cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 20 GeV"               },
   /* 15 */ { "EMR_Fclus_pt040","EM cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 40 GeV"               },  
   /* 16 */ { "EMR_Fclus_pt060","EM cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 60 GeV"               },  
   /* 17 */ { "EMR_Fclus_pt080","EM cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 80 GeV"               },  
   /* 18 */ { "EMR_Fclus_pt100","EM cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 100 GeV"              },  
   /* 19 */ { "EMR_Fclus_pt200","EM cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 200 GeV"              },  
   /* 20 */ { "LCR_Eclus_pt020","LCW cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 20 GeV"                        },  
   /* 21 */ { "LCR_Eclus_pt040","LCW cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 40 GeV"                        },  
   /* 22 */ { "LCR_Eclus_pt060","LCW cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 60 GeV"                        },  
   /* 23 */ { "LCR_Eclus_pt080","LCW cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 80 GeV"                        },  
   /* 24 */ { "LCR_Eclus_pt100","LCW cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 100 GeV"                       },  
   /* 25 */ { "LCR_Eclus_pt200","LCW cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 200 GeV"                       },  
   /* 26 */ { "LCR_Fclus_pt020","LCW cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 20 GeV"              },  
   /* 27 */ { "LCR_Fclus_pt040","LCW cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 40 GeV"              },  
   /* 28 */ { "LCR_Fclus_pt060","LCW cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 60 GeV"              },  
   /* 29 */ { "LCR_Fclus_pt080","LCW cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 80 GeV"              },
   /* 30 */ { "LCR_Fclus_pt100","LCW cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 100 GeV"             },  
   /* 31 */ { "LCR_Fclus_pt200","LCW cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 200 GeV"             },  
   /* 32 */ { "MLR_Eclus_pt020","ML cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 20 GeV"                         },  
   /* 33 */ { "MLR_Eclus_pt040","ML cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 40 GeV"                         },  
   /* 34 */ { "MLR_Eclus_pt060","ML cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 60 GeV"                         },  
   /* 35 */ { "MLR_Eclus_pt080","ML cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 80 GeV"                         },  
   /* 36 */ { "MLR_Eclus_pt100","ML cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 100 GeV"                        },  
   /* 37 */ { "MLR_Eclus_pt200","ML cluster response versus E_{clus}^{dep} for p_{T,jet}^{JES} > 200 GeV"                        },  
   /* 38 */ { "MLR_Fclus_pt020","ML cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 20 GeV"               },  
   /* 39 */ { "MLR_Fclus_pt040","ML cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 40 GeV"               },  
   /* 40 */ { "MLR_Fclus_pt060","ML cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 60 GeV"               },  
   /* 41 */ { "MLR_Fclus_pt080","ML cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 80 GeV"               },
   /* 42 */ { "MLR_Fclus_pt100","ML cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 100 GeV"              },  
   /* 43 */ { "MLR_Fclus_pt200","ML cluster response versus cluster signal fraction for  p_{T,jet}^{JES} > 200 GeV"              },  
   /* 44 */ { "N__Jets"        ,"Number of jets with |y_{jet}^{JES}| < 0.4"                                                      },          
   /* 45 */ { "NconJet"        ,"Number of jet constituents for jets with |y_{jet}^{JES}| < 0.4"                                 },          
   /* 46 */ { "NcoPt_Jet"      ,"Number of jet constituents versus p_{T,jet}^{JES} for |y_{jet}^{JES}| < 0.4"                    },        
   /* 47 */ { "Pt_JEMS"        ,"Constituent scale (LCW clusters) p_{T,jet}^{ConstScale} for |y_{jet}^{JES}| < 0.4"              },          
   /* 48 */ { "Pt_JJES"        ,"Fully calibrated p_{T,jet}^{JES} for |y_{jet}^{JES}| < 0.4"                                     },          
   /* 49 */ { "RapJEMS"        ,"Jet rapidity y_{jet}^{ConstScale} at constituent scale (LCW clusters)"                          },          
   /* 50 */ { "RapJJES"        ,"Fully calibrated jet rapidity y_{jet}^{JES}"                                                    },
   /* 51 */ { "ClEM__Rap_pt020","Cluster signal E_{clus}^{EM} for p_{T,jet}^{JES} > 20 GeV"                                      },  
   /* 52 */ { "ClEM__Rap_pt040","Cluster signal E_{clus}^{EM} for p_{T,jet}^{JES} > 40 GeV"                                      },  
   /* 53 */ { "ClEM__Rap_pt060","Cluster signal E_{clus}^{EM} for p_{T,jet}^{JES} > 60 GeV"                                      },  
   /* 54 */ { "ClEM__Rap_pt080","Cluster signal E_{clus}^{EM} for p_{T,jet}^{JES} > 80 GeV"                                      },  
   /* 55 */ { "ClEM__Rap_pt100","Cluster signal E_{clus}^{EM} for p_{T,jet}^{JES} > 100 GeV"                                     },  
   /* 56 */ { "ClEM__Rap_pt200","Cluster signal E_{clus}^{EM} for p_{T,jet}^{JES} > 200 GeV"                                     }  
  }; 


  // Canvas descriptor lookup
  std::map<std::string,Types::Canvas::Identifier>  knownCanvas = {
   { Types::Hist::name(knownHists.at( 0)), { "JetAzimuthConstScale", "jet_azimuth_constscale"      } },          
   { Types::Hist::name(knownHists.at( 1)), { "JetAzimuthJES"       , "jet_azimuth_jes"             } },          
   { Types::Hist::name(knownHists.at( 2)), { "ClusterRapidityPt020", "cluster_rapidity_jet_pt020"  } },  
   { Types::Hist::name(knownHists.at( 3)), { "ClusterRapidityPt040", "cluster_rapidity_jet_pt040"  } },  
   { Types::Hist::name(knownHists.at( 4)), { "ClusterRapidityPt060", "cluster_rapidity_jet_pt060"  } },  
   { Types::Hist::name(knownHists.at( 5)), { "ClusterRapidityPt080", "cluster_rapidity_jet_pt080"  } },  
   { Types::Hist::name(knownHists.at( 6)), { "ClusterRapidityPt100", "cluster_rapidity_jet_pt100"  } },  
   { Types::Hist::name(knownHists.at( 7)), { "ClusterRapidityPt200", "cluster_rapidity_jet_pt200"  } },  
   { Types::Hist::name(knownHists.at( 8)), { "EMResponseEclusPt020", "em_response_eclus_jet_pt020" } },  
   { Types::Hist::name(knownHists.at( 9)), { "EMResponseEclusPt040", "em_response_eclus_jet_pt040" } },  
   { Types::Hist::name(knownHists.at(10)), { "EMResponseEclusPt060", "em_response_eclus_jet_pt060" } },  
   { Types::Hist::name(knownHists.at(11)), { "EMResponseEclusPt080", "em_response_eclus_jet_pt080" } },  
   { Types::Hist::name(knownHists.at(12)), { "EMResponseEclusPt100", "em_response_eclus_jet_pt100" } },  
   { Types::Hist::name(knownHists.at(13)), { "EMResponseEclusPt200", "em_response_eclus_jet_pt200" } },  
   { Types::Hist::name(knownHists.at(14)), { "EMResponseFclusPt020", "em_response_fclus_jet_pt020" } },
   { Types::Hist::name(knownHists.at(15)), { "EMResponseFclusPt040", "em_response_fclus_jet_pt040" } },  
   { Types::Hist::name(knownHists.at(16)), { "EMResponseFclusPt060", "em_response_fclus_jet_pt060" } },  
   { Types::Hist::name(knownHists.at(17)), { "EMResponseFclusPt080", "em_response_fclus_jet_pt080" } },  
   { Types::Hist::name(knownHists.at(18)), { "EMResponseFclusPt100", "em_response_fclus_jet_pt100" } },  
   { Types::Hist::name(knownHists.at(19)), { "EMResponseFclusPt200", "em_response_fclus_jet_pt200" } },  
   { Types::Hist::name(knownHists.at(20)), { "LCResponseEclusPt020", "lc_response_eclus_jet_pt020" } },  
   { Types::Hist::name(knownHists.at(21)), { "LCResponseEclusPt040", "lc_response_eclus_jet_pt040" } },  
   { Types::Hist::name(knownHists.at(22)), { "LCResponseEclusPt060", "lc_response_eclus_jet_pt060" } },  
   { Types::Hist::name(knownHists.at(23)), { "LCResponseEclusPt080", "lc_response_eclus_jet_pt080" } },  
   { Types::Hist::name(knownHists.at(24)), { "LCResponseEclusPt100", "lc_response_eclus_jet_pt100" } },  
   { Types::Hist::name(knownHists.at(25)), { "LCResponseEclusPt200", "lc_response_eclus_jet_pt200" } },  
   { Types::Hist::name(knownHists.at(26)), { "LCResponseFclusPt020", "lc_response_fclus_jet_pt020" } },  
   { Types::Hist::name(knownHists.at(27)), { "LCResponseFclusPt040", "lc_response_fclus_jet_pt040" } },  
   { Types::Hist::name(knownHists.at(28)), { "LCResponseFclusPt060", "lc_response_fclus_jet_pt060" } },  
   { Types::Hist::name(knownHists.at(29)), { "LCResponseFclusPt080", "lc_response_fclus_jet_pt080" } },
   { Types::Hist::name(knownHists.at(30)), { "LCResponseFclusPt100", "lc_response_fclus_jet_pt100" } },  
   { Types::Hist::name(knownHists.at(31)), { "LCResponseFclusPt200", "lc_response_fclus_jet_pt200" } },  
   { Types::Hist::name(knownHists.at(32)), { "MLResponseEclusPt020", "ml_response_eclus_jet_pt020" } },  
   { Types::Hist::name(knownHists.at(33)), { "MLResponseEclusPt040", "ml_response_eclus_jet_pt040" } },  
   { Types::Hist::name(knownHists.at(34)), { "MLResponseEclusPt060", "ml_response_eclus_jet_pt060" } },  
   { Types::Hist::name(knownHists.at(35)), { "MLResponseEclusPt080", "ml_response_eclus_jet_pt080" } },  
   { Types::Hist::name(knownHists.at(36)), { "MLResponseEclusPt100", "ml_response_eclus_jet_pt100" } },  
   { Types::Hist::name(knownHists.at(37)), { "MLResponseEclusPt200", "ml_response_eclus_jet_pt200" } },  
   { Types::Hist::name(knownHists.at(38)), { "MLResponseFclusPt020", "ml_response_fclus_jet_pt020" } },  
   { Types::Hist::name(knownHists.at(39)), { "MLResponseFclusPt040", "ml_response_fclus_jet_pt040" } },  
   { Types::Hist::name(knownHists.at(40)), { "MLResponseFclusPt060", "ml_response_fclus_jet_pt060" } },  
   { Types::Hist::name(knownHists.at(41)), { "MLResponseFclusPt080", "ml_response_fclus_jet_pt080" } },
   { Types::Hist::name(knownHists.at(42)), { "MLResponseFclusPt100", "ml_response_fclus_jet_pt100" } },  
   { Types::Hist::name(knownHists.at(43)), { "MLResponseFclusPt200", "ml_response_fclus_jet_pt200" } },  
   { Types::Hist::name(knownHists.at(44)), { "NJetsEvt"            , "n_jets_evt"                  } },          
   { Types::Hist::name(knownHists.at(45)), { "NConstituentJet"     , "n_constituent_jet"           } },          
   { Types::Hist::name(knownHists.at(46)), { "NConstituentsPtJet"  , "n_constituents_ptjet"        } },        
   { Types::Hist::name(knownHists.at(47)), { "JetPtConstScale"     , "jet_pt_constscale"           } },          
   { Types::Hist::name(knownHists.at(48)), { "JetPtJES"            , "jet_pt_jes"                  } },          
   { Types::Hist::name(knownHists.at(49)), { "JetRapConstScale"    , "jet_rap_constscale"          } },          
   { Types::Hist::name(knownHists.at(50)), { "JetRapJES"           , "jet_rap_jes"                 } },
   { Types::Hist::name(knownHists.at(51)), { "ClusterEMEnergyPt020", "cluster_emenergy_jet_pt020"  } },  
   { Types::Hist::name(knownHists.at(52)), { "ClusterEMEnergyPt040", "cluster_emenergy_jet_pt040"  } },  
   { Types::Hist::name(knownHists.at(53)), { "ClusterEMEnergyPt060", "cluster_emenergy_jet_pt060"  } },  
   { Types::Hist::name(knownHists.at(54)), { "ClusterEMEnergyPt080", "cluster_emenergy_jet_pt080"  } },  
   { Types::Hist::name(knownHists.at(55)), { "ClusterEMEnergyPt100", "cluster_emenergy_jet_pt100"  } },  
   { Types::Hist::name(knownHists.at(56)), { "ClusterEMEnergyPt200", "cluster_emenergy_jet_pt200"  } }
  };

  // specialities
  std::map<std::string,bool> doResponseLines = { 
   /* 00 */ { "AziJEMS"        , false },          
   /* 01 */ { "AziJJES"        , false },          
   /* 02 */ { "ClLCW_Rap_pt020", false },  
   /* 03 */ { "ClLCW_Rap_pt040", false },  
   /* 04 */ { "ClLCW_Rap_pt060", false },  
   /* 05 */ { "ClLCW_Rap_pt080", false },  
   /* 06 */ { "ClLCW_Rap_pt100", false },  
   /* 07 */ { "ClLCW_Rap_pt200", false },  
   /* 08 */ { "EMR_Eclus_pt020", true  },  
   /* 09 */ { "EMR_Eclus_pt040", true  },  
   /* 10 */ { "EMR_Eclus_pt060", true  },  
   /* 11 */ { "EMR_Eclus_pt080", true  },  
   /* 12 */ { "EMR_Eclus_pt100", true  },  
   /* 13 */ { "EMR_Eclus_pt200", true  },  
   /* 14 */ { "EMR_Fclus_pt020", true  },
   /* 15 */ { "EMR_Fclus_pt040", true  },  
   /* 16 */ { "EMR_Fclus_pt060", true  },  
   /* 17 */ { "EMR_Fclus_pt080", true  },  
   /* 18 */ { "EMR_Fclus_pt100", true  },  
   /* 19 */ { "EMR_Fclus_pt200", true  },  
   /* 20 */ { "LCR_Eclus_pt020", true  },  
   /* 21 */ { "LCR_Eclus_pt040", true  },  
   /* 22 */ { "LCR_Eclus_pt060", true  },  
   /* 23 */ { "LCR_Eclus_pt080", true  },  
   /* 24 */ { "LCR_Eclus_pt100", true  },  
   /* 25 */ { "LCR_Eclus_pt200", true  },  
   /* 26 */ { "LCR_Fclus_pt020", true  },  
   /* 27 */ { "LCR_Fclus_pt040", true  },  
   /* 28 */ { "LCR_Fclus_pt060", true  },  
   /* 29 */ { "LCR_Fclus_pt080", true  },
   /* 30 */ { "LCR_Fclus_pt100", true  },  
   /* 31 */ { "LCR_Fclus_pt200", true  },  
   /* 32 */ { "MLR_Eclus_pt020", true  },  
   /* 33 */ { "MLR_Eclus_pt040", true  },  
   /* 34 */ { "MLR_Eclus_pt060", true  },  
   /* 35 */ { "MLR_Eclus_pt080", true  },  
   /* 36 */ { "MLR_Eclus_pt100", true  },  
   /* 37 */ { "MLR_Eclus_pt200", true  },  
   /* 38 */ { "MLR_Fclus_pt020", true  },  
   /* 39 */ { "MLR_Fclus_pt040", true  },  
   /* 40 */ { "MLR_Fclus_pt060", true  },  
   /* 41 */ { "MLR_Fclus_pt080", true  },
   /* 42 */ { "MLR_Fclus_pt100", true  },  
   /* 43 */ { "MLR_Fclus_pt200", true  },  
   /* 44 */ { "N__Jets"        , false },          
   /* 45 */ { "NconJet"        , false },          
   /* 46 */ { "NcoPt_Jet"      , false },        
   /* 47 */ { "Pt_JEMS"        , false },          
   /* 48 */ { "Pt_JJES"        , false },          
   /* 49 */ { "RapJEMS"        , false },          
   /* 50 */ { "RapJJES"        , false },
   /* 51 */ { "ClEM__Ene_pt020", false },  
   /* 52 */ { "ClEM__Ene_pt040", false },  
   /* 53 */ { "ClEM__Ene_pt060", false },  
   /* 54 */ { "ClEM__Ene_pt080", false },  
   /* 55 */ { "ClEM__Ene_pt100", false },  
   /* 56 */ { "ClEM__Ene_pt200", false }  
  }; 
  
  //////////////
  // Plotting //
  //////////////

  // general settings
  gStyle->SetTitleSize(0.75*gStyle->GetTitleSize("x"),"x");
  gStyle->SetTitleSize(0.75*gStyle->GetTitleSize("y"),"y");
  gStyle->SetTitleOffset(1.25*gStyle->GetTitleOffset("x"),"x");

  // plotting cache
  std::map<std::string,Types::Plot::Content> plotLookup; 
  // set plot frame
  double prw(gStyle->GetPadRightMargin());                // remember old style right frame
  gStyle->SetPadRightMargin(gStyle->GetPadLeftMargin());  // set left and right frame to same width
  // open file
  TFile* fptr = new TFile(fileName.c_str(),"READ");
  if ( fptr == nullptr ) { printf("[plotClusterJet] ABRT cannot allocate file \042%s\042\n",fileName.c_str()); return; }
  // allocate all plots 
  for ( auto pdescr : knownHists ) {
    const std::string& rname = Types::Hist::name(pdescr); 
    const std::string& rtype = Types::Hist::type(pdescr);
    auto fplot(knownPlots.find(rname));
    std::string ptitle = fplot != knownPlots.end() ? fplot->second : ""; 
    // printf("[plotClusterJet] INFO access histogram type %s\n",rtype.c_str());
    if ( rtype == "TH1D" ) { 
      TH1D* hptr = (TH1D*)fptr->FindObjectAny(rname.c_str()); 
      if ( hptr != nullptr ) { 
	printf("[plotClusterJet] INFO booked %s at %p name = \042%s\042\n",rtype.c_str(),(void*)hptr,hptr->GetName());
	plotLookup[rname] = { pdescr, hptr, false, (TGraph*)0, ptitle };
      }
    } else if ( rtype == "TH2D" ) { 
      TH2D* hptr = (TH2D*)fptr->FindObjectAny(rname.c_str()); 
      if ( hptr != nullptr ) {
 	printf("[plotClusterJet] INFO booked %s at %p name = \042%s\042 => ",rtype.c_str(),(void*)hptr,hptr->GetName());
	plotLookup[rname] = { pdescr, hptr, true, (TGraph*)HistUtils::graph(hptr,"response",2,HistUtils::Mean,"RMS",minEntries), ptitle }; 
      }
    }
  }
  // open output file
  //  std::string prefix = fileName.front() == 'J' ? fileName.substr(0,fileName.find_first_of('.')) : fileName.substr(0,fileName.find_first_of('_'));  
  std::string prefix = fileName.substr(0,fileName.find_first_of('.'));
  TFile* outFile = new TFile(TString::Format("%s_summary.root",prefix.c_str()).Data(),"RECREATE"); 
  // get the graphs for all plots
  printf("[plotClusterJet] INFO found %zu distributions\n",plotLookup.size());
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
      TGraphAsymmErrors* gptr = (TGraphAsymmErrors*)Types::Plot::graph(pcont);
      if ( gptr != nullptr ) { 
	gptr->SetLineStyle(1)   ; gptr->SetLineColorAlpha(kRed,0.25) ; gptr->SetLineWidth(2)   ;/* gptr->SetFillColorAlpha(kGreen,0.75); */ 
	gptr->SetMarkerStyle(20); gptr->SetMarkerColor(kRed)         ; gptr->SetMarkerSize(0.5); 
	// gptr->Draw("same p2");
	gptr->Draw("same p");
	gptr->SetName(TString::Format("%s_graph_mean",hptr->GetName()).Data()); gptr->Write();
	if ( doResponseLines.at(rname) ) {
	  TLine* cl = new TLine(xmin,1.0,xmax,1.0); cl->SetLineWidth(1); cl->SetLineStyle(9); cl->Draw("lsame");
	  TLine* ul = new TLine(xmin,1.1,xmax,1.1); ul->SetLineWidth(1); ul->SetLineStyle(7); ul->Draw("lsame");
	  TLine* dl = new TLine(xmin,0.9,xmax,0.9); dl->SetLineWidth(1); dl->SetLineStyle(7); dl->Draw("lsame");
	  TLine* hl = new TLine(xmin,1.2,xmax,1.2); hl->SetLineWidth(1); hl->SetLineStyle(2); hl->Draw("lsame");
	  TLine* ll = new TLine(xmin,0.8,xmax,0.8); ll->SetLineWidth(1); ll->SetLineStyle(2); ll->Draw("lsame");
	}
      }
    }
    // title
    if ( ptitle != "" ) { 
      double xtit(1.-gStyle->GetPadRightMargin());
      double ytit(1.-gStyle->GetPadTopMargin()/2.);
      TLatex* tlat = new TLatex(); tlat->SetNDC(); tlat->SetTextSize(0.5*tlat->GetTextSize()); tlat->SetTextAlign(32); 
      tlat->DrawLatex(xtit,ytit,TString::Format("[ATLAS %s LCTopo |y_{jet}| < 0.4]: %s",prefix.c_str(),ptitle.c_str()).Data());
    }
    // print 
    cv->RedrawAxis();
    Types::Canvas::print(cv,knownCanvas.at(rname),fdir,true,true);
    // save
    cv->Write(); 
    hptr->Write();
    printf("[plotClusterJet] INFO canvas \042%s\042 with histogram %s written to file \042%s\042\n",cv->GetName(),hptr->GetName(),outFile->GetName());
  }
  outFile->Close();
}
