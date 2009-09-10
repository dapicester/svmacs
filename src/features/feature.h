/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef FEATURE_H
#define FEATURE_H

#include <itpp/base/vec.h>
#include <string>

namespace features {

using itpp::vec;
using std::string;

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

public:
    inline string getName() const { 
        return name; 
    }
    
    inline int getSamplerate() const {
        return samplerate;
    }

    virtual Type getType() const = 0;

    /** Process an audio frame and returns its features 
     \param frame data to be processed
     \param features features vector to which append data
     */
    virtual void extract(const vec& frame, vec& features) const = 0;

};

}

#endif
