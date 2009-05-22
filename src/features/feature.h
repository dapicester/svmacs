/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef FEATURE_H
#define FEATURE_H

#include <string>
using namespace std;

namespace features {

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
    
public:
    string getName() const { 
        return name; 
    }
    
    int getSamplerate() const {
        return samplerate;
    }

    /** Process an audio frame and returns its features */
    virtual float* extract(const float frame[]) const = 0;
    
};

}

#endif
