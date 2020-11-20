#ifndef RTSA_EXTERN_H
#define RTSA_EXTERN_H

enum {
    UNIT_GHZ = 1,
    UNIT_MHZ = 2,
    UNIT_KHZ = 3,
    UNIT_HZ = 4
};

enum {
    UNIT_NS = 1,
    UNIT_US = 2,
    UNIT_MS = 3,
    UNIT_S   = 4,
    UNIT_kS   = 5,
};

//by Steve,0308
enum RtSa_bitKey
{

  /*
  BIT_BTN_NUM1 = 2,
  BIT_BTN_NUM2 = 6,
  BIT_BTN_NUM3 = 10,
  BIT_BTN_NUM4 = 14,
  BIT_BTN_NUM5 = 18,
  BIT_BTN_NUM6 = 3,
  BIT_BTN_NUM7 = 7,
  BIT_BTN_NUM8 = 11,
  BIT_BTN_NUM9 = 15,
  BIT_BTN_NUM0 = 19,
*/


  BIT_BTN_NUM1 = 2,
  BIT_BTN_NUM2 = 3,
  BIT_BTN_NUM3 = 4,
  BIT_BTN_NUM4 = 5,
  BIT_BTN_NUM5 = 6,
  BIT_BTN_NUM6 = 7,
  BIT_BTN_NUM7 = 8,
  BIT_BTN_NUM8 = 9,
  BIT_BTN_NUM9 = 10,
  BIT_BTN_NUM0 = 11,


  BIT_DOC = 52,
  BIT_JAJ = 8,
  BIT_ESC = 1,
  BIT_MENU = 16,
  BIT_ENTER = 20,
  BIT_UP = 103,
  BIT_DOWN = 108,
  BIT_LEFT = 105,
  BIT_RIGHT = 106,
  BIT_PRESET = 0

};

enum Rtsa_keyType
{
    // 펑션키
    BTN_F1 = 0x4D,          // 77
    BTN_F2 = 0x56,          // 86
    BTN_F3 = 0x33,          // 51
    BTN_F4 = 0x36,          // 54
    BTN_F5 = 0x39,          // 57
    BTN_F6 = 0x42,          // 66

    // 모드 전환키
    MBTN_MEAS = 0x43,
    MBTN_FREQ = 0x44,
    MBTN_SPAN = 0x45,
    MBTN_MARKER = 0x46,
    MBTN_PEAK = 0x47,
    MBTN_TRACE = 0x48,
    MBTN_AMP = 0x49,
    MBTN_BWSWP = 0x4A,
    MBTN_SYSTEM = 0x4B,
    MBTN_PRESET = 0x5A,
    //MBTN_SCREEN_SAVE = 0x4F,

    // 숫자키 및 기호키
    BTN_NUM1 = 0x31,
    BTN_NUM2 = 0x34,
    BTN_NUM3 = 0x37,
    BTN_NUM4 = 0x41,
    BTN_NUM5 = 0x54,
    BTN_NUM6 = 0x55,
    BTN_NUM7 = 0x32,
    BTN_NUM8 = 0x35,
    BTN_NUM9 = 0x38,
    BTN_NUM0 = 0x30,
    BTN_MINUS = 0x53,
    BTN_PERIOD = 0x57,

    // 단위키
    BTN_GHZ = 0x4C,
    BTN_MHZ = 0x2D,
    BTN_KHZ = 0x4E,

    // 입력값 적용키 및 취소키
    BTN_ESC = 0x50,
    BTN_ENTER = 0x51,
    BTN_BSPACE = 0x4F,

    // 방향키 및 로터리
    BTN_DOWN = 0x52,
    BTN_UP = 0x3D,
    BTN_RTCW = 0x58,
    BTN_RTCCW = 0x59,

};
extern Rtsa_keyType RtSa_key;


typedef struct {
    unsigned int       pointNum;
    unsigned long long freq;
    double             powerLevel;
} _RTSA_1PONT;

typedef struct {
    _RTSA_1PONT buffer[601];
    unsigned int sweepTime;   // millisecond
} _RTSA_SM_601POINT;     // ctrlApp->GUI



//struct GUI_DRAW_SET {
//    unsigned int gridHorStep;
//    unsigned int gridVerStep;
//    int markerOnCount;   // Marker View On 갯수 저장
//    int limitLineOnCount;     // Limit Segment 설정 갯수 저장
//    int peakPos;
//}__attribute__((packed));

//extern struct GUI_DRAW_SET guiDrawSet;

//struct WATTS_UNIT {
//    char value[17];
//    char unit[3];
//}__attribute__((packed));

//extern struct WATTS_UNIT watts_unit;





//class RtSa_User_Variable;
//extern RtSa_User_Variable *globalUserVariable;


#endif // EXTERN

