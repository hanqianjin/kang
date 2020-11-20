#ifndef RTSA_THREADGRAPH_H
#define RTSA_THREADGRAPH_H

#include <QThread>
#include "rtsa_user_variable.h"
#include "rtsa_interface.h"
class RtSa_ThreadGraph : public QThread
{
    Q_OBJECT
public:
    RtSa_ThreadGraph(QObject *parent = 0);
    ~RtSa_ThreadGraph();
public:
    void setGobalVariable(RtSa_User_Variable* userVariable);
    void setInterface(RtSa_Interface* interface);
    qint32 rtsa_thread_state;
private:
    void run();
signals:
   void FinishCount(const qint32 value);

public slots:

private:
   RtSa_User_Variable* globalUserVariable;
   RtSa_Interface* InterfaceObj;
};

#endif // RTSA_THREADGRAPH_H
