/***************************************************************************
 *   Copyright (C) 2009-2011 by Paolo D'Apice                              *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include "config.h"
#include "svmaccli.h"

#include "engine/engine.h"
#include "exceptions/exceptions.h"

#define RLOG_COMPONENT "cli"
#include <rlog/rlog.h>

#include <boost/bind.hpp>
#include <cstdlib>
#include <csignal>

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
        rError(e.what());
        return;
    }
    
    // trap signals
    rInfo("use CTRL-C to quit");
    signal(SIGTERM, &cleanup);
    signal(SIGINT, &cleanup);
    //signal(SIGABRT, &cleanup);
    //signal(SIGTERM, boost::bind<void>(&SvmacCli::cleanup, this, _1, _2));
    //signal(SIGINT, boost::bind<void>(&SvmacCli::cleanup, this, _1, _2));
    
    // main loop
    while(flag) {
        sleep(1); 
    } 
    
    engine->stop();
    rInfo("quitting ... ");
}

void SvmacCli::cleanup(int) {
    rDebug("CTRL-C trapped");
    flag = false;
}
