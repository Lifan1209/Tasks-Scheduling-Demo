#include "systemcontrol.h"
#include "methods.h"

SystemControl::SystemControl(QObject *parent):
    QObject(parent)
{
}

void SystemControl::doClose()
{
    Methods::on=0;
}
