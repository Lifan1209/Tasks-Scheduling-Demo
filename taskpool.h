#ifndef TASKPOOL_H
#define TASKPOOL_H
#include <iostream>
#include "task.h"
#include <QString>

class TaskPool
{
    Task** pool;//从1开始放，head=1，能放99个
    int tail;//实指,当tail==99时池满，不可再放

public:
        //有两个线程可能同时访问作业池：设MyThread为P0，GenerateThread为P1
        bool flag[2]={false,false};
        int turn=-1;
        //在线程内部保证原子操作

    TaskPool(Task*[]);//通过分配内存空间初始化taskpool
    void poolSwap(int,int);//Tool:通过索引交换数组内容
    int getTailIndex(){return this->tail;}//获取当前tail值（保护封装）
    Task *getHead();//获取作业池头作业（索引为1）（保护封装）

    /////作业参数更新
    void refresh();//wait++,priority--
    /////插入场景
    void insert(Task*);//插入合适的位置
    /////删除场景
    Task* deleteHead(); //获取作业池头作业（索引为1），
                        //并将其从池中删除（放到最后并且tail--），
                        //并调整好堆结构
    void clear();//清除池中到期未执行的作业，并调整好堆结构
    /////格式化输出
    QString print();//无脑按顺序对池中作业进行格式化输出

};

#endif // TASKPOOL_H
