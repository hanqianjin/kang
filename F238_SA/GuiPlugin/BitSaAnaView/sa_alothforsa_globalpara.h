#ifndef _SA_ALOTHFORSA_GLOBALPARA_
#define _SA_ALOTHFORSA_GLOBALPARA_

#include "sa_stdafx.h"
#include "define.h"


typedef struct
{
    qreal r;
    qreal d;
    qreal feedback;
    qreal iffreq;

} LO_FREQ_DIV; /*calc differ seg freq div values*/

//added by Steve,0227
const qreal ESP = 1.0e-3;
/*qreal freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,
                           7500000000.0,9500000000.0, 11500000000.0,13500000000.0,
                           15500000000.0,16300000000.0,17500000000.0,20000000000.0,
                           22700000000.0,26000000000.0,29000000000.0,32000000000.0,
                           35000000000.0,37800000000.0,41000000000.0,43000000000.0};*/
#ifdef SA_F239
//Johnson 190919
const qreal freqChannelList[] = {9000.0,1366250000.0,2800000000.0,7200000000.0,9500000000.0,
                            12000000000.0,15000000000.0,18000000000.0,21000000000.0,24500000000.0,
                           28000000000.0,31500000000.0,35000000000.0,39000000000.0,43000000000.0};
#endif
#ifdef SA_F238
/*190704*/
const qreal freqChannelList[] = {9000.0,1366250000.0,2600000000.0,4133750000.0,
                           7500000000.0,9500000000.0, 11500000000.0,13500000000.0,
                           15500000000.0,16300000000.0,17500000000.0,20000000000.0,
                           22420000000.0,25550000000.0,28700000000.0,31450000000.0,
                           34500000000.0,37250000000.0,39700000000.0,43000000000.0};
#endif
#ifdef SA_F238_SMART
const qreal freqChannelList[] = {9000.0,1366250000.0,2600000000.0,7200000000.0,9500000000.0,
                                 11500000000.0,13500000000.0,15000000000.0};
#endif

const SA_CHANNEL_PARAM  chparamlist[] = {
  //rbwHz fsHz  stepHz						 Nfs
    {3000, 46080, 34560, 64,   2.133, 0.0, 0.75, 32000, 1.0/46.08, 47},
    {1000, 46080, 34560, 256,  2.844, 0.0, 0.75, 128000, 1.0/46.08, 47},
    {300,  46080, 34560, 512,  1.707, 0.0, 0.75, 256000, 1.0/46.08, 47},
    {100,  46080, 34560, 2048, 2.275, 0.0, 0.75, 1024000, 1.0/46.08, 47},
    {30,   4608,  3456,  512,  1.707, 0.0, 0.75, 2560000, 1.0/4.608, 47},
    {10,   4608,  3456,  2048, 2.275, 0.0, 0.75, 10240000, 1.0/4.608, 47},
    {3,    4608,  3456,  8192, 2.731, 0.0, 0.75, 40960000, 1.0/4.608, 47},
    {1,    2304,  1843.2,  16384, 3.641, 0.0, 0.8,  1638400000, 1.0/2.304, 47}};//FFT mode

const qreal rbwList[] = {5.0e6,3.0e6,1.0e6,3.0e5,1.0e5,3.0e4,1.0e4,3000,1000,300,100,30, 10, 3, 1};
#define FFREQ 184320000

//Johnson 190621
const qint32 frbw[] = {4,8,24,80,240,800,2400,4000,4000,4000,4000,40000,40000,40000,80000};

const qreal dealTimeList[] = {1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0  ,1000.0 ,1000.0 ,1000.0,1000.0,1000.0,1000.0,1000.0,1000.0};//last part spend time
const qreal rbwtospan = 0.01;//span to rbw,when small down 1
qint32 rbwTrigDoor = 0;//set rbw when 0 ifself,1 function call
const qint32 REF_CLOCK = 50000000;//ref clock
const qreal vbwtorbw = 1.0;//vbw to rbw
const qreal firStep = 0.2;//FIR lo step
const qreal fstimens = 1000. / 46.08;//acq time

enum anaMode {FIR_MODE = 0,FFT_MODE = 3};

#ifdef SA_F239
//Johnson 190919
const LO_FREQ_DIV lodivList[] =
{
    // r  d  feedback iffreq
     {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
     {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
     {1.0,1.0,4.0,9866250000.0},//2.8~7.2G
     {1.0,1.0,4.0,3633750000.0},//7.2~9.5G
     {1.0,1.0,4.0,3633750000.0},//9.5~12G
     {1.0,1.0,4.0,3633750000.0},//12~15G
     {1.0,1.0,4.0,-3633750000.0},//15~18G
     {1.0,0.5,4.0,3633750000.0},//18~21G
     {1.0,0.5,4.0,3633750000.0},//21~24.5G
     {1.0,0.5,4.0,-3633750000.0},//24.5~28G
     {1.0,0.5,4.0,-3633750000.0},//28~31.5G
     {1.0,0.5,4.0,-3633750000.0},//31.5~35G
     {1.0,0.5,4.0,-3633750000.0},//35~39G
     {1.0,0.5,4.0,-3633750000.0}//39~43G
};
#endif
#ifdef SA_F238
const LO_FREQ_DIV lodivList[] =
{
     {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
     {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
     {1.0,1.0,4.0,9866250000.0},//2.6~4.13375G
     {1.0,1.0,4.0,9866250000.0},//4.13375~7.5G
     {1.0,1.0,4.0,3633750000.0},//7.5~9.5G
     {1.0,1.0,4.0,3633750000.0},//9.5~11.5G
     {1.0,1.0,4.0,3633750000.0},//11.5~13.5G
     {1.0,1.0,4.0,3633750000.0},//13.5~15.5G
     {1.0,1.0,4.0,3633750000.0},//15.5~16.3G
     {1.0,1.0,4.0,-3633750000.0},//16.3~17.5G
     {1.0,1.0,4.0,-3633750000.0},//17.5~20G
     {1.0,0.5,4.0,3633750000.0},//20~22.42G
     {1.0,0.5,4.0,3633750000.0},//22.42~25.55G
     {1.0,0.5,4.0,3633750000.0},//25.55~28.7G
     {1.0,0.5,4.0,3633750000.0},//28.7~31.45G
     {1.0,0.5,4.0,3633750000.0},//31.45~34.5G
     {1.0,0.5,4.0,-3633750000.0},//34.5~37.25G
     {1.0,0.5,4.0,-3633750000.0},//37.25~39.7G
     {1.0,0.5,4.0,-3633750000.0}//39.7~43G
};
#endif
#ifdef SA_F238_SMART
const LO_FREQ_DIV lodivList[] =
{
    // r  d  feedback iffreq
    {1.0,4.0,4.0,3633750000.0},//9k~1.36625G
    {1.0,2.0,4.0,3633750000.0},//1.36625-2.6GHz
    {1.0,1.0,4.0,9866250000.0},//2.6~7.2G
    {1.0,1.0,4.0,3633750000.0},//7.2~9.5G
    {1.0,1.0,4.0,3633750000.0},//9.5~11.5G
    {1.0,1.0,4.0,3633750000.0},//11.5~13.5G
    {1.0,1.0,4.0,3633750000.0}//13.5~15G
};
#endif

//0424
const qreal firfskHzlist[] = {0.25/11250.0,0.5/11250.0,0.5/5625.0,0.5/1125.0,0.5/375.0,0.25/112.5,0.25/37.5,0.5/11.25,0.5/3.75,0.5/1.125,0.5/0.375,0.5/0.1125,0.5/0.0375,0.5/0.01125,0.5/0.00375};//rbw from 5000kHz to 1 Hz

//0711
const quint32 firfliterOrder[] = {11,11,19,19,19,35,35,35,35,35,35,35,35,35,35};//rbw from 5M to 10kHz
const qreal interRuptCommutimems = 0.0;

const qreal sweepTrigCircle = 1.5;//us

//0428,lo keep time and suoxiang bujing time
//change only suoxiang bujing time from 4 to 2,0503
qreal loStepandStaytime = 0.0;//

//****used for SettingSweepTimeManmode()
static qint32 gsweepflag = 0;//when 1 means not itself call

//****used for ConfigureSweepCoupling()
static qint32 rbwFlag = 0;//1 state changed
//steve,0504
qint32 SA_autoChangerbwflag = 0;//1 change, 0 nochange
//steve,0703
qint32 SA_autoChangevbwflag = 0;//1 change, 0 nochange

//Johnson 190814
const qreal autoSetDotSweepTime[] = {0.002,0.002,0.002,0.002,0.005,0.02,0.06};//rbw from 5M to 10k,unit is ms

#endif // _SA_ALOTHFORSA_GLOBALPARA_

