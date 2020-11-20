/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:macrobus.h
** Latest Version: V0.0.1
** Latest modified Date:  2018-12-13
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2018-12-13
** Descriptions:such as error msg;
**
*********************************************************************************************************/
#ifndef MACROBUS_H
#define MACROBUS_H
#include <QObject>

static qint64 PLF_FREQ_UNIT_MULTIPLE[] = {1,//PLF_Hz
                                          1000,//PLF_KHZ
                                          1000000,//PLF_MHZ
                                          1000000000};//PLF_GHZ
static qreal PLF_TIME_UNIT_MULTIPLE[] = {1/1000000,//PLF_NS
                                         1/1000,     //PLF_US
                                         1,  //PLF_MS
                                         1000,//PLT_S
};

qint32 plf_compre_frequnit(QString ustr);

qreal plt_compre_timeunit(QString ustr);
qint32 plf_compre_amptunit(QString ustr);

#endif // MACROBUS_H
