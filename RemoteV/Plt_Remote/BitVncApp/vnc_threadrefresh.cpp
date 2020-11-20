#include "vnc_threadrefresh.h"
#include "bitvnchandle.h"

//extern pthread_mutex_t Vnc_CommuLock;
extern pthread_mutex_t SA_lockobj;
vnc_threadrefresh::vnc_threadrefresh(QObject *parent):
    QThread(parent),
    vnc_listenState(1),
    pRefreStatus(0),
    pRefreUsec(100000)
{

}

vnc_threadrefresh::~vnc_threadrefresh()
{

}
//SGYABGSJIIIU
void vnc_threadrefresh::run()
{
    pRefreStatus = 1;
    pRefreData = 1;
    while(vnc_listenState)
    {
        QThread::usleep(pRefreUsec);
        //Triggering rendering events
        if(pRefreStatus)
        {
            if(pRefreData)//更新原始数据
            {
//                pthread_mutex_lock(&SA_lockobj);
                //copy data to cache
                //qreal a[801];
                //memcpy(a,BitVncHandle::GetVncAppHandle()->pSaAna->pcontrolInterface->globalUserVariable->gOriginalMeasureVal,sizeof(qreal)*801);

                qreal* data = BitVncHandle::GetVncInternetHandle()->getOriData();
                if(!data || !(*data))
                {
                    qDebug()<<"111";
                }else
                {

                    memcpy(remoteinterface::getsaremotehandle()->pcontrolInterface->globalUserVariable->gOriginalMeasureVal,data,NUM_SWEEP_POINT * 8);
                    //memcpy(BitVncHandle::GetVncAppHandle()->pSaAna->pcontrolInterface->globalUserVariable->gTraceMeasureVal,data + NUM_SWEEP_POINT * 8,NUM_SWEEP_POINT * 8 * 6);
                }

//                pthread_mutex_unlock(&SA_lockobj);
            }

            //send signal for refresh UI
            //BitVncHandle::GetVncAppHandle()->pSaAna->graphRefreshFunc();
            emit refresh();
        }
    }
}
