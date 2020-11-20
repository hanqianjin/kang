/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:loadctrlrunparam.cpp
** Latest Version: V0.0.1
** Latest modified Date:  2018-12-14
** Modified by:
** Descriptions:
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2018-12-14
** Descriptions:load all mode ctrl app msg from .ini
**
*********************************************************************************************************/
#include "loadctrlrunparam.h"
#include <QFile>
#include <QSettings>
#include "qdebug.h"

/**
* @class loadctrlrunparam
* @brief for open or close ctrl app
*/
loadctrlrunparam::loadctrlrunparam()
{  
  if(iniallmodectrlpath() < 0)
    {
      qFatal("param failed");
    }
}

/**
 * @brief load all modes ctrl app path for switching
 * @return under zero means error
 * @note [pctrlpathvec will be extended when add a new ctrl]
 * @author steve
 * @since {2018-12-14}
*/
qint32 loadctrlrunparam::iniallmodectrlpath()
{
  QSettings *pconHandle = new QSettings("platiniconfig.ini", QSettings::IniFormat);
  sactrlpath = pconHandle->value("/SAPATH/sactrlpath").toString();
  pctrlpathvec.append(sactrlpath);

  rtsactrlpath = pconHandle->value("/RTSAPATH/rtsactrlpath").toString();
  pctrlpathvec.append(rtsactrlpath);

  pctrlpathvec.append("bit");
  pctrlpathvec.append("bit");

  ltefddctrlpath = pconHandle->value("/LTEFDDPATH/ltefddpath").toString();
  pctrlpathvec.append(ltefddctrlpath);

  ltetddctrlpath = pconHandle->value("/LTETDDPATH/ltetddpath").toString();
  pctrlpathvec.append(ltetddctrlpath);

  /**
* @class
* @brief
* @since {2019-09-17}
*/
  fgnrctrlpath = pconHandle->value("/FGNRPATH/fgnrpath").toString();
  pctrlpathvec.append(fgnrctrlpath);
  delete pconHandle;
  return 0;
}
