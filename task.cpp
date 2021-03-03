#include "task.h"
#include "freememorylist.h"
#include <QString>
#include "mcb.h"


Task::Task(int tid, int priority, int start,MCB* memory)
{
    this->tid=tid;
    this->priority=priority;
    this->start=start;
    this->end=this->start+priority;
    this->wait=0;
    this->executeTime=0;
    this->memory=memory;
}

Task::~Task()
{

}
