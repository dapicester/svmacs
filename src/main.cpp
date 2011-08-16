/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "version.h"
#include "config.h"
#include "cli/svmaccli.h"
#include "utils/execpath.h"

#ifdef ENABLE_GUI
#include "gui/svmacgui.h"
#include <QApplication>
#endif

#define RLOG_COMPONENT "main"
#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>
using namespace rlog;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>

void showVersion() {
    using namespace std;
    cout << "svmacs " 
            << VERSION_MAJOR << "." 
            << VERSION_MINOR << "." 
            << VERSION_PATCH << endl;
    // TODO: show copyright and no warranty advise
}

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

    // initialize 
    ExecPath::init(argv[0]);
    
    // Declare the supported options.
    float length = 0.5;
    float overlap = 50.0;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message\n")
        ("length,N", po::value<float>(), 
                   "set frame length (in seconds),\ndefaults to 0.5 second\n")
        ("overlap,R", po::value<float>(), 
                    "set frames overlapping ratio (percentage),\ndefaults to 50 %\n")
#ifdef ENABLE_GUI        
        ("gui,g", "launch the gui")
#endif
        ("version,v", "show version")
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
        return 0;
    }
    
    if (vm.count("version")) {
        showVersion();
        return 0;
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
    
#ifdef ENABLE_GUI
    bool gui = false;
    if (vm.count("gui")) {
        gui = true;
    }
    
    if (gui) {
        rInfo("launching the GUI interface ...");
        Q_INIT_RESOURCE(application);
        QApplication app(argc, argv);
        SvmacGui gui(length, overlap);
        gui.show();
        return app.exec();
    }
#endif

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
