/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "feature.h"

Feature::Feature(int sr, Type t) : samplerate(sr), type(t) {}

Feature::~Feature() {}

inline
std::ostream& operator<<(std::ostream& os, const Feature& feature) {
  os << feature.getName() << std::endl;
  return os;
}
