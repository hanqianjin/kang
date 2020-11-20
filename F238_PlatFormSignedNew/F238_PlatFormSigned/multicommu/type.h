#ifndef BASICTYPE_H
#define BASICTYPE_H

#include <QObject>

#define CHANNEL_NUM         7
#define WIRING_GROUP_MAX    3
#define CHANNEL_POWERBOARD_TOTAL      8		 //功率子板最大个数
//#define MOTOR_SLOT          ((BoardSlot)((PhySics_Slot1) + CHANNEL_NUM))
//#define LAST_POWER_SLOT     ((PhySics_Slot1) + CHANNEL_NUM - 1)
//#define LAST_WIR_SLOT       ((Channel_wir1) + WIRING_GROUP_MAX - 1)
//#define WIR_SLOT(x)         ((Channel_wir1) + x - 1)
typedef enum MEAUSRE_WINDOW{
    WIN_NULL            = 0x0000,
    WIN_NUMERIC         = 0x0001,
    WIN_WAVE            = 0x0002,
    WIN_WAVEOPERATOR    = 0x0004,
    WIN_TREND           = 0x0008,
    WIN_IECHARM         = 0x0010,
    WIN_FFT             = 0x0020,
    WIN_VECTOR          = 0x0040,
    WIN_FLICKER         = 0x0080,
    WIN_BAR             = 0x0100,
    WIN_MOTOR           = 0x0200,
    WIN_INFO            = 0x0400,
    WIN_HELPMANUAL      = 0x0800,
    WIN_ROOT            = 0x1000,
    WIN_SPLITTER        = 0x2000,
}MeasureWindow;

typedef enum enum_element
{
    Element1 = 0x00000001,
    Element2 = 0x00000002,
    Element3 = 0x00000004,
    Element4 = 0x00000008,
    Element5 = 0x00000010,
    Element6 = 0x00000020,
    Element7 = 0x00000040,
    ElementAll = 0x0000007f,
}ElementChannel;

//基本测试功能对象索引枚举值定义
typedef enum enum_BasicItem
{
    // PowerBoard or WiringGroup (36): Start(Urms)-End(WQ) <==> [1, 35]
    None = 0    ,ItemUrms    ,ItemIrms   ,ItemUmn     ,ItemImn    ,ItemUdc    ,ItemIdc    ,ItemUac     ,ItemIac    ,ItemUrmn     ,
    ItemIrmn    ,ItemP       ,ItemS      ,ItemQ       ,ItemLambda ,ItemPhi    ,ItemFreqU  ,ItemFreqI   ,ItemUpUpeak,ItemUpIpeak  ,
    ItemLowUpeak,ItemLowIpeak,ItemUpPpeak,ItemLowPpeak,ItemCfU    ,ItemCfI    ,ItemPc     ,ItemTime    ,ItemWP     ,ItemWPplus   ,
    ItemWPminus ,Item_q      ,Item_qPlus ,Item_qMinus ,ItemWS     ,ItemWQ,
    // PowerBoard (27): Start(U(*))-End(hcf) <==> [36, 62]
    ItemU0      ,ItemI0      ,ItemP0     ,ItemS0      ,ItemQ0     ,ItemLambda0,ItemPhi0   ,ItemPhiU0   ,ItemPhiI0  ,ItemZ0       ,
    ItemRs0     ,ItemXs0     ,ItemRp0    ,ItemXp0     ,ItemUhdf0  ,ItemIhdf0  ,ItemPhdf0  ,ItemUthd    ,ItemIthd   ,ItemPthd     ,
    ItemK_Factor,ItemUthf    ,ItemIthf   ,ItemUtif    ,ItemItif   ,Item_hvf   ,Item_hcf,
    // WiringGroup (12): Start(ΔF1)-End(φUi_Ik) <==> [63, 74]
    ItemDeltaF1 ,ItemDeltaF2 ,ItemDeltaF3,ItemDeltaF4 ,ItemDeltaP1,ItemDeltaP2,ItemDeltaP3,ItemPhiUi_Uj,ItemPhiUi_Uk,ItemPhiUi_Ii,
    ItemPhiUi_Ij,ItemPhiUi_Ik,
    // MotorBoard (11): Start(Speed)-End(Pm2) <==> [75, 85]
    ItemSpeed   ,ItemTorque  ,ItemTheta  ,ItemSyncSp  ,ItemSlip   ,ItemPm     ,ItemSpeed2  ,ItemTorque2,ItemSyncSp2 ,ItemSlip2   ,
    ItemPm2,
    // UserDefined1 (8): Start(η1)-End(Udef2) <==> [86, 93]
    ItemEta1    ,ItemEta2    ,ItemEta3   ,ItemEta4    ,ItemEta5   ,ItemEta6   ,ItemUdef1   ,ItemUdef2,
    // UserDefined2 (20): Start(F1)-End(F20) <==> [94, 113]
    ItemF1      ,ItemF2      ,ItemF3     ,ItemF4      ,ItemF5     ,ItemF6     ,ItemF7      ,ItemF8     ,ItemF9      ,ItemF10     ,
    ItemF11     ,ItemF12     ,ItemF13    ,ItemF14     ,ItemF15    ,ItemF16    ,ItemF17     ,ItemF18    ,ItemF19     ,ItemF20     ,
    // SUM: 36 + 27 + 12 + 11 + 8 + 20 = 114 即Number值为114
    ItemNumber,
}BasicItems;
typedef enum E_BoardSlot
{
    Slot_None = -1,
    PhySics_Slot1 = 0,
    PhySics_Slot2,
    PhySics_Slot3,
    PhySics_Slot4,
    PhySics_Slot5,
    PhySics_Slot6,
    PhySics_Slot7,
    PhySics_Slot8,
    Channel_wir1,				//该对象从属于接线组A
    Channel_wir2,				//该对象从属于接线组B
    Channel_wir3,				//该对象从属于接线组C
    Channel_max
}BoardSlot;

typedef struct ITEM_BUFFER_TYPE{
    BoardSlot item_Channel;
    BasicItems item_Function;
    unsigned int item_Order;
}ITEM_BUFFER;

typedef enum E_ScpiMode{
    Mode_local = 0,
    Mode_remote_internet,
    Mode_remote_usb,
    Mode_remote_gpib,
    Mode_remote_uart,
}ScpiMode;

typedef enum E_ScpiPort{
    Port_null,
    Port_internet,
    Port_usb,
    Port_gpib,
    Port_uart,
}ScpiPort;

typedef struct SYSTEM_STATUS_TYPE{
    ScpiMode        mode;
    ScpiPort        port;
}SYSTEM_STATUS;

#endif // BASICTYPE_H
