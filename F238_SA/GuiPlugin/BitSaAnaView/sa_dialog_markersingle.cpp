#include "sa_dialog_markersingle.h"
#include "ui_sa_dialog_markersingle.h"
#include "sa_applicationcontrol.h"
SA_Dialog_MarkerSingle::SA_Dialog_MarkerSingle(controlInterface *interface, user_variable *puser_variable,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_MarkerSingle)
{
    mControl = interface;
    globalUserVariable = puser_variable;

    mControl->setMarkerSelect(mIndex);
    hide();
    //mControl->setMarkerSelect(mIndex);
    //setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initWidget();
    initDisplay();
    this->setFocus();
}

SA_Dialog_MarkerSingle::~SA_Dialog_MarkerSingle()
{
    delete ui;
}
/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
 * @note   Must be placed after "initMap()";
*/
void SA_Dialog_MarkerSingle::initWidget()
{
    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPAN_MODE != mMode)
    {
        ui->lblMarkerTo->setVisible(false);
        ui->pb_Start->setVisible(false);
        ui->pb_Center->setVisible(false);
        ui->pb_Stop->setVisible(false);

        ui->lblPeak->move(18,191);
        ui->pb_PeakSearch->move(18,209);
        ui->pb_MinSearch->move(18,242);
        ui->pb_NextPeak->move(18,275);
        ui->pb_PeakLeft->move(18,308);
        ui->pb_PeakRight->move(18,341);
        ui->lblPeakTrack->move(18,391);
        ui->pb_PeakTrack->move(94,391);
    }else
    {
        ui->lblMarkerTo->setVisible(true);
        ui->pb_Start->setVisible(true);
        ui->pb_Center->setVisible(true);
        ui->pb_Stop->setVisible(true);

        ui->lblPeak->move(18,259);
        ui->pb_PeakSearch->move(18,277);
        ui->pb_MinSearch->move(18,310);

        ui->pb_NextPeak->move(18,343);
        ui->pb_PeakLeft->move(18,376);
        ui->pb_PeakRight->move(18,409);
        ui->lblPeakTrack->move(18,459);
        ui->pb_PeakTrack->move(94,459);
    }
    ui->edit_MkrFreq->setFocus();
    return;
}

/**
 * @brief  Init the display of marker setup dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-28
*/
void SA_Dialog_MarkerSingle::initDisplay()
{
    qint32 mMarkerView,mMarkerType;

    mIndex = mControl->getMarkerSelect();
    mMarkerView = mControl->getMarkerViewStatus(mIndex);
    mMarkerType = mControl->getMarkerType(mIndex);
    ui->pb_Mkr_On->setChecked(mMarkerView);
    ui->pb_PeakTrack->setChecked(mControl->getPeakTrackStatus());
    switch (mMarkerType)
    {
    case REF:
        ui->pb_Normal->setChecked(true);
        break;
    case DELTA:
        ui->pb_Delta->setChecked(true);
        break;
    case DELTA_PAIR:
        ui->pb_Delta_Pair->setChecked(true);
        break;
    default:
        break;
    }
    refreshInfo();
    return;
}
void SA_Dialog_MarkerSingle::refreshTitle()
{
    QString mTitle;
    //qint32 mMarkerType;

    mIndex = mControl->getMarkerSelect();
    //mMarkerType = mControl->getMarkerType(mIndex);
//    if(mMarkerType == REF)
//    {
        mTitle = QString("M%1").arg(QString::number(mIndex+1));
//    }else
//    {
//        mTitle = QString("D%1").arg(QString::number(mIndex+1));
//    }
    ui->lblTitle->setText(mTitle);
    return;
}

void SA_Dialog_MarkerSingle::refreshState()
{
    qint32 mMarkerView;
    mIndex = mControl->getMarkerSelect();
    mMarkerView = mControl->getMarkerViewStatus(mIndex);;
    ui->pb_Mkr_On->setChecked(mMarkerView);
    refreshMarkerEdit(mIndex);

}
void SA_Dialog_MarkerSingle::refreshMarkerEdit(qint32 index)
{
   QString strGab;
   qreal   value;
   qreal   tmpvalue;
   qint32  minus = 0;
   qint32  MkrType;
   if(index <0 ||index>=MARKER_TOTAL_CNT)
   {
       index = mControl->getMarkerSelect();
   }
   if(!mControl->getMarkerViewStatus(index) || !mControl->getTraceViewStatus())
   {
       ui->edit_MkrFreq->setText("");
       return;
   }

    MkrType = mControl->getMarkerType(index);
    if(!mControl->globalUserVariable->gSpanMode)
    {
        switch (MkrType) {
        case REF:
            value =(qreal) mControl->getMarkerRefFreq(index);
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        case DELTA:
            value = mControl->getMarkerDeltaFreq(index);
            tmpvalue =  mControl->getMarkerRefFreq(index);
            value -= tmpvalue;
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        }
        strGab =globalUserVariable->freqValueToQstring(value);
        if(minus)
        {
            strGab = "-"+strGab;
        }
    }else
    {
        switch (MkrType) {
        case REF:
            value =(qreal) mControl->getMarkerRefTime(index);
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        case DELTA:
            value = mControl->getMarkerDeltaTime(index);
            tmpvalue =  mControl->getMarkerRefTime(index);
            value -= tmpvalue;
            if(value<0)
            {
                minus = 1;
                value *= -1;
            }
            break;
        }
        strGab = globalUserVariable->TimeTransformToQstring(value);
        if(minus)
        {
            strGab = "-"+strGab;
        }
    }

    ui->edit_MkrFreq->setText(strGab);
    return;
}
void SA_Dialog_MarkerSingle::refreshInfo()
{
    qreal value,tmpvalue;
    qint32 minusFlag;
    qint32 mMarkerView = mControl->getMarkerViewStatus(mIndex);
    qint32 mMarkerType = mControl->getMarkerType(mIndex);
    qint32 mTraceView = mControl->getTraceViewStatus();
    QString strFreq,strAmpt;
    if(!mMarkerView || !mTraceView)
    {
        strFreq = "-- --";
        strAmpt = "-- --";
    }else
    {
       if(mMarkerType == REF)
       {
           if(!globalUserVariable->gSpanMode)
           {
               value =(qreal)globalUserVariable->gMarkerRefFreq[mIndex] + mControl->getFreqOffset();
               if(value<0)
               {
                   value *= -1;
                   minusFlag = 1;
               }else
               {
                   minusFlag = 0;
               }
               strFreq = globalUserVariable->freqValueToQstring(value);
               if(minusFlag)
                   strFreq="-"+strFreq;
           }
           else
           {
               value =mControl->getMarkerRefTime(mIndex);
               if(value<0)
               {
                   value *= -1;
                   minusFlag = 1;
               }else
               {
                   minusFlag = 0;
               }
               strFreq = globalUserVariable->TimeTransformToQstring(value);
               if(minusFlag)
                   strFreq="-"+strFreq;
           }

           value = (qreal)globalUserVariable ->gTraceMeasureVal[globalUserVariable ->gTraceSelect][globalUserVariable->gMarkerRefPos[mIndex]] + globalUserVariable ->gRefOffset;
           strAmpt = globalUserVariable->amptTransformToQstring(mControl->getAmpUnit(),value);
       }else if(mMarkerType == DELTA)
       {
           if(!globalUserVariable->gSpanMode)
           {
               value = globalUserVariable->gMarkerDeltaFreq[mIndex];
               tmpvalue = globalUserVariable->gMarkerRefFreq[mIndex];
               value = value -tmpvalue;
               if(value<0)
               {
                   value *= -1;
                   minusFlag = 1;
               }else
               {
                   minusFlag = 0;
               }
               strFreq = globalUserVariable->freqValueToQstring(value);
               if(minusFlag)
                   strFreq="-"+strFreq;
           }else
           {
               value = mControl->getMarkerDeltaTime(mIndex);
               tmpvalue = mControl->getMarkerRefTime(mIndex);
               value = value -tmpvalue;
               if(value<0)
               {
                   value *= -1;
                   minusFlag = 1;
               }else
               {
                   minusFlag = 0;
               }
               strFreq = globalUserVariable->TimeTransformToQstring(value);
               if(minusFlag)
                   strFreq="-"+strFreq;
           }
           value = globalUserVariable->gMarkerDeltaAmpt[mIndex];
//           strAmpt = QString::number(value,'f',2)+" dB";
//           strAmpt = globalUserVariable->amptTransformToQstring(mControl->getAmpUnit(),value);
           //value = value - tmpvalue;
           if(mControl->getAmpUnit() == SA_VOLT)
           {
               strAmpt = globalUserVariable->amptTransformToQstring(SA_DELTA_VOLT,value);
           }
           else if(mControl->getAmpUnit() ==SA_WATTS)
           {
               strAmpt = globalUserVariable->amptTransformToQstring(SA_DELTA_WATTS,value);
           }
           else
           {
               strAmpt = globalUserVariable->amptTransformToQstring(SA_NONE,value);
           }
           if(!globalUserVariable->gSpanMode)
           {
               if(globalUserVariable->gMarkerDeltaFreq[mIndex] < globalUserVariable->gStartFreq ||
                  globalUserVariable->gMarkerDeltaFreq[mIndex] > globalUserVariable->gStopFreq)
               {
                   strAmpt = "-- --";
               }
           }else
           {
               if(mControl->getMarkerDeltaTime(mIndex) < 0 ||
                   mControl->getMarkerDeltaTime(mIndex) > globalUserVariable->gSweepTime)
               {
                   strAmpt = "-- --";
               }
           }

       }else if(mMarkerType == DELTA_PAIR)
       {

       }
    }
    ui->lblFreq->setText(strFreq);
    ui->lblAmpt->setText(strAmpt);
    refreshTitle();
    refreshMarkerEdit(mIndex);
    return;
}
void SA_Dialog_MarkerSingle::on_pb_close_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_MarkerSingle::on_pb_Normal_clicked()
{
    mControl->setMarkerType(REF,mIndex);
    refreshInfo();
    return;
}

void SA_Dialog_MarkerSingle::on_pb_Delta_clicked()
{
    mControl->setMarkerType(DELTA,mIndex);
    return;
}

void SA_Dialog_MarkerSingle::on_pb_Delta_Pair_clicked()
{
    mControl->setMarkerType(DELTA_PAIR,mIndex);
    return;
}

void SA_Dialog_MarkerSingle::on_pb_Start_clicked()
{
    mControl->setMarkerToStart();
    refreshInfo();
    return;
}

void SA_Dialog_MarkerSingle::on_pb_Center_clicked()
{
    mControl->setMarkerToCF();
    refreshInfo();
    return;
}

void SA_Dialog_MarkerSingle::on_pb_Stop_clicked()
{
    mControl->setMarkerToStop();
    refreshInfo();
    return;
}

void SA_Dialog_MarkerSingle::on_pb_PeakSearch_clicked()
{
//    if(ui->pb_Mkr_On->isChecked())
//    {
//        mControl->setMarkerViewStatus(true);
//    }
    mControl->setPeak();
    refreshInfo();
    ui->pb_Mkr_On->setChecked(true);
    return;
}

void SA_Dialog_MarkerSingle::on_pb_MinSearch_clicked()
{
    mControl->setMinSearch();
    refreshInfo();
    ui->pb_Mkr_On->setChecked(true);
    return;
}

void SA_Dialog_MarkerSingle::on_pb_NextPeak_clicked()
{
    mControl->setNextPeak();
    refreshInfo();
    return;
}

void SA_Dialog_MarkerSingle::on_pb_PeakLeft_clicked()
{
     mControl->setPeakLeftSearch();
     refreshInfo();
     return;
}

void SA_Dialog_MarkerSingle::on_pb_PeakRight_clicked()
{
    mControl->setPeakRightSearch();
    refreshInfo();
    return;
}

void SA_Dialog_MarkerSingle::on_pb_Mkr_On_clicked()
{
    qint32 checked = ui->pb_Mkr_On->isChecked();
    mControl->setMarkerViewStatus(checked);
    initDisplay();
    return;
}

void SA_Dialog_MarkerSingle::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
    switch (keyvalue) {
    case Qt::Key_Escape:
        hideWidget();
        return;
    case Qt::Key_Shift:
        if(globalUserVariable->bShiftKeyPressed)
            globalUserVariable->bShiftKeyPressed = false;
        else
            globalUserVariable->bShiftKeyPressed = true;
        hideWidget();
        return;
    case Qt::Key_F3:
    case Qt::Key_F4:
        return QWidget::keyPressEvent(event);
    }
}

void SA_Dialog_MarkerSingle::on_pb_PeakTrack_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_PeakTrack->setText("On");
    }else
    {
        ui->pb_PeakTrack->setText("Off");
    }
    return ;
}

void SA_Dialog_MarkerSingle::on_pb_Mkr_On_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_Mkr_On->setText("On");
    }else
    {
        ui->pb_Mkr_On->setText("Off");
    }
    return ;
}

void SA_Dialog_MarkerSingle::on_pb_PeakTrack_clicked(bool checked)
{
    if(checked)
    {
//        if(!ui->pb_Mkr_On->isChecked())
//        {
//            ui->pb_Mkr_On->setChecked(true);
//            mControl->setMarkerViewStatus(SA_ON);
//        }
        mControl->setPeakTrackStatus(true);
    }
    else
    {
        mControl->setPeakTrackStatus(false);
    }

    initDisplay();
}
void SA_Dialog_MarkerSingle::showWidget()
{
    initDisplay();
    show();
    return;
}

void SA_Dialog_MarkerSingle::hideWidget()
{
    hide();
    emit mDialogHide();
    return;
}

void SA_Dialog_MarkerSingle::on_edit_MkrFreq_clicked()
{
    editclicked();
    return;
}

void SA_Dialog_MarkerSingle::editclicked(qint32 index)
{
    if(index < -1 || index >= MARKER_TOTAL_CNT)
    {
        index = mControl->getMarkerSelect();
    }
    qint32 MarkerType = mControl->getMarkerType(index);
    qint32 showIndex;
    if(mControl->getMarkerViewStatus(index) == SA_OFF)
        mControl->setMarkerViewStatus(SA_ON,index);
    if(MarkerType == REF)
    {
        showIndex =  SA_INPUT_MARKER_EDIT;
    }else if(MarkerType == DELTA)
    {
        showIndex =  SA_INPUT_DELTA_MARKER_EDIT;
    }
    showInputDialog(showIndex);
}

void SA_Dialog_MarkerSingle::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    return;
}

void SA_Dialog_MarkerSingle::showInputDialog(qint32 index)
{
    digitInputClose();
    mInputDialog = new SA_Dialog_DigitInput(mControl,globalUserVariable,index,this);
    mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()-DIGITINPUT_WIDTH,mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog->show();
    return ;
}

void SA_Dialog_MarkerSingle::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;
    initDisplay();
    return ;
}
