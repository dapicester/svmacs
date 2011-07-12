/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "execpath.h"
#include "exceptions/exceptions.h"
#include <boost/filesystem/convenience.hpp>

ExecPath* ExecPath::single = NULL;

void ExecPath::init(const std::string& argv) {
    if (single) {
        delete single;
    }
        
    single = new ExecPath(argv);
}

ExecPath* ExecPath::getInstance() {
    if (!single) {
        throw NotInitialized();
    } 
    return single;
}

ExecPath::ExecPath(const std::string& argv) {
   boost::filesystem::path argvPath(argv);
   path = boost::filesystem::path( argvPath.parent_path() ); 
}

std::string ExecPath::getPath(const std::string& fileName) const { 
    boost::filesystem::path file = path / boost::filesystem::path(fileName);
    return file.string(); 
}
