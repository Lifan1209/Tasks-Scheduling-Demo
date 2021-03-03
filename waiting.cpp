#include "waiting.h"
#include "methods.h"
//#include "mythread.h"
#include <iostream>
#include <unistd.h>
#include <QObject>
#include <QString>
#include "task.h"
#include "taskpool.h"


using std::cout;
using std::endl;

Waiting:: Waiting(QObject *parent):QObject(parent),//继承自QObject类
    m_counter(0),
    m_waiting("              Welcome!")
{

}


void Waiting::doWaitingChange(){
    QString value=this->pool->print();//print()内部处理空数组
    setWaiting(value);
}
void Waiting::setWaiting(QString value){
    m_waiting=value;
    std::cout<<"waitingList:"<<std::endl;
    std::cout<<value.toStdString()<<std::endl;
    std::cout<<"--------------------------------------------------------------------------"<<endl;
    emit waitingChanged();
}


