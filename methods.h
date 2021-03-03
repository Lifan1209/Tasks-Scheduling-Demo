#ifndef METHODS_H
#define METHODS_H
#include <QString>
#include "task.h"
#include "mcb.h"
#include "freememorylist.h"

class Methods
{
public:
    static int USER_TOTAL_NUM;//内存块数
    static int USER_MEMORY_SIZE;//每块内存大小
    static int SystemTime;//系统时钟
    static Task* mailBox;//消息邮箱/size one buffer
    static int nextId;//下一个被生成的作业的id
    static int on;//线程开关
    static int *UserMemory;//内存池
    static FreeMemoryList* list;//空内存控制块链表
    static int exeInTime;//成功调用的作业数
    static int exefailed;//没来得及调用就过期的作业数
    static int exeMemoryOverbound;//执行过程中因为内存溢出而被迫停止的作业数
    static int generateFailed_FullMemory;//由于没有空内存控制块而无法生成新作业的次数
    static QString showTime(int second);//时间格式化输出
    static QString showNumber(int second);//数字格式化输出
    static QString showSec(int second);//秒数格式化输出

};

#endif // METHODS_H
