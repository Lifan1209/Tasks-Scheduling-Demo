#include <QGuiApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "message.h"
#include "waiting.h"
#include "systemcontrol.h"
#include "executing.h"
#include "mythread.h"
#include "task.h"
#include "taskpool.h"
#include "mcb.h"
#include "freememorylist.h"
#include "methods.h"
#include <QThread>

//static int exeInTime;
//static int exefailed;
//static int exeMemoryOverbound;
//static int generateFailed_FullMemory;

void generate(TaskPool* pool){
    if(Methods::on==0)return;
    srand((unsigned)time(NULL));
    while(Methods::on&&pool->getTailIndex()<100){
            pool->flag[1]=true;pool->turn=0;
            while(pool->flag[0]&&pool->turn==0);
            if(Methods::list->length!=0){
                Methods::list->flag[1]=true;Methods::list->turn=0;
                while(Methods::list->flag[0]&&Methods::list->turn==0);
                MCB* memory=Methods::list->takeOut();
                Methods::list->flag[1]=false;
                memory->holder=Methods::nextId;
                Task* task=new Task(Methods::nextId++,rand()%10+1,Methods::SystemTime,memory);
                pool->insert(task);
            }else{
                Methods::generateFailed_FullMemory++;
                std::cout<<"Generate task failed: No Memory Exception"<<std::endl;//回头学一下异常处理类
            }
            pool->flag[1]=false;
            sleep(rand()%3);
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }
    std::cout<<"generate thread off."<<std::endl;
}



void execute(){
    if(Methods::on==0)return;
    while(Methods::on){
        while (!Methods::mailBox) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        Methods::exeInTime++;
        while(Methods::SystemTime-Methods::mailBox->executeTime!=Methods::mailBox->end-Methods::mailBox->start){//已经执行了的时间！=应该执行的时间
            if(Methods::mailBox->memory->usage<Methods::USER_MEMORY_SIZE){
                Methods::UserMemory[Methods::mailBox->memory->pointer+Methods::mailBox->memory->usage++]=1;
            }
            else{
                Methods::exeMemoryOverbound++;
                std::cout<<"task"<<Methods::mailBox->tid<<" is forced to stop: memory used out"<<std::endl;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        Methods::list->flag[0]=true;Methods::list->turn=1;
        while(Methods::list->flag[1]&&Methods::list->turn==1);
        Methods::list->putIn(Methods::mailBox->memory);
        Methods::list->flag[0]=false;
        std::cout<<"Memory usage of task "<<Methods::mailBox->tid<<": "<<Methods::mailBox->memory->usage<<"/"<<Methods::USER_MEMORY_SIZE<<std::endl;
        Methods::mailBox=NULL;
    }
    std::cout<<"execute thread off."<<std::endl;
}

/*需要初始化：
Systemtime
mailBox
GenerateThread
ExecuteThread
TaskPool
*/

int main(int argc, char *argv[])
{
    Methods::on=1;

    QGuiApplication app(argc,argv);
    QQmlApplicationEngine engine;
    Message my_msg;
    Executing my_exe;
    Waiting my_wait;
    SystemControl my_handler;
    auto root_context=engine.rootContext();
    //ask the engine to give a pointer to the actual qml context
    root_context->setContextProperty("messageClass",&my_msg);
    root_context->setContextProperty("executingClass",&my_exe);
    root_context->setContextProperty("waitingClass",&my_wait);
    root_context->setContextProperty("systemcontrolClass",&my_handler);
    //use the context to tell the qml about my c++ class
    //two parameters:
    //1.the name of which I want to refer to my class when I'm in qml
    //2.the pointer to my class instance
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    Task* pool[100];
    for(int i=0;i<100;i++)pool[i]=NULL;
    TaskPool taskPool(pool);

    std::thread generateTask(generate,&taskPool);
    std::thread executeTask(execute);

    MyThread myThread(&my_handler,&my_msg,&my_wait,&my_exe,&taskPool);
    myThread.start();//到此都ok

    int exit=app.exec();//app.exec()会阻塞线程

    return exit;
    //报错也不能用joint!会阻塞线程的！！！
}
