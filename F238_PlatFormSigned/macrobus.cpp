/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-02-13
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-02-13
** Descriptions: common algorithm
**
*********************************************************************************************************/
#include "macrobus.h"

static const QString bitfrequnit[] = {"Hz","kHz","MHz","GHz"};
/**
 * @brief get unit index for back to Hz
 * @param[in]
 * @param[in]
 * @return  0Hz 1kHz 2MHz 3GHz ...
 * @note <0 uninclude
 * @author steve
 * @since {2019-02-13}
*/
qint32 plf_compre_frequnit(QString ustr)
{
  qint32 ilen = sizeof(bitfrequnit) / sizeof(QString);
  qint32 i = 0;
  for(i = 0;i < ilen;i++)
    {
      if(bitfrequnit[i] == ustr)
        {
          return i;
        }
    }
  return -1;
}