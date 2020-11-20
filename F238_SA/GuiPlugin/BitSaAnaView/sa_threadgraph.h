#ifndef THREADGRAPH_H
#define THREADGRAPH_H

#include <QThread>
#include "sa_user_variable.h"
#include "sa_applicationcontrol.h"

class ThreadGraph : public QThread
{
    Q_OBJECT
public:
    explicit ThreadGraph(controlInterface &control,user_variable &m_user_variable,QObject *parent = 0);
    ~ThreadGraph();
    user_variable *globalUserVariable;
    controlInterface *mControl;
    qint32 sa_listenState;

private:
    void run();

signals:
   void FinishCount(const int value); 

public slots:

};

#endif // THREADGRAPH_H
