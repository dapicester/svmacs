/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "version.h"
#include "config.h"
#include "cli/svmaccli.h"

#ifdef ENABLE_GUI
#include "gui/svmacgui.h"
#include <QApplication>
#endif

#define RLOG_COMPONENT "main"
#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>

#include <boost/filesystem.hpp>
namespace bf = boost::filesystem;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <fstream>
#include <iostream>

using namespace svmacs;
using namespace rlog;
using namespace std;

void showVersion() {
    cout << "svmacs " 
            << VERSION_MAJOR << "." 
            << VERSION_MINOR << "." 
            << VERSION_PATCH << endl;
    cout << "Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>" << endl;
    cout << "This software is provided as-is, with absolutely no warranty." << endl;
}

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

    // generoptions allowed only on command line
    po::options_description generic("Generic options");
    generic.add_options()
#ifdef ENABLE_GUI        
        ("gui,g", "launch the gui")
#endif
        ("help,h", "print help message")
        ("version,v", "show version string")
    ;

    // Declare the supported options.
    float length, overlap;
    string dmodel, cmodel;

    // options allowed both on command line and config file
    po::options_description config("Configuration");
    config.add_options()
        ("config,F", po::value<string>(),
                    "use configuration file")
        ("length,N", po::value<float>(&length)->default_value(0.5), 
                   "set frame length (in seconds)")
        ("overlap,R", po::value<float>(&overlap)->default_value(50.0), 
                    "set frames overlapping ratio (percentage)")
    ;

    // hidden options, allowed both on command line and config file
    po::options_description hidden("Hidden options");
    hidden.add_options()
        ("cfile,C", po::value<string>(), "Classification model file")
        ("dfile,D", po::value<string>(), "Detection model file")
    ;

    // options configuration
    po::options_description cmdlineOptions;
    cmdlineOptions.add(generic).add(config).add(hidden);

    po::options_description cfgfileOptions;
    cfgfileOptions.add(config).add(hidden);

    po::options_description visibleOptions("Allowed options");
    visibleOptions.add(generic).add(config);
#ifndef NDEBUG
    visibleOptions.add(hidden);
#endif

    // parsing options
    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, cmdlineOptions), vm);

        if (not bf::exists(CONFIG_FILE)) {
            rWarning("No configuration file found");
        } else {
            rInfo("Using configuration file %s", CONFIG_FILE);
            ifstream configFile(CONFIG_FILE);
            po::store(po::parse_config_file(configFile, cfgfileOptions), vm);
        }
        po::notify(vm);
    } catch (po::error& e) {
        rError("Error: %s@", e.what());
        return 1;
    }

    if (vm.count("help")) {
        cout << visibleOptions << endl;
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
    } 

    if (vm.count("overlap")) {
        overlap = vm["overlap"].as<float>();
        rInfo("frames overlap set to %.2f%%", overlap);
    } 

    if (vm.count("dfile")) {
        dmodel.assign(vm["dfile"].as<string>());
        rInfo("using detection model: %s", dmodel.c_str());
    } else {
        rError("detection model not set.");
        return 1;
    }
    if (vm.count("cfile")) {
        cmodel.assign(vm["cfile"].as<string>());
        rInfo("using classification model: %s", cmodel.c_str());
    } else {
        rError("classification model not set.");
        return 1;
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
        SvmacGui gui(length, overlap, dmodel, cmodel);
        gui.show();
        return app.exec();
    }
#endif

    rInfo("Launching the CLI interface ...");
    SvmacCli* cli = new SvmacCli;
    try {
        cli->start(length, overlap, dmodel, cmodel);
    } catch (runtime_error& e) {
        rError("Error: %s", e.what());
    }

    delete cli;
    rInfo("Bye!");

    return 0;
};
