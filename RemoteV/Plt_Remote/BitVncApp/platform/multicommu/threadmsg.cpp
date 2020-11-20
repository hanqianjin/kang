#include "threadmsg.h"

#include "scpiport.h"

#include <QDebug>
extern ScpiPort_common   *g_pPortCommon;
extern int g_msgid_recv;


ThreadMsg::ThreadMsg(QObject *parent) :
    QThread(parent)
{
}

void ThreadMsg::run()
{
//    while(1)
//    {
//        if (::msgrcv(g_msgid_recv, (void *)&m_recvMsg, sizeof(process_msg), 0, 0) != -1)
//        {
//            switch (m_recvMsg.msg_type)
//            {
//            case MSG_CONFIG_SCPI_UART:
//                //emit sigRestartUart();
//                break;
//            case MSG_CONFIG_SCPI_USB:
//                emit sigRestartUSB();
//                break;
//            case MSG_CONFIG_SCPI_GPIB:
//                //emit sigRestartGPIB();
//                break;
//            default:
//                break;
//            }

//            if(g_pPortCommon)
//            {
//                emit g_pPortCommon->sigLostConn();
//            }
//        }
//    }
}
