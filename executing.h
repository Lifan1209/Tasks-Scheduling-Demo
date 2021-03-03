#ifndef EXECUTING_H
#define EXECUTING_H
#include <QObject>
#include <QString>
#include "task.h"
#include "taskpool.h"
#include "methods.h"
#include <iostream>
#include <unistd.h>

class Executing:public QObject
{
    Q_OBJECT//最好放在头文件中
    Q_PROPERTY(QString executing READ executing WRITE setExecuting NOTIFY executingChanged)

public:
    TaskPool *pool;
    explicit Executing(QObject *parent=0);
    QString executing() const {return m_executing;}
    void setExecuting(QString value);

//public slots://使用Q_PROPERTY之后就不需要槽函数了
    void doExecutingChange();

signals://for c++->qml communication
    //void messageChanged(QString value);
    void executingChanged();

private:
    int m_counter;
    QString m_executing;
    Task* executingTask;
    //explicit Message(const Message& rhs)=delete;//强制明确调用
    //Message& operator=(const Message& rhs)=delete;
};

#endif // MESSAGE_H


