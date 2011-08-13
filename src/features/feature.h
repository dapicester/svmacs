/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef FEATURE_H
#define FEATURE_H

#include <itpp/base/vec.h>
#include <boost/noncopyable.hpp>

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
class Feature : boost::noncopyable {
public:
    Feature(int sampleRate, Type type);
    virtual ~Feature();
    
    /// Operator overload
    friend std::ostream& operator<< (std::ostream& os, const Feature& feature);
    
    /// Getter for the type property.
    Type getType() const { return type; }
    
    /// Getter for the name property.
    std::string getName() const { return name; }

    /**
     * Processes an audio frame and returns the computed features.
     * \param data 
     * 	 data to be processed
     * \param features 
     *   features vector to which append the computed feature
     */
    virtual void extract(const itpp::vec& data, itpp::vec* features) const = 0;
    
protected:
    /// The actual sample rate;
    int samplerate;
    
    /// The feature type.
    Type type;
    
    /// The feature name.
    std::string name;  
};

#endif
