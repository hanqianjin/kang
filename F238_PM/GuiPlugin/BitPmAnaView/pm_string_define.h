/**************Copyright (c)**************************************
 **
 **               INNO Instrument(China) Co.,Ltd.
 **
 **------------File Info------------------------------------------
 **Class name:              string_define.h
 **Latest Version:          V1.0.0
 **Latest modified Date:
 **Created by:              Roc
 **Created date:            2019.12.4
 **Descriptions:            use to change display language string ID
 **/
#ifndef PM_STRING_DEFINE_H
#define PM_STRING_DEFINE_H
enum
{
    // FREQ set dialog string
    STR_FREQ_TOP = 0, STR_FREQ_DIALOG_TITLE, STR_FREQ_START, STR_FREQ_STOP, STR_FREQ_STEP, STR_FREQ_OFFSET, STR_SPAN,
    STR_SPAN_FULL, STR_CHST_NAME, STR_CHST_NUM, STR_CHST_STEP, STR_CHST_TYPE, STR_UPLINK, STR_DOWNLINK,

    //Ampt set dialog string
    STR_AMPT_TOP, STR_AMPT_DIALOG_TITLE, STR_AUTOSCALE, STR_REFLEVEL, STR_ATTEN, STR_ATTEN_AUTO, STR_SCALE, STR_REF_OFFSET,
    STR_UNITS,STR_PREAMP,

    //Display set dialog string
    STR_SISPLAY, STR_SISPLAY_DIALOG_TITLE, STR_DISPLAY_TYPE, STR_DISPLAY_CONT, STR_DISPLAY_SINGLE, STR_SWP_ONCE, STR_SPECTRUM,
    STR_SPECTROGRAM, STR_DENSITY, STR_PERSISTENCE, STR_INFINITE,STR_FINITE, STR_PERSISTENCE_TIME, STR_DENSITY_HIGH,
    STR_DENSITY_LOW, STR_CURVE, STR_DENSITY_AUTO,

    STR_END,
};
#endif // PM_STRING_DEFINE_H
