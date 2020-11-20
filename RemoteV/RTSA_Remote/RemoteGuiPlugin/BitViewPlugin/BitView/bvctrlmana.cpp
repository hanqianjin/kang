#include "bvctrlmana.h"

ctrlmana::ctrlmana(QObject *parent) : QObject(parent)
{
  gtraceonoffflag[0] = BITON;
  gtraceonoffflag[1] = BITOFF;
  gtraceonoffflag[2] = BITOFF;
  gtraceonoffflag[3] = BITOFF;
  gtraceonoffflag[4] = BITOFF;
  gtraceonoffflag[5] = BITOFF;


  gtracetype[0] = BIT_CLEAR_WRITE;
  gtracetype[1] = BIT_TRACE_OFF;
  gtracetype[2] = BIT_TRACE_OFF;
  gtracetype[3] = BIT_TRACE_OFF;
  gtracetype[4] = BIT_TRACE_OFF;
  gtracetype[5] = BIT_TRACE_OFF;

  gtraceavagflag[0] = BITOFF;
  gtraceavagflag[1] = BITOFF;
  gtraceavagflag[2] = BITOFF;
  gtraceavagflag[3] = BITOFF;
  gtraceavagflag[4] = BITOFF;
  gtraceavagflag[5] = BITOFF;

  greavagflag[0] = BITOFF;
  greavagflag[1] = BITOFF;
  greavagflag[2] = BITOFF;
  greavagflag[3] = BITOFF;
  greavagflag[4] = BITOFF;
  greavagflag[5] = BITOFF;

  gnowavagnum[0] = BITOFF;
  gnowavagnum[1] = BITOFF;
  gnowavagnum[2] = BITOFF;
  gnowavagnum[3] = BITOFF;
  gnowavagnum[4] = BITOFF;
  gnowavagnum[5] = BITOFF;

  gavagnum[0] = BIT_AVERAGE_DEFUALT;
  gavagnum[1] = BIT_AVERAGE_DEFUALT;
  gavagnum[2] = BIT_AVERAGE_DEFUALT;
  gavagnum[3] = BIT_AVERAGE_DEFUALT;
  gavagnum[4] = BIT_AVERAGE_DEFUALT;
  gavagnum[5] = BIT_AVERAGE_DEFUALT;

  gmaxkeepreflag[0] = BITOFF;
  gmaxkeepreflag[1] = BITOFF;
  gmaxkeepreflag[2] = BITOFF;
  gmaxkeepreflag[3] = BITOFF;
  gmaxkeepreflag[4] = BITOFF;
  gmaxkeepreflag[5] = BITOFF;

  gminkeepreflag[0] = BITOFF;
  gminkeepreflag[1] = BITOFF;
  gminkeepreflag[2] = BITOFF;
  gminkeepreflag[3] = BITOFF;
  gminkeepreflag[4] = BITOFF;
  gminkeepreflag[5] = BITOFF;

  gMarkerDisplay = BIT_MARKER_ONLY;
  gMarkerSelect = 0;
  gtraceIndex = 0;
  for(qint32 i=0;i<BIT_MARKER_TOTAL_CNT;i++)
  {
      gMarkerView[i] = BIT_MARKER_OFF;
      gMarkerNoise[i] = BITOFF;
      gMarkerType[i] = BIT_MARKER_ONLY;
      gMarkerNormalFreq[i] = 0;
      gMarkerNormalIndex[i] = 0;
      gMarkerDeltaFreq[i] = 0;
      gMarkerDeltaIndex[i] = 0;
      gMarkerRefAmpt[i] = 0;
      gMarkerNormalPosY[i] = 0;
  }
  gLimitSelect = 0;
  gLimitTest = BITOFF;
  gLimitVisiable = BITOFF;
  for(qint32 i=0;i<BIT_LIMIT_TOTAL_CNT;i++)
  {
      gLimitMargin[i] = 0;
      gLimitView[i] = BITOFF;
      gLimitType[i] = BIT_LIMIT_UPPER;
      gLimitPointCnt[i] = 0;
  }
  memset(&uFmtRGB,0,sizeof(uFmtRGB));
}
