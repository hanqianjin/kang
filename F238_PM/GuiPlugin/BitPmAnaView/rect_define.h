/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              rect_define.h
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Roc
 **Created date:            2019.12.4
 **Descriptions:            PM window rect information
 **
 ** ---------------------------------------------------
 ** |                   top_info                      |
 ** --------------------------------------------------
 ** |left_info |                         | right_info |
 ** -----------                          -------------
 ** |left_info |                         | right_info |
 ** -----------        Draw_main         -------------
 ** |left_info |                         | right_info |
 ** -----------                          -------------
 ** |left_info |                         | right_info |
 ** ---------------------------------------------------
 ** |                 bottom_info                     |
 ** ---------------------------------------------------
 *****************************************************************/
#ifndef RECT_DEFINE_H
#define RECT_DEFINE_H

#define PM_WINDOW_WIDTH        1280
#define PM_WINDOW_HEIGHT       713

#define PM_LEFT_INFO_WIDTH     254
#define PM_LEFT_INFO_HEIGHT    648

#define PM_TOP_INFO_HEIGHT     (65)
#define PM_TOP_INFO_WIDTH      1280

#define PM_RIGHT_INFO_WIDTH    85
#define PM_RIGHT_INFO_HEIGHT   100

#define PM_BOTTOM_INFO_WIDTH    1280
#define PM_BOTTOM_INFO_HEIGHT   74

#define RECT_CHANGE 0

#define PM_PSTART_X 0
#define PM_PSTART_Y_BIG 3
#define PM_PSTART_Y_SMALL PM_LEFT_INFO_WIDTH

#endif // RECT_DEFINE_H
