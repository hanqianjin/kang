#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scpidef/autoproductcommand.h"

#define LEN_HEIGHT_LOW
//#define LEN_LOW_HEIGHT

bool  m_bDataSplicingFlg = false; //数据拼接标志
QByteArray m_tmpData = 0;   //临时数据
QByteArray m_errData = 0;   //错误数据

int recMessgFlag = 0;

ushort CRC_Ccitt_Table[] =
{
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

/**
 * @brief CrcCcittGet
 * @param i_buf
 * @param i_buf_len
 * @return
 */
ushort CrcCcittGet (const char *i_buf, int i_buf_len)
{
    ushort crc;
    uint   i;

    crc = 0x0000;

    if(i_buf_len > 6000)
        i_buf_len = 6000;

    for(i = 0; i < (uint)i_buf_len; i++)
    {
        crc = (crc << 8) ^ CRC_Ccitt_Table[((crc >> 8) & 0xff) ^ i_buf[i]];
    }

    return (crc);
}

/**
 * @brief ChecksumGet
 * @param i_buf
 * @param i_buf_len
 * @return
 */
unsigned char ChecksumGet (const char *i_buf, int i_buf_len)
{
    uint crc;
    uint   i;

    crc = 0;

    if(i_buf_len > 6000)
        i_buf_len = 6000;

    for(i = 0; i < (uint)i_buf_len; i++)
    {
        crc += (uint)i_buf[i];
    }

    return ((unsigned char)(crc & 0xFF));
}

/**
 * @brief charToByteArray
 * @param sendArray
 * @return
 */
QByteArray charToByteArray(const char *sendArray)
{
    double tmpL;
    char str[20];
    memset(str,0,20);

    sscanf(sendArray,"%lg",&tmpL);

    qlonglong lData = (qlonglong)tmpL;
    sprintf(str,"%lx",lData);
    int l_Str = strlen(str);
    QByteArray retArray;
    retArray.clear();
    if(l_Str%2 == 0) retArray.resize(l_Str/2);
    else retArray.resize((l_Str+1)/2);

    for(int i = retArray.size() - 1;i>=0;i--)
    {
        retArray[i] = (lData>>((retArray.size() - i - 1)*8)) & 0xff;
    }

    return retArray;
}
/**
 * @brief cmdDataSend
 * @param indexFlg
 * @param sendData
 * @return
 */
QByteArray cmdDataSend(int indexFlg,QByteArray sendData)
{
    ushort nCmdDataSize = 0;//指令数据长度
    ushort crcCcit;//指令CRC校验
    char data[1024] = {0,};

    data[0] = 0x3c;
    data[1] = 0x3c;
    data[2] = 0x3c;
    data[3] = 0x3c;

    switch (indexFlg)
    {
    case ESE_REQUEST:
        data[4] = 0x10;
        data[5] = 0x01;
        break;
    case ESR_REQUEST:
        data[4] = 0x10;
        data[5] = 0x03;
        break;
    case IDN_REQUEST:
        data[4] = 0x10;
        data[5] = 0x04;
        break;
    case OPC_REQUEST:
        data[4] = 0x10;
        data[5] = 0x06;
        break;
    case SRE_REQUEST:
        data[4] = 0x10;
        data[5] = 0x08;
        break;
    case STB_REQUEST:
        data[4] = 0x10;
        data[5] = 0x0A;
        break;
    case TST_REQUEST:
        data[4] = 0x10;
        data[5] = 0x0B;
        break;
    case RFTMP_REQUEST:
        data[4] = 0x12;
        data[5] = 0x0A;
        break;
    case BOARDTMP_REQUEST:
        data[4] = 0x12;
        data[5] = 0x0B;
        break;
    case FPGATMP_REQUEST:
        data[4] = 0x12;
        data[5] = 0x0C;
        break;
    case BATTERYTMP_REQUEST:
        data[4] = 0x12;
        data[5] = 0x0D;
        break;
    case CENTERFREQ_REQUEST:
        data[4] = 0x20;
        data[5] = 0x01;
        break;
    case STARTFREQ_REQUEST:
        data[4] = 0x20;
        data[5] = 0x03;
        break;
    case STOPFREQ_REQUEST:
        data[4] = 0x20;
        data[5] = 0x05;
        break;
    case STEPFREQ_REQUEST:
        data[4] = 0x20;
        data[5] = 0x07;
        break;
    case OFFSETFREQ_REQUEST:
        data[4] = 0x20;
        data[5] = 0x09;
        break;
    case SPANFREQ_REQUEST:
        data[4] = 0x20;
        data[5] = 0x0B;
        break;
    case REFLEVEL_REQUEST:
        data[4] = 0x21;
        data[5] = 0x02;
        break;
    case SCALE_REQUEST:
        data[4] = 0x21;
        data[5] = 0x04;
        break;
    case ATTENAUTO_REQUEST:
        data[4] = 0x21;
        data[5] = 0x06;
        break;
    case ATTEN_REQUEST:
        data[4] = 0x21;
        data[5] = 0x08;
        break;
    case PREAMP_REQUEST:
        data[4] = 0x21;
        data[5] = 0x0A;
        break;
    case REFOFFSET_REQUEST:
        data[4] = 0x21;
        data[5] = 0x0C;
        break;
    case DIVISION_REQUEST:
        data[4] = 0x21;
        data[5] = 0x0E;
        break;
    case SWEEPTIMEAUTO_REQUEST:
        data[4] = 0x22;
        data[5] = 0x01;
        break;
    case SWEEPTIME_REQUEST:
        data[4] = 0x22;
        data[5] = 0x03;
        break;
    case COUNTINUOUS_REQUEST:
        data[4] = 0x22;
        data[5] = 0x05;
        break;
    case BANDWIDTH_RBWAUTO_REQUEST:
        data[4] = 0x23;
        data[5] = 0x01;
        break;
    case BWIDTH_RBWAUTO_REQUEST:
        data[4] = 0x23;
        data[5] = 0x03;
        break;
    case BANDWIDTH_RBW_REQUEST:
        data[4] = 0x23;
        data[5] = 0x05;
        break;
    case BWIDTH_RBW_REQUEST:
        data[4] = 0x23;
        data[5] = 0x07;
        break;
    case BANDWIDTH_VBWAUTO_REQUEST:
        data[4] = 0x23;
        data[5] = 0x09;
        break;
    case BWIDTH_VBWAUTO_REQUEST:
        data[4] = 0x23;
        data[5] = 0x0B;
        break;
    case BANDWIDTH_VBW_REQUEST:
        data[4] = 0x23;
        data[5] = 0x0D;
        break;
    case BWIDTH_VBW_REQUEST:
        data[4] = 0x23;
        data[5] = 0x0F;
        break;
    case BANDWIDTH_RATIO_REQUEST:
        data[4] = 0x23;
        data[5] = 0x11;
        break;
    case BWIDTH_RATIO_REQUEST:
        data[4] = 0x23;
        data[5] = 0x13;
        break;
    case IFOUTPUT_REQUEST:
        data[4] = 0x23;
        data[5] = 0x15;
        break;
    case TRIGGER_SOURCE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x01;
        break;
    case EXTERNAL_LEVEL_REQUEST:
        data[4] = 0x24;
        data[5] = 0x05;
        break;
    case VEDIO_LEVEL_REQUEST:
        data[4] = 0x24;
        data[5] = 0x06;
        break;
    case RFBURST_LEVEL_REQUEST:
        data[4] = 0x24;
        data[5] = 0x07;
        break;
    case EXTERNAL_SLOPE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x0B;
        break;
    case VEDIO_SLOPE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x0C;
        break;
    case RFBURST_SLOPE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x0D;
        break;
    case EXTERNAL_DELAYSTATE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x12;
        break;
    case VEDIO_DELAYSTATE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x13;
        break;
    case PERIODIC_DELAYSTATE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x14;
        break;
    case RFBURST_DELAYSTATE_REQUEST:
        data[4] = 0x24;
        data[5] = 0x15;
        break;
    case RFBURST_DELAY_REQUEST:
        data[4] = 0x24;
        data[5] = 0x1A;
        break;
    case EXTERNAL_DELAY_REQUEST:
        data[4] = 0x24;
        data[5] = 0x1B;
        break;
    case VEDIO_DELAY_REQUEST:
        data[4] = 0x24;
        data[5] = 0x1C;
        break;
    case PERIODIC_DELAY_REQUEST:
        data[4] = 0x24;
        data[5] = 0x1D;
        break;
    case PERIODIC_REQUEST:
        data[4] = 0x24;
        data[5] = 0x1F;
        break;
    case TRACE1_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x06;
        break;
    case TRACE2_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x07;
        break;
    case TRACE3_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x08;
        break;
    case TRACE4_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x09;
        break;
    case TRACE5_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x0A;
        break;
    case TRACE6_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x0B;
        break;
    case TRACE1_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x12;
        break;
    case TRACE2_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x13;
        break;
    case TRACE3_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x14;
        break;
    case TRACE4_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x15;
        break;
    case TRACE5_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x16;
        break;
    case TRACE6_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x17;
        break;
    case TRACE1_AVECOUNT_REQUEST:
        data[4] = 0x25;
        data[5] = 0x1E;
        break;
    case TRACE2_AVECOUNT_REQUEST:
        data[4] = 0x25;
        data[5] = 0x1F;
        break;
    case TRACE3_AVECOUNT_REQUEST:
        data[4] = 0x25;
        data[5] = 0x20;
        break;
    case TRACE4_AVECOUNT_REQUEST:
        data[4] = 0x25;
        data[5] = 0x21;
        break;
    case TRACE5_AVECOUNT_REQUEST:
        data[4] = 0x25;
        data[5] = 0x22;
        break;
    case TRACE6_AVECOUNT_REQUEST:
        data[4] = 0x25;
        data[5] = 0x23;
        break;
    case TRACE_DETECTOR_REQUEST:
        data[4] = 0x25;
        data[5] = 0x25;
        break;
    case TRACEDATA_REQUEST:
        data[4] = 0x25;
        data[5] = 0x26;
        break;
    case TRACEDATA_RAWDATA_REQUEST:
        data[4] = 0x25;
        data[5] = 0x27;
        break;
    case TRACEDATA_DRAWDATA_REQUEST:
        data[4] = 0x25;
        data[5] = 0x28;
        break;
    case MARKER_SELECT_REQUEST:
        data[4] = 0x25;
        data[5] = 0x2A;
        break;
    case MARKER1_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x31;
        break;
    case MARKER2_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x32;
        break;
    case MARKER3_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x33;
        break;
    case MARKER4_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x34;
        break;
    case MARKER5_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x35;
        break;
    case MARKER6_DISPLAYSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x36;
        break;
    case MARKER1_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x3D;
        break;
    case MARKER2_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x3E;
        break;
    case MARKER3_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x3F;
        break;
    case MARKER4_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x40;
        break;
    case MARKER5_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x41;
        break;
    case MARKER6_TYPE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x42;
        break;
    case MARKER1_X_REQUEST:
        data[4] = 0x25;
        data[5] = 0x4C;
        break;
    case MARKER2_X_REQUEST:
        data[4] = 0x25;
        data[5] = 0x4D;
        break;
    case MARKER3_X_REQUEST:
        data[4] = 0x25;
        data[5] = 0x4E;
        break;
    case MARKER4_X_REQUEST:
        data[4] = 0x25;
        data[5] = 0x4F;
        break;
    case MARKER5_X_REQUEST:
        data[4] = 0x25;
        data[5] = 0x50;
        break;
    case MARKER6_X_REQUEST:
        data[4] = 0x25;
        data[5] = 0x51;
        break;
    case MARKER1_FREQCOUNTSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x58;
        break;
    case MARKER2_FREQCOUNTSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x59;
        break;
    case MARKER3_FREQCOUNTSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x5A;
        break;
    case MARKER4_FREQCOUNTSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x5B;
        break;
    case MARKER5_FREQCOUNTSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x5C;
        break;
    case MARKER6_FREQCOUNTSTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x5D;
        break;
    case MARKER1_NOISESTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x64;
        break;
    case MARKER2_NOISESTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x65;
        break;
    case MARKER3_NOISESTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x66;
        break;
    case MARKER4_NOISESTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x67;
        break;
    case MARKER5_NOISESTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x68;
        break;
    case MARKER6_NOISESTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x69;
        break;
    case MARKER_PEAKTRACESTATE_REQUEST:
        data[4] = 0x25;
        data[5] = 0x70;
        break;
    case PEAKPOINT_FREQ_REQUEST:
        data[4] = 0x25;
        data[5] = 0x72;
        break;
    case PEAKPOINT_AMP_REQUEST:
        data[4] = 0x25;
        data[5] = 0x73;
        break;
    default: break;
    }

    nCmdDataSize = sendData.size();
    data[6] = nCmdDataSize>> 8;
    data[7] = nCmdDataSize& 0xFF;

    for(int i = 0;i <nCmdDataSize;i++)
    {
        data[8 + i] = sendData[i];
    }

    int nSendLen=  4 + 2 + 2 + nCmdDataSize;

    crcCcit= CrcCcittGet(data,nSendLen);
    data[nSendLen++] = crcCcit& 0xFF;
    data[nSendLen++] = crcCcit>> 8;
    data[nSendLen++] = 0xf3;

    QByteArray retArray;
    retArray.resize(nSendLen);
    for(int i = 0;i<nSendLen;i++)
    {
        retArray[i] = data[i];
    }


    return retArray;
}

/**
* @brief	QByteArray转换为qint16   按照从低位到高位数据排列
* @noteQByteArray bytes  要判断qint16的字符串
*       qint32 nBegin要判断哪2位为qint16的起始位置
* @Author	ROC
* @date     2019.12.12
*/
ushort QByteArrayByLowHToqint16(QByteArray bytes,qint32 nBegin)
{
    qint16 addr;
    addr  = bytes[nBegin + 0] & 0x00FF;
    addr |= ((bytes[nBegin + 1] << 8) & 0xFF00);
    return addr;
}
/**
* @brief	QByteArray转换为qint16   按照从高位到低位数据排列
* @noteQByteArray bytes  要判断qint16的字符串
*       qint32 nBegin要判断哪2位为qint16的起始位置

* @Author	ROC
* @date     2019.12.12
*/
qint16 QByteArrayByHightLToqint16(QByteArray bytes,qint32 nBegin)
{
    qint16 addr;
    addr  =   bytes[nBegin + 1]       & 0x00FF;
    addr |= ((bytes[nBegin + 0] << 8) & 0xFF00);
    return addr;
}

/**
 * @brief analysisCommand
 * @param buffer
 * @return
 */
QString analysisCommand(QByteArray& buffer)
{
    ushort nCmdDataSize;

    #ifdef LEN_HEIGHT_LOW // 指令长度高字节在前低字节在后
    nCmdDataSize = QByteArrayByHightLToqint16(buffer,6);
    #endif
    #ifdef LEN_LOW_HEIGHT// 指令长度低字节在前高字节在后
    nCmdDataSize = QByteArrayByLowHToqint16(buffer,6);
    #endif

    QString cmdData;
    cmdData.clear();
    QByteArray  arrayData;
    arrayData.clear();
    arrayData.resize(nCmdDataSize); 

    qlonglong tmpData = 0;
    for(int i = 0;i <nCmdDataSize;i++)
    {
        arrayData[i] = buffer[8+i];
        tmpData |= ((uchar)arrayData[i])<<((nCmdDataSize - 1 - i)*8);
    }

    switch (buffer[4])
    {
    case '\x10':
        switch(buffer[5])
        {
        case '\x00': cmdData = "*CLS"; break;
        case '\x01': cmdData = "*ESE"; break;
        case '\x02': cmdData = "*ESE?"; recMessgFlag = ESE_REQUEST; break;
        case '\x03': cmdData = "*ESR?"; recMessgFlag = ESR_REQUEST; break;
        case '\x04': cmdData = "*IDN?"; recMessgFlag = IDN_REQUEST; break;
        case '\x05': cmdData = "*OPC"; break;
        case '\x06': cmdData = "*OPC?"; recMessgFlag = OPC_REQUEST; break;
        case '\x07': cmdData = "*RST"; break;
        case '\x08': cmdData = "*SRE"; break;
        case '\x09': cmdData = "*SRE?"; recMessgFlag = SRE_REQUEST; break;
        case '\x0A': cmdData = "*STB?"; recMessgFlag = STB_REQUEST; break;
        case '\x0B': cmdData = "*TST?"; recMessgFlag = TST_REQUEST; break;
        }
        break;
    case '\x12':
        switch(buffer[5])
        {
        case '\x0A': cmdData = ":STATus:RF:TMPTUre?"; recMessgFlag = RFTMP_REQUEST; break;
        case '\x0B': cmdData = ":STATus:BOARD:TMPTUre?"; recMessgFlag = BOARDTMP_REQUEST; break;
        case '\x0C': cmdData = ":STATus:FPGA:TMPTUre?"; recMessgFlag = FPGATMP_REQUEST; break;
        case '\x0D': cmdData = ":STATus:BATTERY:TMPTUre?"; recMessgFlag = BATTERYTMP_REQUEST; break;
        default: break;
        }
        break;
    case '\x20' :
        switch(buffer[5])
        {
        case '\x00': cmdData = ":FREQuency:CENTer"; break;
        case '\x01': cmdData = ":FREQuency:CENTer?"; recMessgFlag = CENTERFREQ_REQUEST; break;
        case '\x02': cmdData = ":FREQuency:STARt"; break;
        case '\x03': cmdData = ":FREQuency:STARt?"; recMessgFlag = STARTFREQ_REQUEST; break;
        case '\x04': cmdData = ":FREQuency:STOP"; break;
        case '\x05': cmdData = ":FREQuency:STOP?"; recMessgFlag = STOPFREQ_REQUEST; break;
        case '\x06': cmdData = ":FREQuency:STEP"; break;
        case '\x07': cmdData = ":FREQuency:STEP?"; recMessgFlag = STEPFREQ_REQUEST; break;
        case '\x08': cmdData = "FREQuency:OFFSet"; break;
        case '\x09': cmdData = ":FREQuency:OFFSet?"; recMessgFlag = OFFSETFREQ_REQUEST; break;
        case '\x0A': cmdData = ":FREQuency:SPAN"; break;
        case '\x0B': cmdData = ":FREQuency:SPAN?"; recMessgFlag = SPANFREQ_REQUEST; break;
        case '\x0C': cmdData = ":FREQuency:SPAN:FULL"; break;
        case '\x0D': cmdData = ":FREQuency:SPAN:ZERO"; break;
        case '\x0E': cmdData = ":FREQuency:SPAN:PREVious"; break;
        default: break;
        }
        break;
    case '\x21':
        switch(buffer[5])
        {
        case '\x00': cmdData = ":AMPLitude:SCALe:AUTO"; break;
        case '\x01': cmdData = ":AMPLitude:RLEVel"; break;
        case '\x02': cmdData = ":AMPLitude:RLEVel?"; recMessgFlag = REFLEVEL_REQUEST; break;
        case '\x03': cmdData = ":AMPLitude:SCALe"; break;
        case '\x04': cmdData = ":AMPLitude:SCALe?"; recMessgFlag = SCALE_REQUEST; break;
        case '\x05': cmdData = ":AMPLitude:ATTEnuation:AUTO"; break;
        case '\x06': cmdData = ":AMPLitude:ATTEnuation:AUTO?"; recMessgFlag = ATTENAUTO_REQUEST; break;
        case '\x07': cmdData = ":AMPLitude:ATTEnuation"; break;
        case '\x08': cmdData = ":AMPLitude:ATTEnuation?"; recMessgFlag = ATTEN_REQUEST; break;
        case '\x09': cmdData = ":AMPLitude:PREAmp"; break;
        case '\x0A': cmdData = ":AMPLitude:PREAmp?"; recMessgFlag = PREAMP_REQUEST; break;
        case '\x0B': cmdData = ":AMPLitude:RLEVel:OFFSet"; break;
        case '\x0C': cmdData = ":AMPLitude:RLEVel:OFFSet?"; recMessgFlag = REFOFFSET_REQUEST; break;
        case '\x0D': cmdData = ":AMPLitude:PDIVision"; break;
        case '\x0E': cmdData = ":AMPLitude:PDIVision?"; recMessgFlag = DIVISION_REQUEST; break;
        default: break;
        }
        break;
    case '\x22':
        switch(buffer[5])
        {
        case '\x00': cmdData = ":SWEEp:TIME:AUTO"; break;
        case '\x01': cmdData = ":SWEEp:TIME:AUTO?"; recMessgFlag = SWEEPTIMEAUTO_REQUEST; break;
        case '\x02': cmdData = ":SWEEp:TIME"; break;
        case '\x03': cmdData = ":SWEEp:TIME?"; recMessgFlag = SWEEPTIME_REQUEST; break;
        case '\x04': cmdData = ":SWEEp:CONTinuous"; break;
        case '\x05': cmdData = ":SWEEp:CONTinuous?"; recMessgFlag = COUNTINUOUS_REQUEST; break;
        default: break;
        }
        break;
    case '\x23':
        switch(buffer[5])
        {
        case '\x00': cmdData = ":BANDwidth:RBW:AUTO"; break;
        case '\x01': cmdData = ":BANDwidth:RBW:AUTO?"; recMessgFlag = BANDWIDTH_RBWAUTO_REQUEST; break;
        case '\x02': cmdData = ":BWIDth:RBW:AUTO"; break;
        case '\x03': cmdData = ":BWIDth:RBW:AUTO?"; recMessgFlag = BWIDTH_RBWAUTO_REQUEST; break;
        case '\x04': cmdData = ":BANDwidth:RBW"; break;
        case '\x05': cmdData = ":BANDwidth:RBW?"; recMessgFlag = BANDWIDTH_RBW_REQUEST; break;
        case '\x06': cmdData = ":BWIDth:RBW"; break;
        case '\x07': cmdData = ":BWIDth:RBW?"; recMessgFlag = BWIDTH_RBW_REQUEST; break;
        case '\x08': cmdData = ":BANDwidth:VBW:AUTO"; break;
        case '\x09': cmdData = ":BANDwidth:VBW:AUTO?"; recMessgFlag = BANDWIDTH_VBWAUTO_REQUEST; break;
        case '\x0A': cmdData = ":BWIDth:VBW:AUTO"; break;
        case '\x0B': cmdData = ":BWIDth:VBW:AUTO?"; recMessgFlag = BWIDTH_VBWAUTO_REQUEST; break;
        case '\x0C': cmdData = ":BANDwidth:VBW"; break;
        case '\x0D': cmdData = ":BANDwidth:VBW?"; recMessgFlag = BANDWIDTH_VBW_REQUEST; break;
        case '\x0E': cmdData = ":BWIDth:VBW"; break;
        case '\x0F': cmdData = ":BWIDth:VBW?"; recMessgFlag = BWIDTH_VBW_REQUEST; break;
        case '\x10': cmdData = ":BANDwidth:RATIo"; break;
        case '\x11': cmdData = ":BANDwidth:RATIo?"; recMessgFlag = BANDWIDTH_RATIO_REQUEST; break;
        case '\x12': cmdData = ":BWIDth:RATIo"; break;
        case '\x13': cmdData = ":BWIDth:RATIo?"; recMessgFlag = BWIDTH_RATIO_REQUEST; break;
        case '\x14': cmdData = ":IFOUtput"; break;
        case '\x15': cmdData = ":IFOUtput?"; recMessgFlag = IFOUTPUT_REQUEST; break;
        default: break;
        }
        break;
    case '\x24':
        switch(buffer[5])
        {
        case '\x00': cmdData = ":TRIGger:SOURce"; break;
        case '\x01': cmdData = ":TRIGger:SOURce?"; recMessgFlag = TRIGGER_SOURCE_REQUEST; break;
        case '\x02': cmdData = ":TRIGger:EXTErnal:LEVEl"; break;
        case '\x03': cmdData = ":TRIGger:VEDIo:LEVEl"; break;
        case '\x04': cmdData = ":TRIGger:RFBUrst:LEVEl"; break;
        case '\x05': cmdData = ":TRIGger:EXTErnal:LEVEl?"; recMessgFlag = EXTERNAL_LEVEL_REQUEST; break;
        case '\x06': cmdData = ":TRIGger:VEDIo:LEVEl?"; recMessgFlag = VEDIO_LEVEL_REQUEST; break;
        case '\x07': cmdData = ":TRIGger:RFBUrst:LEVEl?"; recMessgFlag = RFBURST_LEVEL_REQUEST; break;
        case '\x08': cmdData = ":TRIGger:EXTErnal:SLOPe"; break;
        case '\x09': cmdData = ":TRIGger:VEDIo:SLOPe"; break;
        case '\x0A': cmdData = ":TRIGger:RFBUrst:SLOPe"; break;
        case '\x0B': cmdData = ":TRIGger:EXTErnal:SLOPe?"; recMessgFlag = EXTERNAL_SLOPE_REQUEST; break;
        case '\x0C': cmdData = ":TRIGger:VEDIo:SLOPe?"; recMessgFlag = VEDIO_SLOPE_REQUEST; break;
        case '\x0D': cmdData = ":TRIGger:RFBUrst:SLOPe?"; recMessgFlag = RFBURST_SLOPE_REQUEST; break;
        case '\x0E': cmdData = ":TRIGger:EXTErnal:DELAy:STATe"; break;
        case '\x0F': cmdData = ":TRIGger:VEDIo:DELAy:STATe"; break;
        case '\x10': cmdData = ":TRIGger:PERIodic:DELAy:STATe"; break;
        case '\x11': cmdData = ":TRIGger:RFBUrst:DELAy:STATe"; break;
        case '\x12': cmdData = ":TRIGger:EXTErnal:DELAy:STATe?"; recMessgFlag = EXTERNAL_DELAYSTATE_REQUEST; break;
        case '\x13': cmdData = ":TRIGger:VEDIo:DELAy:STATe?"; recMessgFlag = VEDIO_DELAYSTATE_REQUEST; break;
        case '\x14': cmdData = ":TRIGger:PERIodic:DELAy:STATe?"; recMessgFlag = PERIODIC_DELAYSTATE_REQUEST; break;
        case '\x15': cmdData = ":TRIGger:RFBUrst:DELAy:STATe?"; recMessgFlag = RFBURST_DELAYSTATE_REQUEST; break;
        case '\x16': cmdData = ":TRIGger:EXTErnal:DELAy"; break;
        case '\x17': cmdData = ":TRIGger:VEDIo:DELAy"; break;
        case '\x18': cmdData = ":TRIGger:PERIodic:DELAy"; break;
        case '\x19': cmdData = ":TRIGger:RFBUrst:DELAy"; break;
        case '\x1A': cmdData = ":TRIGger:RFBUrst:DELAy?"; recMessgFlag = RFBURST_DELAY_REQUEST; break;
        case '\x1B': cmdData = ":TRIGger:EXTErnal:DELAy?"; recMessgFlag = EXTERNAL_DELAY_REQUEST; break;
        case '\x1C': cmdData = ":TRIGger:VEDIo:DELAy?"; recMessgFlag = VEDIO_DELAY_REQUEST; break;
        case '\x1D': cmdData = ":TRIGger:PERIodic:DELAy?"; recMessgFlag = PERIODIC_DELAY_REQUEST; break;
        case '\x1E': cmdData = ":TRIGger:PERiodic"; break;
        case '\x1F': cmdData = ":TRIGger:PERiodic?"; recMessgFlag = PERIODIC_REQUEST; break;
        default: break;
        }
        break;
    case '\x25':
        switch(buffer[5])
        {
        case '\x00': cmdData = ":TRACe:1:DISPlay"; break;
        case '\x01': cmdData = ":TRACe:2:DISPlay"; break;
        case '\x02': cmdData = ":TRACe:3:DISPlay"; break;
        case '\x03': cmdData = ":TRACe:4:DISPlay"; break;
        case '\x04': cmdData = ":TRACe:5:DISPlay"; break;
        case '\x05': cmdData = ":TRACe:6:DISPlay"; break;
        case '\x06': cmdData = ":TRACe:1:DISPlay?"; recMessgFlag = TRACE1_DISPLAYSTATE_REQUEST; break;
        case '\x07': cmdData = ":TRACe:2:DISPlay?"; recMessgFlag = TRACE2_DISPLAYSTATE_REQUEST; break;
        case '\x08': cmdData = ":TRACe:3:DISPlay?"; recMessgFlag = TRACE3_DISPLAYSTATE_REQUEST; break;
        case '\x09': cmdData = ":TRACe:4:DISPlay?"; recMessgFlag = TRACE4_DISPLAYSTATE_REQUEST; break;
        case '\x0A': cmdData = ":TRACe:5:DISPlay?"; recMessgFlag = TRACE5_DISPLAYSTATE_REQUEST; break;
        case '\x0B': cmdData = ":TRACe:6:DISPlay?"; recMessgFlag = TRACE6_DISPLAYSTATE_REQUEST; break;
        case '\x0C': cmdData = ":TRACe:1:TYPE"; break;
        case '\x0D': cmdData = ":TRACe:2:TYPE"; break;
        case '\x0E': cmdData = ":TRACe:3:TYPE"; break;
        case '\x0F': cmdData = ":TRACe:4:TYPE"; break;
        case '\x10': cmdData = ":TRACe:5:TYPE"; break;
        case '\x11': cmdData = ":TRACe:6:TYPE"; break;
        case '\x12': cmdData = ":TRACe:1:TYPE?"; recMessgFlag = TRACE1_TYPE_REQUEST; break;
        case '\x13': cmdData = ":TRACe:2:TYPE?"; recMessgFlag = TRACE2_TYPE_REQUEST; break;
        case '\x14': cmdData = ":TRACe:3:TYPE?"; recMessgFlag = TRACE3_TYPE_REQUEST; break;
        case '\x15': cmdData = ":TRACe:4:TYPE?"; recMessgFlag = TRACE4_TYPE_REQUEST; break;
        case '\x16': cmdData = ":TRACe:5:TYPE?"; recMessgFlag = TRACE5_TYPE_REQUEST; break;
        case '\x17': cmdData = ":TRACe:6:TYPE?"; recMessgFlag = TRACE6_TYPE_REQUEST; break;
        case '\x18': cmdData = ":TRACe:1:AVECount"; break;
        case '\x19': cmdData = ":TRACe:2:AVECount"; break;
        case '\x1A': cmdData = ":TRACe:3:AVECount"; break;
        case '\x1B': cmdData = ":TRACe:4:AVECount"; break;
        case '\x1C': cmdData = ":TRACe:5:AVECount"; break;
        case '\x1D': cmdData = ":TRACe:6:AVECount"; break;
        case '\x1E': cmdData = ":TRACe:1:AVECount?"; recMessgFlag = TRACE1_AVECOUNT_REQUEST; break;
        case '\x1F': cmdData = ":TRACe:2:AVECount?"; recMessgFlag = TRACE2_AVECOUNT_REQUEST; break;
        case '\x20': cmdData = ":TRACe:3:AVECount?"; recMessgFlag = TRACE3_AVECOUNT_REQUEST; break;
        case '\x21': cmdData = ":TRACe:4:AVECount?"; recMessgFlag = TRACE4_AVECOUNT_REQUEST; break;
        case '\x22': cmdData = ":TRACe:5:AVECount?"; recMessgFlag = TRACE5_AVECOUNT_REQUEST; break;
        case '\x23': cmdData = ":TRACe:6:AVECount?"; recMessgFlag = TRACE6_AVECOUNT_REQUEST; break;
        case '\x24': cmdData = ":TRACe:DETEctor"; break;
        case '\x25': cmdData = ":TRACe:DETEctor?"; recMessgFlag = TRACE_DETECTOR_REQUEST; break;
        case '\x26': cmdData = ":TRACe:DATA?"; recMessgFlag = TRACEDATA_REQUEST; break;
        case '\x27': cmdData = ":TRACe:DATA:RAWData?"; recMessgFlag = TRACEDATA_RAWDATA_REQUEST; break;
        case '\x28': cmdData = ":TRACe:DATA:DRAWdata?"; recMessgFlag = TRACEDATA_DRAWDATA_REQUEST; break;
        case '\x29': cmdData = ":MARKer:SELEct"; break;
        case '\x2A': cmdData = ":MARKer:SELEct?"; recMessgFlag = MARKER_SELECT_REQUEST; break;
        case '\x2B': cmdData = ":MARKer:1:DISPlay"; break;
        case '\x2C': cmdData = ":MARKer:2:DISPlay"; break;
        case '\x2D': cmdData = ":MARKer:3:DISPlay"; break;
        case '\x2E': cmdData = ":MARKer:4:DISPlay"; break;
        case '\x2F': cmdData = ":MARKer:5:DISPlay"; break;
        case '\x30': cmdData = ":MARKer:6:DISPlay"; break;
        case '\x31': cmdData = ":MARKer:1:DISPlay?"; recMessgFlag = MARKER1_DISPLAYSTATE_REQUEST; break;
        case '\x32': cmdData = ":MARKer:2:DISPlay?"; recMessgFlag = MARKER2_DISPLAYSTATE_REQUEST; break;
        case '\x33': cmdData = ":MARKer:3:DISPlay?"; recMessgFlag = MARKER3_DISPLAYSTATE_REQUEST; break;
        case '\x34': cmdData = ":MARKer:4:DISPlay?"; recMessgFlag = MARKER4_DISPLAYSTATE_REQUEST; break;
        case '\x35': cmdData = ":MARKer:5:DISPlay?"; recMessgFlag = MARKER5_DISPLAYSTATE_REQUEST; break;
        case '\x36': cmdData = ":MARKer:6:DISPlay?"; recMessgFlag = MARKER6_DISPLAYSTATE_REQUEST; break;
        case '\x37': cmdData = ":MARKer:1:TYPE"; break;
        case '\x38': cmdData = ":MARKer:2:TYPE"; break;
        case '\x39': cmdData = ":MARKer:3:TYPE"; break;
        case '\x3A': cmdData = ":MARKer:4:TYPE"; break;
        case '\x3B': cmdData = ":MARKer:5:TYPE"; break;
        case '\x3C': cmdData = ":MARKer:6:TYPE"; break;
        case '\x3D': cmdData = ":MARKer:1:TYPE?"; recMessgFlag = MARKER1_TYPE_REQUEST; break;
        case '\x3E': cmdData = ":MARKer:2:TYPE?"; recMessgFlag = MARKER2_TYPE_REQUEST; break;
        case '\x3F': cmdData = ":MARKer:3:TYPE?"; recMessgFlag = MARKER3_TYPE_REQUEST; break;
        case '\x40': cmdData = ":MARKer:4:TYPE?"; recMessgFlag = MARKER4_TYPE_REQUEST; break;
        case '\x41': cmdData = ":MARKer:5:TYPE?"; recMessgFlag = MARKER5_TYPE_REQUEST; break;
        case '\x42': cmdData = ":MARKer:6:TYPE?"; recMessgFlag = MARKER6_TYPE_REQUEST; break;
        case '\x43': cmdData = ":MARKer:TO:CENTer"; break;
        case '\x44': cmdData = ":MARKer:TO:STARt"; break;
        case '\x45': cmdData = ":MARKer:TO:STOP"; break;
        case '\x46': cmdData = ":MARKer:1:X"; break;
        case '\x47': cmdData = ":MARKer:2:X"; break;
        case '\x48': cmdData = ":MARKer:3:X"; break;
        case '\x49': cmdData = ":MARKer:4:X"; break;
        case '\x4A': cmdData = ":MARKer:5:X"; break;
        case '\x4B': cmdData = ":MARKer:6:X"; break;
        case '\x4C': cmdData = ":MARKer:1:X?"; recMessgFlag = MARKER1_X_REQUEST; break;
        case '\x4D': cmdData = ":MARKer:2:X?"; recMessgFlag = MARKER2_X_REQUEST; break;
        case '\x4E': cmdData = ":MARKer:3:X?"; recMessgFlag = MARKER3_X_REQUEST; break;
        case '\x4F': cmdData = ":MARKer:4:X?"; recMessgFlag = MARKER4_X_REQUEST; break;
        case '\x50': cmdData = ":MARKer:5:X?"; recMessgFlag = MARKER5_X_REQUEST; break;
        case '\x51': cmdData = ":MARKer:6:X?"; recMessgFlag = MARKER6_X_REQUEST; break;
        case '\x52': cmdData = ":MARKer:1:FCOUnt:STATe"; break;
        case '\x53': cmdData = ":MARKer:2:FCOUnt:STATe"; break;
        case '\x54': cmdData = ":MARKer:3:FCOUnt:STATe"; break;
        case '\x55': cmdData = ":MARKer:4:FCOUnt:STATe"; break;
        case '\x56': cmdData = ":MARKer:5:FCOUnt:STATe"; break;
        case '\x57': cmdData = ":MARKer:6:FCOUnt:STATe"; break;
        case '\x58': cmdData = ":MARKer:1:FCOUnt:STATe?"; recMessgFlag = MARKER1_FREQCOUNTSTATE_REQUEST; break;
        case '\x59': cmdData = ":MARKer:2:FCOUnt:STATe?"; recMessgFlag = MARKER2_FREQCOUNTSTATE_REQUEST; break;
        case '\x5A': cmdData = ":MARKer:3:FCOUnt:STATe?"; recMessgFlag = MARKER3_FREQCOUNTSTATE_REQUEST; break;
        case '\x5B': cmdData = ":MARKer:4:FCOUnt:STATe?"; recMessgFlag = MARKER4_FREQCOUNTSTATE_REQUEST; break;
        case '\x5C': cmdData = ":MARKer:5:FCOUnt:STATe?"; recMessgFlag = MARKER5_FREQCOUNTSTATE_REQUEST; break;
        case '\x5D': cmdData = ":MARKer:6:FCOUnt:STATe?"; recMessgFlag = MARKER6_FREQCOUNTSTATE_REQUEST; break;
        case '\x5E': cmdData = ":MARKe:1:NOISe:STATe"; break;
        case '\x5F': cmdData = ":MARKe:2:NOISe:STATe"; break;
        case '\x60': cmdData = ":MARKe:3:NOISe:STATe"; break;
        case '\x61': cmdData = ":MARKe:4:NOISe:STATe"; break;
        case '\x62': cmdData = ":MARKe:5:NOISe:STATe"; break;
        case '\x63': cmdData = ":MARKe:6:NOISe:STATe"; break;
        case '\x64': cmdData = ":MARKer:1:NOISe:STATe?"; recMessgFlag = MARKER1_NOISESTATE_REQUEST; break;
        case '\x65': cmdData = ":MARKer:2:NOISe:STATe?"; recMessgFlag = MARKER2_NOISESTATE_REQUEST; break;
        case '\x66': cmdData = ":MARKer:3:NOISe:STATe?"; recMessgFlag = MARKER3_NOISESTATE_REQUEST; break;
        case '\x67': cmdData = ":MARKer:4:NOISe:STATe?"; recMessgFlag = MARKER4_NOISESTATE_REQUEST; break;
        case '\x68': cmdData = ":MARKer:5:NOISe:STATe?"; recMessgFlag = MARKER5_NOISESTATE_REQUEST; break;
        case '\x69': cmdData = ":MARKer:6:NOISe:STATe?"; recMessgFlag = MARKER6_NOISESTATE_REQUEST; break;
        case '\x6A': cmdData = ":MARKer:PMAXimum"; break;
        case '\x6B': cmdData = ":MARKer:PMINimum"; break;
        case '\x6C': cmdData = ":MARKer:PMAXimum:NEXT"; break;
        case '\x6D': cmdData = ":MARKer:PMAXimum:LEFT"; break;
        case '\x6E': cmdData = ":MARKer:PMAXimum:RIGHt"; break;
        case '\x6F': cmdData = ":MARKer:PTRAck"; break;
        case '\x70': cmdData = ":MARKer:PTRAck?"; recMessgFlag = MARKER_PEAKTRACESTATE_REQUEST; break;
        case '\x71': cmdData = ":MARKer:ALLClear"; break;
        case '\x72': cmdData = ":PEAkPOInt:FReq?"; recMessgFlag = PEAKPOINT_FREQ_REQUEST; break;
        case '\x73': cmdData = ":PEAkPOInt:Amp?"; recMessgFlag = PEAKPOINT_AMP_REQUEST; break;
        default: break;
        }
        break;
    default:
        break;
    }

    if(tmpData)
    {
        cmdData += " ";
        cmdData += QString::number(tmpData,10);
    }
    cmdData += "\n";

    return cmdData;
}

/**
 * @brief cmdDataProcess
 * @param rcvData
 * @return
 */
QString cmdDataProcess(QByteArray rcvData)
{
    QString retStr;
    retStr.clear();

    if(m_bDataSplicingFlg)//上一次数据需要和本次数据合并
    {
        rcvData.insert(0,m_tmpData);
        m_tmpData.clear();
    }
    int nLen = 0 ;
    while(1)
    {
        nLen = rcvData.size();
        if(nLen >=  10)     //10 = (头) 3c 3c3c3c + （指令）00 00 + (长度)00 00  + (校验) 00 00 + (结束) f3
        {
            if(('\x3c' ==rcvData[0])&&('\x3c' == rcvData[1]) &&('\x3c' == rcvData[2] )&&('\x3c' == rcvData[3]))
            {
                qDebug()<<"Error Data "<<m_errData.toHex() <<endl;
                m_errData.clear();

                quint16 nCmdDataSize = 0;

#ifdef LEN_HEIGHT_LOW // 指令长度高字节在前低字节在后
nCmdDataSize = QByteArrayByHightLToqint16(rcvData,6);
#endif
#ifdef LEN_LOW_HEIGHT// 指令长度低字节在前高字节在后
nCmdDataSize = QByteArrayByLowHToqint16(rcvData,6);
#endif
                if(nLen>= 4 + 2 + 2 + nCmdDataSize + 2+1)
                {
                    if('\xf3' == rcvData[4 + 2 + 2 + nCmdDataSize + 2])
                    {
                        QByteArray commandData = rcvData.left(4 + 2 + 2 + nCmdDataSize + 2 + 1);

                        qDebug()<<"Command Data "<<commandData.toHex() <<endl;
                        retStr = analysisCommand(commandData);
                        rcvData.remove(0,4 + 2 + 2 + nCmdDataSize + 2 + 1);
                    }
                    else //Error Command
                    {
                        m_errData.append(rcvData[0]);
                        rcvData.remove(0,1);
                        continue;
                    }
                }
                else break;
            }
            else
            {
                m_errData.append(rcvData[0]);
                rcvData.remove(0,1);
            }
        }
        else break;
    }

    nLen = rcvData.size();
    if(0 <nLen)
    {
        m_tmpData.append(rcvData);
        m_bDataSplicingFlg = true;
    }
    else  //0 is complete
    {
        m_bDataSplicingFlg = false;
    }
    return retStr;
}
