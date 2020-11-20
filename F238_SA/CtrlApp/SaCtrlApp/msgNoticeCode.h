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
 * @param notichandle
 * @return
 */
DiUInt32 GetNoticeCode();

#define REDIRECT_YES 1
#define REDIRECT_NO  0
#define WRSHM_YES    1
#define WRSHM_NO     0

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
    SA_Shm_Init = 0,
    SA_ShmGetID_startflag,
    SA_ShmGetAddr_startflag,
    SA_ShmGetID_basctrl,
    SA_ShmGetAddr_basctrl,
    SA_ShmGetID_configsweep,
    SA_ShmGetAddr_configsweep,
    SA_ShmGetID_configmeasure,
    SA_ShmGetAddr_configmeasure,
    SA_ShmGetID_sweepdata,
    SA_ShmGetAddr_sweepdata,
    SA_ShmGetID_measuredata,
    SA_ShmGetAddr_measuredata,
    SA_ShmGetID_sync,
    SA_ShmGetAddr_sync,
    SA_ShmGetID_configupdate,
    SA_ShmGetAddr_configupdate,
    SA_ShmGetID_channelparam,
    SA_ShmGetAddr_channelparam,
    SA_ShmGetID_fftfircommonnum,
    SA_ShmGetAddr_fftfircommonnum,
    SA_ShmGetID_sweepnum,
    SA_ShmGetAddr_sweepnum,
    SA_ShmGetID_tempercalc,
    SA_ShmGetAddr_tempercalc,

    SA_Sweepinterrupt_Init,
    SA_MemMap_Init,
    SA_FreqCntInterrupt_Init,
    SA_Sm_syncHandle_Create,
    SA_Sm_syncHandle_Init,
    SA_Sm_guiHandle_Create,
    SA_Sm_guiHandle_Init,
    SA_Sm_sweepHandle_Create,
    SA_Sm_sweepHandle_Init,
    SA_FreqCount_Thread_Init,
    SA_MidMsg_Thread_Init,
    SA_DataAcq_Thread_Init,
    SA_Sweep_Thread_Init,
    SA_RF_Init,
    SA_FreqMode_Init,
    SA_CALCData_Load,
    SA_IF_ATTEN,
    SA_RF_Path,
    SA_ZEROFRE_AMPAtten,
    SA_SECMEDFRE_Atten,
    SA_ZEROFRE_Phase,
    SA_LOW_PREAtten,
    SA_LOW_FRONTGate,
    SA_HIGH_PREAtten,
    SA_HIGH_FRONTGate,
    SA_LO_Control,
    SA_RBW,
    SA_VBW,
    SA_DETECTORMode,
    SA_DATAPROMode,
    SA_SWPStart,
    SA_ZEROSPANFlag,
    SA_DOTSWPTime,
    SA_TOTALSWPTime,
    SA_DISPLAYNum,
    SA_DETECTORFlag,
    SA_DATAADDRClr,
    SA_FFTBUCKETNum,
    SA_FFTCALNum,
    SA_FFTDirection,
    SA_FFTVALIDSTANum,
    SA_FFTVALIDENDNum,
    SA_FFTDOTSWPTime,
    SA_BUCKETTRIGTime,
    SA_RBWVBWFIL_DELAYTime,
    SA_TRIGType,
    SA_TRIGDirect,
    SA_TRIGTIME,
    SA_VEDIOTRIGAmp,
    SA_TRIGPERTIME,
    SA_RFBURSTTRIGAmp,
    SA_LASTBand,
    SA_LOStep,
    SA_LOLastBandKeeptime,
    SA_SEGPoint,
    SA_SWPStop,
    SA_CHECKSegNum,
    SA_FIRBUcketTime,
    SA_GETSPECData,
    SA_FreqSeg,
    SA_SweepInterrupt_Start,
    SA_SweepInterrupt_Stop,
    SA_FSRGet_Start,
    SA_FSRGet_Stop,
    SA_GateSweep_Source,
    SA_GateSweep_Control,
    SA_GateSweep_ControlValue,
    SA_GateSweep_GateMethod,
    SA_GateSweep_SynSrc,
    SA_GateSweep_Gate,
    SA_GateSweep_GateDelay,
    SA_GateSweep_GateLength,
    SA_GateSweep_PreventStatus,
    SA_GateSweep_PreventTime,
    SA_GateSweep_Period,
    SA_GateSweep_PerTrig_SrcDelay,
    SA_GateSweep_PerTrig_PrvStatus,
    SA_GateSweep_PerTrig_PrvTime,
    SA_GateSweep_RFBurst_TrigLevl,
    SA_ShmGetID_noticecode,
    SA_ShmGetAddr_noticecode,
};
#endif
