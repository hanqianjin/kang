#ifndef MSG_DICT
#define MSG_DICT

#include <QObject>
#include "rtsa_status_code.h"

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

typedef struct Noticmsg
{
    short npflag;
    short ntype;
    short keep;
    short source;
    short logicmode;
    short keepex;
    short index;//对应信息字典“索引”
}NOTICMSG,*PNOTICMSG;
extern NOTICMSG noticobj;

/**
 * @brief initNoticeCode
 * @param source
 * @param logicmode
 */
void initNoticeCode(qint16 logicmode = APPLICATION_PROGRAM);

/**
 * @brief setNoticeCode
 * @param npflag
 * @param ntype
 * @param dictIndex
 */
 void setNoticePara(qint16 npflag, qint16 ntype,qint16 dictIndex, qint16 source = SA_MODU);

 /**
 * @brief GetNoticeCode
 * @param notichandle
 * @return
 */
quint32 GetNoticeCode();

#define REDIRECT_YES 1
#define REDIRECT_NO  0
#define WRITESHM_YES 1
#define WRITESHM_NO  0

/**
 * @brief errorOutput
 * @param redirectFlag
 * @param writeShmFlag
 */
void errorOutput(bool redirectFlag = REDIRECT_YES,bool writeShmFlag = WRITESHM_YES);

#endif
