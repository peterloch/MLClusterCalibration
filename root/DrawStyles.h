// -*- c++ -*-
#ifndef DRAWSTYLES_H
#define DRAWSTYLES_H
static const std::map<Types::Graph::ScaleTag,Types::Graph::LineDescriptor> lineStyles = { 
  { Types::Graph::knownScales.at(0), Types::Graph::DescriptionFactory::Line((int)kRed     ,1,2,0.90) },  // EM red
  { Types::Graph::knownScales.at(1), Types::Graph::DescriptionFactory::Line((int)kBlue    ,1,2,0.90) },  // LC blue
  { Types::Graph::knownScales.at(2), Types::Graph::DescriptionFactory::Line((int)kOrange+3,1,2,0.90) }   // ML brown 
};
static const std::map<Types::Graph::ScaleTag,Types::Graph::MarkerDescriptor> markerStyles = { 
  { Types::Graph::knownScales.at(0), Types::Graph::DescriptionFactory::Marker((int)kRed     ,20,0.75,0.) },  // EM red
  { Types::Graph::knownScales.at(1), Types::Graph::DescriptionFactory::Marker((int)kBlue    ,20,0.75,0.) },  // LC blue
  { Types::Graph::knownScales.at(2), Types::Graph::DescriptionFactory::Marker((int)kOrange+3,20,0.75,0.) }   // ML brown 
};
static const std::map<Types::Graph::ScaleTag,Types::Graph::FillDescriptor> fillStyles = { 
  { Types::Graph::knownScales.at(0), Types::Graph::DescriptionFactory::Fill((int)kRed-9   ,1001,200,0.90) },  // EM red
  { Types::Graph::knownScales.at(1), Types::Graph::DescriptionFactory::Fill((int)kBlue-9  ,1001,200,0.90) },  // LC blue
  { Types::Graph::knownScales.at(2), Types::Graph::DescriptionFactory::Fill((int)kOrange-9,1001,200,0.90) }   // ML brown 
};
#endif
