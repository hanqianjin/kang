#ifndef VNC_THREADREFRESH_H
#define VNC_THREADREFRESH_H
#include <QThread>

class vnc_threadrefresh: public QThread
{
    Q_OBJECT
public:
    vnc_threadrefresh(QObject *parent = NULL);
    ~vnc_threadrefresh();
private:
    void run();

    qint32 vnc_listenState;
    qint32 pRefreStatus;
    qint32 pRefreData;
    ulong pRefreUsec;
signals:
    void refresh();

public slots:

};

#endif // VNC_THREADREFRESH_H
