#include <QtGui>
#include "svmacsgui.h"

SvmacGui::SvmacGui(QWidget *parent) {
   setupUi(this);
   
   connect( startButton, SIGNAL( clicked() ), this, SLOT( startJackClient() ) );
   connect( stopButton, SIGNAL( clicked() ), this, SLOT( doSomething() ) );
   connect( quitButton, SIGNAL( clicked() ), this, SLOT( quit() ) );
}

void SvmacGui::doSomething() {
   textEdit->append("did something");
}

void SvmacGui::quit() {
   textEdit->append("wanna quit");
}

void SvmacGui::startJackClient() {
    client = JackClient::getInstance();
}
