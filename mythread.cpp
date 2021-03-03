#include "mythread.h"
#include <QThread>
#include <iostream>
#include "message.h"
#include "executing.h"
#include "systemcontrol.h"
#include "waiting.h"
#include "task.h"
#include "taskpool.h"
#include "methods.h"
#include <unistd.h>

MyThread::MyThread(SystemControl* my_handler, Message* my_message,Waiting* my_waiting,Executing* my_executing,TaskPool* my_pool){
        handler=my_handler;
        message=my_message;//在Message的父类QObject中将赋值运算符给delete掉了，所以只允许通过指针传递Message类对象
        wait=my_waiting;
        exe=my_executing;
        pool=my_pool;
    }
void MyThread:: run(){
        while(Methods::on){
        exe->pool=this->pool;
        wait->pool=this->pool;

        this->pool->flag[0]=true;this->pool->turn=1;
        while(this->pool->flag[1]&&this->pool->turn==1);
        if(this->pool->getTailIndex()>0){
            this->pool->refresh();
            this->pool->clear();
        }
        //此时作业池中应该是干净而且有序的
        Methods::SystemTime++;//正在执行的作业失效
        std::cout<<Methods::SystemTime<<std::endl;   ///////////////////////输出时间/////////////////////////
        this->pool->flag[0]=false;

        sleep(1);//大多数情况下task在此生成

        message->doMessageChange();

        this->pool->flag[0]=true;this->pool->turn=1;
        while(this->pool->flag[1]&&this->pool->turn==1);
        exe->doExecutingChange();
        wait->doWaitingChange();
        this->pool->flag[0]=false;
}
        delete [] Methods::UserMemory;
        std::cout<<"Statistic:"<<std::endl;
        std::cout<<"Successfully generated tasks number: "<<Methods::nextId-1<<std::endl;
        std::cout<<"Failed to generate tasks because of full Memory: "<<Methods::generateFailed_FullMemory<<std::endl;
        std::cout<<"Successfully execute tasks number: "<<Methods::exeInTime<<std::endl;
        std::cout<<"Execution forced to stop because of memory overbound: "<<Methods::exeMemoryOverbound<<std::endl;
        std::cout<<"Failed to execute tasks number: "<<Methods::exefailed<<std::endl;


    }



