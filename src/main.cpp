/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "cli/svmaccli.h"

#define RLOG_COMPONENT "main"
#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>
using namespace rlog;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>

/**
 *  @brief The application CLI.
 *  @author Paolo D'Apice
 */
int main(int argc, char** argv) {
    // initialize logging
    RLogInit(argc, argv);
    StdioNode log;
#ifdef ENABLE_LOG
    log.subscribeTo( GetGlobalChannel("debug") );
#endif 
    log.subscribeTo( GetGlobalChannel("info") );
    log.subscribeTo( GetGlobalChannel("warning") );
    log.subscribeTo( GetGlobalChannel("error") );
    
    // Declare the supported options.
    float length = 1.0;
    float overlap = 0.0;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message\n")
        ("length,N", po::value<float>(), //(&length)->default_value(1.0), 
                   "set frame length (in seconds),\ndefaults to 1 second\n")
        ("overlap,R", po::value<float>(), //(&overlap)->default_value(0.0),
                    "set frames overlapping ratio (percentage),\ndefaults to 0 %%\n")
    ;
    
    // parsing command line
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (po::error& e) {
        rError("Error: %s@", e.what());
        return 1;
    }
    
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    // TODO check arguments
    if (vm.count("length")) {
        length = vm["length"].as<float>();
        rInfo("frame length set to %.2f seconds", length);
    } else {
        rInfo("using default frame length: %.2f seconds", length);
    }
    
    if (vm.count("overlap")) {
        overlap = vm["overlap"].as<float>();
        rInfo("frames overlap set to %.2f %%", overlap);
    } else {
        rInfo("using default frame overlap: %.2f %%", overlap);
    }
     
    rInfo("Launching the CLI interface ...");
    SvmacCli* cli = new SvmacCli;
    try {
        cli->start(length, overlap);
    } catch (std::runtime_error& e) {
        rError("Error: %s", e.what());
    }
  
    delete cli;
    rInfo("Bye!");
    
    return 0;
};
