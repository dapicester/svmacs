/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVMACS_GUI_H
#define SVMACS_GUI_H
#include "ui_svmacsgui.h"
#include "../jack/jackclient.h"

class SvmacGui : public QWidget, private Ui::svmacsgui {
    Q_OBJECT
    JackClient* client;
public:
    SvmacGui(QWidget *parent = 0);

public slots:
    void startJackClient();
    void doSomething();
    void quit();
};

#endif //SVMACS_GUI_H
