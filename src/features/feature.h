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
 * Abstract class for feature extractors. 
 */
class Feature {
  
  public:
        
    /// Getter for the name property.
    string getName() const;

    /// Getter for the type property.
    Type getType() const;

    /**
     * Processes an audio frame and returns the computed features.
     * \param frame 
     * 	 data to be processed
     * \param features 
     *   features vector to which append the computed feature
     */
    virtual void extract(const vec& frame, vec& features) const = 0;
    
  protected:
    
    /// Constructor.
    Feature(int sr, Type type);
    
    /// Setter for the name property.
    void setName(const string& n);
    
    /// The actual sampleate;
    int samplerate;
       
  private:
    
    /// The feature type.
    Type type;
    
    /// The feature name.
    string name;
    
};
    
}

#endif
