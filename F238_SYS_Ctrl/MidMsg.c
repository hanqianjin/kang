//==============================================================================
//
// Title:		MidMsg.c
// Purpose:		A short description of the implementation.
//
// Created on:	2018/1/11 at 8:39:55 by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "MidMsg.h"
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "SysDev.h"
#include "Temp.h"
#include "Touch.h"
#include "lplay.h"
#include "uniuser.h"
#include "bitReload.h"
#include "udisk.h"
#include "whoref.h"
#include "FPGATemp.h"
//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static int  MID_SLEEP_TIME = 1000;
extern PCONFIG_UPDATE sm_config_update;
//extern PCONFIG_RSA_CTRL sm_config_rsa_ctrl;
extern PCONFIG_SYSTEM sm_config_system;
extern PTEMP_CALC sm_temper_calc;
#define CALC_REF_TEMP 56. //modify by albert

extern DEVMSG devmsg;

//==============================================================================
// Static functions
static void ClearConfigMsg(void *param);
static void ClearSysMsg(void *param);
static DiInt32 DoSystemAction(DiUInt32 msg);
//Albert 1024
extern PSYSTEM_INFO sm_system_info;
//!Albert 1026 intial Driver
DiSession bitSundryDriver = 0;        //sundry Dev
DiSession bitGpsDriver = 0;             //Gps Dev
DiSession bitBatteryDriver = 0;       //Battery Dev
DiSession bitFMDriver= 0;		      //FM Dev
DiSession bitTempMainDriver= 0;  //MainBoard Temp Dev
DiSession bitTempRFDriver= 0;	     //RFBoard Temp Dev
DiSession bitUDiskDriver= 0;            //UDisk Dev
DiSession bitMiscDriver= 0;          //Misc Dev
Driver_func Driver_Array[] = 
{
    {"VIRTUAL:0:DEVICE",0},	// za xiang she bei
    {"ASRL_PL:0:DEVICE",0}, // GPS
    {"I2C:0:DEVICE",0},	// MAIN BOARD TEMP
    {"I2C:1:DEVICE",0}, //rf board temp
    {"ASRL_PL:1:DEVICE",0},	//BATTERY
    {"VIRTUAL:1:DEVICE",0},//fm
    //	{"VIRTUAL:5:DEVICE",0}, //Udisk & mouse
    {"VIRTUAL:7:DEVICE",0},//FPGA temp
    //{"USB:1:DEVICE",0}, //mini usb
};


extern DiSession bitdevHandle;
extern PALL_NOTIC_CODE sm_notic_excep;
//!Albert UDisk callback function. 10-26
DiInt32 udisk_callback(void *data)
{
    usbDevInfo *usbDev = (usbDevInfo *)data;
    if(usbDev->state < USB_UNKNOW )
        {
            sm_system_info->USBMemoryStatus = usbDev->state;
        }

    printf("usb staus:%d\n", usbDev->state);
    return 0;
}

// Albert 0222
void FirstReadInfo()
{
    // Battery info
    PowerInfo aPowerInfo;
    batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo);
    sm_system_info->BatterChargeStatus = aPowerInfo.power_supply_status - 1;
    sm_system_info->BatteryRemaind = aPowerInfo.power_supply_capacity;

}
void McuDevStatus()
{
    PowerInfo aPowerInfo;
    batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo);
    sm_system_info->BatterChargeStatus = aPowerInfo.power_supply_status - 1;
    sm_system_info->BatteryRemaind = aPowerInfo.power_supply_capacity;
    //*xuyao tian jia dui feng shan bao jing de zhuang tai bao cun
    //			fanClose(Driver_Array[DEV_BATTERY].dev_handle);


}

static DiInt32 DoSystemInfoAction(DiUInt32 msg);

//0810 steve
extern void ErrOutPut(DiInt32 errCode,DiInt32 itype);

//0925
//extern PRSA_RUN_SYNC sm_rasctrl;
extern RSA_EXIT gappexit;
void* MidMsgFunc(void *functionData)
{
    DiInt32 iflag = 0;
    while(gappexit.midmsgthreadExit)
        {

            if(sm_config_update->top_flag_conf & IXT_ConfigSystem)
                {
                    iflag = sm_config_update->system_flag_conf;

                    DoSystemAction(sm_config_update->system_flag_conf);
                    if(iflag == sm_config_update->system_flag_conf)
                        {
                            ClearConfigMsg(NULL);
                        }
                    else
                        {
                            printf("Attention,cmd conflict\n");
                        }
                }
            //!Albert 1026 add
            if(sm_config_update->top_flag_sys & IXT_System_Info)
                {
                    DoSystemInfoAction(sm_config_update->sys_flag_info);
                    ClearSysMsg(NULL);
                }
            else
                {
                    usleep(MID_SLEEP_TIME);
                }
        };
    printf("mid msg thread stop\n");
    gappexit.mainthreadExit = 0;
    return NULL;
}

static void ClearConfigMsg(void *param)
{	   
    sm_config_update->top_flag_conf = 0;
    sm_config_update->system_flag_conf = 0;
    return;
}

static void ClearSysMsg(void *param)
{
    sm_config_update->top_flag_sys = 0;
    sm_config_update->sys_flag_info = 0;
    return;
}

ReloadInfo bitInfo;
//for once not polling mode 
static DiInt32 glcdpower = 1;//1 on,0 off
static DiInt32 DoSystemAction(DiUInt32 msg)
{
    DiInt32 iBack = 0;
    if(msg & IXS_Calc)
        {
printf("enter cal\n");
printf("sm_config_system->AnaMode's value is %d\n",sm_config_system->AnaMode);
            //disableTouch(Driver_Array[DEV_SUNDRY].dev_handle);
            fanOpen(Driver_Array[DEV_BATTERY].dev_handle);
            if(0 == sm_config_system->AnaMode)
                {
//fock exec waitpid
                    system("/app/pltcalc.sh sa");			
                }
            else if(1 == sm_config_system->AnaMode)
                {
                    system("/app/pltcalc.sh rtsa");
                }

        }

    if(msg & IXS_FreqCalc)
        {
            if(SetOsciFreq(bitdevHandle,sm_config_system->PSFreqCalc) < 0)
                {
                    setNoticePara(1,2,4,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("freq osci calc failed\n");
                }
        }
    if(msg & IXS_SecIfAtten)
        {

            if(SetSecIfAttendB(bitdevHandle,sm_config_system->secifatten) < 0)
                {
                    setNoticePara(1,2,8,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("sec if atten failed\n");
                }
        }

    // CONFIG_SYSTEM
    if(msg & IXS_SwitchPic)
        {
            if(sm_config_system->PicSwitch)
                {
                    if(gpsDevDisable(Driver_Array[DEV_GPS].dev_handle) < 0)
                        {
                            setNoticePara(1,2,9,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("GPS disable failed\n");
                        }
                    if(CloseDev(Driver_Array[DEV_GPS].dev_handle) < 0)
                        {
                            setNoticePara(1,2,10,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("close device handle failed\n");
                        }
                    if(lcdSwitchOpen(0) < 0)
                        {
                            setNoticePara(1,2,11,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("open lcd switch failed\n");
                        }
                }
            else
                {

                    //clock_t start, end;
                    //start = clock();
                    if(OpenDev(Driver_Array[DEV_GPS].dev_name, &Driver_Array[DEV_GPS].dev_handle) < 0)
                        {
                            setNoticePara(1,2,12,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("open device handle failed\n");
                        }
                    if(gpsDevEnable(Driver_Array[DEV_GPS].dev_handle) < 0)
                        {
                            setNoticePara(1,2,13,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("GPS enable failed\n");
                        }
                    if(lcdSwitchClose(0) < 0)
                        {
                            setNoticePara(1,2,14,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("close lcd switch failed\n");
                        }

                    //end = clock();
                    //double seconds  =(double)(end - start)/CLOCKS_PER_SEC;

                    //printf("cut picture spend time is %lf\n",seconds);
                }
        }
    if(msg & IXS_BurnAction)
        {

            bitInfo.gps_handle = Driver_Array[1].dev_handle;
            DiString bitnamestr = NULL;
            //FpgaCpldIniHigh(bitdevHandle);
            //Sa
            if(0 == sm_config_system->AnaMode)
                {
                    bitnamestr = "F238_FPGA_SA.bit";
                    ReloadBitfile(bitnamestr,&bitInfo);
                }
            //Rtsa
            else if(1 == sm_config_system->AnaMode)
                {
                    bitnamestr = "F238_FPGA_RTSA.bit";
                    ReloadBitfile(bitnamestr,&bitInfo);
                }
            //INTERF_MODE
            else if(2 == sm_config_system->AnaMode)
                {
                    //bitnamestr = "F238_FPGA.bit";
                    //ReloadBitfile(bitnamestr,&bitInfo);
                }
            //PM_MODE
            else if(3 == sm_config_system->AnaMode)
                {
                    //bitnamestr = "F238_FPGA.bit";
                    //ReloadBitfile(bitnamestr,&bitInfo);
                }
            //LTE_FDD_MODE
            else if(4 == sm_config_system->AnaMode)
                {

                    bitnamestr = "F238_FPGA_FDD.bit";
                    ReloadBitfile(bitnamestr,&bitInfo);
                }
            else if(5 == sm_config_system->AnaMode)
                {
                    bitnamestr = "F238_FPGA_TDD.bit";
                    ReloadBitfile(bitnamestr,&bitInfo);
                }
            else if(6 == sm_config_system->AnaMode)
                {
                    bitnamestr = "F238_FPGA_FGNR.bit";
                    ReloadBitfile(bitnamestr,&bitInfo);
                }

            //FpgaCpldIniHigh(bitdevHandle);
            //FpgaCpldIniLow(bitdevHandle);
            usleep(10000);
            if(SetOsciFreq(bitdevHandle,sm_config_system->PSFreqCalc) < 0)
                {
                    setNoticePara(1,2,4,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("freq osci calc failed\n");
                }

            if(InOutRefCtrl(bitdevHandle,sm_config_system->refset) < 0)
                {
                    setNoticePara(1,2,15,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("setting ref failed\n");
                }
            sm_config_system->Convertflag = 0;
        }
    //wifi and bluetooth whether put in sysctrl app?
    if(msg & IXS_Ref)
        {
            if(InOutRefCtrl(bitdevHandle,sm_config_system->refset) < 0)
                {
                    setNoticePara(1,2,15,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("setting ref failed\n");
                }
	
        }
    if(msg & IXS_WIFI)
        {
            if(sm_config_system->wifiswitch)
                {
					wifiBtOpen(0);
                    //if(gpsDevEnable(Driver_Array[DEV_WIFI].dev_handle) < 0)
                    //    {
                    //        setNoticePara(1,2,13,PLT_EXCE_SOURCE);
                    //        sm_notic_excep->noticode = GetNoticeCode();
                    //        printf("GPS enable failed\n");
                    //    }
                    //printf("enable wifi power\n");
                }
            else
                {
					wifiBtClose(0);
                    //if(gpsDevDisable(Driver_Array[DEV_GPS].dev_handle) < 0)
                    //    {
                    //        setNoticePara(1,2,9,PLT_EXCE_SOURCE);
                    //        sm_notic_excep->noticode = GetNoticeCode();
                    //        printf("GPS disable failed\n");
                    //    }
                    //printf("disable wifi power\n");
                }
        }
    if(msg & IXS_BLUETOOTH)
        {

        }
    if(msg & IXS_PLAYMUSICON)
        {
            if(playWav(sm_config_system->WavFileName) < 0)
                {
                    setNoticePara(1,2,16,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("play wav file failed\n");
                }
        }
    if(msg & IXS_PLAYMUSICOFF)
        {
            if(stopSnd() < 0)
                {
                    setNoticePara(1,2,17,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("stop play wav failed\n");
                }
        }

    if(msg & IXS_Local_Remote)
        {
            printf("get local remote msg\n");
        }
    if(msg & IXS_LcdpadLight)
        {
            if(sm_config_system->LcdpadLight)
                {
                    if(!glcdpower)
                        {
                            if(lcdPwrOpen(0) < 0)
                                {
                                    setNoticePara(1,2,18,PLT_EXCE_SOURCE);
                                    sm_notic_excep->noticode = GetNoticeCode();
                                    printf("lighten lcd power failed\n");
                                }
                            glcdpower = 1;
                        }
                }
            else
                {
                    if(glcdpower)
                        {
                            if(lcdPwrClose(0) < 0)
                                {
                                    setNoticePara(1,2,19,PLT_EXCE_SOURCE);
                                    sm_notic_excep->noticode = GetNoticeCode();
                                    printf("close lcd power failed\n");
                                }
                            glcdpower = 0;
                        }
                }	
        }
    if(msg & IXS_LCDBrightness)
        {
            if(SetBrightnessLevel(bitdevHandle,sm_config_system->LCDBrightness) < 0)
                {
                    setNoticePara(1,2,20,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("adjust lcd brightness failed\n");
                }				
        }
    if(msg & IXS_SleepMode)
        {
            printf("get sleep mode msg\n");
        }
    if(msg & IXS_Volume)
        {
            if(setVolume(sm_config_system->Volume)<0)
                {
                    setNoticePara(1,2,21,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("adjust volume failed\n");
                }

            if(playWav("button.wav") < 0)
                {
                    setNoticePara(1,2,39,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("play button wav failed at volume\n");
                }
        }
    if(msg & IXS_KeyBeep)
        {
            if(sm_config_system->KeyBeep)
                {
                    if(playWav("button.wav") < 0)
                        {
                            setNoticePara(1,2,39,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("play button wav failed at keybeep\n");
                        }	
                }	
        }
    if(msg & IXS_LimitBeep)
        {
            printf("get limitbeep msg\n");
        }
    if(msg & IXS_FWupdateRequest)
        {
            printf("get fwupdaterequest msg\n");
        }
    if(msg & IXS_TouchScreen)
        {

            if(sm_config_system->TouchScreen == 1)
                {
                    if(enableTouch(&Driver_Array[DEV_SUNDRY].dev_handle) < 0)
                        {
                            setNoticePara(1,2,22,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("touch screen enable failed\n");
                        }
                }
            else
                {
                    if(disableTouch(Driver_Array[DEV_SUNDRY].dev_handle) < 0)
                        {
                            setNoticePara(1,2,23,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("touch screen disabled failed\n");
                        }
                }
        }
    //NO.1
    if(msg & IXS_InvenAppMajor)
        {
            if(0)
                {
                    setNoticePara(1,2,24,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get InvenApp Major msg failed\n");
                }
        }
    //NO.2
    if(msg & IXS_InvenAppMiinor)
        {
            if(0)
                {
                    setNoticePara(1,2,25,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get InvenAppMiinor msg failed \n");
                }
        }
    //NO.3
    if(msg & IXS_ADCOver)
        {
            if(GetAdcoverFlag(bitdevHandle,&sm_config_system->adcover) < 0)
                {
                    setNoticePara(1,2,28,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get adc over msg failed\n");
                }
        }
    //NO.4
    if(msg & IXS_SELFTest)
        {
            if(GetFpgaState(bitdevHandle,&sm_config_system->selftest) < 0)
                {
                    setNoticePara(1,2,40,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get self test msg failed\n");
                }
        }
    //NO.5
    if(msg & IXS_InvenSerialNo)
        {
            if(0)
                {
                    setNoticePara(1,2,28,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get InvenSerialNo msg failed\n");
                }
        }
    //NO.16
    if(msg & IXS_PSModel)
        {
            if(0)
                {
                    setNoticePara(1,2,29,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get ps mode msg failed\n");
                }
        }
    //NO.17
    /*



    if(msg & IXS_PSType)
        {
            printf("get PSType msg\n");
        }
        //NO.18
    if(msg & IXS_PSMethod)
        {
            printf("get PSMethod msg\n");
        }
        //NO.19

    if(msg & IXS_PSSerialNo)
        {
            printf("get PSSerialNo msg\n");
        }
        //NO.20
    if(msg & IXS_PSInvenMajor)
        {
            printf("get PSInvenMajor msg\n");
        }
        //NO.21
    if(msg & IXS_PSInvenMinor)
        {
            printf("get PSInvenMinor msg\n");
        }
*/

    //NO.23
    if(msg & IXS_GPSSwitch)
        {  		
            if(sm_config_system->Gpswitch)
                {
                    if(gpsDevEnable(Driver_Array[DEV_GPS].dev_handle) < 0)
                        {
                            setNoticePara(1,2,13,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("GPS enable failed\n");
                        }
                    //printf("enable gps power\n");
                }
            else
                {
                    if(gpsDevDisable(Driver_Array[DEV_GPS].dev_handle) < 0)
                        {
                            setNoticePara(1,2,9,PLT_EXCE_SOURCE);
                            sm_notic_excep->noticode = GetNoticeCode();
                            printf("GPS disable failed\n");
                        }
                    //printf("disable gps power\n");
                }

        }
    //NO.28
    if(msg & IXS_PLAYMUSICVOL)
        {
            if(setVolume(sm_config_system->Volume) < 0)
                {
                    setNoticePara(1,2,21,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("adjust volume failed\n");
                }
        }

    return 0;
}


static DiReal64 lasttemp = CALC_REF_TEMP;
static DiInt32 DoSystemInfoAction(DiUInt32 msg)
{
    DiInt32 iBack = 0;
    //!Albert add 1024
    // SYSTEM_INFO

    //NO.6
    if(msg & IXS_BoardTemp)
        {
            DiReal64 temp;
            if(readTemp(Driver_Array[DEV_TEMP_MAIN].dev_handle,&temp) < 0)
                {
                    setNoticePara(1,2,30,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get board temperature failed\n");
                }
            sm_system_info->BoardTemp = temp;

        }
    //NO.7
    if(msg & IXS_BatteryInfoAll)
        {
            // printf("IXS_BatteryInfoAll msg +++++++++++\n");
            PowerInfo aPowerInfo;
            if(batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo) < 0)
                {
                    setNoticePara(1,2,31,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get battery information failed\n");
                }
            sm_system_info->BatterChargeStatus = aPowerInfo.power_supply_status - 1;
            /*	 DiChar flag = aPowerInfo.power_supply_status[0];
                         switch(flag)
                                {
                                case 'U':
                                case 'u':
                                        sm_system_info->BatterChargeStatus = 0;
                                        break;
                                case 'C':
                                case 'c':
                                        sm_system_info->BatterChargeStatus = 1;
                                        break;
                                case 'D':
                                case 'd':
                                        sm_system_info->BatterChargeStatus = 2;
                                        break;
                                case 'F':
                                case 'f':
                                        sm_system_info->BatterChargeStatus = 3;
                                        break;
                                default:
                                        break;
                                }
*/
            sm_system_info->BatteryRemaind = aPowerInfo.power_supply_capacity;
sm_system_info->BatteryTemp = aPowerInfo.power_supply_temp;
sm_system_info->batvoltage = aPowerInfo.power_supply_voltage_now;
sm_system_info->batcurrent = aPowerInfo.power_supply_current_now;


            //  printf("get BatterChargeStatus msg %.2f\n", aPowerInfo.power_supply_status);
        }
    //NO.8
    if(msg & IXS_BatteryRemaind)
        {
            PowerInfo aPowerInfo;
            if(batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo) < 0)
                {
                    setNoticePara(1,2,31,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get battery information failed\n");
                }
            sm_system_info->BatteryRemaind = aPowerInfo.power_supply_capacity;

        }
    //NO.9
    if(msg & IXS_BatterChargeStatus)
        {
            PowerInfo aPowerInfo;
            if(batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo) < 0)
                {
                    setNoticePara(1,2,31,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get battery information failed\n");
                }
            /*		 DiChar flag = aPowerInfo.power_supply_status[0];
                         switch(flag)
                                {
                                case 'U':
                                case 'u':
                                        sm_system_info->BatterChargeStatus = 0;
                                        break;
                                case 'C':
                                case 'c':
                                        sm_system_info->BatterChargeStatus = 1;
                                        break;
                                case 'D':
                                case 'd':
                                        sm_system_info->BatterChargeStatus = 2;
                                        break;
                                case 'F':
                                case 'f':
                                        sm_system_info->BatterChargeStatus = 3;
                                        break;
                                default:
                                        break;
                                }
*/
            //printf("get BatteryStatus msg  %d\n",sm_system_info->BatterChargeStatus);
        }
    //NO.10
    if(msg & IXS_ACStatus)
        {
            PowerInfo aPowerInfo;
            if(batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo) < 0)
                {
                    setNoticePara(1,2,31,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get battery information failed\n");
                }
            /*		 DiChar flag = aPowerInfo.power_supply_name[5];
                         switch(flag)
                                {
                                case 'A':
                                case 'a':
                                        sm_system_info->ACStatus = 0;
                                        break;
                                case 'B':
                                case 'b':
                                        sm_system_info->ACStatus = 1;
                                        break;
                                default:
                                        break;
                                }
*/

        }

    //NO.14
    if(msg & IXS_BatteryTempAlarm)
        {
            DiReal32 temp;
            PowerInfo aPowerInfo;
            if(batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo) < 0)
                {
                    setNoticePara(1,2,31,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get battery information failed\n");
                }
            temp = aPowerInfo.power_supply_temp;
            if(temp > 85)
                {
                    sm_system_info->BoardTempAlarm = 1;
                }
            else
                {
                    sm_system_info->BoardTempAlarm = 0;
                }
        }
    //NO.15
    if(msg & IXS_BoardTempAlarm)
        {
            static DiInt32 iswitch = -1;
            sm_system_info->RfTemp = 0.;
            DiInt32 iBack = readTemp(Driver_Array[DEV_TEMP_RF].dev_handle,&sm_system_info->RfTemp);
            if(iBack < 0)
                {
                    setNoticePara(1,2,32,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get rf temperature failed\n");
                }
            else
                {
                    //printf("rf board temp is %lf\n",sm_system_info->RfTemp);
                    if(sm_system_info->RfTemp - lasttemp >= 1.0 || sm_system_info->RfTemp - lasttemp <= -1.0)
                        {
                            sm_temper_calc->detatemp = sm_system_info->RfTemp - CALC_REF_TEMP;
                            sm_temper_calc->calctop = IXT_Tempercalc;
                            lasttemp = sm_system_info->RfTemp;
                        }
                }
            sm_system_info->BoardTemp = 0.;
            iBack = readTemp(Driver_Array[DEV_TEMP_MAIN].dev_handle,&sm_system_info->BoardTemp);
            if(iBack < 0)
                {
                    setNoticePara(1,2,33,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get main board temp failed\n");
                }

            iBack = readFpgaTemp(Driver_Array[DEV_FPGA_TEMP].dev_handle,&sm_system_info->FpgaTemp);
            if(iBack < 0)
                {
                    setNoticePara(1,2,34,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get PL temperature failed\n");
                }


            if(sm_system_info->BoardTemp >= 55. || sm_system_info->RfTemp >= 55. || sm_system_info->FpgaTemp >= 65.0)
                {
                    if(iswitch != 0)
                        {
                            iswitch = 0;
                            if(fanOpen(Driver_Array[DEV_BATTERY].dev_handle) < 0)
                                {
                                    setNoticePara(1,2,35,PLT_EXCE_SOURCE);
                                    sm_notic_excep->noticode = GetNoticeCode();
                                    printf("open fan failed\n");
                                }
                        }
                }
            else if(sm_system_info->BoardTemp < 50.0 && sm_system_info->RfTemp < 50.0 && sm_system_info->FpgaTemp < 55.0)
                {
                    if(iswitch != 1)
                        {
                            iswitch = 1;
                            if(fanClose(Driver_Array[DEV_BATTERY].dev_handle) < 0)
                                {
                                    setNoticePara(1,2,36,PLT_EXCE_SOURCE);
                                    sm_notic_excep->noticode = GetNoticeCode();
                                    printf("close fan failed\n");
                                }
                        }
                }

        }



    //NO.24
    if(msg & IXS_GPSInfoAll)
        {
            nmeaINFO aNmeInfo;
            //			gpsDevEnable(Driver_Array[DEV_GPS].dev_handle);
            //			iBack = gpsDevReadDatex86Test(Driver_Array[DEV_GPS].dev_handle,&aNmeInfo);
            iBack = gpsDevReadDate(Driver_Array[DEV_GPS].dev_handle,&aNmeInfo);
            if(iBack < 0)
                {
                    setNoticePara(1,2,37,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get gps information failed\n");
                    return -1;
                }
            if(aNmeInfo.lat >= 0)
                {
                    sprintf(sm_system_info->GPSLatitude,"%f N",aNmeInfo.lat/100);
                }
            else
                {
                    sprintf(sm_system_info->GPSLatitude,"%f S",aNmeInfo.lat/100);
                }
            if(aNmeInfo.lon >= 0)
                {
                    sprintf(sm_system_info->GPSLongitude,"%f E",aNmeInfo.lon/100);
                }
            else
                {
                    sprintf(sm_system_info->GPSLongitude,"%f W",aNmeInfo.lon/100);
                }

            sm_system_info->GPSElevation = aNmeInfo.elv;

            sm_system_info->GPSSatelliteNum = aNmeInfo.satinfo.inuse;
            sm_system_info->GPSInView = aNmeInfo.satinfo.inview;

            sm_system_info->GPSStatus = aNmeInfo.sig;


            sprintf(sm_system_info->GPSDate,"%04d-%02d-%02d",aNmeInfo.utc.year+1900,aNmeInfo.utc.mon+1,aNmeInfo.utc.day);

            sprintf(sm_system_info->GPSTime,"%02d:%02d:%02d",aNmeInfo.utc.hour+8,aNmeInfo.utc.min,aNmeInfo.utc.sec);
            sm_system_info->GpsSpeedKmh = aNmeInfo.speed;
            sm_system_info->GpsDirection = aNmeInfo.direction;
            sm_system_info->GpsOperMode = aNmeInfo.fix;
            sm_system_info->GpsPrnNumber = aNmeInfo.satinfo.sat[0].id;
            //printf("%d\n",sm_system_info->GPSSatelliteNum);
            //printf("%d\n",sm_system_info->GPSStatus);
        }
    //NO.25
    if(msg & IXS_GPSLongitude)
        {
            nmeaINFO aNmeInfo;
            //			gpsDevEnable(Driver_Array[DEV_GPS].dev_handle);
            iBack = gpsDevReadDate(Driver_Array[DEV_GPS].dev_handle,&aNmeInfo);
            if(iBack < 0)
                {
                    setNoticePara(1,2,37,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get gps information failed\n");
                }
            sprintf(sm_system_info->GPSLongitude,"%f",aNmeInfo.lon);
            printf("%s\n",sm_system_info->GPSLongitude);
        }
    //NO.26
    if(msg & IXS_GPSDate)
        {
            nmeaINFO aNmeInfo;
            //			gpsDevEnable(Driver_Array[DEV_GPS].dev_handle);
            iBack = gpsDevReadDate(Driver_Array[DEV_GPS].dev_handle,&aNmeInfo);
            if(iBack < 0)
                {
                    setNoticePara(1,2,37,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get gps information failed\n");
                }
            sprintf(sm_system_info->GPSDate,"%4d%2d%2d",aNmeInfo.utc.year,aNmeInfo.utc.mon,aNmeInfo.utc.day);
            printf("%s\n",sm_system_info->GPSDate);
        }
    //NO.27
    if(msg & IXS_GPSTime)
        {
            nmeaINFO aNmeInfo;
            //		gpsDevEnable(Driver_Array[DEV_GPS].dev_handle);
            iBack = gpsDevReadDate(Driver_Array[DEV_GPS].dev_handle,&aNmeInfo);
            if(iBack < 0)
                {
                    setNoticePara(1,2,37,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get gps information failed\n");
                }
            sprintf(sm_system_info->GPSTime,"%2d%2d%2d.%2d",aNmeInfo.utc.hour,aNmeInfo.utc.min,aNmeInfo.utc.sec,aNmeInfo.utc.hsec);
            printf("%s\n",sm_system_info->GPSTime);
        }
    //NO.28
    else if(msg & IXS_BatteryOnline)
        {
            PowerInfo aPowerInfo;
            if(batteryDevReadDate(Driver_Array[DEV_BATTERY].dev_handle,&aPowerInfo) < 0)
                {
                    setNoticePara(1,2,31,PLT_EXCE_SOURCE);
                    sm_notic_excep->noticode = GetNoticeCode();
                    printf("get battery information failed\n");
                }
        }

    return 0;
}
DiInt32 InitSysApiDev()
{
    //here need init all device first
    InitDevs();
    DiUInt32 iBack = 0;
    int i = 0;
    for(i = 0 ; i < sizeof(Driver_Array)/sizeof(Driver_Array[0]);i ++)
        {
            iBack = OpenDev(Driver_Array[i].dev_name,&Driver_Array[i].dev_handle);

            if(iBack < 0)
                {
                    printf("Open %s failed!\n",Driver_Array[i].dev_name);
                }
        }
    if(Driver_Array[DEV_SUNDRY].dev_handle != 0)
        {
            RegisterCallback(Driver_Array[DEV_SUNDRY].dev_handle,McuDevStatus);
        }
    if(Driver_Array[DEV_BATTERY].dev_handle != 0)
        {
            //Albert 19/03/07 keyborad back light control.
            openBackLightEpoll(Driver_Array[DEV_BATTERY].dev_handle);
        }

    return iBack;
}

DiInt32 CloseApiDev()
{
    DiUInt32 iBack = 0;
    int i = 0;
    for(i = 0 ; i < sizeof(Driver_Array)/sizeof(Driver_Array[0]);i ++)
        {
            if(DEV_BATTERY == i)
                {
                    closeBackLightEpoll(Driver_Array[DEV_BATTERY].dev_handle);
                }
            iBack = OpenDev(Driver_Array[i].dev_name,&Driver_Array[i].dev_handle);

            if(iBack < 0)
                {
                        setNoticePara(1,2,38,PLT_EXCE_SOURCE);
                        sm_notic_excep->noticode = GetNoticeCode();
                        printf("close to release handle failed\n");
                }
        }
    return iBack;
}
/*
DiInt32 RegisterUDisk()
{
                if(Driver_Array[DEV_SUNDRY].dev_handle != 0)
                        {
                                RegisterCallback(Driver_Array[DEV_UDISK].dev_handle,udisk_callback);
                        }
        return 0;
}*/

