#include "BitSehInfo.h"
#include "DpxContrl.h"
#include <math.h>
//macro defines
#define DPXINIADDR                 0x80000100
#define DPXBITATTENSTEPADDR        0x80000250
#define DPXDENSITYSTEPADDR         0x80000260
#define DPXBLUECOLORSTEPADDR       0x80000270
#define DPXGREENCOLORSTEPADDR      0x80000280
#define DPXREDCOLORSTEPADDR        0x80000290
#define DPXREFAMPADDR              0x800002A0
#define DPXSCALESCOPEADDR          0x800002B0
#define DPXCOUNTERADDR        	   0x800002C0
#define DPXMAXDENSITYINDEXADDR     0x800002D0
#define DPXMINDENSITYINDEXADDR     0x800002E0


//Albert 19/04/03 
#define DPX_PERSISTENCE_TIME_ADDR					0x80000110	// 7 bits (each bit indicate 50ms)
#define DPX_AMPT_AXIS_MIN_ADDR						0x80000120
#define DPX_AMPT_AXIS_ZOOM_ADDR					0x80000130
#define DPX_ALL_FFT_NUM_ADDR							0x80000150

#define DPX_COLOR_TABLE_START							0x86000000

#define DPX_FMT_DATA_START								0x86002000
#define DPX_FMT_CONFIG											0x80000140

#define DPX_PROBILITY												0x84000028



//DiUInt32 ColorTable[1024] = {0};
//Albert add density color table {0, {0%~100%},0}
DiUInt32 ColorTable[1024] = 
{
0,
0xff0000ff, 0xff0004ff, 0xff0008ff, 0xff000cff, 0xff0010ff, 0xff0014ff, 0xff0018ff, 0xff001cff, 0xff0020ff, 0xff0024ff,
0xff0028ff, 0xff002cff, 0xff0030ff, 0xff0034ff, 0xff0038ff, 0xff003cff, 0xff0040ff, 0xff0044ff, 0xff0048ff, 0xff004cff,
0xff0050ff, 0xff0054ff, 0xff0058ff, 0xff005cff, 0xff0060ff, 0xff0064ff, 0xff0068ff, 0xff006cff, 0xff0070ff, 0xff0074ff,
0xff0078ff, 0xff007cff, 0xff0080ff, 0xff0084ff, 0xff0088ff, 0xff008cff, 0xff0090ff, 0xff0094ff, 0xff0098ff, 0xff009cff,
0xff00a0ff, 0xff00a4ff, 0xff00a8ff, 0xff00acff, 0xff00b0ff, 0xff00b4ff, 0xff00b8ff, 0xff00bcff, 0xff00c0ff, 0xff00c4ff,
0xff00c8ff, 0xff00ccff, 0xff00d0ff, 0xff00d4ff, 0xff00d8ff, 0xff00dcff, 0xff00e0ff, 0xff00e4ff, 0xff00e8ff, 0xff00ecff,
0xff00f0ff, 0xff00f4ff, 0xff00f8ff, 0xff00fffc, 0xff00fff8, 0xff00fff4, 0xff00fff0, 0xff00ffec, 0xff00ffe8, 0xff00ffe4,
0xff00ffe0, 0xff00ffdc, 0xff00ffd8, 0xff00ffd4, 0xff00ffd0, 0xff00ffcc, 0xff00ffc8, 0xff00ffc4, 0xff00ffc0, 0xff00ffbc,
0xff00ffb8, 0xff00ffb4, 0xff00ffb0, 0xff00ffac, 0xff00ffa8, 0xff00ffa4, 0xff00ffa0, 0xff00ff9c, 0xff00ff98, 0xff00ff94,
0xff00ff90, 0xff00ff8c, 0xff00ff88, 0xff00ff84, 0xff00ff80, 0xff00ff7c, 0xff00ff78, 0xff00ff74, 0xff00ff70, 0xff00ff6c,
0xff00ff68, 0xff00ff64, 0xff00ff60, 0xff00ff5c, 0xff00ff58, 0xff00ff54, 0xff00ff50, 0xff00ff4c, 0xff00ff48, 0xff00ff44,
0xff00ff40, 0xff00ff3c, 0xff00ff38, 0xff00ff34, 0xff00ff30, 0xff00ff2c, 0xff00ff28, 0xff00ff24, 0xff00ff20, 0xff00ff1c,
0xff00ff18, 0xff00ff14, 0xff00ff10, 0xff00ff0c, 0xff00ff08, 0xff00ff04, 0xff00ff00, 0xff03ff00, 0xff07ff00, 0xff0bff00,
0xff0fff00, 0xff13ff00, 0xff17ff00, 0xff1bff00, 0xff1fff00, 0xff23ff00, 0xff27ff00, 0xff2bff00, 0xff2fff00, 0xff33ff00,
0xff37ff00, 0xff3bff00, 0xff3fff00, 0xff43ff00, 0xff47ff00, 0xff4bff00, 0xff4fff00, 0xff53ff00, 0xff57ff00, 0xff5bff00,
0xff5fff00, 0xff63ff00, 0xff67ff00, 0xff6bff00, 0xff6fff00,0xff73ff00,  0xff77ff00, 0xff7bff00, 0xff7fff00, 0xff83ff00,
0xff87ff00, 0xff8bff00, 0xff8fff00, 0xff93ff00, 0xff97ff00, 0xff9bff00, 0xff9fff00, 0xffa3ff00, 0xffa7ff00, 0xffabff00,
0xffafff00, 0xffb3ff00, 0xffb7ff00, 0xffbbff00, 0xffbfff00, 0xffc3ff00, 0xffc7ff00, 0xffcbff00, 0xffcfff00, 0xffd3ff00,
0xffd7ff00, 0xffdbff00, 0xffdfff00, 0xffe3ff00, 0xffe7ff00, 0xffebff00, 0xffefff00, 0xfff3ff00, 0xfff7ff00, 0xfffbff00,
0xffffff00, 0xfffffc00, 0xfffff800, 0xfffff400, 0xfffff000, 0xffffec00, 0xffffe800, 0xffffe400, 0xffffe000, 0xffffdc00,
0xffffd800, 0xffffd400, 0xffffd000, 0xffffcc00, 0xffffc800, 0xffffc400, 0xffffc000, 0xffffbc00, 0xffffb800, 0xffffb400,
0xffffb000, 0xffffac00, 0xffffa800, 0xffffa400, 0xffffa000, 0xffff9c00, 0xffff9800, 0xffff9400, 0xffff9000, 0xffff8c00,
0xffff8800, 0xffff8400, 0xffff8000, 0xffff7c00, 0xffff7800, 0xffff7400, 0xffff7000, 0xffff6c00, 0xffff6800, 0xffff6400,
0xffff6000, 0xffff5c00, 0xffff5800, 0xffff5400, 0xffff5000, 0xffff4c00, 0xffff4800, 0xffff4400, 0xffff4000, 0xffff3c00,
0xffff3800, 0xffff3400, 0xffff3000, 0xffff2c00, 0xffff2800, 0xffff2400, 0xffff2000, 0xffff1c00, 0xffff1800, 0xffff1400,
0xffff1000, 0xffff0c00, 0xffff0800, 0xffff0400, 0xffff0000,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0
};

DiUInt32 ColorPointTable[1024] = 
{
0,
0xff0000ff, 0xff0008ff, 0xff0010ff, 0xff0018ff, 0xff0020ff,
0xff0028ff, 0xff0030ff, 0xff0038ff, 0xff0040ff, 0xff0048ff,
0xff0050ff, 0xff0058ff, 0xff0060ff, 0xff0068ff, 0xff0070ff,
0xff0078ff, 0xff0080ff, 0xff0088ff, 0xff0090ff, 0xff0098ff,
0xff00a0ff, 0xff00a8ff, 0xff00b0ff, 0xff00b8ff, 0xff00c0ff, 
0xff00c8ff, 0xff00d0ff, 0xff00d8ff, 0xff00e0ff, 0xff00e8ff,
0xff00f0ff, 0xff00f8ff, 0xff00fff8, 0xff00fff0, 0xff00ffe8, 
0xff00ffe0, 0xff00ffd8, 0xff00ffd0, 0xff00ffc8, 0xff00ffc0,
0xff00ffb8, 0xff00ffb0, 0xff00ffa8, 0xff00ffa0, 0xff00ff98, 
0xff00ff90, 0xff00ff88, 0xff00ff80, 0xff00ff78, 0xff00ff70,

0xff00ff68, 0xff00ff60, 0xff00ff58, 0xff00ff50, 0xff00ff48, 
0xff00ff40, 0xff00ff38, 0xff00ff30, 0xff00ff28, 0xff00ff20, 
0xff00ff18, 0xff00ff10, 0xff00ff08, 0xff00ff00, 0xff07ff00, 
0xff0fff00, 0xff17ff00, 0xff1fff00, 0xff27ff00, 0xff2fff00, 
0xff37ff00, 0xff3fff00, 0xff47ff00, 0xff4fff00, 0xff57ff00, 
0xff5fff00, 0xff67ff00, 0xff6fff00, 0xff77ff00, 0xff7fff00, 
0xff87ff00, 0xff8fff00, 0xff97ff00, 0xff9fff00, 0xffa7ff00,
0xffafff00, 0xffb7ff00, 0xffbfff00, 0xffc7ff00, 0xffcfff00, 
0xffd7ff00, 0xffdfff00, 0xffe7ff00, 0xffefff00, 0xfff7ff00, 
0xffffff00, 0xfffff800, 0xfffff000, 0xffffe800, 0xffffe000, 

0xffffd800, 0xffffd000, 0xffffc800, 0xffffc000, 0xffffb800, 
0xffffb000, 0xffffa800, 0xffffa000, 0xffff9800, 0xffff9000, 
0xffff8800, 0xffff8000, 0xffff7800, 0xffff7000, 0xffff6800, 
0xffff6000, 0xffff5800, 0xffff5000, 0xffff4800, 0xffff4000, 
0xffff3800, 0xffff3000, 0xffff2800, 0xffff2000, 0xffff1800, 
0xffff1000, 0xffff0800, 0xffff0000,

0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000, 0xffff0000,
0xffff0000, 0xffff0000, 
				  
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0 , 0, 0, 0, 0, 0, 0, 0, 0
};
#define DPXCOLORLEVEL         200
#define CLOCK                 180//100MHz
//---------------------------------//
  
/*
purpose:ini the ctrl of Dpx
func:DpxEn,DpxPersisteceMode,DpxBitmapCtrl,DpxBitmapExact
0param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 DpxEn(DiSession devHandle,DiInt32 dpxOpenClose)
{
#if BIT_DEBUG
return 0;
#endif
	DiUInt32 iData = 0;
	DiInt32 iBack = BitRead32(devHandle,DPXINIADDR,&iData);		
	iData &= 0xfffffffe;
	iData |= dpxOpenClose;  
	iBack = BitWrite32(devHandle,DPXINIADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_DPX_ENABLE;
	return iBack;
}
/*
purpose:ini the ctrl of Dpx
func:DpxDisable
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxOpenClose:open DPX or close DPX
return:>=0 is ok
*/
DiInt32 DpxDisable(DiSession devHandle)
{
#if BIT_DEBUG
return 0;
#endif
	DiUInt32 iBack = 0;
	iBack = BitWrite32(devHandle,DPXINIADDR,1);
	if(iBack < 0)
	  iBack = RTSA_CTL_DPX_DISABLE;
	return iBack;
}

/*
purpose:set the persistence of Dpx
func:DpxPersisteceMode
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxPersisMode:dpx persistence mode
return:>=0 is ok
*/
//DiInt32 DpxPersisteceMode(DiSession devHandle,DiInt32 dpxPersisMode)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,DPXINIADDR,&iData); 	
//	iData &= 0xfffffffd;
//	iData |= dpxPersisMode<<1;	
//	iBack = BitWrite32(devHandle,DPXINIADDR,iData);
//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;
//}

/*
purpose:set the clear contrl of Dpx
func:DpxBitmapCtrl
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxClearCtrl:dpx clear mode
return:>=0 is ok
*/
//DiInt32 DpxBitmapCtrl(DiSession devHandle,DiInt32 dpxClearCtrl)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,DPXINIADDR,&iData); 	
//	iData &= 0xfffffffb;
//	iData |= dpxClearCtrl<<2;	
//	iBack = BitWrite32(devHandle,DPXINIADDR,iData);
//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;
//}

/*
purpose:set the extrac contrl of Dpx
func:DpxBitmapExact
param:<in>devHandle:dev's ctrl handle from ini 
      <in>dpxExtrac:dpx extrac mode
return:>=0 is ok
*/

//DiInt32 DpxBitmapExact(DiSession devHandle,DiInt32 dpxExtrac)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiUInt32 iData = 0;
//	DiInt32 iBack = BitRead32(devHandle,DPXINIADDR,&iData); 	
//	iData &= 0xfffffff7;
//	iData |= dpxExtrac<<3;	
//	iBack = BitWrite32(devHandle,DPXINIADDR,iData);
//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;
//}
/*
purpose: bitmap atten step by persistence time and acquire time
func:DpxBitAttenStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>persistenceTime:set the persistence time
      <in>acqTime:set the acquire time
	  user set
return:>=0 is ok
 */
DiInt32 GetAttenStep(DiReal32 attentStep)
{
#if BIT_DEBUG
return 0;
#endif
	DiInt32 iBack = 0;
	DiInt32 data[20] = {0};
	DiReal32 tempData = attentStep;
	int i = 0;
	for(i = 0;i<20;i++)
	{
		if(tempData - 1/pow(2,i+1) == 0)
		{
			data[i] = 1;
			break;
		}
		else if(tempData - 1/pow(2,i+1) > 0)
		{
			data[i] = 1;
			tempData = tempData - 1/pow(2,i+1);
		}	
		else if(tempData - 1/pow(2,i+1) < 0)
		{
			data[i] = 0;
		}	
		iBack = iBack|(data[i]<<(19-i));
	}
	return iBack;
}
/*
purpose: bitmap atten step by persistence time and acquire time
func:DpxBitAttenStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>persistenceTime:set the persistence time
      <in>acqTime:set the acquire time
	  user set
return:>=0 is ok
 */
//DiInt32 DpxBitAttenStep(DiSession devHandle,DiReal32 persistenceTime,DiReal32 acqTime)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiUInt32 iData = 0;
//	DiInt32 iBack = 0;
//	if(acqTime - persistenceTime >= 0) iData = 1 - 1;
//	else iData = GetAttenStep(1 - acqTime/persistenceTime);
//	
//	iBack = BitWrite32(devHandle,DPXBITATTENSTEPADDR,iData);
//	if(iBack < 0)
//	   iBack = ERR_Init;
//	return iBack;
//}

/*
purpose: bitmap density step by maxDensity and minDensity
func:DpxBitDensityStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
	  user set
return:>=0 is ok
 */
//DiInt32 DpxBitDensityStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiUInt32 iData = (DiUInt32)((maxDensity - minDensity)/DPXCOLORLEVEL*100000);
//	DiInt32 iBack  = BitWrite32(devHandle,DPXDENSITYSTEPADDR,iData);

//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;
//}

/*
purpose: blue color step by maxDensity and minDensity
func:DpxBitDensityStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
      <in>curve:set the curve
	  user set
return:>=0 is ok
 */
//DiInt32 DpxBlueColorStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity,DiReal32 curve)
//{
//}

/*
purpose: green color step by maxDensity and minDensity
func:DpxGreenColorStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
      <in>curve:set the curve
	  user set
return:>=0 is ok
 */
//DiInt32 DpxGreenColorStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity,DiReal32 curve)
//{
//}

/*
purpose: red color step by maxDensity and minDensity
func:DpxRedColorStep
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the maxDensity
      <in>minDensity:set the minDensity
      <in>curve:set the curve
	  user set
return:>=0 is ok
 */
//DiInt32 DpxRedColorStep(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity,DiReal32 curve)
//{
//}
/*
purpose: reference amplitude 
func:DpxRefAmp
param:<in>devHandle:dev's ctrl handle from ini
      <in>refAmp:set the reference amplitude
      <in>refOffset:set the reference offset
	  user set
return:>=0 is ok
 */
//DiInt32 DpxRefAmp(DiSession devHandle,DiReal32 refAmp,DiReal32 refOffset)
//{
//}

/*
purpose: scale scope 
func:DpxScaleScope
param:<in>devHandle:dev's ctrl handle from ini
      <in>scaleScope:set the scale scope
	  scaleScope = 1/10*scale
return:>=0 is ok
 */
//DiInt32 DpxScaleScope(DiSession devHandle,DiReal32 scaleScope)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiReal32 iData = 1/(10  * scaleScope);
//	DiInt32 iBack  = BitWrite32(devHandle,DPXSCALESCOPEADDR,iData);

//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;
//}

/*
purpose: the max counter 
func:DpxMaxCounter
param:<in>devHandle:dev's ctrl handle from ini
      <in>persistenceTime:set the persistence time,uint must be second
	  outPutToFpga = persistenceTime/clock
return:>=0 is ok
 */
//DiInt32 DpxMaxCounter(DiSession devHandle,DiReal32 persistenceTime,DiReal32 acqTime)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiUInt32 iData = (DiUInt32)(persistenceTime * CLOCK * 1000000);
//	DiInt32 iBack  = BitWrite32(devHandle,DPXCOUNTERADDR,iData);

//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;

//}

/*
purpose: the max density index
func:DpxMaxDensityIndex
param:<in>devHandle:dev's ctrl handle from ini
      <in>maxDensity:set the max density
      <in>minDensity:set the min density
return:>=0 is ok
 */

//DiInt32 DpxMaxDensityIndex(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity)
//{
//#if BIT_DEBUG
//return 0;
//#endif
//	DiUInt32 iData = (DiUInt32)(maxDensity/((maxDensity - minDensity)/DPXCOLORLEVEL));
//	DiInt32 iBack  = BitWrite32(devHandle,DPXMAXDENSITYINDEXADDR,iData);

//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;

//}

/*
purpose: the min density index
func:DpxMinDensityIndex
param:<in>devHandle:dev's ctrl handle from ini
	  <in>maxDensity:set the max density
      <in>minDensity:set the min density
return:>=0 is ok
 */

//DiInt32 DpxMinDensityIndex(DiSession devHandle,DiReal32 maxDensity,DiReal32 minDensity)
//{
//#if BIT_DEBUG
//    return 0;
//#endif
//	DiUInt32 iData = (DiUInt32)(minDensity/((maxDensity - minDensity)/DPXCOLORLEVEL));
//	DiInt32 iBack  = BitWrite32(devHandle,DPXMINDENSITYINDEXADDR,iData);

//	if(iBack < 0)
//	  iBack = ERR_Init;
//	return iBack;

//}

/*
purpose: dpx persistence time 50ms/bits
func:DpxPersistenceTime
param:<in>devHandle:dev's ctrl handle from ini
	  <in>persistenceTime:set persistence time
return:>=0 is ok
 */
DiInt32 DpxPersistenceTime(DiSession devHandle,DiInt32 persistenceTime)
{
#if BIT_DEBUG
printf("PersistenceTime ----- %d\n",persistenceTime);
return 0;
#endif
	DiUInt32 iData = 0;
	iData &= 0xffffff00;
	iData |= (persistenceTime & 0x7f);
	DiInt32 iBack  = BitWrite32(devHandle,DPX_PERSISTENCE_TIME_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_PERSIS_TIME;
	return iBack;
}
/*
purpose: dpx ampt axis min value
func:DpxAmptAxisMin
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptMin:set ampt min value
return:>=0 is ok
 */
DiInt32 DpxAmptAxisMin(DiSession devHandle,DiInt32 amptMin)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 iData = 0;
	
	//0~15 bit set 0
	iData &=  0x00000000;
	iData |= (amptMin & 0x00ffffff);

#if BIT_DEBUG
printf("amptMin ----- %0x\n",iData);
return 0;
#endif
//	printf("amptMin ----- %0x\n",iData);
//insert
//		iBack = BitWrite32(devHandle,DPX_AMPT_AXIS_MIN_ADDR,0xf9c000);

	iBack = BitWrite32(devHandle,DPX_AMPT_AXIS_MIN_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_DPX_AXIS_MIN;
	return iBack;
}
/*
purpose: dpx ampt axis zoom value
func:DpxAmptAxisZoom
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptZoom:set ampt zoom value
return:>=0 is ok
 */
DiInt32 DpxAmptAxisZoom(DiSession devHandle,DiInt32 amptZoom)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 iData = 0;

	//0~15 bit set 0
	iData &=  0xffff0000;
	iData |= (amptZoom & 0xffff);
#if BIT_DEBUG
printf("amptZoom ----- %0x\n",amptZoom);
return 0;
#endif
//printf("amptZoom ----- %0x\n",amptZoom);
	//insert
	iBack = BitWrite32(devHandle,DPX_AMPT_AXIS_ZOOM_ADDR,iData);
	if(iBack < 0)
	  iBack = RTSA_CTL_DPX_AXIS_ZOOM;
	return iBack;
}
/*
purpose:get dpx color table
func:getDpxColorTable
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 getDpxColorTable(DiSession devHandle)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiInt32 i = 0;
	DiUInt32 tempaddr = DPX_COLOR_TABLE_START;
	DiInt32 iaddrstep = sizeof(DiUInt32);
	for(i = 0; i < 1024; i++)
		{
			iBack = BitRead32(devHandle,tempaddr, &ColorTable[i]);
			if(iBack < 0)
          {
//              printf("get dpx color table error at  %d \n",i);
              return iBack;
          }
			tempaddr += iaddrstep;
//			printf("get dpx color table ok at%d,  %0x \n",i,ColorTable[i]);
		}
	return iBack;
}

DiInt32 CalCurveColor(DiReal32 SrcColor, DiReal32 colorFactor, DiInt32 lowest, DiInt32 Highest)
{
	DiInt32 DisColor = 0;
//	printf("SrcColor----------%f            %f,   %d,    %d\n",colorFactor,SrcColor,lowest,Highest);
	DiReal32 low = (DiReal32)(lowest / 100.0);
	DiReal32 High = (DiReal32)(Highest / 100.0);
	
	if(colorFactor == 1)
		{
		if(SrcColor == 0)
			{
			   DisColor = 0;
			}
		else if(SrcColor <= low)
			{
				DisColor = 1;
			}
		else if(SrcColor >= High)
			{
			   DisColor = 255;
			}
		else
			{
				if(round(255.0 * SrcColor) > 1)
					{
						DisColor = round(255.0 * SrcColor);
					}
				else
					{
					 	DisColor = 1;
					}
			}
		}
	else
		{
		if(SrcColor == 0)
			{
			   DisColor = 0;
			}
		else if(SrcColor <= low)
			{
				DisColor = 1;
			}
		else if(SrcColor >= High)
			{
			   DisColor = 255;
			}
		else
			{
			if(round(255.0 * (pow(colorFactor, (SrcColor - low)/(High - low)) - 1) / (colorFactor-1)) > 1)
				{
					DisColor = round(255.0 * (pow(colorFactor, (SrcColor - low)/(High - low)) - 1) / (colorFactor-1));
					
				}
			else
				{
					DisColor = 1;
				}
			}
		}
		
	return DisColor;
}
/*
purpose: dpx Probability Color Table
func:setDpxColorTable
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptZoom:set ampt zoom value
return:>=0 is ok
 */
DiInt32 setHighestDpxColorTable(DiSession devHandle,DiInt32 colorFactor)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiInt32 index = (volatile DiUInt32)(colorFactor / 100.0 * 255);
//	printf("get dpx color table index %d \n",index);
	DiUInt32 tempaddr = DPX_COLOR_TABLE_START;
	DiUInt32 tempCol[1024];
	
	DiInt32 iaddrstep = sizeof(DiUInt32);
	DiInt32 i = 0;
	for(i = 0; i <  1024; i++)
		{
		tempCol[i] = ColorTable[i];
		if(i >= index)
			{
				tempCol[i] = ColorTable[255];
			}
			iBack = BitWrite32(devHandle,tempaddr, tempCol[i]);
			if(iBack < 0)
          {
              iBack = RTSA_CTL_DPX_DENSITY_HIGHEST;
              return iBack;
          }
			tempaddr += iaddrstep;
		}
	return iBack;
}
/*
purpose: dpx Probability Color Table
func:setDpxColorTable
param:<in>devHandle:dev's ctrl handle from ini
	  <in>amptZoom:set ampt zoom value
return:>=0 is ok
 */
DiInt32 setLowestDpxColorTable(DiSession devHandle,DiInt32 colorFactor)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiInt32 index = (volatile DiUInt32)(colorFactor / 100.0 * 255);
	DiUInt32 tempaddr = DPX_COLOR_TABLE_START;
//	printf("get Lowest dpx color table index %d \n",index);
	DiUInt32 tempCol[1024];
	
	DiInt32 iaddrstep = sizeof(DiUInt32);
	DiInt32 i = 0;
	tempCol[0] = 0;
	for(i = 0; i < 1024; i++)
		{
		iBack = BitRead32(devHandle,tempaddr, &tempCol[i]);
//		printf("get dpx color  %0x\n",tempCol[i]);
		if(i <= index && (i > 0))
			{
				tempCol[i] = ColorTable[1];
			}
			iBack = BitWrite32(devHandle,tempaddr, tempCol[i]);
			if(iBack < 0)
          {
              iBack = RTSA_CTL_DPX_DENSITY_LOWEST;
              return iBack;
          }
			tempaddr += iaddrstep;
		}
	return iBack;
}
/*
purpose:set dpx fmt table
func:setFmtData
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 setFmtData(DiSession devHandle, DiPInt32 data)
{
#if BIT_DEBUG
	DiInt32 j = 0;
//	for(j= 0; j < 801; j++)
//		{
//			printf("fmt data at %d,    %0x\n",data[j],data[j]);
//		}
    return 0;
#endif
	DiInt32 iBack = 0;
	DiInt32 i = 0;
	DiUInt32 tempaddr = DPX_FMT_DATA_START;
	DiInt32 iaddrstep = sizeof(DiUInt32);
	
	for(i = 0; i < 801; i++)
		{
//			printf("fmt data at %d,    %0x\n",i,data[i]);
//			printf("tempaddr   %0x\n",tempaddr);
			iBack = BitWrite32(devHandle, tempaddr, data[i]);
			if(iBack < 0)
          {
	          iBack = RTSA_CTL_FMT_DATA;
              return iBack;
          }
			tempaddr += iaddrstep;
		}
	return iBack;
}
DiInt32 setDpxCurveColor(DiSession devHandle, DiReal32 colorFactor,DiInt32 lowest, DiInt32 Highest)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;
	DiUInt32 tempaddr = DPX_COLOR_TABLE_START;
	DiUInt32 tempCol[1024];
	DiInt32 calCol;
	colorFactor = 0 - colorFactor;
	if(colorFactor == 0)
		{
			colorFactor = 1;
		}
	else if(colorFactor < 0)
		{
		 colorFactor = -1.0 / colorFactor;
		}
	DiInt32 iaddrstep = sizeof(DiUInt32);
	DiInt32 i = 0;
	DiReal32 colorSrc = 0.0;
	for(i = 0; i <  256; i++)
		{
		colorSrc = (DiReal32)(i/255.0);
		calCol = CalCurveColor(colorSrc,colorFactor,lowest,Highest);
//		printf("calCol---------- %d,    %d\n",calCol,i);
       if(calCol <= 0)
       	{
       	  tempCol[i] = 0;
       	}
	   else if(calCol >= 255)
	   	{
	   	    tempCol[i] = 0xffff0000;
	   	}
	   else if(calCol >= 64*3)
	   	{
	   	 	tempCol[i] = 0xffff0000 + (63 - calCol % 64)*1024;
	   	}
		else if(calCol >= 64*2)
		{
			tempCol[i] = (255*256 + 4*(calCol % 64) + 3)*65536 + 0xff00;
		}
		else if(calCol >= 64)
		{
		  tempCol[i] = 0xff000000 + 255*256 + 252 - (calCol % 64)*4;
		}
    else
    	{
    	   tempCol[i] = 255 + 256*((calCol % 64)*4 - 4) + 0xff000000;
    	}
	iBack = BitWrite32(devHandle,tempaddr, tempCol[i]);
			if(iBack < 0)
          {
              iBack = RTSA_CTL_DPX_CURVE;
              return iBack;
          }
			tempaddr += iaddrstep;
		}
	return iBack;
}
/*
purpose:set dpx fmt table
func:setFmtData
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 ConfigFmtReg(DiSession devHandle, DiInt32 type)
{
#if BIT_DEBUG
printf("fmt state %d\n",type);
    return 0;
#endif
	DiInt32 iBack = 0;
	DiInt32 iData = type << 18;
	iData |= (3 << 16);
	iData &= 0x7ffff;
	iBack = BitWrite32(devHandle, DPX_FMT_CONFIG, iData);
	if(iBack < 0)
		{
		  iBack = RTSA_CTL_FMT_REG;
		}
	return iBack;
}
/*
purpose:set dpx fmt trigger criterion
func:setFmtData
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 ConfigFmtTriggerCriterion(DiSession devHandle, DiInt32 type)
{
	DiInt32 iBack = 0;
	DiInt32 iData = 0;
	iBack = BitRead32(devHandle, DPX_FMT_CONFIG, &iData);
	//iData = iData  | 0x40000;
	type = type & 0xffff;
	if(type == 0)
	{
	  //iData = iData | 0x70000;
          iData = 0x70000;
	}
	else
	{
 	  iData = iData & 0x50000;
	  iData |= type;
	}

	iBack = BitWrite32(devHandle, DPX_FMT_CONFIG, iData);
	if(iBack < 0)
		{
              iBack = RTSA_CTL_FMT_CRITERION;
              return iBack;
		}
	return iBack;
}
/*
purpose:get dpx probability 
func:getDensityProbability
param:<in>devHandle:dev's ctrl handle from ini 
return:>=0 is ok
*/
DiInt32 getDensityProbability(DiSession devHandle, DiPInt32 DpxHighPro)
{
	DiInt32 iBack = 0;
#if BIT_DEBUG
return 0;
#endif
  	//read high density probality
  	iBack = BitRead32(devHandle, DPX_PROBILITY, DpxHighPro);
	if(iBack < 0)
		{
		   return 0;
		}
	return iBack;
}


DiInt32 DpxTest(DiSession devHandle)
{
#if BIT_DEBUG
    return 0;
#endif
	DiInt32 iBack = 0;

		iBack = BitWrite32(devHandle,0x80000100,0);
		
	iBack = BitWrite32(devHandle,0x80000110,0);


	iBack = BitWrite32(devHandle,0x80000120,0xf92000);

	iBack = BitWrite32(devHandle,0x80000130,0x0200);

	iBack = BitWrite32(devHandle,0x80000010,0);

	
	return iBack;
}
