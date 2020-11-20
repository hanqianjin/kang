#include "msgNoticeCode.h"

NOTICMSG noticobj;

/**
 * @brief initNoticeCode
 * @param source
 * @param logicmode
 */
void initNoticeCode(DiInt16 source,DiInt16 logicmode)
{
    noticobj.logicmode = logicmode&0x0001;
    noticobj.source    = source&0x001f;
}

/**
 * @brief setNoticePara
 * @param npflag
 * @param ntype
 * @param dictIndex
 */
void setNoticePara(DiInt16 npflag, DiInt16 ntype,DiInt16 dictIndex)
{
    noticobj.npflag = npflag&0x0001;
    noticobj.ntype  = ntype&0x0003;
    noticobj.index  = dictIndex&0x0fff;
}

/**
 * @brief GetNoticeCode
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
