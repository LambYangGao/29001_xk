#ifndef THREADOBJECT_H
#define THREADOBJECT_H

#include <QObject>
#include <QThread>

class ThreadObject : public QObject
{
    Q_OBJECT
public:
    explicit ThreadObject(QObject *parent = nullptr);
    virtual ~ThreadObject(); //这个类会被继承，使用虚析构可以实现多态
    void startThread();
    void stopThread();
signals:

public slots:

private:
    QThread*    m_thread;
};

#endif // THREADOBJECT_H
