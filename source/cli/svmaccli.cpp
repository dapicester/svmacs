/*
 * Copyright (C) 2009-2012  Paolo D'Apice <paolo.dapice@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

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

void
SvmacCli::start(const float length, const float overlap,
        const std::string& dmodel, const std::string& cmodel) {
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

void
SvmacCli::cleanup(int sig) {
    rDebug("Signal %d trapped", sig);
    flag = false;
}

NS_SVMACS_END
