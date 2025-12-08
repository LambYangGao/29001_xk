#include "threadobject.h"

ThreadObject::ThreadObject(QObject *parent)
    : QObject(parent)
    , m_thread(new QThread())
{

}

ThreadObject::~ThreadObject()
{
    stopThread();
    delete m_thread;
    m_thread = NULL;
}


void ThreadObject::startThread()
{
    this->moveToThread(m_thread);
    m_thread->start();
}

void ThreadObject::stopThread()
{
    m_thread->quit();
    m_thread->wait();
}
