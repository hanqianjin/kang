#ifndef __MSG_DICT__
#define __MSG_DICT__

#include "BitVisaType.h"

typedef struct Noticmsg
{
	DiInt16 npflag;
	DiInt16 ntype;
	DiInt16 keep;
	DiInt16 source;
	DiInt16 logicmode;
	DiInt16 keepex;
	DiInt16 index;//对应信息字典“索引”
}NOTICMSG,*PNOTICMSG;
extern NOTICMSG noticobj;

/**
 * @brief initNoticeCode
 * @param source
 * @param logicmode
 */
void initNoticeCode(DiInt16 source,DiInt16 logicmode);

/**
 * @brief setNoticeCode
 * @param npflag
 * @param ntype
 * @param dictIndex
 */
void setNoticePara(DiInt16 npflag, DiInt16 ntype,DiInt16 dictIndex);

 /**
 * @brief GetNoticeCode
 * @return NoticeCode
 */
DiUInt32 GetNoticeCode();

//Sign
enum{
    NOTIC_MESSAGE = 0,
    WARNING_EXCEPTION_MESSAGE,
};

//Message Type
enum{
    EXECUTE_WARNING = 0,
    EXECUTE_ERR_EXCEPTION,
    SYSTEM_ERR,
    SCRIPT_ERR,
};

//Notice Message Source
enum{
    SA_MODU = 0,
    RTSA_MODU,
    IA_MODU,
    PM_MODU,
    LTEFDD_MODU,
    LTETDD_MODU,
    FIFTHGNR_MODU,
};

//Notice Message Logic Mode
enum{
    CONTROL_PROGRAM = 0,
    APPLICATION_PROGRAM,
};

//Message Dict Index
enum{
    NO_ERR = 0,
    FILEOPEN_ERR,
    FILEWRITE_ERR,
    FILEREAD_ERR,
};
#endif
