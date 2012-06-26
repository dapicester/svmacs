/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "feature.h"

NS_SVMACS_BEGIN

// FIXME: inline this!!!

Feature::Feature(int sr, Type t) : samplerate(sr), type(t) {}

Feature::~Feature() {}

inline
std::ostream& operator<<(std::ostream& os, const Feature& feature) {
  os << feature.getName() << std::endl;
  return os;
}

NS_SVMACS_END
