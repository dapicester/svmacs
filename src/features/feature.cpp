/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <features/feature.h>
using namespace features;

Feature::Feature(int sr, Type t) : samplerate(sr), type(t) {}

Feature::~Feature() {}

std::string 
Feature::getName() const { 
  return name; 
}

Type
Feature::getType() const {
  return type;
}

void 
Feature::setName(const std::string& n) {
  name = n; 
} 
