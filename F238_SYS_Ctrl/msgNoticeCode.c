#include "msgNoticeCode.h"


NOTICMSG noticobj;

/**
 * @brief initNoticeCode
 * @param logicmode
 */
void initNoticeCode(DiInt16 logicmode)
{
  noticobj.logicmode = logicmode & 0x0001;
}

/**
 * @brief setNoticePara
 * @param npflag
 * @param ntype
 * @param dictIndex
 */
void setNoticePara(DiInt16 npflag, DiInt16 ntype, DiInt16 dictIndex, DiInt16 source)
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
DiUInt32 GetNoticeCode()
{
  DiUInt32 NoticeCode = 0;
  NoticeCode |= ((DiUInt32)noticobj.npflag)<<31;
  NoticeCode |= ((DiUInt32)noticobj.ntype)<<29;
  NoticeCode |= ((DiUInt32)noticobj.source)<<20;
  NoticeCode |= ((DiUInt32)noticobj.logicmode)<<19;
  NoticeCode |= noticobj.index;
  return NoticeCode;
}
