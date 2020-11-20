/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-10-14
** Modified by:
** Descriptions:create the whole software exception and notice msg mechanism
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-10-14
** Descriptions:
**
*********************************************************************************************************/
#include "excenoti.h"
#include "pltdictionary/pltsadiction.h"
#include "pltdictionary/pltrtsadiction.h"
#include "pltdictionary/pltfdddiction.h"
#include "pltdictionary/pltfgnrdiction.h"
#include "pltdictionary/plthomediction.h"
#include "pltdictionary/pltiadiction.h"
#include "pltdictionary/pltpmdiction.h"
#include "pltdictionary/pltsysctrldiction.h"
#include "pltdictionary/plttdddiction.h"
#include "pltdictionary/pltdiction.h"

excenoti::excenoti()
{

}

void excenoti::anaexcenoticode(quint32 code)
{
  if(0 == code)
    {
      return;
    }
  getexecnotihandle()->codemsg.npflag = static_cast<short>((0x80000000 & code) >> 31);
  getexecnotihandle()->codemsg.ntype = static_cast<short>((0x60000000 & code) >> 29);
  getexecnotihandle()->codemsg.source = static_cast<short>((0x01f00000 & code) >> 20);
  getexecnotihandle()->codemsg.logicmode = static_cast<short>((0x00080000 & code) >> 19);
  getexecnotihandle()->codemsg.index = static_cast<short>(0x00000fff & code);
  return;
}

excenoti* excenoti::innernotic = new excenoti();
excenoti *excenoti::getexecnotihandle()
{
  return innernotic;
}

const char* excenoti::alldictionary[][220] = {
  //sa
  PLTSADICT
  //rtsa
  PLTRTSADICT
  //ia
  PLTIADICT
  //pm
  PLTPMDICT
  //ltefdd
  PLTFDDDICT
  //ltetdd
  PLTTDDDICT
  //fgnr
  PLTFGNRDICT
  //reverse 7~15
  {NULL},{NULL},{NULL},{NULL},{NULL},{NULL},{NULL},{NULL},{NULL},
  //sysctrl
  PLTSYSDICT
  //home
  PLTHOMEDICT
  //plt itself
  PLTDICT
};

const char* excenoti::unknowdic[] = {
  "unkown notice msg"
};

short excenoti::execsumlist[] =
{
  204,//sa
  53,//rtsa
  0,//ia
  0,//pm
  0,//fdd
  0,//tff
  0,//fgnr
  0,0,0,0,0,0,0,0,0,
  41,//sysctrl
  8,//home
  22,//plt itself
};
//const PPLTCODEUNIT excenoti::alldictionary[] =
//{
//  //sa
//  {
//    {0,"sa param1 error"},
//    {1,"sa param2 error"},
//    {2,"sa param3 error"},
//    NULL,
//  },
//  //rtsa
//  {
//    {0,"sa param1 error"},
//    {1,"sa param2 error"}
//  }
//};
