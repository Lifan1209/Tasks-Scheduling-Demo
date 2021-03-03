#ifndef FREEMEMORYLIST_H
#define FREEMEMORYLIST_H
#include "mcb.h"

class FreeMemoryList
{
    MCB* head;
public:
    bool flag[2]={false,false};
    int turn=-1;
    //在线程内部保证原子操作

    int length;
    FreeMemoryList(int);
    MCB *takeOut();
    void putIn(MCB *);
};

#endif // FREEMEMORYLIST_H
