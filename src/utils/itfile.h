/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef IT_FILE_H
#define IT_FILE_H

#include <itpp/itbase.h>

/** Saves the input vector with the given name to the specified file */ 
inline void write_vec(const itpp::it_file& file, const itpp::vec& input, const std::string& name) {
    file << itpp::Name(name) << input;
}

/** Reads the specified variable from a file */ 
inline itpp::vec read_vec(const itpp::it_ifile file, const std::string& name) {
    vec tmp;
    file >> itpp::Name(name) >> a;
    return tmp;
}

#endif
