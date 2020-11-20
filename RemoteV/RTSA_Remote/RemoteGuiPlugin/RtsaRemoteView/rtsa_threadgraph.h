#ifndef RTSA_THREADGRAPH_H
#define RTSA_THREADGRAPH_H

#include <QThread>
#include "rtsa_user_variable.h"
#include "rtsa_remote_interface.h"
class RtSa_ThreadGraph : public QThread
{
    Q_OBJECT
public:
    RtSa_ThreadGraph(QObject *parent = 0);
    ~RtSa_ThreadGraph();
public:
    void setGobalVariable(RtSa_User_Variable* userVariable);
    void setInterface(Rtsa_Remote_Interface *RtsaRemoteInterface);
    void SetLinkFlg(bool bFlg);
    qint32 rtsa_thread_state;
private:
    void run();
signals:
    void FinishCount(const qint32 value);

public slots:

private:
    bool bConnectF238;  //是否连接238
    RtSa_User_Variable* globalUserVariable;
    Rtsa_Remote_Interface *RemoteInterfaceObj;
};

#endif // RTSA_THREADGRAPH_H
