/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVMACS_CLI_H
#define SVMACS_CLI_H
#include "../jack/jackclient.h"

class SvmacCli {
    JackClient* client;

public:
    mainLoop();
};

#endif // SVMACS_CLI_H
