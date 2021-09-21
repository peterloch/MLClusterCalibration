
#include "ClusterPlotsBase.h"

#define CB_SET_LOC( M, E ) this->locateEntry( #M, #E )
#define CB_GET_MOD         this->moduleName(m_location)     
#define CB_GET_ENT         this->entryName(m_location)
#define CB_GET_LOC( M, E ) M = this->moduleName(m_location); E = this->entryName(m_location)

ClusterPlotsBase::ClusterPlotsBase() {
  CB_SET_LOC( ClusterPlotsBase, ClusterPlotsBase );
  ClusterPlots::Utils::objectMessage(*this,"ClusterplotsBase","ClusterPlotsBase()");
  m_config.name = ClusterPlots::Utils::objectName(ClusterPlots::Utils::objectType(*this));
  if (!this->init()) {
    this->print(ClusterPlots::Msg::Type::ABRT, CH_GET_MOD, CB_GET_ENT, "initialization failure, no object instantiated." );
    delete this; 
  }
}

ClusterPlotsBase::ClusterPlotsBase(const ClusterPlotsCfg& cfg) : m_config(cfg) { 
  CB_SET_LOC( ClusterPlotsBase, ClusterPlotsBase );
  ClusterPlots::Utils::objectMessage(*this,"ClusterPlotsBase(const ClusterPlotsCfg&)");
  if (!this->init()) {
    this->print(ClusterPlots::Msg::Type::ABRT, CH_GET_MOD, CB_GET_ENT, "initialization failure, no object instantiated." );
    delete this; 
  }
}

// configure object 
void ClusterPlotsBase::setInputFile (const std::string& inputFile ) { 
  CB_SET_LOC( ClusterPlotsBase, setInputFile  ); m_config.inputFileName  = inputFile ; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new inputFileName  .: %s", inputFileName.c_str()); 
}
void ClusterPlotsBase::setOutputFile(const std::string& outputFile) { 
  CB_SET_LOC( ClusterPlotsBase, setOutputFile ); m_config.outputFileName = outputFile; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new outputFileName .: %s", outputFileName.c_str()); 
}
void ClusterPlotsBase::setTreeName  (const std::string& treeName  ) { 
  CB_SET_LOC( ClusterPlotsBase, setTreeName   ); m_config.treeName       = treeName  ; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new treeName .......: %s", treeName.c_str()); 
}
void ClusterPlotsBase::setEntries   (int entries                  ) { 
CB_SET_LOC( ClusterPlotsBase, setEntries      ); m_config.entries        = entries   ; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new entries ........: %i", entries); 
} 
void ClusterPlotsBase::setPrintInfo (bool flag                    ) { 
  CB_SET_LOC( ClusterPlotsBase, setPrintInfo  ); m_config.printInfo      = flag      ; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new printInfo status: %s", ClusterPlots::Msg::boolToCharta(pm_config.rintInfo)); 
}
void ClusterPlotsBase::setPrintAbrt (bool flag                    ) { 
  CB_SET_LOC( ClusterPlotsBase, setPrintAbrt  ); m_config.printAbrt      = flag      ; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new printAbrt status: %s", ClusterPlots::Msg::boolToChar.at(m_config.printAbrt)); 
} 
void ClusterPlotsBase::setPrintWarn (bool flag                    ) { 
  CB_SET_LOC( ClusterPlotsBase, setPrintWarn  ); m_config.printWarn      = flag      ; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new printWarn status: %s", ClusterPlots::Msg::boolToChar.at(m_config.printWarn)); 
}
void ClusterPlotsBase::setPrintDebg (bool flag                    ) { 
  CB_SET_LOC( ClusterPlotsBase, setPrintDebg  ); m_config.printDebg      = flag      ; this->print(ClusterPlots::Msg::Type::INFO, CB_GET_MOD, CB_GET_ENT, "new printDebg status: %s", ClusterPlots::Msg::boolToChar.at(m_config.printDebg)); 
}

// retrieve configuration
const std::string& ClusterPlotsBase::name()           const { CB_SET_LOC( ClusterPlotsBase, name()           ); return m_config.name          ; }
const std::string& ClusterPlotsBase::inputFileName () const { CB_SET_LOC( ClusterPlotsBase, inputFileName () ); return m_config.inputFileName ; } 
const std::string& ClusterPlotsBase::outputFileName() const { CB_SET_LOC( ClusterPlotsBase, outputFileName() ); return m_config.outputFileName; }
const std::string& ClusterPlotsBase::treeName()       const { CB_SET_LOC( ClusterPlotsBase, treeName()       ); return m_config.treeName      ; }
const int          ClusterPlotsBase::entries()        const { CB_SET_LOC( ClusterPlotsBase, entries()        ); return m_config.entries       ; }
const bool         ClusterPlotsBase::printInfo()      const { CB_SET_LOC( ClusterPlotsBase, printInfo()      ); return m_config.printInfo     ; }
const bool         ClusterPlotsBase::printAbrt()      const { CB_SET_LOC( ClusterPlotsBase, printAbrt()      ); return m_config.printAbrt     ; }
const bool         ClusterPlotsBase::printWarn()      const { CB_SET_LOC( ClusterPlotsBase, printWarn()      ); return m_config.printWarn     ; }
const bool         ClusterPlotsBase::printDebg()      const { CB_SET_LOC( ClusterPlotsBase, printDebg()      ); return m_config.printDebg     ; }

// retrieve infrastructure
TTree* ClusterPlotsBase::tree     () { CB_SET_LOC( ClusterPlotsBase, tree()      ); return m_tree     ; } 
TFile* ClusterPlotsBase::inputFile() { CB_SET_LOC( ClusterPlotsBase, inputFile() ); return m_inputFile; } 

// do-nothing implementations for IClusterBase interfaces
bool ClusterPlotsBase::book()  { CB_SET_LOC( ClusterPlotsBase, book()  ); return false; }
bool ClusterPlotsBase::fill()  { CB_SET_LOC( ClusterPlotsBase, fill()  ); return false; }
bool ClusterPlotsBase::write() { CB_SET_LOC( ClusterPlotsBase, write() ); return false; }

const std::string& ClusterPlotsBase::name() const { return this->moduleName(m_location); }


void ClusterPlotsBase::print(ClusterPlots::Msg::Type mtype,const std::string& entryName,const std::string& fmtStr,...) {
  if ( !this->printFlag(mtype) ) { return; }
  va_list args; va_start(args,fmtStr); ClusterPlots::Msg::print(mtype,name(),entryName,fmtStr,args); va_end(args); 
}
void ClusterPlotsBase::print(ClusterPlots::Msg::Type mtype,const std::string& fmtStr,...) { 
  if ( !this->printFlag(mtype) ) { return; }
  va_list args; va_start(args,fmtStr); ClusterPlots::Msg::print(mtype,name(),fmtStr,args); va_end(args); 
}

// initialization/setup
bool ClusterPlotsBase::init() {
  CB_SET_LOC( ClusterPlotsBase, init() );
  if ( m_setup ) { 
    this->print(ClusterPlots::Msg::WARN,"init()","module already set up, ignored");
    return true; 
  } 
  // preload printflags
  m_printFlags.clear();
  if ( this->printInfo() ) { m_printFlags[ClusterPlots::Msg::INFO] = 0; }
  if ( this->printWarn() ) { m_printFlags[ClusterPlots::Msg::WARN] = 0; }
  if ( this->printDebg() ) { m_printFlags[ClusterPlots::Msg::DEBG] = 0; }
  if ( this->printAbrt() ) { m_printFlags[ClusterPlots::Msg::ABRT] = 0; }

  // open input file
  m_inputFile = new TFile(inputFileName().c_str(),"READ"); 
  if ( m_inputFile == nullptr ) { 
    this->print(ClusterPlots::Msg::ABRT,"init()","cannot open file \042%s\042, abort.",inputFileName().c_str());
    return m_setup; 
  }
  // allocate tree
  m_tree = (TTree*)inputFile()->FindObjectAny(this->treeName().c_str());
  if ( m_tree == nullptr ) { 
    this->print(ClusterPlots::Msg::ABRT,"init()","cannot find tree \042%s\042 in input file \042%s\042, abort.",treeName().c_str(),inputFileName().c_str());
    return m_setup;
  }
  // successfully allocated inputs
  m_setup = true;
  this->print(ClusterPlots::Msg::INFO,"allocated tree \042%s\042 in file \042%s\042",tree()->GetName(),inputFile()->GetName());
  return m_setup; 
}

bool ClusterPlotsBase::printFlag(ClusterPlots::Msg::Type mtype) {
  auto fprint(m_printFlags.find(mtype));
  if ( fprint != m_printFlags.end() ) { ++(fprint->second); return true; } else { return false; }
}
