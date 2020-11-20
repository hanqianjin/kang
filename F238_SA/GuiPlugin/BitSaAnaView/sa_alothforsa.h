#ifndef ALOTHFORSA_H
#define ALOTHFORSA_H

#include "sa_user_variable.h"

///////////////////////////////////////////////////////////////////////////
class alothforsa
{
public:
  alothforsa(user_variable &m_user_variable);
  user_variable *globalUserVariable;
  ~alothforsa();
 public:
  //*******external interface
  qint32 ConfigureFrequencyStartStop (qreal startFrequency,qreal stopFrequency);//**used int freq setting and span setting and auto sweep time setting
  //steve 0716 man setting sweep times
  void SettingSweepTimeManmode(qreal sweeptimems, qreal autotimems);//***used to set sweep time and this class
  //steve 0718 zero span mode vari rbw's min time ms
  qreal GetZeroSpanRbwMinms(quint32 tracenums);//***used in zerospan
  void GetZeroShmTimes(qreal timems, quint32 tracenum);//***used in zerospan
  qint32 GetrbwIndex(qreal rbwHz);//used int auto sweep time and this class
  //used in rbw setting and vbw setting and this class
  qint32 ConfigureSweepCoupling (quint32 resolutionBandwidthAuto,qreal resolutionBandwidth,quint32 videoBandwidthAuto,qreal videoBandwidth,quint32 vbwtorbwAuto,qreal vbwtorbwValue);
  void ParamConvertByRbw(qint32 iIndex);//used int auto sweep time setting and this class
public:
  //*********internal interface , used int this class
   qint32 GetFreqChannelIndex(qreal freqHz);
   void GetSegmentWaveIndex(void* param) ;
   void RefCalSweepParams(qint32 sweepMode);
   qint32 GetFftRbwIndex();
   //steve,0522,lin jie dian belong to former or later,add a param,later belong to qian,starter belong to hou duan
   void GetFreqDivValue(qreal freqHz,qreal dffthalfstepHz,quint32* intdiv,quint32* fracdiv);
   //by Steve,20180328
   void GetStepFrqDivValue(qreal startfreq,qreal stepHz,quint32* lowbits,quint32* highbits);
   void GetLastPartTime(qint32 iIndex);

   qreal caculateFreqCount(qreal centerFreq, qint32 fsr, quint32 rbwValue);

#define DOTTIME_200409 1
#define SWEEP_K 2.5




};
#endif // ALOTHFORSA_H
