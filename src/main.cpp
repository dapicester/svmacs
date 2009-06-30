/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "cli/svmaccli.h"
using namespace cli;

#include "gui/svmacgui.h"

#define RLOG_COMPONENT "main"
#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>

#include <QApplication>

#include <iostream>
#include <string>

using namespace std;
using namespace rlog;

void usage(const char* s);

/**
 @brief The application entry point.
 
 It sets up the loggers, parse the command line arguments 
 and instantiate either the CLI or the GUI.
 
 @author Paolo D'Apice
 */
int main(int argc, char *argv[]) {
    // initialize logging    
    RLogInit(argc, argv);
    StdioNode log;
#ifdef ENABLE_DEBUG
    log.subscribeTo( GetGlobalChannel("debug") );
#endif 
    log.subscribeTo( GetGlobalChannel("info") );
    log.subscribeTo( GetGlobalChannel("warning") );
    log.subscribeTo( GetGlobalChannel("error") );
     
    // check arguments 
    if (argc > 4) {
        rDebug("too many arguments (%i)", argc);
        usage(argv[0]); 
        exit(1);
    }
    
    string interface; 
    if (argc == 1) {
        rDebug("no arguments");
        interface = "cli";
    } else {
        interface = argv[1]; 
    }
    
    if ((interface.compare("gui") != 0) && (interface.compare("cli") != 0)) {
        rDebug("wrong argument ('%s')", argv[1]);
        usage(argv[0]); 
        exit(1);
    }
    
    // launch the application
    if (interface.compare("cli") == 0) {
        /* CLI */
        float N = 0.5, R = 0.25;
        if (argc > 2) {
            N = atof(argv[2]);
            if (argc > 3) {
                R = atof(argv[3]);
            }
        }
        rInfo("frame length N = %f seconds", N);
        rInfo("overlapping  R = %f percent", R*100);
        
        rInfo("Launching the CLI interface ...");
        SvmacCli* cli = SvmacCli::getInstance();
        cli->mainLoop(N,R);
        return 0;
    } else {
        /* GUI */
        rInfo("Launching the GUI interface ...");
        Q_INIT_RESOURCE(application);
        QApplication app(argc, argv);
        SvmacGui* gui = new SvmacGui;
        gui->show();
        return app.exec();
    }
};

/// Print the launching parameters
void usage(const char* s) {
//TODO usare opzioni del tipo [-r overlap -n size]
    cout << "Usage: " << s << " [interface] [size] [overlap]" << endl;
    cout << "Arguments" << endl;
    cout << "  interface   select the user interface, values are:" << endl;
    cout << "                gui  " << endl;
    cout << "                cli  [default]" << endl;
    cout << "  size        frame length in seconds (N)" << endl;
    cout << "  overlap     percentage of overlapping (R)" << endl;
    cout << endl;
}
