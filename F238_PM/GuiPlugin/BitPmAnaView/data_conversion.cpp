#include "data_conversion.h"


//基本和单片机交互 数据 都是16进制的 我们这里自己写一个的函数
/**
* @brief	 Qstring 转为 16进制
* @note
* @Author	ROC
* @date     2019.12.12
*/

void QStringToHexQByteArray(QString &str, QByteArray &byteData)
{
    int hexdata,lowhexdata;
    int hexdatalen = 0;
    int len = str.length();
    byteData.resize(len/2);
    char lstr,hstr;
    for(int i=0; i<len; )
    {
        //char lstr,
        hstr=str[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        if(i >= len)
            break;
        lstr = str[i].toLatin1();
        hexdata = CharToHexChar(hstr);
        lowhexdata = CharToHexChar(lstr);
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata*16+lowhexdata;
        i++;
        byteData[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    byteData.resize(hexdatalen);
}
/**
* @brief	char 转为 16进制
* @note
* @Author	ROC
* @date     2019.12.12
*/
char CharToHexChar(char ch)
{
    /*
        0x30等于十进制的48，48也是0的ASCII值，，
        1-9的ASCII值是49-57，，所以某一个值－0x30，，
        就是将字符0-9转换为0-9

        */
    if((ch >= '0') && (ch <= '9'))
        return ch-0x30;
    else if((ch >= 'A') && (ch <= 'F'))
        return ch-'A'+10;
    else if((ch >= 'a') && (ch <= 'f'))
        return ch-'a'+10;
    else return (-1);
}

/**
* @brief	qint32 转换为QByteArray  按照从高位到低位数据排列
* @note
* @Author	ROC
* @date     2019.12.12
*/
void qint32ToQByteArrayByHightL(qint32 nData,QByteArray &array)
{
    QByteArray bytes;
    bytes.resize(sizeof(qint32));
    bytes[0] = (unsigned char)((0xff000000 & nData) >> 24);
    bytes[1] = (unsigned char)((0x00ff0000 & nData) >> 16);
    bytes[2] = (unsigned char)((0x0000ff00 & nData) >> 8);
    bytes[3] = (unsigned char)(0x000000ff & nData);
    array.append(bytes[0]);
    array.append(bytes[1]);
    array.append(bytes[2]);
    array.append(bytes[3]);
}

/**
* @brief	qint32 转换为QByteArray  按照从低位到高位数据排列
* @note
* @Author	ROC
* @date     2019.12.12
*/
void qint32ToQByteArrayByLowH(qint32 nData,QByteArray &array)
{
    QByteArray bytes;
    bytes.resize(sizeof(qint32));
    bytes[0] = (unsigned char)((0xff000000 & nData) >> 24);
    bytes[1] = (unsigned char)((0x00ff0000 & nData) >> 16);
    bytes[2] = (unsigned char)((0x0000ff00 & nData) >> 8);
    bytes[3] = (unsigned char)(0x000000ff & nData);
    array.append(bytes[3]);
    array.append(bytes[2]);
    array.append(bytes[1]);
    array.append(bytes[0]);
}

/**
* @brief	qint16转换为QByteArray  按照从高位到低位数据排列
* @note
* @Author	ROC
* @date     2019.12.12
*/
void qint16ToQByteArrayByHightL(quint16 nData,QByteArray &array)
{
    QByteArray bytes;
    bytes.resize(sizeof(quint16));
    bytes[0] = (unsigned char)((0xff00 & nData) >> 8);
    bytes[1] = (unsigned char)(0x00ff & nData);
    array.append(bytes[0]);
    array.append(bytes[1]);
}

/**
* @brief	qint16转换为QByteArray  按照从低位到高位数据排列
* @note     array.append(bytes[1]);   ->  array.append(bytes[0]);
* @Author	ROC
* @date     2019.12.12
*/
void qint16ToQByteArrayByLowH(quint16 nData,QByteArray &array)
{
    QByteArray bytes;
    bytes.resize(sizeof(quint16));
    bytes[0] = (unsigned char)((0xff00 & nData) >> 8);
    bytes[1] = (unsigned char)(0x00ff & nData);
    array.append(bytes[1]);
    array.append(bytes[0]);
}

/**
* @brief	QByteArray转换为qint32   按照从低位到高位数据排列
* @note
* @Author	ROC
* @date     2019.12.12
*/
qint32 QByteArrayByLowHToqint32(QByteArray bytes,qint32 nBegin)
{
//    qint16 addr =   bytes[nBegin + 0]       & 0x00FF;
//    addr       |= ((bytes[nBegin + 1] << 8) & 0xFF00);
        qint32 addr = bytes[nBegin + 0] & 0x000000FF;
        addr |= ((bytes[nBegin + 1] << 8) & 0x0000FF00);
        addr |= ((bytes[nBegin + 2] << 16) & 0x00FF0000);
        addr |= ((bytes[nBegin + 3] << 24) & 0xFF000000);
    return addr;
}

/**
* @brief	QByteArray转换为qint32   按照从高位到低位数据排列
* @note
* @Author	ROC
* @date     2019.12.12
*/
qint32 QByteArrayByHightLToqint32(QByteArray bytes,qint32 nBegin)
{
    qint32 addr = bytes[nBegin + 3] & 0x000000FF;
    addr |= ((bytes[nBegin + 2] << 8) & 0x0000FF00);
    addr |= ((bytes[nBegin + 1] << 16) & 0x00FF0000);
    addr |= ((bytes[nBegin + 0] << 24) & 0xFF000000);
    return addr;
}

/**
* @brief	QByteArray转换为qint16   按照从低位到高位数据排列
* @note
* @Author	ROC
* @date     2019.12.12
*/
qint16 QByteArrayByLowHToqint16(QByteArray bytes,qint32 nBegin)
{
    qint16 addr;
    addr  =   bytes[nBegin + 0]       & 0x00FF;
    addr |= ((bytes[nBegin + 1] << 8) & 0xFF00);
    return addr;
}
/**
* @brief	QByteArray转换为qint16   按照从高位到低位数据排列
* @note
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
* @brief	将ByteArray前N个字符转换为字符串
* @note
* @Author	ROC
* @date     2020.1.3
*/
QString QByteArrayToqQString(QByteArray bytes,qint32 nBegin,qint32 nLen)
{
    QByteArray tempBytes = bytes;
    QString strReturn;
    tempBytes.remove(0,nBegin);
   strReturn =  tempBytes.left(nLen);

    return strReturn;
}

/**
* @brief	将ByteArray前N个字符转换为字符串
* @note
* @Author	ROC
* @date     2020.1.3
*/
qint32 QByteArrayToInt(QByteArray bytes,qint32 nBegin,qint32 nLen)
{
    QByteArray tempBytes = bytes;
    qint32 nReturn;
    tempBytes.remove(0,nBegin);
      QString strTemp = tempBytes.left(nLen);
    nReturn =  strTemp.toInt();

    return nReturn;
}
