#ifndef MCB_H
#define MCB_H


class MCB
{    friend class FreeMemoryList;

    MCB* nextFree;
public:
     int pointer;//SystemMemory段头
     int holder;//持有该内存块的作业id
      int usage;//该内存块使用量
    MCB(int pi);
};

#endif // MCB_H
