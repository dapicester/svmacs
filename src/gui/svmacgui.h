/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/
#ifndef SVMACS_GUI_H
#define SVMACS_GUI_H

#include "ui_svmacgui.h"
#include "../jack/jackclient.h"
using jack::JackClient;

class SvmacGui : public QWidget, private Ui::SvmacQt {
    Q_OBJECT
    JackClient* client;

protected:
    void enableButton(QPushButton* button);
    void disableButton(QPushButton* button);

public:
    SvmacGui(QWidget *parent = 0);

public slots:
    void startJackClient();
    void stopJackClient();
    void quitApp();    
    void about();

};

#endif //SVMACS_GUI_H
