#include "taskpool.h"
#include "methods.h"
#include <iostream>
#include "task.h"
#include <QString>

TaskPool::TaskPool(Task* taskPool[])
{
    this->pool=taskPool;
    this->tail=0;
}

void TaskPool:: poolSwap(int ia,int ib){//通过索引交换数组内容
    Task* temp=pool[ia];
    pool[ia]=pool[ib];
    pool[ib]=temp;
}

void TaskPool::insert(Task* newTask)
{
    //std::cout<<"before insert: tail="<<tail<<std::endl;
    pool[++tail]=newTask;
    int cur=tail;
    int pre=tail/2;
    while(pre!=0&&newTask->priority<pool[pre]->priority){//愚蠢的错误+1
        poolSwap(pre,cur);
        cur=pre;
        pre=pre/2;
    }
    //std::cout<<"before insert: tail="<<tail<<std::endl;

}

Task *TaskPool::deleteHead()
{
    std::cout<<"before get newly exe task:(tail="<<tail<<")";
    for(int i=1;i<=tail;i++)std::cout<<pool[i]->tid<<"/"<<pool[i]->priority<<" ";
    std::cout<<std::endl;

    Task* head=pool[1];
    if(tail<1)return NULL;//愚蠢的错误+1，不能return head。
    poolSwap(1,tail);
    tail--;//不知道是不是tail--放到了函数参数中的问题 不是……
    int cur=1;//算法有问题！！！！！
    while(cur*2<=tail){
        if(cur*2+1<=tail){
            if(pool[cur]->priority>pool[cur*2]->priority||pool[cur]->priority>pool[cur*2+1]->priority){
                if(pool[cur*2]->priority<pool[cur*2+1]->priority){
                    poolSwap(cur,cur*2);
                    cur=cur*2;
                }else{
                    poolSwap(cur,cur*2+1);
                    cur=cur*2+1;
                }
            }else break;
        }else if(pool[cur]->priority>pool[cur*2]->priority){
            poolSwap(cur,cur*2);//多了一个+1！！！！！愚蠢的错误*n
            cur=cur*2;
        }else break;
    }
    std::cout<<"after get newly execute task:(tail="<<tail<<")";
    for(int i=1;i<=tail;i++)std::cout<<pool[i]->tid<<"/"<<pool[i]->priority<<" ";
    std::cout<<std::endl;

    return head;

}

Task *TaskPool::getHead()
{

    return pool[1];
}



QString TaskPool::print()
{
        //进程号    进入时间    离开时间    等待时间    当前优先级
    QString st="";
    for(int i=1;i<=tail;i++){
        Task *task=pool[i];
        st.append(Methods::showNumber(task->tid))
                .append("    ").append(Methods::showTime(task->start))
                .append("    ").append(Methods::showTime(task->end))
                .append("    ").append(Methods::showTime(task->wait))
                .append("    ").append(QString::number(task->priority)).append("\n");
    }
    return st;
}

void TaskPool::refresh()
{
    for(int i=1;i<=tail;i++){
        pool[i]->priority-=1;
        pool[i]->wait+=1;
    }

}

void TaskPool::clear()
{
    std::cout<<"before clear:(tail="<<tail<<")";
    for(int i=1;i<=tail;i++)std::cout<<pool[i]->tid<<"/"<<pool[i]->priority<<" ";
    std::cout<<std::endl;
    while(tail>=1){
        int cur=1;
        while(cur*2<=tail){
            if(cur*2+1<=tail){
                if(pool[cur]->priority>pool[cur*2]->priority||pool[cur]->priority>pool[cur*2+1]->priority){
                    if(pool[cur*2]->priority<pool[cur*2+1]->priority){
                        poolSwap(cur,cur*2);
                        cur=cur*2;
                    }else{
                        poolSwap(cur,cur*2+1);
                        cur=cur*2+1;
                    }
                }else break;
            }else if(cur*2<=tail&&pool[cur]->priority>pool[cur*2]->priority){
                poolSwap(cur,cur*2);//我怎么没有脑子呢？前面改过来就不知道后面一模一样的地方也改改？
                cur=cur*2;
            }else break;
        }
        if(pool[1]->priority<=0){
            Methods::exefailed++;
            Methods::list->putIn(pool[1]->memory);
            std::cout<<"expire task"<<pool[1]->tid<<std::endl;
            poolSwap(1,tail);
            tail--;
        }
        else break;
    }
    std::cout<<"after clear:(tail="<<tail<<")";
    for(int i=1;i<=tail;i++)std::cout<<pool[i]->tid<<"/"<<pool[i]->priority<<" ";
    std::cout<<std::endl;
}



