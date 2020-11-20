

#define PM_R_StatusNormal							0x000000
#define PM_R_Status_KeypadThreadRun				0x000001
#define PM_R_Status_LogThreadRun					0x000002
#define PM_R_Status_RFMThreadRun					0x000003
#define PM_R_Status_DeviceStatusThreadRun			0x000004
#define PM_R_Status_ExtCommUDPThreadRun			0x000005
#define PM_R_Status_ExtCommUARTThreadRun			0x000006
#define PM_R_Status_ConnectPowerSensor				0x000007
#define PM_R_Status_DisconnectPowerSensor			0x000008
#define PM_R_Status_PCGUI_Login					0x000009
#define PM_R_Status_PCGUI_Logout					0x00000a
#define PM_R_Status_RFM_KillZoneIN					0x00000b
#define PM_R_Status_PSensor_RFMKillZoneIN			0x00000c
#define PM_R_Status_PSensor_RFMKillZoneOUT			0x00000d
#define PM_R_Status_FWupdate_Reboot				0x00000e
#define PM_R_Status_FWupdate_GUIupdate			    0x00000f
#define PM_R_Status_FWupdate_CtrlAppupdate			0x000010
#define PM_R_Status_FWupdate_Totalupdate			0x000011
#define PM_R_Status_FWupdate_UpdateSuccess		    0x000012
#define PM_R_Status_Battery_Low					0x000013
#define PM_R_Status_Battery_DeadLine_PowerOff		0x000014

#define PM_R_Status_1st_DeviceStatus				0x000015
#define PM_R_Status_PCGUI_AliveStatus				0x000016
#define PM_R_Status_SelfTest_Run					0x000017
#define PM_R_Status_SelfTest_Stop					0x000018
#define PM_R_Status_SelfTest_NoError				0x000019
#define PM_R_Status_RFM_SoftResetIN				0x00001a
#define PM_R_Status_RFM_SoftResetOUT				0x00001b

#define PM_R_Status_TempAlarm_Set					0x00001c
#define PM_R_Status_TempAlarm_Clear				0x00001d

#define PM_R_Status_Set_SerialNumber				0x00001e

#define PM_R_Status_Received_CalTable				0x100000
#define PM_R_Status_Read_CalTable_Amp_org			0x100001
#define PM_R_Status_Read_CalTable_Amp_intp			0x100002
#define PM_R_Status_Read_CalTable_Preamp_org		0x100003
#define PM_R_Status_Read_CalTable_Preamp_intp		0x100004
#define PM_R_Status_Read_CalTable_freq_org			0x100005


#define PM_R_StatusCtrlBufferLocked				0x200000



#define PM_R_ErrorMemoryAllocation					0x900001

#define PM_R_ErrorUDP_STX							0xf00001
#define PM_R_ErrorUDP_UnknownCMD					0xf00002
#define PM_R_ErrorKeypadInit						0xf00003
#define PM_R_ErrorUSBInit							0xf00004
#define PM_R_ErrorUART_STX							0xf00005
#define PM_R_ErrorUART_UnknownCMD				    0xf00006

#define PM_R_ErrorInit_ShmGetID_SweepData			0xf00007
#define PM_R_ErrorInit_ShmGetID_Config				0xf00008
#define PM_R_ErrorInit_ShmGetID_Status				0xf00009
#define PM_R_ErrorInit_ShmGetID_Sync				0xf0000a
#define PM_R_ErrorInit_ShmGetID_Log				0xf0000b
#define PM_R_ErrorInit_ShmGetAddr_SweepData		0xf0000c
#define PM_R_ErrorInit_ShmGetAddr_Config			0xf0000d
#define PM_R_ErrorInit_ShmGetAddr_Status			0xf0000e
#define PM_R_ErrorInit_ShmGetAddr_Sync				0xf0000f
#define PM_R_ErrorInit_ShmGetAddr_Log				0xf00010

#define PM_R_ErrorInit_ALSA						0xf00011
#define PM_R_ErrorInit_ALSA_WaveFileOpen			0xf00012

#define PM_R_ErrorInit_LCDBLU_fdOpen				0xf00013
#define PM_R_ErrorInit_LCDBLU_StatusRead			0xf00014

#define PM_R_ErrorInit_Battery_fdOpen				0xf00015
#define PM_R_ErrorInit_Temperature_fdOpen			0xf00016

#define PM_R_ErrorInit_Keypad_fdOpen				0xf00017
#define PM_R_ErrorInit_SystemMem_fdOpen			0xf00018


#define PM_R_ErrorInit_RFM_USBNotFound				0xf00020
#define PM_R_ErrorInit_RFM_USBNotOpen				0xf00021
#define PM_R_ErrorInit_RFM_TempCoctFileNotFound	0xf00022
#define PM_R_ErrorInit_RFM_CalFileNotFound			0xf00023
#define PM_R_ErrorInit_RFM_PowerLevel380Error		0xf00024
#define PM_R_ErrorInit_RFM_SelfTest_PwrDetector	0xf00025
#define PM_R_ErrorInit_RFM_SelfTest_HighBandMixer	0xf00026
#define PM_R_ErrorInit_RFM_SelfTest_LowBandMixer	0xf00027

#define PM_R_ErrorInit_RFM_SelfTest_Attenuator		0xf00028
#define PM_R_ErrorInit_RFM_SelfTest_SecondIF		0xf00029

#define PM_R_ErrorInit_RFM_RangeOver_CenterMIN	    0xf0002a
#define PM_R_ErrorInit_RFM_RangeOver_CenterMAX	    0xf0002b
#define PM_R_ErrorInit_RFM_RangeOver_SPANMIN		0xf0002c
#define PM_R_ErrorInit_RFM_RangeOver_SPANMAX		0xf0002d


#define PM_R_ErrorInit_PowerSensor_ttyUSBx			0xf00030
#define PM_R_ErrorInit_FWupdate_NotFoundFile		0xf00031
#define PM_R_ErrorInit_FWupdate_MountError			0xf00032
#define PM_R_ErrorInit_FWupdate_NotFoundUSBM		0xf00033
#define PM_R_ErrorInit_FWupdate_UpdateFail			0xf00034

#define PM_R_ErrorInit_Read_CalTable_Amp_org		0xf00040
#define PM_R_ErrorInit_Read_CalTable_Amp_intp		0xf00041
#define PM_R_ErrorInit_Read_CalTable_Preamp_org	0xf00042
#define PM_R_ErrorInit_Read_CalTable_Preamp_intp	0xf00043
#define PM_R_ErrorInit_Read_CalTable_freq_org		0xf00044
