#ifndef DATA_CONVERSION_H
#define DATA_CONVERSION_H
#include <QObject>

#ifdef __cplusplus
    extern "C" {
#endif

    void QStringToHexQByteArray(QString &str, QByteArray &byteData);
    char CharToHexChar(char ch);


    void qint32ToQByteArrayByHightL(qint32 nData,QByteArray &array);
    void qint32ToQByteArrayByLowH(qint32 nData,QByteArray &array);

    void qint16ToQByteArrayByHightL(quint16 nData,QByteArray &array);
    void qint16ToQByteArrayByLowH(quint16 nData,QByteArray &array);

    qint32 QByteArrayByLowHToqint32(QByteArray bytes,qint32 nBegin);
    qint32 QByteArrayByHightLToqint32(QByteArray bytes,qint32 nBegin);

    qint16 QByteArrayByLowHToqint16(QByteArray bytes,qint32 nBegin);
    qint16 QByteArrayByHightLToqint16(QByteArray bytes,qint32 nBegin);

    QString QByteArrayToqQString(QByteArray bytes,qint32 nBegin,qint32 nLen);
    qint32 QByteArrayToInt(QByteArray bytes,qint32 nBegin,qint32 nLen);
#ifdef __cplusplus
    }
#endif
#endif // DATA_CONVERSION_H
