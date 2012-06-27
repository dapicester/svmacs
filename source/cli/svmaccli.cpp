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
    rInfo("CLI ready");
}

SvmacCli::~SvmacCli() {
    rInfo("CLI correctly closed");
}

bool SvmacCli::flag = true;

void SvmacCli::start(float length, float overlap,
        const std::string& dmodel, const std::string& cmodel) {
    // FIXME: engine.start()
    rDebug("starting CLI main loop");

    rInfo("initializing Engine ... ");
    try {
        engine.reset(new Engine(length, overlap, dmodel, cmodel));
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
        sleep(1); // XXX: sure to do this?
    }

    engine->stop();
    rInfo("quitting ... ");
}

void SvmacCli::cleanup(int) {
    rDebug("CTRL-C trapped");
    flag = false;
}

NS_SVMACS_END
