#ifndef AUTOPRODUCTCOMMAND_H
#define AUTOPRODUCTCOMMAND_H

#include <QByteArray>

extern bool  m_bDataSplicingFlg; //数据拼接标志
extern QByteArray m_tmpData;   //临时数据
extern QByteArray m_errData;   //错误数据

QByteArray cmdDataSend(int indexFlg,QByteArray sendData);
QByteArray cmdDataProcess(QByteArray rcvData);


#endif // AUTOPRODUCTCOMMAND_H
