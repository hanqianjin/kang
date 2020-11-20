#ifndef __UNIUSER_H__
#define __UNIUSER_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "BitVisaType.h"
#include "error_functions.h"
#include "BitSehInfo.h"

/*****************for user******************/
extern void InitDevs(void);

extern DiInt32 RegisterCallback(DiSession pHandle, DiInt32 (*callback_func)(void *));
extern DiInt32 OpenDev(char *rsrcName, DiPSession pHandle);
extern DiInt32 CloseDev(DiSession pHandle);
//extern DiInt32 DiReadDev(DiSession pHandle, DiInt32 offset, DiInt32 len, void* data);
//extern DiInt32 DiWriteDev(DiSession pHandle, DiInt32 offset, DiInt32 len, void* data);
//extern DiInt32 DiCtlDev(DiSession pHandle, DiInt32 cmd, void *data);

/*
DiInt32 BitWrite32(DiSession devHandle,DiUInt32 addr,DiUInt32 value);

DiInt32 BitRead32(DiSession devHandle,DiUInt32 addr,DiPUInt32 value); 
DiInt32 BitMoveOut8(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt8 buf8);
DiInt32 BitMoveOut16(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt16 buf16); 
DiInt32 BitMoveOut32(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt32 buf32);
DiInt32 BitMoveOut64(DiSession devHandle, DiUInt32 addr, DiBusSize length, DiPUInt64 buf64);

DiInt32 BitWrite32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiUInt32 value);

DiInt32 BitRead32Ex(DiSession devHandle,DiUInt32 space,DiBusAddress offset,DiPUInt32 value);
DiInt32 BitMoveOut8Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt8 buf8);
DiInt32 BitMoveOut16Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt16 buf16);
DiInt32 BitMoveOut32Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt32 buf32);
DiInt32 BitMoveOut64Ex(DiSession devHandle, DiUInt32 space, DiBusAddress offset, DiBusSize length, DiPUInt64 buf64);
*/
/***********************************************/
#ifdef __cplusplus
    }
#endif

#endif
