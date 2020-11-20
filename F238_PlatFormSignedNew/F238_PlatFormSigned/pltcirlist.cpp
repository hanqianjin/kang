/****************************************Copyright (c)****************************************************
**
**                     DaHao Info Co.,Ltd.
**
**--------------File Info---------------------------------------------------------------------------------
** File name:
** Latest Version: V0.0.1
** Latest modified Date:  2019-10-15
** Modified by:
** Descriptions:for multi language to convert for saving history source and index msg
**
**--------------------------------------------------------------------------------------------------------
** Created by: BitYang
** Created date: 2019-10-15
** Descriptions:
**
*********************************************************************************************************/
#include "pltcirlist.h"

pltcirlist::pltcirlist(quint32 inum)
{
  plastest = NULL;
  capacity = 0;
  count = 0;
  if(inum)
    {
      plastest = new PLTCIRNODE[inum];
      quint32 i = 0;
      //build double direct circle list
      for(i = 0;i < inum - 1;i++)
        {
          (plastest + i)->pnext = plastest + i + 1;
          (plastest + inum - 1 - i)->plast = plastest + inum - 2 - i;
        }
      (plastest + inum - 1)->pnext = plastest;
      plastest->plast = plastest + inum - 1;
      capacity = inum;
    }
}

pltcirlist::~pltcirlist()
{
  if(plastest)
    {
      delete plastest;
      plastest = NULL;
    }
}

/**
 * @brief plastest point the first invalid node
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-15}
*/
void pltcirlist::InsertNodeValue(qint32 np, qint32 is, qint32 in)
{
  if(plastest)
    {
      plastest->npflag = np;
      plastest->isource = is;
      plastest->index = in;
      plastest = plastest->pnext;
      count++;
      count = count > capacity ? capacity : count;
    }
}

/**
 * @brief LIFO
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-15}
*/
PPLTCITNODE pltcirlist::GetNodeByStack(qint32 index)
{
  if(index >= count || index >= capacity)
    return NULL;
  ptemp = plastest->plast;
  qint32 i = 1;
  for(i = 1;i <= index;i++)
  {
    ptemp = ptemp->plast;
  }
  return ptemp;
}

/**
 * @brief FIFO
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-15}
*/
PPLTCITNODE pltcirlist::GetNodeByQueue(qint32 index)
{
  if(index >= count || index >= capacity)
    return NULL;
  ptemp = plastest->plast;
  qint32 i = 1;
  for(i = 1;i < count;i++)
    {
      ptemp = ptemp->plast;
    }
  for(i = 0;i < index;i++)
    {
      ptemp = ptemp->pnext;
    }
  return ptemp;
}

/**
 * @brief
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-15}
*/
void pltcirlist::Clear()
{
   count = 0;
}

/**
 * @brief the capacity of the list,decided after init
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-15}
*/
qint32 pltcirlist::Capacity()
{
  return capacity;
}

/**
 * @brief the num of node
 * @param[in]
 * @param[in]
 * @return
 * @note
 * @since {2019-10-15}
*/
qint32 pltcirlist::Count()
{
  return count;
}
