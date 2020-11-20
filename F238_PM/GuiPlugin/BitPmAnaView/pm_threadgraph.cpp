#include "pm_threadgraph.h"
#include <QDebug>
#include "pm_define.h"

#include <sys/time.h>
#include "pm_interface.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <errno.h>
#include <fcntl.h>

#include <QTimer>
#include <QEventLoop>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

static int init_hotplug_sock(void)
{
    struct sockaddr_nl snl;
    const int buffersize = 16 * 1024 * 1024;
    int retval;
    memset(&snl, 0x00, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
    snl.nl_groups = 1;
    int hotplug_sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if(hotplug_sock == -1)
    {
        qDebug("Error getting socket;%s\n", strerror(errno));
        return -1;
    }

    /*set receive buffersize*/
    setsockopt(hotplug_sock, SOL_SOCKET, SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));


//    注意这里最关键的就是
//    int flags=fcntl(hotplug_sock, F_GETFL,0);
//    fcntl(hotplug_sock, F_SETFL, flags | O_NONBLOCK);

    retval = bind(hotplug_sock, (struct sockaddr*)&snl, sizeof(struct sockaddr_nl) );
    if(retval < 0)
    {
        qDebug("bind failed: %s", strerror(errno));
        close(hotplug_sock);
        hotplug_sock = -1;
        return -1;
    }
    return hotplug_sock;

}
Pm_ThreadGraph::Pm_ThreadGraph(QObject *parent)
    :QThread(parent)
    , pm_thread_state(1)
    , m_nContinuous(0)
{

}
Pm_ThreadGraph::~Pm_ThreadGraph()
{
}

void Pm_ThreadGraph::SetContinuousFlg(qint32 nFlg)
{
    m_nContinuous = nFlg;
}
void Pm_ThreadGraph::run()
{
    int hotplug_sock = init_hotplug_sock();
    static int n = 0;
//    while(pm_thread_state)
     while(1)
   {
//        usleep(PmInterfaceObj->getGlobalUserVariable()->gReadMeterDataSleepTime);
//        //        if(PM_CONT == m_nContinuous)
//        //        {
//        //            PmInterfaceObj->cmd_GetSensorPower(PM_CONT);
//        //        }

        char buf[1024] = {0};   //UEVENT_BUFFER_SIZE*2
        //   recv(hotplug_sock, &buf, sizeof(buf), 0);
        //   这个函数，接收消息存至buf里。
        //但默认的hotplug_sock是阻塞的，也就是当执行到recv时，程序就会停在这里，直到再次接收到内核新的消息，程序才会往下执行。为此，程序必须改动，一种思路是开一个线程，专门运行recv，停在那也无所谓；另外一种思路是将这个sock改成非阻塞的，改动部分见.h文件里画红线部分！
        recv(hotplug_sock, &buf, sizeof(buf), 0); //use a timer to query socket from core -netlink
        QString result=buf;

        QString strPort;
        if(0< result.contains("tty/ttyUSB") ||0<result.contains("tty/ttyACM"))
        {
            int nDext = result.lastIndexOf("/");
            strPort = result.right(result.length()-nDext -1);
            if(result.contains("add"))
            {
                qDebug()<<result;
                QEventLoop loop;
                QTimer::singleShot(3000, &loop, SLOT(quit()));
                loop.exec();
                emit findCommPort(1,strPort);
            }
            else if(result.contains("remove"))
            {
                qDebug()<<result;

                QEventLoop loop;
                QTimer::singleShot(3000, &loop, SLOT(quit()));
                loop.exec();
                emit findCommPort(0,strPort);
            }
        }
     }
}

void Pm_ThreadGraph::setInterface(BitPm_Interface *BitPmInterface)
{
    PmInterfaceObj = BitPmInterface;
    return;
}
