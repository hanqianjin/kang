/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              rect_define.h
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Albert
 **Created date:            2018/12/13
 **Descriptions:            RTSA window rect information
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

#define RTSA_WINDOW_WIDTH        1280
#define RTSA_WINDOW_HEIGHT       713

#define RTSA_LEFT_INFO_WIDTH     254
#define RTSA_LEFT_INFO_HEIGHT    648

#define RTSA_TOP_INFO_HEIGHT     (65)
#define RTSA_TOP_INFO_WIDTH      1280

#define RTSA_RIGHT_INFO_WIDTH    85
#define RTSA_RIGHT_INFO_HEIGHT   100

#define RTSA_BOTTOM_INFO_WIDTH    1280
#define RTSA_BOTTOM_INFO_HEIGHT   74

#define RECT_CHANGE 0
#define RTSA_DRAG_START 30

#define RTSA_PSTART_X 0
#define RTSA_PSTART_Y_BIG 3
#define RTSA_PSTART_Y_SMALL RTSA_LEFT_INFO_WIDTH

#endif // RECT_DEFINE_H
