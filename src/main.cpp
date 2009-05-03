/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
// rlog
#define RLOG_COMPONENT "main"
#include <rlog/rlog.h>
#include <rlog/StdioNode.h>
#include <rlog/RLogChannel.h>
// qt4
#include <QApplication>

#include "gui/svmacsgui.h"

using namespace rlog;

int main(int argc, char *argv[]) {
    // initialize logging    
    RLogInit(argc, argv);
    StdioNode log;
    #ifdef DEBUG_LEVEL
    log.subscribeTo( GetGlobalChannel("debug") );
    log.subscribeTo( GetGlobalChannel("info") );
    #endif
    log.subscribeTo( GetGlobalChannel("warning") );
    log.subscribeTo( GetGlobalChannel("error") );
     
    if (argc > 1) {
        rInfo("Launching the CLI interface ...");
        // TODO: CLI
        rError("TODO");
    } else {
        rInfo("Launching the GUI interface ...");
        Q_INIT_RESOURCE(application);
        QApplication app(argc, argv);
        SvmacGui* gui = new SvmacGui;
        gui->show();
        return app.exec();
    }
};
