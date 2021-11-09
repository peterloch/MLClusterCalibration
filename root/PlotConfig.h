// -*- c++ -*-
#ifndef PLOTCONFIG_H
#define PLOTCONFIG_H

#include <TH1.h>
#include <TGraph.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TError.h>

#include <string>
#include <tuple>
#include <vector>

#include <cstdio>
#include <cstring>

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

    // -- dummy reference
    static const std::string invalidReturnStringRef = { "INVALID" };
    static const std::string unknownReturnStringRef = { "UNKNOWN" };

    // -- common graph tags 
    static const std::vector<ScaleTag>     knownScales       = { "EM", "LC", "ML" };
    static       std::map<ScaleTag,size_t> knownScaleIndices = { }; 
    static       int scaleIndex(const ScaleTag& scaleTag) { 
      if ( knownScaleIndices.empty() ) { for ( size_t idx(0); idx<knownScales.size(); ++idx ) { knownScaleIndices[knownScales.at(idx)] = idx; } }
      return knownScaleIndices.find(scaleTag) != knownScaleIndices.end() ? knownScaleIndices.at(scaleTag) : -1; 
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
    template<int I,class T> static const typename std::tuple_element<I,T>::type& access(const T& tuple) { return std::get<I>(tuple); } // get graph pointer or name (constant reference)   
    template<int I,class T> static       typename std::tuple_element<I,T>::type& access(      T& tuple) { return std::get<I>(tuple); } // get graph pointer of name (non-const reference)
    // -- accessors: load graph from file into group
    template<class G> static G* loadGraph(TFile* dataFile,const std::string& graphName) { G* gptr = ( G* )dataFile->FindObjectAny(graphName.c_str()); return gptr; }
    template<class G> static G* loadGraph(TFile* dataFile,const std::string& dirName,const std::string& graphName) { 
      G* gptr = ( G* )0;
      TDirectory* workDir = dataFile->cd(dirName.c_str()) ? TDirectory::CurrentDirectory() : (TDirectory*)0;
      if ( workDir == nullptr ) { printf("[Types::Graph::loadGraph(...)] WARN directory %s/%s not found, no graph loaded\n",dataFile->GetName(),dirName.c_str()); return gptr; }
      workDir->GetObject< G >(graphName.c_str(),gptr); 
      return gptr; 
    } 
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
    // template<class G> static bool loadGraph(TFile* dataFile,const NameGroup& ngrp,PointerGroup& pgrp) { 
      
    // }
    // -- accessor: find graph pointer in group
    template<class G> static G*   findGraph(PointerGroup& pgrp,const std::string& scaleTag) {
      // check input
      int idx(scaleIndex(scaleTag)); if ( idx < 0 ) { printf("[Types::Graph::findGraph(...)] WARN scale tag %s unknown, no graph found in group\n",scaleTag.c_str()); return ( G* )0; }
      // associate index with graph
      G* graphPtr = ( G* )0; 
      switch ( idx ) { 
      case 0 : graphPtr = dynamic_cast< G* >(access<0,PointerGroup>(pgrp)); break; 
      case 1 : graphPtr = dynamic_cast< G* >(access<1,PointerGroup>(pgrp)); break; 
      case 2 : graphPtr = dynamic_cast< G* >(access<2,PointerGroup>(pgrp)); break;
      default: break;
      }
      if ( graphPtr != nullptr ) { 
	printf("[Types::Graph::findGraph(...)] INFO scale tag %s: found graph \042%s\042\n",scaleTag.c_str(),graphPtr->GetName()); 
      } else { 
	printf("[Types::Graph::findGraph(...)] INFO scale tag %s: cannot find graph in pointer group\n",scaleTag.c_str()); 
      }
      return graphPtr; 
    } 
    // -- accessor: find graph name in group
    static std::string findGraph(const NameGroup& ngrp,const std::string& scaleTag) { 
      // check input
      int idx(scaleIndex(scaleTag)); if ( idx < 0 ) { printf("[Types::Graph::findGraph(...)] WARN scale tag %s unknown, no graph found in group\n",scaleTag.c_str()); return unknownReturnStringRef; }
      //
      std::string strRef(invalidReturnStringRef);
      switch ( idx ) {
      case 0 : strRef = access<0,NameGroup>(ngrp); printf("[Types::Graph::findGraph(...)] INFO scale tag %s: found group member #%i with name %s\n",scaleTag.c_str(),idx,strRef.c_str()); break;
      case 1 : strRef = access<1,NameGroup>(ngrp); printf("[Types::Graph::findGraph(...)] INFO scale tag %s: found group member #%i with name %s\n",scaleTag.c_str(),idx,strRef.c_str()); break;
      case 2 : strRef = access<2,NameGroup>(ngrp); printf("[Types::Graph::findGraph(...)] INFO scale tag %s: found group member #%i with name %s\n",scaleTag.c_str(),idx,strRef.c_str()); break;
      default: printf("[Types::Graph::findGraph(...)] WARN scale tag %s invalid, no graph found in group\n",scaleTag.c_str()); 
      }
      return strRef; 
    }

    // --------------------------------------------------------------------- plot configurations and descriptions
    // Position   Content for line/marker
    //    0       color code
    //    1       style
    //    2       width (line), size (marker)
    //    3       transparency   
    typedef std::tuple<Color,Style,Width,Alpha>             LineDescriptor  ; // line descriptor type
    typedef std::tuple<Color,Style,Size ,Alpha>             MarkerDescriptor; // marker descriptor type
    typedef std::tuple<Color,Style,Alpha,Width>             FillDescriptor;   // fill area descriptor

    // --------------------------------------------------------------------- functions for plot configurations
    // generate a descriptor
    struct DescriptionFactory{ 
      static LineDescriptor   Line  (Color color,Style style,Width width,Alpha alpha) { return { color, style, width, alpha }; }
      static FillDescriptor   Fill  (Color color,Style style,Width width,Alpha alpha) { return { color, style, alpha, width }; }
      static MarkerDescriptor Marker(Color color,Style style,Size  size, Alpha alpha) { return { color, style, size,  alpha }; }
    };
    // extract information from descriptors: lines
    static int    getColor(const LineDescriptor&   descriptor) { return std::get<0>(descriptor); }
    static int    getStyle(const LineDescriptor&   descriptor) { return std::get<1>(descriptor); }
    static int    getWidth(const LineDescriptor&   descriptor) { return std::get<2>(descriptor); }
    static double getAlpha(const LineDescriptor&   descriptor) { return std::get<3>(descriptor); }
    // extract information from descriptors: markers
    static int    getColor(const MarkerDescriptor& descriptor) { return std::get<0>(descriptor); }
    static int    getStyle(const MarkerDescriptor& descriptor) { return std::get<1>(descriptor); }
    static double getSize (const MarkerDescriptor& descriptor) { return std::get<2>(descriptor); }
    static double getAlpha(const MarkerDescriptor& descriptor) { return std::get<3>(descriptor); }
    // extract information from descriptors: fill area
    static int    getColor(const FillDescriptor&   descriptor) { return std::get<0>(descriptor); }
    static int    getStyle(const FillDescriptor&   descriptor) { return std::get<1>(descriptor); }
    static int    getWidth(const FillDescriptor&   descriptor) { return std::get<3>(descriptor); }
    static double getAlpha(const FillDescriptor&   descriptor) { return std::get<2>(descriptor); }
    // set style
    template<class H> static void setDrawStyle(H* hptr,const LineDescriptor& descriptor) { 
      double alpha(getAlpha(descriptor)); 
      if ( alpha > 0. && alpha < 1. ) { hptr->SetLineColorAlpha(getColor(descriptor),alpha); } else { hptr->SetLineColor(getColor(descriptor)); }
      hptr->SetLineStyle(getStyle(descriptor)); 
      hptr->SetLineWidth(getWidth(descriptor)); 		       
    }
    template<class H> static void setDrawStyle(H* hptr,const MarkerDescriptor& descriptor) { 
      double alpha(getAlpha(descriptor)); 
      if ( alpha > 0. && alpha < 1. ) { hptr->SetMarkerColorAlpha(getColor(descriptor),alpha); } else { hptr->SetMarkerColor(getColor(descriptor)); }
      hptr->SetMarkerStyle(getStyle(descriptor)); 
      hptr->SetMarkerSize (getSize (descriptor)); 		       
    }
    template<class H> static void setDrawStyle(H* hptr,const FillDescriptor& descriptor) { 
      double alpha(getAlpha(descriptor));
      if ( alpha > 0. && alpha < 1. ) { hptr->SetFillColorAlpha(getColor(descriptor),alpha); } else { hptr->SetFillColor(getColor(descriptor)); }
      hptr->SetFillStyle(getStyle(descriptor));
      if ( getWidth(descriptor) >= 0 ) { hptr->SetLineWidth(getWidth(descriptor)); } 
    }
    template<class H> static void setDrawStyle(H* hptr,const LineDescriptor& ldescr,const FillDescriptor& fdescr,const MarkerDescriptor& mdescr) { 
      setDrawStyle(hptr,ldescr); setDrawStyle(hptr,fdescr); setDrawStyle(hptr,mdescr); 
    }
    template<class H> static void changeTransparencyFill  (H* hptr,double transparency=1.) { hptr->SetFillColorAlpha  (hptr->GetFillColor()  ,transparency); } 
    template<class H> static void changeTransparencyLine  (H* hptr,double transparency=1.) { hptr->SetLineColorAlpha  (hptr->GetLineColor()  ,transparency); } 
    template<class H> static void changeTransparencyMarker(H* hptr,double transparency=1.) { hptr->SetMarkerColorAlpha(hptr->GetMarkerColor(),transparency); } 
  } // Graph
} // Types

namespace File {
  // -- IO modes
  struct IO { 
    enum Mode { Read = 0x01, Write = 0x02, Recreate = 0x12, Append = 0x22, Unknown = 0x00  };
  };
  // -- open a ROOT file
  static TFile* open(const std::string& fileName,IO::Mode ioMode=IO::Read,bool printInfo=true) { 
    const static std::map<IO::Mode,const std::string> rootIOMode = { 
      { IO::Read    , "READ"     },
      { IO::Write   , "WRITE"    },
      { IO::Recreate, "RECREATE" },
      { IO::Append  , "APPEND"   },
      { IO::Unknown , "UNKNOWN"  }
    };
    // check on mode
    if ( ioMode == IO::Unknown ) { printf("[File::open(...)] ABRT unknown IO mode, no file opened\n"); return (TFile*)0; }
    // open file
    TFile* f = new TFile(fileName.c_str(),rootIOMode.at(ioMode).c_str());
    if ( f == nullptr ) { printf("[File::open(...)] WARN could not open file \042%s\042 with mode <%s>\n",fileName.c_str(),rootIOMode.at(ioMode).c_str()); return (TFile*)0; }
    // success
    if ( printInfo ) { printf("[File::open(...)] INFO opened file \042%s\042 with mode <%s>\n",fileName.c_str(),rootIOMode.at(ioMode).c_str()); }
    return f;
  }
  // -- get directory name from input file
  static std::string directory(const std::string& fileName,const char separator='/') { return fileName.substr(0,fileName.find_last_of(separator)); }
  // -- get extension
  static std::string extension(const std::string& fileName,const char separator='.') { auto ipos = fileName.find_last_of(separator); return ipos != std::string::npos ? fileName.substr(ipos+1) : ""; }
  // -- generate a file name by stripping extensions
  static std::string name(const std::string& sourceFileName,bool includeDir=true,const char separatorExt='.',const char separatorDir='/') {
    std::string body = includeDir ? sourceFileName : sourceFileName.substr(0,sourceFileName.find_last_of(separatorDir)); 
    return body.substr(0,body.find_last_of(separatorExt));
  }
  // -- generate print file name 
  static std::string print(const std::string& fileName,const std::string& ext="pdf",bool includeDir=true) { 
    static char _buffer[2048];
    if ( ext == "" ) { return fileName; }
    sprintf(_buffer,"%s.%s",name(fileName,includeDir).c_str(),ext.c_str());    
    return std::string(_buffer); 
  }
  // -- generate print file names for various formats
  static std::vector<std::string> print(const std::string& fileName,const std::vector<std::string>& extensions,bool includeDir=true) { 
    std::vector<std::string> fnames; for ( const auto& ext : extensions ) { fnames.push_back(print(fileName,ext,includeDir)); }
    return fnames;
  }
  // -- print canvas
  static std::string print(const std::string& fileName,TCanvas* pcvs,const std::string& ext="pdf",bool includeDir=true) {
    auto ignoreLvl = gErrorIgnoreLevel; gErrorIgnoreLevel = kWarning;
    std::string fname(print(fileName,ext,includeDir));
    pcvs->Print(fname.c_str()); 
    gErrorIgnoreLevel = ignoreLvl;
    return fileName;
  }
  // -- print canvas in various formats
  static std::vector<std::string> print(const std::string& fileName,TCanvas* pcvs,const std::vector<std::string>& extensions,bool includeDir=true) { 
    auto ignoreLvl = gErrorIgnoreLevel; gErrorIgnoreLevel = kWarning;
    std::vector<std::string> fnames; 
    for ( const auto& ext : extensions ) { fnames.push_back(print(fileName,ext,includeDir)); pcvs->Print(fnames.back().c_str()); }
    gErrorIgnoreLevel = ignoreLvl;
    return fnames; 
  }
  // -- print canvas
  static std::string print(TCanvas* pcvs,const std::string& ext="pdf",bool includeDir=true) {
    auto ignoreLvl = gErrorIgnoreLevel; gErrorIgnoreLevel = kWarning;
    std::string fileName(print(pcvs->GetName(),ext,includeDir));
    pcvs->Print(fileName.c_str()); 
    gErrorIgnoreLevel = ignoreLvl;
    return fileName;
  }
  // -- print canvas in various formats
  static std::vector<std::string> print(TCanvas* pcvs,const std::vector<std::string>& extensions,bool includeDir=true) { 
    auto ignoreLvl = gErrorIgnoreLevel; gErrorIgnoreLevel = kWarning;
    std::vector<std::string> fnames; 
    for ( const auto& ext : extensions ) { fnames.push_back(print(pcvs->GetName(),ext,includeDir)); pcvs->Print(fnames.back().c_str()); }
    gErrorIgnoreLevel = ignoreLvl;
    return fnames; 
  }
} // File

namespace String {
  namespace Tags {
    static const std::string empty = "";
  } // String::Tags 
  static std::string extractVariable(const std::string& varStr) { std::string vs(varStr.substr(0,varStr.find_first_of('['))); return vs.find_last_of(' ') == vs.length()-1 ? vs.substr(0,vs.length()-1) : vs; }
  static std::string extractUnit    (const std::string& varStr) { 
    auto fbegin = varStr.find_first_of('['); if ( fbegin == std::string::npos ) { return Tags::empty; }
    auto fend   = varStr.find_last_of (']'); if ( fend   == std::string::npos ) { return Tags::empty; }
    if ( fend < fbegin ) { return Tags::empty; }
    // return value between []
    return varStr.substr(fbegin+1,fend-fbegin-1);
  }
  static std::string stripFront(const std::string& varStr,const char stripChar=' ') { return varStr.length() > 0 ? varStr.substr(varStr.find_first_not_of(stripChar))                              : varStr; }
  static std::string stripBack (const std::string& varStr,const char stripChar=' ') { return varStr.length() > 0 ? varStr.substr(0,std::min(varStr.length(),varStr.find_last_not_of(stripChar)+1)) : varStr; }
  static std::string strip     (const std::string& varStr,const char stripChar=' ') { return varStr.length() > 0 ? stripFront(stripBack(varStr,stripChar),stripChar)                               : varStr; }
  // remove fragments
  static std::string remove(const std::string& varStr,const std::string& remStr) { 
    // check if string fragment is in string
    std::string::size_type frem = varStr.find(remStr);
    if ( frem == std::string::npos ) { return varStr; }
    // replace by empty string
    std::string::size_type lrem(remStr.length()); 
    std::string rstr(varStr); rstr.replace(frem,lrem,""); 
    return rstr; 
  }
  static std::string remove(const std::string& varStr,const std::vector<std::string>& remList ) { 
    std::string rstr(varStr);
    for ( const auto& remStr : remList ) { rstr = remove(rstr,remStr); }
    return rstr;
  }
  // replace characters
  static std::string replace(const std::string& varStr,const char c,char r='_') {
    std::string rstr(varStr); 
    std::string::size_type fchar = rstr.find_first_of(c,0);
    while ( fchar != std::string::npos ) { rstr[fchar] = r; fchar = rstr.find_first_of(c,fchar); }
    return rstr; 
  }
  static std::string replace(const std::string& varStr,const std::string& cstr,char r='_') { 
    std::string rstr(varStr); 
    std::string::size_type fchar = rstr.find(cstr,0);
    while ( fchar != std::string::npos ) { rstr[fchar] = r; fchar = rstr.find_first_of(cstr,fchar); }
    return rstr; 
  } 
  static std::string replace(const std::string& varStr,const std::vector<char>& cvec,char r='_') { 
    std::string rstr(varStr); 
    for ( auto c : cvec ) { rstr = replace(rstr,c,r); }
    return rstr; 
  } 
 
} // String

#endif
