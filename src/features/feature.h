/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef FEATURE_H
#define FEATURE_H

#include <itpp/itsignal.h>
using namespace itpp;

#include <string>
using namespace std;

namespace features {

/// Type of feature
enum Type { 
    TEMPORAL, 
    SPECTRAL 
};

/** Interface to be implemented. */
class Feature {
private:
    string name;
    int samplerate;
    
protected:
    void setName(const string& n) {
        name = n; 
    }
    
    void setSamplerate(const int& sr) {
        samplerate = sr;
    }

   Type type;
    
public:
    inline string getName() const { 
        return name; 
    }
    
    inline int getSamplerate() const {
        return samplerate;
    }

    inline int getType() {
        return type;
    }

    /** Process an audio frame and returns its features */
    virtual vec extract(const vec& frame) const = 0;

};

}

#endif
