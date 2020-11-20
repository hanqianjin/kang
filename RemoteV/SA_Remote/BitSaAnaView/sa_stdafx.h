#ifndef _SA_STDAFX_
#define _SA_STDAFX_

#include <QObject>
#include "sa_shared_memory.h"
#include "extern.h"

//extern keyType key;
//changed by Tony ,add "SA_"
extern struct GUI_DRAW_SET SA_guiDrawSet;
extern struct WATTS_UNIT SA_watts_unit;
extern pthread_mutex_t SA_lockobj;


#if USABLE
extern SA_MEASURE_DATA *SA_sm_measure_data;
#endif
#if 0
//extern SA_SYSTEM_INFO *sm_system_info;
extern SA_PSWEEP_NUM SA_sm_sweep_num;
extern SA_CONFIG_SWEEP *SA_sm_config_sweep;
extern SA_CONFIG_MEASURE *SA_sm_config_measure;
//extern SA_CONFIG_SYSTEM *sm_config_system;
extern SA_SWEEP_DATA *SA_sm_sweep_data;
extern SA_SM_SYNC *SA_sm_sync;
extern SA_CONFIG_UPDATE *SA_sm_config_update;
extern SA_PSTART_FLAG sm_startflag;//Johnson 190524

//changed by steve
extern SA_PBIT_BSA_VISI SA_sm_bsa_visi;
#endif
//extern qint32 SA_homeuiHandle;
//extern qint32 SA_syncHandle;
//extern qint32 SA_guiHandle;

extern qint32 SA_autoChangerbwflag;
extern qint32 SA_autoChangevbwflag;

extern bool bParaLoad;

#endif // _SA_STDAFX_

