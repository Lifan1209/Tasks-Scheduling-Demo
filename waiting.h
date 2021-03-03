#ifndef WAITING_H
#define WAITING_H
#include "methods.h"
//#include "mythread.h"
#include <iostream>
#include <unistd.h>
#include <QObject>
#include <QString>
#include "task.h"
#include "taskpool.h"

class Waiting:public QObject
{
    Q_OBJECT//最好放在头文件中
    Q_PROPERTY(QString waiting READ waiting WRITE setWaiting NOTIFY waitingChanged)

public:
    TaskPool *pool;
    explicit Waiting(QObject *parent=0);
    QString waiting() const {return m_waiting;}
    void setWaiting(QString value);

//public slots://使用Q_PROPERTY之后就不需要槽函数了
    void doWaitingChange();

signals://for c++->qml communication
    //void messageChanged(QString value);
    void waitingChanged();

private:
    int m_counter;
    QString m_waiting;
    //explicit Message(const Message& rhs)=delete;//强制明确调用
    //Message& operator=(const Message& rhs)=delete;
};

#endif // WAITING_H
