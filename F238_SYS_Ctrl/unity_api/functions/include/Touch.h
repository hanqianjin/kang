/*****************************************************************************
Copyright:    2018-2010,  Tech. Co., Ltd.
File name:    Touch.h
Description:  For touchscreen enable/disable
Author:       brook.lv
Version:      v1.01
Date:         2018.6.12
History:    

*****************************************************************************/

#ifndef __TOUCH_H__
#define __TOUCH_H__

#ifdef __cplusplus
    extern "C" {
#endif

#include "BitVisaType.h"

DiInt32 enableTouch(DiPSession devHandle) ;
DiInt32 readTouchState(DiSession devHandle, DiPInt32 state) ;
DiInt32 disableTouch(DiSession devHandle) ;

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __TOUCH_H__ */
