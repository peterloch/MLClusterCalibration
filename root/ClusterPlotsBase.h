// -*- c++ -*-
#ifndef CLUSTERPLOTSBASE_H
#define CLUSTERPLOTSBASE_H

#include <TFile.h>
#include <TTree.h>

#include<string>
#include<map>

#include <cstdio>
#include <cstdarg>

#include <cxxabi.h>
#include <typeinfo>

namespace ClusterPlots {
  // string constants
  static const std::string emptyString        = { ""             };
  static const std::string unknownString      = { "UNKNOWN"      };
  static const std::string unidentifiedString = { "UNIDENTIFIED" };
  static const std::string invalidString      = { "INVALID"      };

  ///////////////
  // Messaging //
  ///////////////
 
  namespace Msg {
    // -- message type
    enum class Type { INFO = 0x01, ABRT = 0x02, WARN = 0x04, DEBG = 0x08, UNKN = 0x00 };
    // -- type-to-string dictionary
    static const std::map<Type,std::string>  typeToString = { { Type::INFO, "INFO" }, { Type::ABRT, "ABRT" }, { Type::WARN, "WARN" }, { Type::DEBG, "DEBG" }, { Type::UNKN, "UNKN" } };
    // -- string-to-type dictionary
    static const std::map<Type,std::string>  stringToType = { { "INFO", Type::INFO }, { "ABRT", Type::ABRT }, { "WARN", Type::WARN }, { "DEBG", Type::DEBG }, { "UNKN", Type::UNKN } };
    // -- converters
    static const std::string& typeName(Type mtype)               { return typeToString.at(mtype) ; }  // type-to-string
    static const char*        typeChar(Type mtype)               { return typeName(mtype).c_str(); }  // type-to-char
    static Type               nameType(const std::string& tname) { auto ftype(stringToType.find(tname)); return ftype != nameToType.end() ? ftype->second : Type::UNKN; } 
    // -- formatting variable argument list
    static std::string formatted(const std::string& fmtstr,va_list& args) { static char _buffer[4096]; vsprintf(_buffer,fmtstr.c_str(),args); return std::string(_buffer); }
    static std::string formatted(const char*        fmtchr,va_list& args) { static char _buffer[4096]; vsprintf(_buffer,fmtchr,        args); return std::string(_buffer); }
    // -- formatting variable arguments
    static std::string formatted(const char* fmtchr,...        ) { va_list args; va_start(args,fmtchr); std::string fstr(formatted(fmtchr,args)); va_end(args); return fstr; }
    static std::string formatted(const std::string& fmtstr,... ) { va_list args; va_start(args,fmtstr); std::string fstr(formatted(fmtstr,args)); va_end(args); return fstr; }
    // -- printing fully formatted message
    static void print(const std::string& modName,const std::string& entryName,const std::string& msgString,Type mtype=Type::INFO) { printf("[%s::%s] %s %s\n",modName.c_str(),entryName.c_str(),msgString.c_str(),typeChar(mtype)); }
    static void print(const std::string& modName,                             const std::string& msgString,Type mtype=Type::INFO) { printf("[%s] %s %s\n",modName.c_str(),msgString.c_str(),typeChar(mtype));                       }
    // -- printing variable arguments with given format
    static void print(Type mtype,const std::string& modName,const std::string& entryName,const std::string& fmtstr,...) { va_list args; va_start(args,fmtstr); print(modName,entryName,formatted(fmtstr,args),mtype); va_end(args); }
    static void print(Type mtype,const std::string& modName,                             const std::string& fmtstr,...) { va_list args; va_start(args,fmtstr); print(modName,formatted(fmtstr,args),mtype); va_end(args);           }
    // -- printing logical values
    static const std::map<bool,std::string> boolToString = { { true, "true" },                        { false, "false" }                        };
    static const std::map<bool,const char*> boolToChar   = { { true, boolToString.at(true).c_str() }, { false, boolToString.at(false).c_str() } };
    static const std::map(std::string,bool> stringToBool = { { "true", true },                        { "false", false }                        };
  } // ClusterPlots::Msg

  ///////////////
  // Utilities //
  ///////////////

  namespace Utils {
    // -- class name demangling data
    typedef std::tuple<std::string,int> cxa_status_t;                                                // data: <0> demangled class name <1> status flag 
    static std::string&       objectName  (cxa_status_t& rstat      ) { return std::get<0>(rstat); } // extract class name (non-const reference for assignments)       
    static int&               objectStatus(cxa_status_t& rstat      ) { return std::get<1>(rstat); } // extract demangling status (non-const reference for assignments)
    static const std::string& objectName  (const cxa_status_t& rstat) { return std::get<0>(rstat); } // extract class name (const reference for access)       
    static const int          objectStatus(const cxa_status_t& rstat) { return std::get<1>(rstat); } // extract demangling status (const value for access)
    // -- class name demangling function
    template<class T> static cxa_status_t objectType(const T& obj) {                                 
      int ostatus(-999); std::string oname(abi::__cxa_demangle(typeid(obj).name(),0,0,&ostatus)); 
      return { oname, ostatus}; 
    }
    // -- class name demangling status message
    template<class T> static void objectMsg(const T& obj,const std::string& modName,const std::string& entryName) { 
      // get object name and status
      auto rstat = objectType< T >(obj);
      int  istat = objectStatus(rstat); 
      const std::string& nstat = objectName(rstat); 
      // set up message
      switch ( istat ) { 
      case 0:
	if ( entryName == "" ) { ClusterPlots::Msg::print(modName,          ClusterPlots::Msg::formatted("instantiated object type %s",nstat.c_str()),ClusterPlots::Msg::INFO); 
	} else {                 ClusterPlots::Msg::print(modName,entryName,ClusterPlots::Msg::formatted("instantiated object type %s",nstat.c_str()),ClusterPlots::Msg::INFO); }
	break;
      case -1:
	nstat = ClusterPlots::unknownString; 
	if ( entryName == "" ) { ClusterPlots::Msg::print(modName,          ClusterPlots::Msg::formatted("memory allocation failed for object type %s - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); 
	} else {                 ClusterPlots::Msg::print(modName,entryName,ClusterPlots::Msg::formatted("memory allocation failed for object type %s - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); }
	break;
      case -2:
	nstat = ClusterPlots::unidentifiedString; 
	if ( entryName == "" ) { ClusterPlots::Msg::print(modName,          ClusterPlots::Msg::formatted("memory allocation failed for object type %s - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); 
	} else {                 ClusterPlots::Msg::print(modName,entryName,ClusterPlots::Msg::formatted("memory allocation failed for object type %s - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); }
	break;
      case -3:
	nstat = ClusterPlots::unidentifiedString; 
	if ( entryName == "" ) { ClusterPlots::Msg::print(modName,          ClusterPlots::Msg::formatted("one or more arguments for demangling object type %s invalid - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); 
	} else {                 ClusterPlots::Msg::print(modName,entryName,ClusterPlots::Msg::formatted("one or more arguments for demangling object type %s invalid - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); }
	break;
      default:
	nstat = ClusterPlots::invalidString;
	if ( entryName == "" ) { ClusterPlots::Msg::print(modName,          ClusterPlots::Msg::formatted("invalid  object type %s - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); 
	} else {                 ClusterPlots::Msg::print(modName,entryName,ClusterPlots::Msg::formatted("invalid  object type %s - object usable",nstat.c_str()),ClusterPlots::Msg::WARN); }
	break;
      }
    }
  } // ClusterPlots::Utils
} // ClusterPlots

struct ClusterPlotsCfg {std:string name = { "UNKNOWN" };     
  // implementation name
  std::string name           = { ClusterPlots::unknownString };
  // file & tree names
  std::string inputFileName  = { ClusterPlots::emptyString   };
  std::string outputFileName = { ClusterPlots::emptyString   };
  std::string treeName       = { "ClusterTree"               };
  // process control
  int         entries        = { -1 };
  bool        printInfo      = { true };
  bool        printAbrt      = { true };
  bool        printWarn      = { true };
  bool        printDebg      = { true };
  ClusterPlotsCfg() { }
  ClusterPlotsCfg(const ClusterPlotsCfg& cfg) 
    : name          (cfg.name          )
    , inputFileName (cfg.inputFileName )
    , outputFileName(cfg.outputFileName)
    , treeName      (cfg.treeName      )
    , entries       (cfg.entries       )
    , printInfo     (cfg.printInfo     )
    , printAbrt     (cfg.printAbrt     )
    , printWarn     (cfg.printWarn     )
    , printDebg     (cfg.printDebg     )
  { }
  ClusterPlotsCfg& operator=(const ClusterPlotsCfg& cfg) { 
    if ( &cfg != this ) { 
      name           = cfg.name          ;
      inputFileName  = cfg.inputFileName ;
      outputFileName = cfg.outputFileName;
      treeName       = cfg.treeName      ;
      entries        = cfg.entries       ;
      printInfo      = cfg.printInfo     ;
      printAbrt      = cfg.printAbrt     ;
      printWarn      = cfg.printWarn     ;
      printDebg      = cfg.printDebg     ;
    }
    return *this; 
  }
};

class ClusterPlotsBase : virtual public IClusterPlots
{
public:
  ClusterPlotsBase();
  ClusterPlotsBase(const ClusterPlotsCfg& cfg);
  virtual ~ClusterPlotsBase() { }
  
  // configure object 
  void setInputFile (const std::string& inputFile );
  void setOutputFile(const std::string& outputFile);
  void setTreeName  (const std::string& treeName  );
  void setEntries   (int entries=-1  ); 
  void setPrintInfo (bool flag=true  );
  void setPrintAbrt (bool flag=true  ); 
  void setPrintWarn (bool flag=true  );
  void setPrintDebg (bool flag=false );

  // retrieve configuration
  const std::string& inputFileName () const; 
  const std::string& outputFileName() const;
  const std::string& treeName()       const;
  const int          entries()        const;
  const bool         printInfo()      const;
  const bool         printAbrt()      const;
  const bool         printWarn()      const;
  const bool         printDebg()      const; 

  // retrieve infrastructure
  TTree* tree(); 
  TFile* inputFile(); 

  // user hook
  virtual bool book ();
  virtual bool fill ();
  virtual bool write();
  virtual const std::string& name() const;
 
  // // set server (needs to be implemented by clients)
  // using IClusterPlots::setDataServer;
  // template<class SERVER> bool setDataServer(SERVER* server) { return false;   }
  // // get server (needs to be implemented by clients)
  // using IClusterPlots::dataServer;
  // template<class SERVER> SERVER* dataServer()               { return nullptr; }

protected:

  virtual void print(ClusterPlots::Msg::Type mtype,const std::string& entryName,const std::string& fmtStr,...);
  virtual void print(ClusterPlots::Msg::Type mtype,const std::string& fmtStr,...);

  virtual bool init();
  virtual bool printFlag(ClusterPlots::Msg::Type mtype); 
  
  typedef std::tuple<std::string,std::string> Location; 
  
  const std::string& moduleName(const Location& loc) { return std::get<0>(loc); }
  const std::string& entryName (const Location& loc) { return std::get<1>(loc); }
  std::string& moduleName(Location& loc) { return std::get<0>(loc); }
  std::string& entryName (Location& loc) { return std::get<1>(loc); }

private:

  ClusterPlotsCfg m_config     = { ClusterPlotsCfg()         }; // configuration
  std::string     m_className  = { ClusterPlots::emptyString }; // class name
  TFile*          m_inputfile  = { (TFile*)0                 }; // input file pointer
  TTree*          m_tree       = { (TTree*)0                 }; // tree pointer
  bool            m_isSetup    = { false                     }; // setup flag

  std::map<ClusterPlots::Msg::Type,int> m_printFlags;

  Location m_location = { "", "" };

protected:

  virtual void locateEntry(const std::string& modName,const std::string& entryName="") { m_location = { modName, entryName }; }
  virtual const Location& retrieveEntry()                                              { return m_location; }

};
#endif
