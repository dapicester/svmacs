/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#ifndef EXECPATH_H
#define	EXECPATH_H

#include <boost/filesystem/path.hpp>
#include <string>

/**
 * @brief Contains information about the actual executable path.
 */
class ExecPath {
public:
    static void init(const std::string&);
    static ExecPath* getInstance();
            
/*  /// @brief Returns the executable path.
    boost::filesystem::path execPath() const {
        return path;
    };
*/    
    /// @brief Returns the full path string of the given file.
    std::string getPath(const std::string& fileName) const;
    
private:
    ExecPath(const std::string&);
    
    static ExecPath* single;
    
    boost::filesystem::path path;
};

#endif	/* EXECPATH_H */
