#include "msgNoticeCode.h"
#include <QObject>

NOTICMSG noticobj;

/**
 * @brief initNoticeCode
 * @param logicmode
 */
void initNoticeCode(qint16 logicmode)
{
  noticobj.logicmode = logicmode & 0x0001;
}

/**
 * @brief setNoticePara
 * @param npflag
 * @param ntype
 * @param dictIndex
 */
void setNoticePara(qint16 npflag, qint16 ntype, qint16 dictIndex, qint16 source)
{
  noticobj.npflag = npflag & 0x0001;
  noticobj.ntype  = ntype & 0x0003;
  noticobj.source = source & 0x001f;
  noticobj.index  = dictIndex & 0x0fff;
}

/**
 * @brief GetNoticeCode
 * @param notichandle
 * @return NoticeCode
 */
quint32 GetNoticeCode()
{
  quint32 NoticeCode = 0;
  NoticeCode |= ((quint32)noticobj.npflag)<<31;
  NoticeCode |= ((quint32)noticobj.ntype)<<29;
  NoticeCode |= ((quint32)noticobj.source)<<20;
  NoticeCode |= ((quint32)noticobj.logicmode)<<19;
  NoticeCode |= noticobj.index;
  return NoticeCode;
}
