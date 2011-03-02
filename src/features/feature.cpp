#include <features/feature.h>
using namespace features;

Feature::Feature(int sr, Type t) : samplerate(sr), type(t) {}

/*inline*/ string 
Feature::getName() const { 
  return name; 
}

/*inline*/ Type
Feature::getType() const {
  return type;
}

void 
Feature::setName(const string& n) {
  name = n; 
} 
