#pragma once
#include "ajson/ajson.hpp"
#include <QObject>

//模块索引
typedef struct Plt_Pre_State_def
{
  qint32 powerstate = 0;
}PLTPRESTATE_DEF,*PPLTPRESTATE_DEF;
AJSON(Plt_Pre_State_def,
	powerstate)

typedef struct Plt_State_Param_def
{
    qint32 ilastallmesa[7];//-----关机时保存的工作模块(SA RTSA Interference_Analyzer Power_Meter....)测量模式索引,对应每个tab的RumMode
    qint32 iallmesa[7];//!<this used to maintain all mode now measure index,
	//!<when any mode change measure itself should reflesh this butter at the same time //--------工作时用于记录测量模式索引
	
    qint32 iuimode[4];//!<no more than 4 in ui  -------上次关机时，顶部显示的模式索引-对应每个tab的RumMode
	
	qint32 nowshowmodsum = 0;//当前显示的模式数量（对应于上方按钮，打开的tab的数量）
	quint32 orimode = 0;//!RUNMODE <last run modBitRtSa *pRtsaAna;  e,for compare now shm mode,if same,do nothing----当前工作模块
	qint32 oribtnIndex = 0;//------当前工作模块对应top按钮索引 从0开始
	
    PLTPRESTATE_DEF pltpres;//-------开机载入状态：plt_last.cond plt_default.cond plt_user.cond
	qint32 syssetindex = 0;//-----系统设置项索引，General Setting，Self Test....
	qint32 lantype = 0;//-----语言类型
	qint32 freqref = 0;//----参考类型，内参考/10MHz外参考/13MHz外参考/15MHz外参考/GPS
	
	qint32 sleept = 0;//-----lcd背光持续时间
	qint32 dismod = 0;//-----显示模式，室内/室外/夜间
	qint32 lcdbright = 0;//------LCD屏幕亮度
	qint32 soundnum = 0;//------音量
	qint32 soundswitch = 0;//声音开关
	qint32 datetype = 0;//-------日期显示格式
	
	qint32 gpswitch = 0;//-----gps开关
	qint32 gkeybeepswitch = 0;//-----按键声音开关
	qint32 lanport = 0;//-----端口
	char ipstr[32];//-----ip
	char maskstr[32];//------掩码
	char gatewaystr[32];//-----网关
	
	qint32 remoteintertype = 0;//-----程控类型，lan/蓝牙/wifi
	qint32 wifiswitch = 0;//------wifi开关
	qint32 blumode =0 ;//-----蓝牙工作模式
	qint32 bluetswitch = 0;//------蓝牙开关
	char wifimib[32];//-----wifi密码
    Plt_State_Param_def()
	{
        for (int i = 0; i < 7; ++i)
		{
			ilastallmesa[i] = 0;//-----关机时保存的测量模式索引,对应每个tab的RumMode
			iallmesa[i] = 0;//!<this used to maintain all mode now measure index,
		}
        for (int i = 0; i < 4; ++i)
		{
			iuimode[i] = 0;
		}
	}
}PLTSTATEPARAM_def,*PPSTATEPARAM_def;
AJSON(Plt_State_Param_def,
	ilastallmesa,
	//iallmesa,
	//iuimode,
    //nowshowmodsum,
	orimode,
    //oribtnIndex,
	//pltpres,
	//syssetindex,
	lantype,
	freqref,
	sleept,
	dismod,
	lcdbright,
	soundnum,
	soundswitch,
	datetype,
	gpswitch,
	gkeybeepswitch,
	//lanport,
	//ipstr,
	//maskstr,
	//gatewaystr,
	remoteintertype,
	wifiswitch,
	blumode,
	bluetswitch
	//wifimib
)

enum Notify_Type{
    SetRunModeResult = 1,
};
typedef struct ModChange_Notice_Msg{
    qint32 header;
    qint32 notify_type;
    qint32 notify_content_len;//count of Byte
    qint32 notify_content;
    qint32 check;
    ModChange_Notice_Msg(){
        header = 0x55AAAA55;
        notify_type = SetRunModeResult;
        notify_content_len = 4;
        notify_content = 0;
        check = 0;
    }
}MODCHG_NOTIC_MSG,*PMODCHG_NOTIC_MSG;

AJSON(ModChange_Notice_Msg,
      header,
      notify_type,
      notify_content_len,
      notify_content,
      check
)

