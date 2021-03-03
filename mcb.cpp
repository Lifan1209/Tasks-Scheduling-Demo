#include "mcb.h"
#include "methods.h"

MCB::MCB(int pi)
{
    pointer=pi*Methods::USER_MEMORY_SIZE;
    holder=-1;
    usage=0;
    nextFree=NULL;

}
