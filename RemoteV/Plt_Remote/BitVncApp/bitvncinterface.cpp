#include "bitvncinterface.h"
#include "bitvnchandle.h"

static char* triggerMode[6] = {"FREerun","EXTErnal","VIDEo","PERIodic","RFBUrst","GPS"};
bitvncinterface::bitvncinterface()
{

}

void bitvncinterface::SetCenterFreq(qreal mFreqHz)
{
    QString iVal = QString::number(mFreqHz);
    QString strCmd = ":FREQuency:CENTer ";
    strCmd += iVal;
    //BitVncHandle::GetVncInternetHandle()->write;
    //发送SCPI指令
}

qreal bitvncinterface::GetCenterFreq()
{
    QString strCmd = ":FREQuency:CENTer?";
    //发送SCPI指令
}

void bitvncinterface::SetStartFreq(qreal mFreqHz)
{
    QString iVal = QString::number(mFreqHz);
    QString strCmd = ":FREQuency:STARt ";
    strCmd += iVal;
    //发送SCPI指令
}

qreal bitvncinterface::GetStartFreq(qreal mFreqHz)
{
    QString strCmd = ":FREQuency:STARt?";
    //发送SCPI指令
}

void bitvncinterface::SetStopFreq(qreal mFreqHz)
{
    QString iVal = QString::number(mFreqHz);
    QString strCmd = ":FREQuency:STOP ";
    strCmd += iVal;
    //发送SCPI指令
}

qreal bitvncinterface::GetStopFreq(qreal mFreqHz)
{
    QString strCmd = ":FREQuency:STOP?";
}
#if 0
void bitvncinterface::SetStepFreq(qreal mFreqHz)
{
    QString iVal = QString::number(mFreqHz);
    QString strCmd = ":FREQuency:STEP ";
    strCmd += iVal;
    //发送SCPI指令
}

qreal bitvncinterface::GetStepFreq(qreal mFreqHz)
{
    QString strCmd = ":FREQuency:STEP?";
}

void bitvncinterface::SetFreqOffset(qreal mFreqHz)
{
    QString iVal = QString::number(mFreqHz);
    QString strCmd = ":FREQuency:OFFSet ";
    strCmd += iVal;
    //发送SCPI指令
}

qreal bitvncinterface::GetFreqOffset(qreal mFreqHz)
{
    QString strCmd = ":FREQuency:OFFSet?";
}

void bitvncinterface::SetSpan(qreal mFreqHz)
{
    QString iVal = QString::number(mFreqHz);
    QString strCmd = ":FREQuency:SPAN ";
    strCmd += iVal;
    //发送SCPI指令
}

qreal bitvncinterface::GetSpan(qreal mFreqHz)
{
    QString strCmd = ":FREQuency:SPAN?";
}

void bitvncinterface::SetFullSpan()
{
    QString strCmd = ":FREQuency:SPAN:FULL";
    //发送SCPI指令
}

void bitvncinterface::SetZeroSpan()
{
    QString strCmd = ":FREQuency:SPAN:ZERO";
}

void bitvncinterface::SetLastSpan()
{
    QString strCmd = ":FREQuency:SPAN:PREVious";
}

/*        Ampt          */
void bitvncinterface::SetAutoScale()
{
    QString strCmd = ":AMPLitude:SCALe:AUTO";
}

void bitvncinterface::SetAmptRefLevel(qreal mAmptdBm)
{
    QString iVal = QString::number(mAmptdBm);
    QString strCmd = ":AMPLitude:RLEVel ";
    strCmd += iVal;
}

qreal bitvncinterface::GetAmptRefLevel()
{
    QString strCmd = ":AMPLitude:RLEVel?";
}

void bitvncinterface::SetAmptScale(qreal mAmptdB)
{
    QString iVal = QString::number(mAmptdB);
    QString strCmd = ":AMPLitude:RLEVel ";
    strCmd += iVal;
}

qreal bitvncinterface::GetAmptScale()
{
    QString strCmd = ":AMPLitude:RLEVel?";
}

void bitvncinterface::SetAmptAutoAtten(qint32 isAuto)
{
    isAuto = !!isAuto;
    QString iVal = QString::number(isAuto);
    QString strCmd = ":AMPLitude:ATTEnuation:AUTO  ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetAmptAutoAtten()
{
    QString strCmd = ":AMPLitude:ATTEnuation:AUTO?";
}

void bitvncinterface::SetAmptAttenValue(qreal mAmptdB)
{
    QString iVal = QString::number(mAmptdB);
    QString strCmd = ":AMPLitude:ATTEnuation ";
    strCmd += iVal;
}

qreal bitvncinterface::GetAmptScale()
{
    QString strCmd = ":AMPLitude:ATTEnuation?";
}

void bitvncinterface::SetAmptPreampState(qint32 isOn)
{
    isOn = !!isOn;
    QString iVal = QString::number(isOn);
    QString strCmd = ":AMPLitude:PREAmp ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetAmptPreampState()
{
    QString strCmd = ":AMPLitude:PREAmp?";
}

void bitvncinterface::SetAmptRefOffet(qreal mAmptdB)
{
    QString iVal = QString::number(mAmptdB);
    QString strCmd = ":AMPLitude:RLEVel:OFFSet ";
    strCmd += iVal;
}

qreal bitvncinterface::GetAmptScale()
{
    QString strCmd = ":AMPLitude:RLEVel:OFFSet?";
}

void bitvncinterface::SetAmptUnit(qint32 isOn)
{
    isOn = !!isOn;
    QString iVal = QString::number(isOn);
    QString strCmd = ":AMPLitude:PDIVision ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetAmptAmptUnit()
{
    QString strCmd = ":AMPLitude:PDIVision?";
}

/*            Sweep               */
void bitvncinterface::SetSweepAutoTime(qint32 isAuto)
{
    isAuto = !!isAuto;
    QString iVal = QString::number(isAuto);
    QString strCmd = ":SWEEp:TIME:AUTO ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetSweepAutoTime()
{
    QString strCmd = ":SWEEp:TIME:AUTO?";
}

void bitvncinterface::SetSweepTime(qreal mTimeMs)
{
    QString iVal = QString::number(mTimeMs);
    QString strCmd = ":SWEEp:TIME ";
    strCmd += iVal;
}

qreal bitvncinterface::GetSweepAutoTime()
{
    QString strCmd = ":SWEEp:TIME?";
}

void bitvncinterface::SetSweepState(qint32 isCont)
{
    isCont = !!isCont;
    QString iVal = QString::number(isCont);
    QString strCmd = ":SWEEp:CONTinuous ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetSweepAutoTime()
{
    QString strCmd = ":SWEEp:CONTinuous?";
}

/*             BW                      */

void bitvncinterface::SetAutoRBW(qint32 isAuto)
{
    isAuto = !!isAuto;
    QString iVal = QString::number(isAuto);
    QString strCmd = ":BANDwidth:RBW:AUTO ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetAutoRBW()
{
    QString strCmd =":BANDwidth:RBW:AUTO?";
}

void bitvncinterface::SetRBWValue(qreal mAmptdBm)
{
    QString iVal = QString::number(mAmptdBm);
    QString strCmd = ":BANDwidth:RBW ";
    strCmd += iVal;
}

qreal bitvncinterface::GetRBWValue()
{
    QString strCmd =":BANDwidth:RBW?";
}

void bitvncinterface::SetAutoVBW(qint32 isAuto)
{
    isAuto = !!isAuto;
    QString iVal = QString::number(isAuto);
    QString strCmd = ":BANDwidth:VBW:AUTO ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetAutoVBW()
{
    QString strCmd =":BANDwidth:VBW:AUTO?";
}

void bitvncinterface::SetVBWValue(qreal mAmptdBm)
{
    QString iVal = QString::number(mAmptdBm);
    QString strCmd = ":BANDwidth:VBW ";
    strCmd += iVal;
}

qreal bitvncinterface::GetVBWValue()
{
    QString strCmd =":BANDwidth:VBW?";
}

void bitvncinterface::SetRatioValue(qreal mRatio)
{
    QString iVal = QString::number(mRatio);
    QString strCmd = "::BANDwidth:RATIo ";
    strCmd += iVal;
}

qreal bitvncinterface::GetRatioValue()
{
    QString strCmd =":BANDwidth:RATIo?";
}

void bitvncinterface::SetIFOutput(qint32 index)
{
    QString iVal = QString::number(index);
    QString strCmd = ":IFOUtput ";
    strCmd += iVal;
}

qint32 bitvncinterface::GetAutoVBW()
{
    QString strCmd =":IFOUtput?";
}

/*           Trigger            */
void bitvncinterface::SetTriggerMode(qint32 mMode)
{
    QString iVal = QString::number(mMode);
    QString strCmd = ":TRIGger:SOURce ";
    strCmd += iVal;
}
qint32 bitvncinterface::GetTriggerMode()
{
    QString strCmd =":TRIGger:SOURce?";
}

void bitvncinterface::SetTriggerLevel(qreal mLevel,qint32 mode)
{
    QString iVal = QString::number(mLevel);
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:LEVEl ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:LEVEl ").arg(QString(triggerMode[mode]));
    }
    strCmd += iVal;
}
qreal bitvncinterface::GetTriggerLevel(qint32 mode)
{
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:LEVEl?";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:LEVEl?").arg(QString(triggerMode[mode]));
    }
}

void bitvncinterface::SetTriggerSlope(qint32 mSlope,qint32 mode)
{
    QString iVal = QString::number(mSlope);
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:SLOPe ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:SLOPe ").arg(QString(triggerMode[mode]));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetTriggerSlope(qint32 mode)
{
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:SLOPe?";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:SLOPe?").arg(QString(triggerMode[mode]));
    }
}

void bitvncinterface::SetTriggerDelayState(qint32 mState,qint32 mode)
{
    QString iVal = QString::number(mState);
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:DELAy:STATe ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:DELAy:STATe ").arg(QString(triggerMode[mode]));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetTriggerDelayState(qint32 mode)
{
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:DELAy:STATe?";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:DELAy:STATe?").arg(QString(triggerMode[mode]));
    }
}

void bitvncinterface::SetTriggerDelayValue(qreal value,qint32 mode)
{
    QString iVal = QString::number(value);
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:DELAy ";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:DELAy ").arg(QString(triggerMode[mode]));
    }
    strCmd += iVal;
}
qreal bitvncinterface::GetTriggerDelayValue(qint32 mode)
{
    QString strCmd;
    if(mode < 0 || mode > 5)
    {
        strCmd = ":TRIGger:DELAy?";
    }
    else
    {
        strCmd = QString(":TRIGger:%1:DELAy?").arg(QString(triggerMode[mode]));
    }
}

void bitvncinterface::SetTriggerPeriodic(qreal time)
{
    QString iVal = QString::number(time);
    QString strCmd = ":TRIGger:PERiodic ";
    strCmd += iVal;
}
qreal bitvncinterface::GetTriggerPeriodic()
{
    QString strCmd = ":TRIGger:PERiodic?";
}

/*           Trace           */
void bitvncinterface::SetTraceViewState(qint32 mState,qint32 mTrace)
{
    QString strCmd;
    QString iVal = QString::number(mState);

    if(mTrace < 0)
    {
        strCmd = ":TRACe:DISPlay ";
    }else
    {
        strCmd = QString(":TRACe:%1:DISPlay ").arg(QString::number(mTrace));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetTraceViewState(qint32 mTrace)
{
    QString strCmd;
    if(mTrace < 0)
    {
        strCmd = ":TRACe:DISPlay?";
    }else
    {
        strCmd = QString(":TRACe:%1:DISPlay?").arg(QString::number(mTrace));
    }

}

void bitvncinterface::SetTraceType(qint32 mType,qint32 mTrace)
{
    QString strCmd;
    QString iVal = QString::number(mType);

    if(mTrace < 0)
    {
        strCmd = ":TRACe:TYPE ";
    }else
    {
        strCmd = QString(":TRACe:%1:TYPE ").arg(QString::number(mTrace));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetTraceType(qint32 mTrace)
{
    QString strCmd;
    if(mTrace < 0)
    {
        strCmd = ":TRACe:TYPE?";
    }else
    {
        strCmd = QString(":TRACe:%1:TYPE?").arg(QString::number(mTrace));
    }

}

void bitvncinterface::SetTraceAvecount(qint32 value,qint32 mTrace)
{
    QString strCmd;
    QString iVal = QString::number(value);

    if(mTrace < 0)
    {
        strCmd = ":MARKer:TRACe:AVECount ";
    }else
    {
        strCmd = QString(":MARKer:%1:TRACe:AVECount ").arg(QString::number(mTrace));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetTraceAvecount(qint32 mTrace)
{
    QString strCmd;
    if(mTrace < 0)
    {
        strCmd = ":TRACe:AVECount?";
    }else
    {
        strCmd = QString(":TRACe:%1:AVECount?").arg(QString::number(mTrace));
    }
}

void bitvncinterface::SetTraceDetector(qint32 value)
{
    QString strCmd;
    QString iVal = QString::number(value);
    strCmd = ":TRACe:DETEctor ";
    strCmd += iVal;
}
qint32 bitvncinterface::GetTraceDetector()
{
    QString strCmd = ":TRACe:DETEctor?";

}

/* Marker */

void bitvncinterface::SetMarkerSelect(qint32 mMarker)
{
    QString iVal = QString::number(mMarker);

    QString strCmd = ":MARKer:SELEct ";
    strCmd += iVal;
}
qint32 bitvncinterface::GetMarkerSelect()
{
    QString strCmd =":MARKer:SELEct?";
}


void bitvncinterface::SetMarkerViewState(qint32 mState,qint32 mMarker)
{
    QString strCmd;
    QString iVal = QString::number(mState);

    if(mMarker < 0)
    {
        strCmd = ":MARKer:DISPlay ";
    }else
    {
        strCmd = QString(":MARKer:%1:DISPlay ").arg(QString::number(mMarker));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetMarkerViewState(qint32 mMarker)
{
    QString strCmd;
    if(mMarker < 0)
    {
        strCmd = ":MARKer:DISPlay?";
    }else
    {
        strCmd = QString(":MARKer:%1:DISPlay?").arg(QString::number(mMarker));
    }

}

void bitvncinterface::SetMarkerViewType(qint32 mType,qint32 mMarker)
{
    QString strCmd;
    QString iVal = QString::number(mType);

    if(mMarker < 0)
    {
        strCmd = ":MARKer:TYPE ";
    }else
    {
        strCmd = QString(":MARKer:%1:TYPE ").arg(QString::number(mMarker));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetMarkerType(qint32 mMarker)
{
    QString strCmd;
    if(mMarker < 0)
    {
        strCmd = ":MARKer:TYPE?";
    }else
    {
        strCmd = QString(":MARKer:%1:TYPE?").arg(QString::number(mMarker));
    }

}

void bitvncinterface::SetMkrToCenter()
{
    QString strCmd = ":MARKer:TO:CENTer";
}
void bitvncinterface::SetMkrToStart()
{
    QString strCmd = ":MARKer:TO:STARt";
}
void bitvncinterface::SetMkrToStop()
{
    QString strCmd = ":MARKer:TO:STOP";
}

void bitvncinterface::SetMarkerFreq(qreal mFreqHz,qint32 mMarker)
{
    QString strCmd;
    QString iVal = QString::number(mFreqHz);

    if(mMarker < 0)
    {
        strCmd = ":MARKer:X ";
    }else
    {
        strCmd = QString(":MARKer:%1:X ").arg(QString::number(mMarker));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetMarkerFreq(qint32 mMarker)
{
    QString strCmd;
    if(mMarker < 0)
    {
        strCmd = ":MARKer:X?";
    }else
    {
        strCmd = QString(":MARKer:%1:X?").arg(QString::number(mMarker));
    }

}

void bitvncinterface::SetMkrFreqCountState(qint32 mState,qint32 mMarker)
{
    QString strCmd;
    QString iVal = QString::number(mState);

    if(mMarker < 0)
    {
        strCmd = ":MARKer:FCOUnt:STATe ";
    }else
    {
        strCmd = QString(":MARKer:%1:FCOUnt:STATe ").arg(QString::number(mMarker));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetMkrFreqCountState(qint32 mMarker)
{
    QString strCmd;
    if(mMarker < 0)
    {
        strCmd = ":MARKer:FCOUnt:STATe?";
    }else
    {
        strCmd = QString(":MARKer:%1:FCOUnt:STATe?").arg(QString::number(mMarker));
    }

}

void bitvncinterface::SetMkrNoiseState(qint32 mState,qint32 mMarker)
{
    QString strCmd;
    QString iVal = QString::number(mState);

    if(mMarker < 0)
    {
        strCmd = ":MARKer:NOISe:STATe ";
    }else
    {
        strCmd = QString(":MARKer:%1:NOISe:STATe ").arg(QString::number(mMarker));
    }
    strCmd += iVal;
}
qint32 bitvncinterface::GetMkrNoiseState(qint32 mMarker)
{
    QString strCmd;
    if(mMarker < 0)
    {
        strCmd = ":MARKer:NOISe:STATe?";
    }else
    {
        strCmd = QString(":MARKer:%1:NOISe:STATe?").arg(QString::number(mMarker));
    }

}

void bitvncinterface::SetPeakMax()
{
    QString strCmd = ":MARKer:PMAXimum";
}
void bitvncinterface::SetPeakMin()
{
    QString strCmd = ":MARKer:PMINimum";
}
void bitvncinterface::SetPeakNextMax()
{
    QString strCmd = ":MARKer:PMAXimum:NEXT";
}
void bitvncinterface::SetPeakLeftMax()
{
    QString strCmd = ":MARKer:PMAXimum:LEFT";
}
void bitvncinterface::SetPeakRightMax()
{
    QString strCmd = ":MARKer:PMAXimum:RIGHt";
}

void bitvncinterface::SetPeakTrackState(qint32 mState)
{
    QString strCmd;
    QString iVal = QString::number(mState);

    strCmd = ":MARKer:PTRAck ";

    strCmd += iVal;
}
qint32 bitvncinterface::GetPeakTrackState()
{
    QString strCmd = QString(":MARKer:PTRAck?");
}

/*        Limit         */
void bitvncinterface::SetLimitSelect(qint32 mLimit)
{
    QString iVal = QString::number(mLimit);

    QString strCmd = ":LIMIt:SELEct ";
    strCmd += iVal;
}
qint32 bitvncinterface::GetLimitSelect()
{
    QString strCmd =":LIMIt:SELEct?";
}

void bitvncinterface::SetLimitViewState(qint32 mState,qint32 mLimit)
{
    QString strCmd;
    QString iVal = QString::number(mState);

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:DISPlay ";
    }else
    {
        strCmd = QString(":LIMIt:%1:DISPlay ").arg(QString::number(mLimit));
    }
    strCmd += iVal;
}

qint32 bitvncinterface::GetLimitViewState(qint32 mLimit)
{
    QString strCmd;
    if(mLimit < 0)
    {
        strCmd = ":LIMIt:DISPlay?";
    }else
    {
        strCmd = QString(":LIMIt:%1:DISPlay?").arg(QString::number(mLimit));
    }

}

void bitvncinterface::SetLimitEdgeState(qint32 mState,qint32 mLimit)
{
    QString strCmd;
    QString iVal = QString::number(mState);

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:EDGE:STATe ";
    }else
    {
        strCmd = QString(":LIMIt:%1:EDGE:STATe ").arg(QString::number(mLimit));
    }
    strCmd += iVal;
}

qint32 bitvncinterface::GetLimitEdgeState(qint32 mLimit)
{
    QString strCmd;

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:EDGE:STATe?";
    }else
    {
        strCmd = QString(":LIMIt:%1:EDGE:STATe?").arg(QString::number(mLimit));
    }
}

void bitvncinterface::SetLimitEdgeValue(qreal value,qint32 mLimit)
{
    QString strCmd;
    QString iVal = QString::number(value);

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:EDGE ";
    }else
    {
        strCmd = QString(":LIMIt:%1:EDGE ").arg(QString::number(mLimit));
    }
    strCmd += iVal;
}

qint32 bitvncinterface::GetLimitEdgeValue(qint32 mLimit)
{
    QString strCmd;

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:EDGE?";
    }else
    {
        strCmd = QString(":LIMIt:%1:EDGE?").arg(QString::number(mLimit));
    }
}

void bitvncinterface::SetLimitTest(qint32 value)
{
    QString iVal = QString::number(value);

    QString strCmd = ":LIMIt:TEST ";
    strCmd += iVal;
}
qint32 bitvncinterface::GetLimitTest()
{
    QString strCmd =":LIMIt:TEST?";
}

void bitvncinterface::SetLimitType(qint32 mType,qint32 mLimit)
{
    QString strCmd;
    QString iVal = QString::number(mType);

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:TYPE ";
    }else
    {
        strCmd = QString(":LIMIt:%1:TYPE ").arg(QString::number(mLimit));
    }
    strCmd += iVal;
}

qint32 bitvncinterface::GetLimitType(qint32 mLimit)
{
    QString strCmd;

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:TYPE?";
    }else
    {
        strCmd = QString(":LIMIt:%1:TYPE?").arg(QString::number(mLimit));
    }
}

void bitvncinterface::SetLimitDeleteRow(qint32 mLimit)
{
    QString strCmd;

    if(mLimit < 0)
    {
        strCmd = ":LIMIt:DELEte";
    }else
    {
        strCmd = QString(":LIMIt:%1:DELEte").arg(QString::number(mLimit));
    }
}
void bitvncinterface::SetLimitDeleteAllRow()
{
    QString strCmd = QString(":LIMIt:ALL:DELEte");
}
#endif
