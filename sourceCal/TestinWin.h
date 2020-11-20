/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2020. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_TEXTBOX                    2       /* control type: textBox, callback function: (none) */
#define  PANEL_COMMANDBUTTON              3       /* control type: command, callback function: StartTest */
#define  PANEL_COMMANDBUTTON_2            4       /* control type: command, callback function: ReceiveInterrupt */
#define  PANEL_TEXTBOX_2                  5       /* control type: textBox, callback function: (none) */
#define  PANEL_NUMERIC_2                  6       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_3                  7       /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC                    8       /* control type: numeric, callback function: (none) */
#define  PANEL_CANVAS                     9       /* control type: canvas, callback function: (none) */
#define  PANEL_DECORATION                 10      /* control type: deco, callback function: (none) */
#define  PANEL_NUMERIC_12                 11      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_11                 12      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_9                  13      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_5                  14      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_8                  15      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_7                  16      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_10                 17      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_6                  18      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_4                  19      /* control type: numeric, callback function: (none) */
#define  PANEL_COMMANDBUTTON_5            20      /* control type: command, callback function: SetBW */
#define  PANEL_COMMANDBUTTON_3            21      /* control type: command, callback function: SetFreq */
#define  PANEL_TEXTMSG                    22      /* control type: textMsg, callback function: (none) */
#define  PANEL_DECORATION_2               23      /* control type: deco, callback function: (none) */
#define  PANEL_BINARYSWITCH_4             24      /* control type: binary, callback function: (none) */
#define  PANEL_BINARYSWITCH_3             25      /* control type: binary, callback function: SetBW */
#define  PANEL_BINARYSWITCH_2             26      /* control type: binary, callback function: SetBW */
#define  PANEL_GRAPH                      27      /* control type: graph, callback function: (none) */
#define  PANEL_BINARYSWITCH               28      /* control type: binary, callback function: SetBW */
#define  PANEL_COMMANDBUTTON_4            29      /* control type: command, callback function: TestRefAndAtten */
#define  PANEL_NUMERIC_14                 30      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_13                 31      /* control type: numeric, callback function: (none) */
#define  PANEL_TEXTMSG_2                  32      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ReceiveInterrupt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetBW(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SetFreq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartTest(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TestRefAndAtten(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
