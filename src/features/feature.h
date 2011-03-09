/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef FEATURE_H
#define FEATURE_H

#include <itpp/itbase.h>
#include <string>

namespace features {

/**
 * Enumeration for feature types.
 */
enum Type {
  /// Feature based on the signal time-representation.
  TEMPORAL, 
  /// Feature based on the signal frequency-representation.
  SPECTRAL 
};

/**
 * Abstract base class for feature extractors. 
 */
class Feature {
public:
    Feature(int sr, Type type);
    virtual ~Feature();
    
    /// Getter for the name property.
    std::string getName() const;

    /// Getter for the type property.
    Type getType() const;

    /**
     * Processes an audio frame and returns the computed features.
     * \param frame 
     * 	 data to be processed
     * \param features 
     *   features vector to which append the computed feature
     */
    virtual void extract(const itpp::vec& frame, itpp::vec& features) const = 0;
    
protected:
    /// Setter for the name property.
    void setName(const std::string& n);
    
    /// The actual sample rate;
    int samplerate;
       
private:
    /// The feature type.
    Type type;
    
    /// The feature name.
    std::string name;  
};
    
}

#endif
