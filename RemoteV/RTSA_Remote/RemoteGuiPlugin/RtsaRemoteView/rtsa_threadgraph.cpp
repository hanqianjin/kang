#include "rtsa_threadgraph.h"
#include <QDebug>
#include "rtsa_define.h"

#include <sys/time.h>
#include "rtsa_remote_interface.h"


RtSa_ThreadGraph::RtSa_ThreadGraph(QObject *parent)
    :QThread(parent)
    , rtsa_thread_state(1)
    , bConnectF238(0)
{

}
RtSa_ThreadGraph::~RtSa_ThreadGraph()
{
}
//extern int RTSA_syncHandle;//212
//extern int RTSA_guiHandle;
//extern pthread_mutex_t RTSA_lockobj;

void RtSa_ThreadGraph::SetLinkFlg(bool bFlg)
{
    bConnectF238 = bFlg;
}
void RtSa_ThreadGraph::run()
{
    while(rtsa_thread_state)
    {
        usleep(globalUserVariable->gReadMeterDataSleepTime);
        if(bConnectF238)
        {
            RemoteInterfaceObj->GetCurTraceData();
            emit FinishCount(1);
        }

        //****************Johnson 0724********************
        //#if 1
        ////          memcpy(MainUserVariable.gOriginalMeasureVal,sm_rtsa_sweep_data->_PwrLevel,RTSA_NUM_SWEEP_POINT * 8);
        //            RemoteInterfaceObj->updateTraceData(sm_rtsa_sweep_data->_PwrLevel,RTSA_NUM_SWEEP_POINT);
        //            if(globalUserVariable->gDpxOpenFlag)
        //                RemoteInterfaceObj->updateDpxData(sm_rtsa_sweep_data->DpxData,DPX_WIDTH_SIZE * DPX_HEIGHT_SIZE);
        ////          memcpy(TraceObj.gOriginalTrace,sm_rtsa_sweep_data->_PwrLevel,RTSA_NUM_SWEEP_POINT * 8);
        ////          Tony 1207 data size need to modify when FPGA give size
        ////        memcpy(globalUserVariable->gOriginalDPXdata,sm_rtsa_sweep_data->DpxData,BIT_DPXSIZE * 4);
        //#else
        //          memcpy(globalUserVariable->gDpxData,sm_rtsa_sweep_data->DpxData,sizeof(sm_rtsa_sweep_data->DpxData));
        //#endif
        //          //************************************************

    }
}



void RtSa_ThreadGraph::setGobalVariable(RtSa_User_Variable *userVariable)
{
    globalUserVariable = userVariable;
    return;
}
void RtSa_ThreadGraph::setInterface(Rtsa_Remote_Interface *RtsaRemoteInterface)
{
    RemoteInterfaceObj = RtsaRemoteInterface;
    return;
}
