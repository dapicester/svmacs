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

void initLog(int& argc, char* argv[]) {
     RLogInit(argc, argv);
     StdioNode stdLog;
     stdLog.subscribeTo( RLOG_CHANNEL("debug") );
     stdLog.subscribeTo( RLOG_CHANNEL("info") );
     stdLog.subscribeTo( GetGlobalChannel("warning") );
     stdLog.subscribeTo (GetGlobalChannel("error"));
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        rInfo("Launching the CLI interface ...");
        // TODO: CLI
    } else {
        rInfo("Launching the GUI interface ...");
        Q_INIT_RESOURCE(application);
        QApplication app(argc, argv);
        SvmacGui * dialog = new SvmacGui;
        
        dialog->show();
        return app.exec();
    }
};
