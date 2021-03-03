#ifndef MESSAGE_H
#define MESSAGE_H
#include <QObject>
#include <QString>
#include "methods.h"
//#include "mythread.h"
#include <iostream>
#include <unistd.h>


class Message:public QObject
{
    Q_OBJECT//最好放在头文件中
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)

public:
    explicit Message(QObject *parent=0);
    QString message() const {return m_message;}
    void setMessage(QString value);

//public slots://使用Q_PROPERTY之后就不需要槽函数了
    void doMessageChange();

signals://for c++->qml communication
    //void messageChanged(QString value);
    void messageChanged();

private:
    int m_counter;
    QString m_message;
    //explicit Message(const Message& rhs)=delete;//强制明确调用
    //Message& operator=(const Message& rhs)=delete;
};

#endif // MESSAGE_H
