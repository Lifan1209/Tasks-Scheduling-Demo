#include "freememorylist.h"
#include "mcb.h"
#include "methods.h"


FreeMemoryList::FreeMemoryList(int total)
{
    MCB* temp=NULL;
    head=NULL;
    length=0;
    for(int i=0;i<total;i++){
        MCB* newBlock=new MCB(i);
        if(!temp)head=newBlock;
        else temp->nextFree=newBlock;
        length++;
        temp=newBlock;
    }
}
MCB *FreeMemoryList::takeOut()
{
    MCB* block=head;
    head=head->nextFree;
    length--;
    return block;
}
void FreeMemoryList::putIn(MCB *newBlock)
{
    MCB* tempHead=head;
    head=newBlock;
    length++;
    newBlock->nextFree=tempHead;
}


