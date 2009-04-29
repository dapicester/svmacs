/***************************************************************************
 *   Copyright (C) 2009 by Paolo D'Apice                                   *
 *   dapicester@gmail.com                                                  *
 ***************************************************************************/

#include <QApplication>
#include "svmacsgui.h"

int main(int argc, char *argv[]) {
      Q_INIT_RESOURCE(application);
      QApplication app(argc, argv);
      SvmacGui * dialog = new SvmacGui;
      
      dialog->show();
      return app.exec();
}

