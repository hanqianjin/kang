#ifndef PM_THREADGRAPH_H
#define PM_THREADGRAPH_H

#include <QThread>
#include "pm_user_variable.h"
#include "pm_interface.h"
class Pm_ThreadGraph : public QThread
{
    Q_OBJECT
public:
    Pm_ThreadGraph(QObject *parent = 0);
    ~Pm_ThreadGraph();
public:
    void setInterface(BitPm_Interface *BitPmInterface);
    void SetContinuousFlg(qint32 nFlg);
    qint32 pm_thread_state;
private:
    void run();
signals:
    void findCommPort(qint32,QString);
public slots:

private:
    qint32 m_nContinuous;  //是否连续采集
    BitPm_Interface *PmInterfaceObj;
};

#endif // PM_THREADGRAPH_H
