// -*- c++ -*-
#ifndef ICLUSTERPLOTS_H
#define ICLUSTERPLOTS_H

#include <string>

#include <boost/any.hpp>

class IClusterPlots {
public:
  // pure virtual base class destructor
  virtual ~IClusterPlots() { }
  // implementation classes have a name
  virtual const std::string& name()           const = 0; // implementation object name
  virtual const std::string& treeName()       const = 0; // tree name
  virtual const std::string& inputFileName()  const = 0; // input file name
  virtual const std::string& outputFileName() const = 0; // output file name
  // general interface
  virtual bool book()  = 0;
  virtual bool fill()  = 0;
  virtual bool write() = 0;
  // server 
  bool setDataServer(boost::any* server) = 0;
  boost::any* dataServer()               = 0;
};


#endif
