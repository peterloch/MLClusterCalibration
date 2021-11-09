// -*- c++ -*-
#ifndef CLUSTERPLOTSSPECTRA_H
#define CLUSTERPLOTSSPECTRA_H

#include "ClusterPlotsBase.h"

template<class SERVER> class ClusterPlotsSpectra : public ClusterPlotsBase {
public:
  ClusterPlotsSpectra();
  ClusterPlotsSpectra(const ClusterPlotsCfg& cfg); 

  virtual bool book(); 
  virtual bool fill(); 
  virtual bool write();

  using IClusterPlots::setDataServer; virtual bool setDataServer(SERVER* server); 
  using IClusterPlots::dataServer;    virtual SERVER* dataServer(); 
private:

  template<class T>  std::map<std::string,T&> tupleStore; 

};
#endif
