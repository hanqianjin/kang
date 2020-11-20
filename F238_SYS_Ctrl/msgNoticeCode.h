#ifndef MSG_DICT
#define MSG_DICT

#include "BitVisaType.h" 

//Sign
enum{
    NOTIC_MESSAGE = 0,
    WARNING_EXCEPTION_MESSAGE
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

typedef struct Noticmsg
{
    short npflag;
    short ntype;
    short keep;
    short source;
    short logicmode;
    short keepex;
    short index;//diction index
}NOTICMSG,*PNOTICMSG;
extern NOTICMSG noticobj;

/**
 * @brief initNoticeCode
 * @param source
 * @param logicmode
 */
void initNoticeCode(DiInt16 logicmode);

/**
 * @brief setNoticeCode
 * @param npflag
 * @param ntype
 * @param dictIndex
 */
 void setNoticePara(DiInt16 npflag, DiInt16 ntype,DiInt16 dictIndex, DiInt16 source);

 /**
 * @brief GetNoticeCode
 * @param notichandle
 * @return
 */
DiUInt32 GetNoticeCode();
#endif
