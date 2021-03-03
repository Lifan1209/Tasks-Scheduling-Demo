#include "executing.h"
#include <QObject>
#include <QString>
#include "task.h"
#include "taskpool.h"
#include "methods.h"
#include <iostream>
#include <unistd.h>


using std::cout;
using std::endl;

Executing:: Executing(QObject *parent):QObject(parent),//继承自QObject类
    m_counter(0),
    m_executing("nop   00:00   00:00      undef     ")
{
}

void Executing::doExecutingChange()
{
    //进程号      进入时间      调用时间       作业时长     执行进度
    setExecuting("%1   %2   %3   %4   %5");

}

void Executing::setExecuting(QString value){
    if(Methods::mailBox){//不为空,正在忙
        int id=executingTask->tid;
        int start=executingTask->start;
        int executeTime=executingTask->executeTime;
        int longth=executingTask->end-executingTask->start;
        double persentage=((double)(Methods::SystemTime-executingTask->executeTime))/((double)(executingTask->end-executingTask->start));
        int intp=(int)(persentage*100);
        m_executing=value.arg(Methods::showNumber(id)).arg(Methods::showTime(start)).arg(Methods::showTime(executeTime)).arg(Methods::showSec(longth)).arg(QString::number(intp).append("%"));//可以设置多个参数
        std::cout<<"exe: continue on task "<<id<<"("<<intp<<"%)"<<std::endl;///////////////////////执行作业情况/////////////////////////
        emit executingChanged();
        return;
    }
    if(this->pool->getTailIndex()<=0){
        std::cout<<"exe: nop"<<std::endl;   ///////////////////////执行作业情况/////////////////////////
        m_executing=value.arg("nop").arg(Methods::showTime(0)).arg(Methods::showTime(0)).arg("undef").arg("null");//可以设置多个参数
    }else{
        Task* newTask=this->pool->deleteHead();

        //把newTask传给执行线程：把newTask赋给Methods::mailBox
        Methods::mailBox=newTask;
        executingTask=newTask;
        newTask->executeTime=Methods::SystemTime;

        int id=newTask->tid;
        int start=newTask->start;
        int longth=executingTask->end-executingTask->start;
        int executeTime=newTask->executeTime;
        m_executing=value.arg(Methods::showNumber(id)).arg(Methods::showTime(start)).arg(Methods::showTime(executeTime)).arg(Methods::showSec(longth)).arg("00%");//可以设置多个参数
        std::cout<<"executing task:"<<std::endl;
        std::cout<<m_executing.toStdString()<<std::endl;
    }
    emit executingChanged();
}


