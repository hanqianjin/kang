/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              Pm_Communication
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              ROC
 **Created date:            2019/11/09
 **Descriptions:            PM Communication
 **
 *****************************************************************/


#ifndef PM_COMMUNICATION_H
#define PM_COMMUNICATION_H

#include <QObject>
#include "pm_user_variable.h"
#include "qserialportex.h"
#include "crc_command.h"
#include "pm_user_variable.h"

//#define UARTBufferSize					2048			// 2kbytes
//#define StartByte						0x3c
//#define StartFrame						StartByte|StartByte|StartByte|StartByte
//#define EndByte							0xf3
//#define Array_CMD						4
//#define CRC_SIZE						2
//#define EndByte_SIZE					1
//#define S_STX							1
//#define S_CMD							2
//#define S_DATASIZE						3
//#define S_DATA							4
//#define S_Process						5
//// for power sensor
//#define C_PSSingleModeRQ                0x0001
//#define C_PSSingleModeRP                0x0002
//#define C_PSContinuousModeRQ            0x0003
//#define C_PSContinuousModeRP            0x0004
//#define C_PSRawModeRQ                   0x0005
//#define C_PSRawModeRP                   0x0006
//#define C_PSCalTableReadRQ              0x0101
//#define C_PSCalTableReadRP              0x0102
//#define C_PSCalTableWriteRQ             0x0103
//#define C_PSCalTableWriteRP             0x0104
//#define C_PSCalReadyRQ                  0x0105
//#define C_PSCalReadyRP                  0x0106
//#define C_PSCalRT4CWriteRQ              0x0107
//#define C_PSCalRT4CWriteRP              0x0108
//#define C_PSCalRT4CReadRQ               0x0109
//#define C_PSCalRT4CReadRP               0x010a
//#define C_PSInvenReadRQ                 0x0201
//#define C_PSInvenReadRP                 0x0202
//#define C_PSInvenWriteRQ                0x0203
//#define C_PSInvenWriteRP                0x0204
//#define C_PSFWDnReadyRQ                 0x0205
//#define C_PSFWDnReadyRP                 0x0206
//#define C_PSFWDnPackageRQ               0x0207
//#define C_PSFWDnPackageRP               0x0208
//#define C_PSFWDnEndRQ                   0x0209
//#define C_PSFWDnEndRP                   0x020a
//typedef struct
//{
//    unsigned int LOCK_flag;
//    unsigned int read_pt;
//    unsigned int push_pt;
//    unsigned char Buffer[UARTBufferSize];
//}_UART_RingBuffer;
//enum _CommThreadList
//{
//    Thread_ExtCommUART_PowerSensor,
//    Thread_BufferProcess_UART,
//    CommThreadMax
//};
//enum _PowerSensorPortList
//{
//    _NotDetect = 0,
//    _ttyACM0,
//    _ttyACM1,
//    _ttyACM2,
//    _ttyACM3
//};

//enum _PowerSensorStateList
//{
//    _Wait,
//    _Connected,
//    _Disconnected
//};


class Pm_Communication : public QObject
{
    Q_OBJECT
public:
    explicit Pm_Communication(QObject *parent = 0,Pm_User_Variable* userVariable = NULL);
    ~Pm_Communication();

private slots:
    void RecvCommCmd(QByteArray commRecvData);
public:
    void getComboxPortList(QComboBox& comBoBoxListPort);
    void openPowerPort(QString strPort);
    void closePowerPort();
    void sendCommCmd(qint32 indexFlg,QByteArray commRecvData);

    void getPortNameList(QStringList&  listPotrStr);
public:
    QSerialPortEx*  m_serialportPm;
private:
    void processingData(QByteArray& buffer);
    void analysisCommand(QByteArray& buffer);

signals:
    void FinishPower(QByteArray value);
    void FinishSysInfo(QByteArray value);
    void FinishCalRead(QByteArray value);
private:
    __SERIAL_PORT_PARA__ m_serialPortPara;
    bool m_bDataSplicingFlg; //数据拼接标志
    QByteArray m_tmpData;   //临时数据
    QByteArray m_errData;   //错误数据
    CRC_Command m_crcCCITT;

    Pm_User_Variable *mUserVariable;
//    _UART_Header temp_uart_MsgHeader;
//    _UART_RingBuffer uart_ringbuffer;
//    _PowerSensorMsg_Inventory temp_ps_Inventory;
//    _PowerSensorMsg_MeasureModeRP temp_ps_MeasureModeData;
//    _PowerSensorMsg_RawModeRP temp_ps_RawModeData;

//    pthread_t thread_pool_comm[CommThreadMax];
//    int check_status_uart = S_STX, chk_cnt_uart = 0, temp_read_datasize_uart = 0, temp_read_cmd_uart = 0;
//    unsigned char temp_data[1200] = {0,};
//    unsigned char temp_data_uart[1200] = {0,};
//    int fd_powersensor = -1;
//    int powersensor_connected_port = _NotDetect;
//    //        int powersensor_thread_run_flag = _STOP;

//    int init_comm();
//    void CheckPS_ttyACM_Port();
//    void RunPowerSensorMode();
//    void StopPowerSensorMode();
//    int init_ttyACM();
//    int Check_ttyACM();
//    int Serial_open(int dev_num, int baud, int vtime, int vmin);
//    int PowerSensorMsg_Processor(_UART_RingBuffer *targetpt);
//    int PowerSensor_CMD_Processor(int input_cmd, int input_datasize, char *data_startpt);
//    int SendMsg_UART(int fd_target, unsigned int inputcmd, void *inputdata, unsigned int inputdatasize);

//    void SetPSContinuousModeRQ_SendUART(int input_runstop);

//    void *thread_ExtCommUART_PowerSensor(void *args);
//    void *thread_BufferProcess_UART(void *args);

};

#endif // PM_COMMUNICATION_H
