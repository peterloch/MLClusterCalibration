// -*- c++ -*-
#ifndef PLOTCONFIG_H
#define PLOTCONFIG_H

#include <TH1.h>
#include <TGraph.h>
#include <TFile.h>

#include <string>
#include <tuple>
#include <vector>

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
    typedef std::tuple<Hist::Identifier,TH1*,bool,TGraph*,TGraph*,std::string> Content;
    // accessors
    static const Hist::Identifier& histogram   (const Content& pcont)                              { return std::get<0>(pcont); }
    static       TH1*              distribution(const Content& pcont)                              { return std::get<1>(pcont); }
    static       bool              doGraph     (const Content& pcont)                              { return std::get<2>(pcont); }
    static       TGraph*           graph       (const Content& pcont,const std::string& opt="RMS") { return opt == "RMS" ? std::get<3>(pcont) : opt == "ERROR" ? std::get<4>(pcont) : (TGraph*)0; }
    static const std::string&      title       (const Content& pcont)                              { return std::get<5>(pcont); } 
    // helpers
    static Content content(const Hist::Identifier& phid,TH1* phptr=(TH1*)0,bool pdograph=false,TGraph* grptr=(TGraph*)0,TGraph* geptr=(TGraph*)0,const std::string& ptitle="") { 
      return { phid, phptr, pdograph, grptr, geptr, ptitle };
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

  ///////////////////////
  // Graph Descriptors //
  ///////////////////////
  namespace Graph {

    // -- basic types for objects and stores
    typedef std::string                                     Name           ; // name of plot/graph     
    typedef Name                                            Key            ; // key for lookup tables
    typedef TGraph*                                         Pointer        ; // base graph pointer
    typedef std::string                                     ScaleTag       ; // tag for scales
    // -- basic types for plotting
    typedef int                                             Color          ; // color indicator (ROOT)
    typedef int                                             Style          ; // plot style
    typedef int                                             Width          ; // line width
    typedef double                                          Size           ; // marker size
    typedef double                                          Alpha          ; // transparency   

    // -- common graph tags 
    static const std::vector<ScaleTag>     knownScales       = { "EM", "LC", "ML" };
    static       std::map<ScaleTag,size_t> knownScaleIndices = { }; 
    static const int scaleIndex(const ScaleTag& scaleTag) { 
      if ( knownScaleIndices.empty() ) { for ( size_t idx(0); i<knownScales.size(); ++i ) { knownScaleIndices[knownScales.at(idx)] = idx; } }
      return (auto ftag = knownScaleIndices.find(scaleTag)) != knownScaleIndices.end() ? ftag.second : -1; 
    }

    // --------------------------------------------------------------------- object stores and lookup
    // Position   Content
    //    0       pointer to EM response graph
    //    1       pointer to LCW response graph
    //    2       pointer to ML response graph  
    typedef std::tuple<Pointer,Pointer,Pointer>             PointerGroup   ; // group of graphs (stored as pointers)
    typedef std::map<Key,PointerGroup>                      PointerGroupMap; // lookup table for groups of graph pointers
    // Position   Content
    //    0       name of EM response graph in input file
    //    1       name of LCW response graph in input file
    //    2       name of ML response graph in input file
    typedef std::tuple<Name,Name,Name>                      NameGroup      ; // group of graph names 
    typedef std::map<Key,NameGroup>                         NameGroupMap   ; // lookup table for groups of graph names 

    // -- functions for object retrieval
    template<INT I,class T> static const std::tuple_element<I,T>& access(const T& tuple) { return std::get<I>(tuple); } // get graph pointer or name (constant reference)   
    template<INT I,class T> static       std::tuple_element<I,T>& access(      T& tuple) { return std::get<I>(tuple); } // get graph pointer of name (non-const reference)
    // -- accessors: load graph from file into group
    template<class G> static G*   loadGraph(TFile* dataFile,const std::string& graphName)                    { G* gptr = ( G* )dataFile->FindObjectAny(graphName.c_str()); return gptr; }
    template<class G> static bool loadGraph(TFile* dataFile,const std::string& graphName,PointerGroup& pgrp,const std::string& scaleTag) {
      // check input
      int idx(scaleIndex(scaleTag)); if ( idx < 0 ) { printf("[Types::Graph::loadGraph(...)] WARN scale tag %s unknown, no graph loaded\n",scaleTag.c_str()); return false; }
      // find graph in input file
      G* gp = loadGraph< G >(dataFile,graphName); 
      if ( gp == nullptr ) { printf("[Types::Graph::loadGraph(...)] WARN cannot find graph \042%s\042 in input file \042%s\042\n",graphName.c_str(),dataFile->GetName()); return false; }
      // insert pointer to graph
      bool setFlag(false);
      switch ( idx ) { 
      case 0 : access<0,PointerGroup>(pgrp) = gp; setFlag = true; break;
      case 1 : access<1,PointerGroup>(pgrp) = gp; setFlag = true; break;
      case 2 : access<2,PointerGroup>(pgrp) = gp; setFlag = true; break; 
      default: break;
      }
      return setFlag;
    }   
    template<class G> static bool loadGraph(TFile* dataFile,const NameGroup& ngrp,PointerGroup& pgrp) { 
      
    }
    // -- accessor: find graph pointer in group
    template<class G> static G*   findGraph(PointerGroup& pgrp,const std::string& scaleTag) {
      // check input
      int idx(scaleIndex(scaleTag)); if ( idx < 0 ) { printf("[Types::Graph::findGraph(...)] WARN scale tag %s unknown, no graph found in group\n",scaleTag.c_str()); return false; }
      // associate index with graph
      G* graphPtr = ( G* )0; 
      switch ( idx ) { 
      case 0 : graphPtr = dynamic_cast< G* >(access<0,PointerGroup>(pgrp)); break; 
      case 1 : graphPtr = dynamic_cast< G* >(access<1,PointerGroup>(pgrp)); break; 
      case 2 : graphPtr = dynamic_cast< G* >(access<2,PointerGroup>(pgrp)); break;
      default: break;
      }
      return graphPtr; 
    } 
    // -- accessor: find graph name in group
    static const std::string& findGraph(const NameGroup& ngrp,const std::string& scaleTag) { 
      // check input
      int idx(scaleIndex(scaleTag)); if ( idx < 0 ) { printf("[Types::Graph::findGraph(...)] WARN scale tag %s unknown, no graph found in group\n",scaleTag.c_str()); return false; }
      //
      std::string gname;
      switch ( idx ) {
      case 0 : gname = access<0,NameGroup>(ngrp); break;
      case 1 : gname = access<1,NameGroup>(ngrp); break;
      case 2 : gname = access<2,NameGroup>(ngrp); break; 
      }
    } 

    // --------------------------------------------------------------------- plot configurations and descriptions
    // Position   Content for line/marker
    //    0       color code
    //    1       style
    //    2       width (line), size (marker)
    //    3       transparency   
    typedef std::tuple<Color,Style,Width,Alpha>             LineDescriptor  ; // line descriptor type
    typedef std::tuple<Color,Style,Size ,Alpha>             MarkerDescriptor; // marker descriptor type

    // --------------------------------------------------------------------- functions for plot configurations
    // extract information from descriptors
    template<class D> static int    getColor(const D& descriptor) { return std::get<0>(descriptor); }
    template<class D> static int    getStyle(const D& descriptor) { return std::get<1>(descriptor); }
    template<class D> static int    getWidth(const D& descriptor) { return std::get<2>(descriptor); }
    template<class D> static double getSize (const D& descriptor) { return std::get<2>(descriptor); }
    template<class D> static double getAlpha(const D& descriptor) { return std::get<3>(descriptor); }
    // set style
    template<class H,class D> static void setDrawStyle(H* hptr,const D& descriptor) { 
      double alpha(getAlpha< D >(descriptor)); 
      if ( alpha > 0. && alpha < 1. ) { hptr->SetLineColorAlpha(getColor< D >(descriptor),alpha); } else { hptr->SetLineColor(getColor< D >(descriptor)); }
      hptr->SetLineStyle(getStyle< D >(descriptor)); 
      hptr->SetLineWidth(getWidth< D >(descriptor)); 		       
    }
    template<class H> static void setDrawStyle(H* hptr,const MarkerDescriptor& descriptor) { 
      double alpha(getAlpha< D >(descriptor)); 
      if ( alpha > 0. && alpha < 1. ) { hptr->SetMarkerColorAlpha(getColor< D >(descriptor),alpha); } else { hptr->SetMarkerColor(getColor< D >(descriptor)); }
      hptr->SetMarkerStyle(getStyle< D >(descriptor)); 
      hptr->SetMarkerSize (getSize< D > (descriptor)); 		       
    }
  } // Graph
} // Types

#endif
