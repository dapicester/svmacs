/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "svmaccli.h"

#include "engine/engine.h"
#include "exceptions/exceptions.h"

#define RLOG_COMPONENT "cli"
#include <rlog/rlog.h>

#include <boost/bind.hpp>
#include <cstdlib>
#include <csignal>

NS_SVMACS_BEGIN

SvmacCli::SvmacCli() {
    engine = 0; // FIXME engine init qui
    rInfo("CLI ready");
}

SvmacCli::~SvmacCli() {
    delete engine;
    rInfo("CLI correctly closed");
}

bool SvmacCli::flag = true;

void SvmacCli::start(float length, float overlap) {
    // FIXME: engine.start()
    rDebug("starting CLI main loop");
    
    rInfo("initializing Engine ... ");
    try {
        engine = new Engine(length, overlap);
        engine->start();
    } catch (JackException& e) {
        rError("%s", e.what());
        return;
    }
    
    // trap signals
    rInfo("use CTRL-C to quit");
    signal(SIGTERM, &cleanup);
    signal(SIGINT, &cleanup);
#ifdef SIGQUIT
    signal(SIGQUIT, &cleanup);
#endif
    
    // main loop
    while(flag) {
        sleep(1); // XXX: sure to du this?
    } 
    
    engine->stop();
    rInfo("quitting ... ");
}

void SvmacCli::cleanup(int) {
    rDebug("CTRL-C trapped");
    flag = false;
}

NS_SVMACS_END
