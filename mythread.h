#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <iostream>
#include "message.h"
#include "executing.h"
#include "waiting.h"
#include "task.h"
#include "taskpool.h"
#include "systemcontrol.h"
#include "methods.h"
#include <unistd.h>

class MyThread:public QThread
{
    //负责刷新页面的线程
    Q_OBJECT
    TaskPool* pool;
    SystemControl *handler;
    Message *message;
    Waiting *wait;
    Executing *exe;
public:
    MyThread(SystemControl*, Message* ,Waiting* ,Executing*,TaskPool* );
    void run();
};
#endif // MYTHREAD_H


