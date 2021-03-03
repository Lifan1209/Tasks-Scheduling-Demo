#ifndef SYSTEMCONTROL_H
#define SYSTEMCONTROL_H
#include <QObject>

class SystemControl: public QObject
{
    Q_OBJECT
public:
    explicit SystemControl(QObject *parent=0);
public slots:
    void doClose();
private:
    explicit SystemControl(const SystemControl& rhs)=delete;
    SystemControl& operator=(const SystemControl& rhs)=delete;
};

#endif // SYSTEMCONTROL_H
