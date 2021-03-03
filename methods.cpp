#include "methods.h"
#include <QString>
#include "task.h"
#include "mcb.h"
#include "freememorylist.h"

int Methods::SystemTime=0;
Task* Methods::mailBox=NULL;
int Methods::nextId=1;
int Methods::on=0;
int Methods::USER_TOTAL_NUM=8;
int Methods::USER_MEMORY_SIZE=100;
int Methods::exeInTime=0;
int Methods::exefailed=0;
int Methods::exeMemoryOverbound=0;
int Methods::generateFailed_FullMemory=0;

FreeMemoryList * Methods::list=new FreeMemoryList(USER_TOTAL_NUM);
int * Methods::UserMemory=new int[USER_MEMORY_SIZE*USER_TOTAL_NUM];

 QString Methods::showTime(int second){
     int min=second/60;
     int sec=second%60;
     QString stMin=min<10?QString::number(0).append(QString::number(min)):QString::number(min);
     QString stSec=sec<10?QString::number(0).append(QString::number(sec)):QString::number(sec);
     QString time=stMin.append(":").append(stSec);
     return time;
 }

 QString Methods::showNumber(int second)
 {
     QString num=QString::number(second);
     if(second<10)num=QString::number(0).append(num);
     return num;
 }

 QString Methods::showSec(int second)
 {
     QString sec=QString::number(second);
     if(second<10)sec=sec.append("s ");
     else sec=sec.append("s");
     return sec;
 }


