#include "message.h"
#include <QObject>
#include <QString>
#include "methods.h"
//#include "mythread.h"
#include <iostream>
#include <unistd.h>


using std::cout;
using std::endl;



Message:: Message(QObject *parent):QObject(parent),//继承自QObject类
    m_counter(0),
    m_message("00:00")
{
}


void Message::doMessageChange()
{
    setMessage("%1");
}
void Message::setMessage(QString value){
    m_message=value.arg(Methods::showTime(Methods::SystemTime));
    emit messageChanged();
}


