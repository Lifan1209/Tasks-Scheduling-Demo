#ifndef TASK_H
#define TASK_H
#include <QString>
#include "mcb.h"

class Task
{
public:
    Task(int tid,int priority,int start,MCB* memory);
    int tid;
    int priority;
    int start;
    int end;
    int wait;
    int executeTime;
    MCB* memory;
    ~Task();
};

#endif // TASK_H
