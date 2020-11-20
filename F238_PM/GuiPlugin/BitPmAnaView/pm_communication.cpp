#include "Pm_Communication.h"
#include<qdebug.h>
#include <fcntl.h>
#include "data_conversion.h"

Pm_Communication::Pm_Communication(QObject *parent,Pm_User_Variable* userVariable)
    : QObject(parent)
    , mUserVariable(userVariable)
{

    m_serialportPm = new QSerialPortEx();
    connect(m_serialportPm,SIGNAL(ReadComm(QByteArray)),this,SLOT(RecvCommCmd(QByteArray)));

    m_bDataSplicingFlg = false;
}

Pm_Communication::~Pm_Communication()
{
    if(m_serialportPm != NULL)
        delete m_serialportPm;
}

void Pm_Communication::openPowerPort(QString strPort)
{
    if(POWER_SENSOR_V90 == mUserVariable->m_nPowerSensorFlg)
    {
        m_serialPortPara.strSerialPortname = strPort/*"ttyACM0"*/;
        m_serialPortPara.nBaundRate = QSerialPort::Baud9600;
    }
    else if(POWER_SENSOR_V91 == mUserVariable->m_nPowerSensorFlg)
    {
        m_serialPortPara.strSerialPortname = strPort/*"/dev/ttyUSB0"*/;
        m_serialPortPara.nBaundRate = QSerialPort::Baud115200;
    }
    m_serialPortPara.nDataBits = QSerialPort::Data8;
    m_serialPortPara.nFlowControl = QSerialPort::NoFlowControl;
    m_serialPortPara.nParity = QSerialPort::NoParity;
    m_serialPortPara.nStopBits = QSerialPort::OneStop;
    m_serialportPm->openPort(m_serialPortPara);
}

void Pm_Communication::closePowerPort()
{
    m_serialportPm->closePort();
}

/**
* @brief 根据接收指令值解析数据
* @note
* @author Roc
* @since  2019.11.12
*/
void Pm_Communication::RecvCommCmd(QByteArray commRecvData)
{
    processingData(commRecvData);
}

void Pm_Communication::processingData(QByteArray& buffer)
{
    if(m_bDataSplicingFlg)//上一次数据需要和本次数据合并
    {
        buffer.insert(0,m_tmpData);
        m_tmpData.clear();
    }
    qint32 nLen = 0 ;
    while(true)
    {
        nLen = buffer.size();
        if(nLen >=  10)//10 = (头) 3c 3c 3c 3c + （指令）00 00 + (长度)00 00  + (校验) 00 00 + (结束) f3
        {
            if(('\x3c' ==buffer[0])&&
                    ('\x3c' == buffer[1]) &&
                    ('\x3c' == buffer[2] )&&
                    ('\x3c' == buffer[3]))
            {
                qDebug()<<"Error Data "<<m_errData.toHex() << endl;
                m_errData.clear();

                quint16 nCmdDataSize = 0;

                if(POWER_SENSOR_V90 == mUserVariable->m_nPowerSensorFlg)
                {
                    nCmdDataSize = QByteArrayByHightLToqint16(buffer,6);
                }
                else  if(POWER_SENSOR_V91 == mUserVariable->m_nPowerSensorFlg)
                {
                    nCmdDataSize = QByteArrayByLowHToqint16(buffer,6);
                }
                if(nLen  >= 4 + 2 + 2 + nCmdDataSize + 2+1)
                {
                    if('\xf3' == buffer[4 + 2 + 2 + nCmdDataSize + 2])
                    {
                        QByteArray commandData = buffer.left(4 + 2 + 2 + nCmdDataSize + 2 + 1);

                        qDebug()<<"Command Data "<<commandData.toHex() << endl;
                        analysisCommand(commandData);
                        buffer.remove(0,4 + 2 + 2 + nCmdDataSize + 2 + 1);

                    }
                    else //Error Command
                    {
                        m_errData.append(buffer[0]);
                        buffer.remove(0,1);
                        continue;
                    }
                }
                else
                    break;
            }
            else
            {
                m_errData.append(buffer[0]);
                buffer.remove(0,1);
            }
        }
        else
            break;
    }

    nLen = buffer.size();
    if(0 < nLen)
    {
        m_tmpData.append(buffer);
        m_bDataSplicingFlg = true;
    }else  //0 is complete
    {
        m_bDataSplicingFlg = false;
    }
    return;
}

/**
* @brief	解析指令
* @note
* @Author	ROC
* @date	2019.12.4
*/
void Pm_Communication::analysisCommand(QByteArray& buffer)
{
    quint16 nCmdDataSize;

    if(POWER_SENSOR_V90 == mUserVariable->m_nPowerSensorFlg)
    {
        nCmdDataSize = QByteArrayByHightLToqint16(buffer,6);
        QByteArray arrayData;
        arrayData.clear();
        arrayData.resize(nCmdDataSize);
        for(int i = 0;i < nCmdDataSize;i++)
        {
            arrayData[i] = buffer[8+i];
        }
        switch (buffer[4])
        {
        case '\x00' ://
            switch(buffer[5])
            {
            case '\x02':
            case '\x04':
                emit FinishPower(arrayData);
                break;
            }
            break;
        case '\x01' :
            switch(buffer[5])
            {
            case '\x02':
                emit FinishCalRead(arrayData);
                break;
            }

            break;
        case '\x02' :
            switch(buffer[5])
            {
            case '\x02':
                emit FinishSysInfo(arrayData);
                break;
            }

            break;
        default:
            break;
        }
    }
    else if(POWER_SENSOR_V91 == mUserVariable->m_nPowerSensorFlg)
    {
        nCmdDataSize = QByteArrayByLowHToqint16(buffer,6);
        QByteArray arrayData;
        arrayData.clear();
        arrayData.resize(nCmdDataSize);
        for(int i = 0;i < nCmdDataSize;i++)
        {
            arrayData[i] = buffer[8+i];
        }
        switch (buffer[5])
        {
        case '\x00' ://
            switch(buffer[4])
            {
            case '\x00':
            case '\x01':
                emit FinishPower(arrayData);
                break;
            }
            break;

        case '\x02' ://
            switch(buffer[4])
            {
            case '\x00':
                emit FinishSysInfo(arrayData);
                break;
            }

            break;
        default:
            break;
        }
    }
}

/**
* @brief   根据指令值设置发送指令
* @note
* @author  Roc
* @since   2019.11.10
*/
void Pm_Communication::sendCommCmd(qint32 indexFlg,QByteArray commRecvData)
{
    quint16 nCmdDataSize = 0;
    quint16 crcCcit;
    char data[1024] = {0,};
    if(POWER_SENSOR_V90 == mUserVariable->m_nPowerSensorFlg)
    {
        data[0] = 0x3c;
        data[1] = 0x3c;
        data[2] = 0x3c;
        data[3] = 0x3c;

        switch (indexFlg)
        {
        case V90_SINGLE_MODE:
            data[4] = 0x00;
            data[5] = 0x01;
            break;
        case V90_CONTINUOUS_MODE:
            data[4] = 0x00;
            data[5] = 0x03;
            break;
        case V90_CALIBRATION_TABLE_READ:
            data[4] = 0x01;
            data[5] = 0x01;
            break;
        case V90_CALIBRATION_TABLE_WRITE:
            data[4] = 0x01;
            data[5] = 0x03;
            break;
        case V90_CALIBRATION_READY:
            data[4] = 0x01;
            data[5] = 0x05;
            break;
        case V90_INVENTORY_READ:
            data[4] = 0x02;
            data[5] = 0x01;
            break;
        case V90_INVENTORY_WRITE:
            data[4] = 0x02;
            data[5] = 0x03;
            break;
        case V90_F_W_DOWNLOAD_READY:
            data[4] = 0x02;
            data[5] = 0x05;
            break;
        case V90_F_W_DOWNLOAD_PACKAGE:
            data[4] = 0x02;
            data[5] = 0x07;
            break;
        case V90_F_W_DOWNLOAD_PACKAGE_END:
            data[4] = 0x02;
            data[5] = 0x09;
            break;
        default:
            break;
        }

        nCmdDataSize = commRecvData.size();
        data[6] = nCmdDataSize >> 8;
        data[7] = nCmdDataSize & 0xFF;

        for(int i = 0;i < nCmdDataSize;i++)
        {
            data[8 + i] = commRecvData[i];
        }

        int nSendLen =  4 + 2 +2 + nCmdDataSize;

        crcCcit = m_crcCCITT.CrcCcittGet(data,nSendLen);
        data[nSendLen++] = crcCcit & 0xFF;
        data[nSendLen++]= crcCcit >> 8;
        data[nSendLen++] = 0xf3;

        m_serialportPm->sendInfo(data,nSendLen);
    }
    else  if(POWER_SENSOR_V91 == mUserVariable->m_nPowerSensorFlg)
    {
        data[0] = 0x3c;
        data[1] = 0x3c;
        data[2] = 0x3c;
        data[3] = 0x3c;

        switch (indexFlg)
        {
        case V91_SINGLE_MODE_GET:
            data[4] = 0x00;
            data[5] = 0x00;
            break;
        case V91_CONTINUOUS_MODE_GET:
            data[4] = 0x01;
            data[5] = 0x00;
            break;
        case V91_CONTROL_DATA_GET:
            data[4] = 0x00;
            data[5] = 0x01;
            break;
        case V91_CONTROL_DATA_SET:
            data[4] = 0x01;
            data[5] = 0x01;
            break;
        case V91_INVENTORY_DATA_GET:
            data[4] = 0x00;
            data[5] = 0x02;
            break;
        case V91_F_W_DOWNLOAD_START:
            data[4] = 0x00;
            data[5] = 0x10;
            break;
        case V91_F_W_DOWNLOAD_DATA:
            data[4] = 0x01;
            data[5] = 0x10;
            break;
        case V91_F_W_DOWNLOAD_FINAL:
            data[4] = 0x02;
            data[5] = 0x10;
            break;
        default:
            break;
        }

        nCmdDataSize = commRecvData.size();
        data[6] = nCmdDataSize & 0xFF;
        data[7] = nCmdDataSize >> 8;

        for(int i = 0;i < nCmdDataSize;i++)
        {
            data[8 + i] = commRecvData[i];
        }

        int nSendLen =  4 + 2 +2 + nCmdDataSize;

        crcCcit = m_crcCCITT.CrcCcittGet(data,nSendLen);
        data[nSendLen++] = crcCcit & 0xFF;
        data[nSendLen++]= crcCcit >> 8;
        data[nSendLen++] = 0xf3;

        m_serialportPm->sendInfo(data,nSendLen);
    }
}


/**
* @brief   得到串口字符串列表
* @note    串口字符串列表
* @author  Roc
* @since   2019.11.12
*/
void  Pm_Communication::getPortNameList(QStringList&  listPotrStr)
{
    //获取可用串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QString strName = info.portName();
        if(!info.isBusy() && (0< strName.contains("ttyUSB") ||0<strName.contains("ttyACM")))
        {
            listPotrStr.append(strName);
            qDebug()<<strName;
        }
    }
}

/**
* @brief   得到Combox串口列表
* @note
* @author  Roc
* @since   2019.11.12
*/
void Pm_Communication::getComboxPortList(QComboBox& comBoBoxListPort)
{
    QStringList  m_listPotrStr;
    getPortNameList(m_listPotrStr);
    comBoBoxListPort.addItems(m_listPotrStr);
}


//int Pm_Communication::init_comm()
//{
//    memset (&temp_uart_MsgHeader, 0, sizeof(_UART_Header));
//    memset (&uart_ringbuffer, 0, sizeof(_UART_RingBuffer));
//    return 0;
//}

//void Pm_Communication::RunPowerSensorMode()
//{
//    int detect_status = 0, for_loop = 0;

//    // check fd, init ttyACM()
//    if (-1 == fd_powersensor)
//    {
//        if (0 == init_ttyACM())
//        {
//            // check inventory
//            SendMsg_UART(fd_powersensor, C_PSInvenReadRQ, NULL, 0);
//            memset(&temp_ps_Inventory, 0, sizeof(temp_ps_Inventory));

//            for(for_loop=0;for_loop<1000;for_loop++)
//            {
//                if (0 != temp_ps_Inventory.FW_Ver[0])
//                {
//                    detect_status = 1;
//                    break;
//                }

//                usleep(100);
//            }

//            if (1 == detect_status)
//            {
//                sm_system_info->PSStatus = _Connected;              //[0]Wait, [1]Connected, [2]Disconnected

//                // sweep stop
//                Update_SweepConfig_Flag(ConfigUpdate_PowerSensorRun);

//                // set continuous mode - Run
//                SetPSContinuousModeRQ_SendUART(_RUN);
//            }
//            else
//            {
//                // detect fail
//                printf("Power Sensor Connect Fail::Inventory is Zero\n\r");

//                sm_system_info->PSStatus = _Wait;              //[0]Wait, [1]Connected, [2]Disconnected
//                powersensor_thread_run_flag = _STOP;
//                close(fd_powersensor);
//                fd_powersensor = -1;
//            }
//        }
//        else
//        {
//            printf("Not Found ttyACM.\n\r");
//        }
//    }
//    else
//    {
//        printf("Already Connected PowerSensor.\n\r");
//    }
//}

//void Pm_Communication::StopPowerSensorMode()
//{
//    if (-1 != fd_powersensor)
//    {
//        // set continuous mode - Stop
//        if (_NotDetect != Check_ttyACM())
//        {
//            SetPSContinuousModeRQ_SendUART(_STOP);
//            usleep(10);
//        }

//        powersensor_thread_run_flag = _STOP;
//        usleep(100);

//        // from thread_ExtCommUART_PowerSensor()
//        //close(fd_powersensor);
//        //fd_powersensor = -1;

//        // clear infomation
//        memset(sm_system_info->PSModel, 0, 16);             //Power Sensor Model Name
//        sm_system_info->PSType = 0;                         //Power Sensor Type
//        memset(sm_system_info->PSSerialNo, 0, 16);          //Power Sensor Serial Number
//        memset(sm_system_info->PSInvenFwVersion, 0, 3);   // Power Sensor FW Version; char[0] H/W 255, char[1] S/W Major255, char[2] S/W Patch255
//        sm_system_info->PSTemp = 0.;                        //Power Sensor Temperature

//        // disconnect
//        sm_system_info->PSStatus = _Wait;                   //[0]Wait, [1]Connected, [2]Disconnected
//    }
//}

//int Pm_Communication::init_ttyACM()
//{
//    int return_val = -1, tmep_ttyacmport = _NotDetect;

//    // check ttyUSB
//    tmep_ttyacmport = Check_ttyACM();

//    if (_NotDetect != tmep_ttyacmport)
//    {
//        powersensor_connected_port = tmep_ttyacmport;

//        // open()
//        fd_powersensor = Serial_open(tmep_ttyacmport, 115200, 0, 1);

//        memset (&uart_ringbuffer, 0, sizeof(uart_ringbuffer));

//        // run receive thread
//        powersensor_thread_run_flag = _RUN;
//        pthread_create(&thread_pool_comm[Thread_ExtCommUART_PowerSensor],NULL, thread_ExtCommUART_PowerSensor, NULL);

//        return_val = 0;
//    }
//    else
//    {
//        powersensor_thread_run_flag = _STOP;
//        powersensor_connected_port = _NotDetect;
//        printf("init_ttyACM()::Check_ttyACM fail!\n\r");
//    }


//    return return_val;
//}

//int Pm_Communication::Check_ttyACM()
//{
//    int output = _NotDetect;

//    if (0 == access("/dev/ttyACM0",F_OK)) output = _ttyACM0;
//    else if (0 == access("/dev/ttyACM1",F_OK)) output = _ttyACM1;
//    else if (0 == access("/dev/ttyACM2",F_OK)) output = _ttyACM2;
//    else if (0 == access("/dev/ttyACM3",F_OK)) output = _ttyACM3;

//    return output;
//}

//int Pm_Communication::Serial_open(int dev_num, int baud, int vtime, int vmin)
//{
//    int fd = 0;
//    char *port_name = NULL;
//    struct termios newtio;

//    switch(dev_num)
//    {
//        case _ttyACM0:
//            port_name = "/dev/ttyACM0";
//            break;
//        case _ttyACM1:
//            port_name = "/dev/ttyACM1";
//            break;
//        case _ttyACM2:
//            port_name = "/dev/ttyACM2";
//            break;
//        case _ttyACM3:
//            port_name = "/dev/ttyACM3";
//            break;

//        default:
//            port_name = "/dev/ttyACM0";
//            break;
//    }

//    fd = open(port_name, O_RDWR | O_NOCTTY | O_NONBLOCK);
//    if (fd <0)
//    {
//        //perror((char*)dev_num); //exit(-1);
//        printf("open error port name[%s]\n\r",port_name);
//        return -1;
//    }

//    memset(&newtio,0,sizeof(newtio));
//    newtio.c_cflag = CS8 | CLOCAL | CREAD;
//    newtio.c_iflag = IGNPAR;
//    newtio.c_oflag = 0;

//    switch(baud)
//    {
//        case 115200:
//            //printf("115200");
//            newtio.c_cflag |= B115200;
//            break;
//        case 57600:
//            newtio.c_cflag |= B57600;
//            break;
//        case 38400:
//            newtio.c_cflag |= B38400;
//            break;
//        case 19200:
//            newtio.c_cflag |= B19200;
//            break;
//        case 9600:
//            newtio.c_cflag |= B9600;
//            break;
//        case 4800:
//            newtio.c_cflag |= B4800;
//            break;
//        case 2400:
//            newtio.c_cflag |= B2400;
//            break;
//        default :
//            newtio.c_cflag |= B115200;
//            break;

//    }

//    newtio.c_lflag = 0;
//    newtio.c_cc[VMIN]=vmin;
//    newtio.c_cc[VTIME]=vtime;

//    tcflush(fd,TCIFLUSH);
//    tcsetattr(fd,TCSANOW,&newtio);

//    return fd;
//}

////================================================================================ UART PowerSensor functions [
//void *Pm_Communication::thread_ExtCommUART_PowerSensor(void *args)
//{
//    int read_cnt = 0;
//    unsigned char temp_buffer = 0;
//    void *return_val = NULL;

//    printf("Run ExtCommUART PowerSensor Thread\n\r");
//    pthread_detach(pthread_self());
//    //code_log(__FUNCTION__, R_Status_ExtCommUARTThreadRun, "ConnectPowerSensor\0");

//    // check UART device driver
//    if (0 == fd_powersensor)
//    {
//        printf("thread_ExtComm_UART::fd_powersensor is Zero\n\r");
//        return return_val;
//    }

//    // run bufferprocess thread
//    pthread_create(&thread_pool_comm[Thread_BufferProcess_UART],NULL, thread_BufferProcess_UART, NULL);
//    //pthread_create(&thread_pool_comm[Thread_PowerSensor_watchdog],NULL, thread_PowerSensor_Watchdog, NULL);


//    // receive
//    while(powersensor_thread_run_flag == _RUN)
//    {
//        while(0 < ( read_cnt = read(fd_powersensor, &temp_buffer, 1) ) )
//        {
//            uart_ringbuffer.Buffer[uart_ringbuffer.push_pt++] = temp_buffer;
//            if (uart_ringbuffer.push_pt > UARTBufferSize-1) uart_ringbuffer.push_pt = 0;
//        }
//        usleep(rand() / (RAND_MAX / 3) + 2);
//    }


//    close(fd_powersensor);
//    fd_powersensor = -1;


//    return return_val;
//}

//void *Pm_Communication::thread_BufferProcess_UART(void *args)
//{
//    void *return_val = NULL;

//    printf("Run BufferProcess UART Thread\n\r");
//    pthread_detach(pthread_self());

//    while(powersensor_thread_run_flag == _RUN)
//    {
//        PowerSensorMsg_Processor(&uart_ringbuffer);

//        usleep(rand() / (RAND_MAX / 3) + 2);
//    }
//    return return_val;
//}

//int Pm_Communication::PowerSensorMsg_Processor(_UART_RingBuffer *targetpt)
//{
//    _UART_RingBuffer *temp_targetpt = targetpt;

//    // check current receive point & read point
//    while (temp_targetpt->read_pt != temp_targetpt->push_pt)
//    {
//        //printf("UARTMsg_Processor()::#1read_pt[%d] push_pt[%d]\n\r",temp_targetpt->read_pt, temp_targetpt->push_pt);

//        switch (check_status_uart)
//        {
//            case S_STX:
//                if (temp_targetpt->Buffer[temp_targetpt->read_pt] == StartByte)
//                {
//                    temp_targetpt->read_pt++;

//                    if (chk_cnt_uart == 3)
//                    {
//                        memset(&temp_uart_MsgHeader, 0, sizeof(temp_uart_MsgHeader));
//                        memset(&temp_data_uart, 0, sizeof(temp_data_uart));

//                        check_status_uart = S_CMD;
//                        chk_cnt_uart = 0;
//                    }
//                    else chk_cnt_uart++;
//                }
//                else
//                {
//                    chk_cnt_uart = 0;
//                    //printf("R_ErrorUART_STX[0x%x]",temp_targetpt->Buffer[temp_targetpt->read_pt]);
//                    temp_targetpt->read_pt++;

//                    //return R_ErrorUART_STX;
//                }

//                break;

//            case S_CMD:
//                temp_uart_MsgHeader._CMD[chk_cnt_uart] = temp_targetpt->Buffer[temp_targetpt->read_pt];
//                temp_targetpt->read_pt++;

//                if (chk_cnt_uart == 1)
//                {
//                    check_status_uart = S_DATASIZE;
//                    chk_cnt_uart = 0;
//                }
//                else chk_cnt_uart++;
//                break;

//            case S_DATASIZE:
//                temp_uart_MsgHeader._Length[chk_cnt_uart] = temp_targetpt->Buffer[temp_targetpt->read_pt];
//                //printf("[S_DATASIZE][0x%x][%d][%d]",temp_targetpt->Buffer[temp_targetpt->read_pt],temp_targetpt->read_pt,chk_cnt_uart);

//                temp_targetpt->read_pt++;

//                if (chk_cnt_uart == 1)
//                {
//                    // data + crc + endbyte
//                    temp_read_datasize_uart = (temp_uart_MsgHeader._Length[0] << 8) + (temp_uart_MsgHeader._Length[1] ) + EndByte_SIZE;
//                    //printf("[R][S_DATASIZE][0x%x]",temp_read_datasize_uart);
//                    check_status_uart = S_DATA;
//                    if (temp_read_datasize_uart == 0)
//                    {
//                        temp_read_cmd_uart = (temp_uart_MsgHeader._CMD[0] << 8) + (temp_uart_MsgHeader._CMD[1]);
//                        //printf("[R][S_CMD][0x%x]",temp_read_cmd_uart);

//                        check_status_uart = S_STX;
//                        //PowerSensor_CMD_Processor(temp_read_cmd_uart, temp_read_datasize_uart, (char*)&temp_data_uart);
//                    }
//                    else if (temp_read_datasize_uart < 0)
//                    {
//                        check_status_uart = S_STX;
//                    }
//                    chk_cnt_uart = 0;
//                }
//                else chk_cnt_uart++;
//                break;

//            case S_DATA:
//                temp_data_uart[chk_cnt_uart] = temp_targetpt->Buffer[temp_targetpt->read_pt];
//                temp_targetpt->read_pt++;

//                //printf("[S_DATA][size%d]",temp_read_datasize_uart);

//                if (chk_cnt_uart == (temp_read_datasize_uart-1))
//                {
//                    check_status_uart = S_STX;
//                    chk_cnt_uart = 0;

//                    temp_read_cmd_uart = (temp_uart_MsgHeader._CMD[0] << 8) + (temp_uart_MsgHeader._CMD[1]);
//                    //printf("[R][S_DATA][CMD 0x%x]",temp_read_cmd_uart);

//                    PowerSensor_CMD_Processor(temp_read_cmd_uart, temp_read_datasize_uart-CRC_SIZE-EndByte_SIZE, (char*)&temp_data_uart);
//                }
//                else chk_cnt_uart++;
//                break;

//            case S_Process:

//                check_status_uart = S_STX;
//                chk_cnt_uart = 0;
//                break;
//        }

//        // check ring buffer read point
//        if(temp_targetpt->read_pt > UARTBufferSize-1) temp_targetpt->read_pt = 0;

//    }

//    return R_StatusNormal;

//}


//int Pm_Communication::PowerSensor_CMD_Processor(int input_cmd, int input_datasize, char *data_startpt)
//{
//    switch (input_cmd)
//    {
//        case C_PSInvenReadRP:
//            memcpy(&temp_ps_Inventory, data_startpt, sizeof(temp_ps_Inventory));

//            memcpy(sm_system_info->PSModel, temp_ps_Inventory.modelnum, 16);            //Power Sensor Model Name
//            sm_system_info->PSType = temp_ps_Inventory.type;                            //Power Sensor Type
//            memcpy(sm_system_info->PSSerialNo, temp_ps_Inventory.serialnum, 16);    //Power Sensor Serial Number
//            memcpy(sm_system_info->PSInvenFwVersion, temp_ps_Inventory.FW_Ver, 3);  // Power Sensor FW Version; char[0] H/W 255, char[1] S/W Major255, char[2] S/W Patch255
//            break;

//        case C_PSSingleModeRP:
//            memcpy(&temp_ps_MeasureModeData, data_startpt, sizeof(temp_ps_MeasureModeData));

//            sm_system_info->PSTemp = (float)temp_ps_MeasureModeData.Temperature/10.;        //Power Sensor Temperature *10
//            sm_measure_data->PSLevel = (double)temp_ps_MeasureModeData.PowerLevel/100.;     //Power level * 100
//            break;

//        case C_PSContinuousModeRP:
//            memcpy(&temp_ps_MeasureModeData, data_startpt, sizeof(temp_ps_MeasureModeData));

//            sm_system_info->PSTemp = (float)temp_ps_MeasureModeData.Temperature/10.;        //Power Sensor Temperature *10
//            sm_measure_data->PSLevel = (double)temp_ps_MeasureModeData.PowerLevel/100.;     //Power level * 100
//            break;

//        case C_PSRawModeRP:
//            memcpy(&temp_ps_RawModeData, data_startpt, sizeof(temp_ps_RawModeData));
//            //temp_ps_RawModeData.ADCdata;
//            sm_system_info->PSTemp = (float)temp_ps_RawModeData.Temperature/10.;        //Power Sensor Temperature *10
//            sm_measure_data->PSLevel = (double)temp_ps_RawModeData.PowerLevel/100.;     //Power level * 100
//            break;

//        default:
//            printf("PowerSensor_CMD_Processor::UnkownCMD[0x%x]\n\r",input_cmd);
//            break;
//    }

//    return R_StatusNormal;
//}

//int Pm_Communication::SendMsg_UART(int fd_target, unsigned int inputcmd, void *inputdata, unsigned int inputdatasize)
//{
//    unsigned char send_buffer[100] = {0,};
//    int temp_position = 0, return_val = R_StatusNormal;
//    unsigned int sum_totalsize = inputdatasize+CRC_SIZE;
//    unsigned short mk_crc = 0;
//    _UART_Header mk_header;

//    mk_header._STX[0] = StartByte;
//    mk_header._STX[1] = StartByte;
//    mk_header._STX[2] = StartByte;
//    mk_header._STX[3] = StartByte;

//    mk_header._CMD[0] = (inputcmd>>8)&0xff;
//    mk_header._CMD[1] = (inputcmd)&0xff;

//    mk_header._Length[0] = (sum_totalsize>>8)&0xff;
//    mk_header._Length[1] = (sum_totalsize)&0xff;

//    // push udp header
//    temp_position = sizeof(_UART_Header);
//    memcpy(&send_buffer, &mk_header, temp_position);

//    // push data
//    if (inputdatasize != 0) memcpy(&send_buffer[temp_position], inputdata, inputdatasize);
//    temp_position += inputdatasize;

//    // push crc
//    mk_crc = CrcCcittGet(&send_buffer[Array_CMD], temp_position -4);

//    send_buffer[temp_position++] = (mk_crc>>8)&0xff;
//    send_buffer[temp_position++] = (mk_crc)&0xff;
//    send_buffer[temp_position++] = EndByte;


//    printf("SendMsg_UART::DataFrame\n\r");
//    //for (for_loop=0; for_loop<temp_position; for_loop++)
//    //{
//        //printf("[%d] [0x%x]\n\r",for_loop, send_buffer[for_loop]);
//    //}
//    return_val = write(fd_target, send_buffer, temp_position);
//    return return_val;
//}

//void Pm_Communication::SetPSContinuousModeRQ_SendUART(int input_runstop)
//{
//    _PowerSensorMsg_ContinuousModeRQ temp_contModerq;

//    temp_contModerq.RunStop = input_runstop;
//    temp_contModerq.SetFreq = (unsigned short)(sm_config_measure->PSFreq/1000000.);
//    SendMsg_UART(fd_powersensor, C_PSContinuousModeRQ, &temp_contModerq, sizeof(temp_contModerq));
//}

//void Pm_Communication::CheckPS_ttyACM_Port(void)
//{
//    if (_Connected == sm_system_info->PSStatus)
//    {
//        int result = -1;

//        switch(powersensor_connected_port)
//        {
//            case _ttyACM0:
//                if (0 == access("/dev/ttyACM0",F_OK)) result = 0;
//                break;
//            case _ttyACM1:
//                if (0 == access("/dev/ttyACM1",F_OK)) result = 0;
//                break;
//            case _ttyACM2:
//                if (0 == access("/dev/ttyACM2",F_OK)) result = 0;
//                break;
//            case _ttyACM3:
//                if (0 == access("/dev/ttyACM3",F_OK)) result = 0;
//                break;
//        }

//        if (0 != result)
//        {
//            printf("CheckPS_ttyACM_Port::ttyACM:LostPort\n\r");
//            StopPowerSensorMode();
//        }
//    }

//}

////================================================================================ UART PowerSensor functions ]




