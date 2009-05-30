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
        interface = "gui";
    } else {
        interface = argv[1]; 
    }
    
    if ((interface.compare("gui") != 0) && (interface.compare("cli") != 0)) {
        rDebug("wrong argument ('%s')", argv[1]);
        usage(argv[0]); 
        exit(1);
    }
    
    if (interface.compare("cli") == 0) {
        float N = 1.0, R = 0.0;
        if (argc > 2) {
            N = atof(argv[2]);
            if (argc > 3) {
                R = atof(argv[3]);
            }
        }
        rInfo("N = %f", N);
        rInfo("R = %f", R);
        
        rInfo("Launching the CLI interface ...");
        SvmacCli* cli = SvmacCli::getInstance();
        cli->mainLoop(N,R);
        return 0;
    } else {
        rInfo("Launching the GUI interface ...");
        Q_INIT_RESOURCE(application);
        QApplication app(argc, argv);
        SvmacGui* gui = new SvmacGui;
        gui->show();
        return app.exec();
    }
};

void usage(const char* s) {
//TODO usare opzioni del tipo [-r overlap -n size]
    cout << "Usage: " << s << " [interface] [size] [overlap]" << endl;
    cout << "Arguments" << endl;
    cout << "  interface   select the user interface, values are:" << endl;
    cout << "                gui  [default]" << endl;
    cout << "                cli  command-line" << endl;
    cout << "  size        frame length in seconds (N)" << endl;
    cout << "  overlap     percentage of overlapping (R)" << endl;
    cout << endl;
}
