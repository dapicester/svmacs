/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#include "cli/svmaccli.h"
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
    log.subscribeTo( GetGlobalChannel("info") );
    log.subscribeTo( GetGlobalChannel("warning") );
#endif 
    log.subscribeTo( GetGlobalChannel("error") );
     
    // check arguments 
    if (argc > 2) {
        rDebug("too many arguments (%i)", argc);
        usage(argv[0]); 
        exit(1);
    }   
     
    string argument; 
    if (argc == 1) {
        rDebug("no arguments");
        argument = "gui";
    } else {
        argument = argv[1]; 
    }
        
    if ((argument.compare("gui") != 0) && (argument.compare("cli") != 0)) {
        rDebug("wrong argument ('%s')", argv[1]);
        usage(argv[0]); 
        exit(1);
    }
    
    if (argument.compare("cli") == 0) {
        rInfo("Launching the CLI interface ...");
        SvmacCli* cli = SvmacCli::getInstance();
        cli->mainLoop();
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
    cout << "Usage: " << s << " [interface]" << endl;
    cout << "Arguments" << endl;
    cout << "  interface   select the user interface, values are:" << endl;
    cout << "                gui  [default]" << endl;
    cout << "                cli  command-line" << endl << endl;
}
