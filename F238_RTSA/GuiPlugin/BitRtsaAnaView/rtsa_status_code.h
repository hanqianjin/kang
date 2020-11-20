#ifndef _RTSA_STATUS_CODE_H_
#define _RTSA_STATUS_CODE_H_

#define RTSA_R_StatusNormal							0x000000
//sa application message notice dict
enum{
    RTSA_APP_SHM_INIT = 0,
    RTSA_APP_FILE_PERS,
    RTSA_APP_FILE_LAST,
    RTSA_APP_FILE_DEFAULT,
    RTSA_APP_FILE_USER,
    RTSA_APP_CHANNEL_FILE,
    RTSA_DPX_MEM_OPEN,
    RTSA_APP_DPX_EPOLL_ENABLE,
    RTSA_APP_DPX_EPOLL_DISABLE,
    RTSA_APP_DPX_MEM_CLOSE,
    RTSA_SAVE_STATE,
    RTSA_SAVE_TRACE_DATA,
    RTSA_LOAD_STATE,
    RTSA_LOAD_TRACE_DATA,
    RTSA_CAPTURE_SCREEN,
    RTSA_SHM_SWEEP_ID_INIT,
    RTSA_SHM_SWEEP_ADDR_INIT,
    RTSA_SHM_CTRL_ID_INIT,
    RTSA_SHM_CTRL_ADDR_INIT,
    RTSA_SHM_SWEEPDATA_ID_INIT,
    RTSA_SHM_SWEEPDATA_ADDR_INIT,
    RTSA_SHM_SYNC_ID_INIT,
    RTSA_SHM_SYNC_ADDR_INIT,
    RTSA_SHM_UPDATE_ID_INIT,
    RTSA_SHM_UPDATE_ADDR_INIT,
    RTSA_SHM_START_ID_INIT,
    RTSA_SHM_START_ADDR_INIT,
};
#endif
