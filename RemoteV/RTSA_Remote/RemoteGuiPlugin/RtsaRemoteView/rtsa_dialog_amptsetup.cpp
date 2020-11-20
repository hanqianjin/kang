#include "rtsa_dialog_amptsetup.h"
#include "ui_rtsa_dialog_amptsetup.h"
#include <QListView>
RtSa_Dialog_AmptSetup::RtSa_Dialog_AmptSetup(Rtsa_Remote_Interface *RtsaRemoteInterface,RtSa_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_AmptSetup),
    RemoteInterfaceObj(RtsaRemoteInterface),
    mInputDialog(input),
    mSelectInputID(RTSA_INPUT_REF_LEVEL),
    mUpDownFlag(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
//    ui->pb_AttenType->setView(new  QListView());
    ui->pb_unitSelect->setView(new  QListView());
    initMap();
    initDisplay();
    this->setAttribute(Qt::WA_NoChildEventsForParent,true);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    //    ui->pb_Stick->setVisible(false);
//    setAttribute(Qt::WA_DeleteOnClose);
//    setAttribute(Qt::WA_TranslucentBackground, true);
//    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Dialog);
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_ampt(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));

    setProperty("status",rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);

}
/**
 * @brief RtSa_Dialog_AmptSetup::~RtSa_Dialog_AmptSetup
 */
RtSa_Dialog_AmptSetup::~RtSa_Dialog_AmptSetup()
{
    delete ui;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_AmptSetup::initMap()
{
//    mUnitGroup = new QButtonGroup;
//    mUnitGroup->addButton(ui->pb_unit_dBm,RTSA_DBM);
////    mUnitGroup->addButton(ui->pb_unit_dBv,RTSA_DBV);
//    mUnitGroup->addButton(ui->pb_unit_dBmV,RTSA_DBMV);
//    mUnitGroup->addButton(ui->pb_unit_dBuV,RTSA_DBUV);
//    mUnitGroup->addButton(ui->pb_unit_V,RTSA_VOLT);
//    mUnitGroup->addButton(ui->pb_unit_W,RTSA_WATTS);
//    connect(mUnitGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(unitSelect(qint32)));


    mEditList.insert(RTSA_INPUT_REF_LEVEL,ui->leRefLevel);
    mEditList.insert(RTSA_INPUT_ATTEN,ui->leAtten);
    mEditList.insert(RTSA_INPUT_SCALEDIV,ui->leScaleDiv);
    mEditList.insert(RTSA_INPUT_REF_OFFSET,ui->leRefOffset);

    ui->pbPreAmptOn->setChecked(RemoteInterfaceObj->IsPreAmpOn());

//    ui->pbAutoAttenOn->setChecked(mControl->IsAttenAuto());
    return ;
}

/**
 * @brief  Button clicked event.
 * @param  void
 * @author Tony
 * @since 2018-12-26
*/
void RtSa_Dialog_AmptSetup::btn_clicked()
{
    qint32 index;
    RtSa_LineEdit* btn = qobject_cast<RtSa_LineEdit*>(sender());
    index = mEditList.key(btn,-1);
    if(index == -1)
    {
        return ;
    }
//    switch (index) {
//    case value:

//        break;
//    default:
//        break;
//    }
    return ;
}

/**
 * @brief  Init the display.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_AmptSetup::initDisplay()
{
    refreshEditDisplay(RTSA_INPUT_REF_LEVEL);
    refreshEditDisplay(RTSA_INPUT_ATTEN);
    refreshEditDisplay(RTSA_INPUT_SCALEDIV);
    refreshEditDisplay(RTSA_INPUT_REF_OFFSET);
    refreshButtonDisplay();
    refreshAttenAutoButton();
    return ;
}
void RtSa_Dialog_AmptSetup::mousePressEvent(QMouseEvent *event)
{
    initDisplay();
    return;
}
void RtSa_Dialog_AmptSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
//    qint32 FreqUnit = mInputDialog->getUnitNo();
//    qreal tempStepFreq = 0;
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
            return;
        }
        this->close();
        break;
    case Qt::Key_Shift:
        RemoteInterfaceObj->setShiftKeyEnable(true);
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
        }
        this->close();
        break;
    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
    case Qt::Key_Period:
    case Qt::Key_Minus:  // - Minus
    case Qt::Key_F2:    //  +/-
    case Qt::Key_F6://key_left
    case Qt::Key_Right:
    case Qt::Key_F7:
        if(mInputDialog->isHidden())
        {
            showInputDialog(mSelectInputID);
            mInputDialog->clearEdit();
        }
        mInputDialog->keyresponse(keyvalue);
        break;
    case Qt::Key_F3:
    case Qt::Key_Up:
    case Qt::Key_F8:
        mUpDownFlag = 0;
        if(timer->isActive())
        {
        }
        else
        {
            timer->start(100);
        }
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_F4:
        mUpDownFlag = 1;
        if(timer->isActive())
        {
        }
        else
        {
            timer->start(100);
        }
        break;
    default:
        break;
    }
    return;
}
//bool RtSa_Dialog_AmptSetup::eventFilter(QObject *watched, QEvent *event)
//{
//    int a = 0;
//    return QWidget::eventFilter(watched,event);
//}
/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-24
*/
void RtSa_Dialog_AmptSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case RTSA_INPUT_REF_LEVEL:
        value = RemoteInterfaceObj->getRefLevel();
        strGab = RemoteInterfaceObj->getRefLevelAdjustStr();
        if(value > 0)
        {
            ui->pbPreAmptOn->setEnabled(false);
            ui->pbPreAmptOn->setChecked(false);
        }
        else
        {
            ui->pbPreAmptOn->setEnabled(true);
        }
        break;
    case RTSA_INPUT_ATTEN:
        value = RemoteInterfaceObj->getAttenVal();
        strGab.sprintf("%.0f dB",value);
//        strGab = QString::number(value) + QString(" dB");
        break;
    case RTSA_INPUT_SCALEDIV:
        value = RemoteInterfaceObj->getScaleDiv();
        strGab.sprintf("%.2f dB",value);
//        strGab = QString::number(value) + QString(" dB");
        break;
    case RTSA_INPUT_REF_OFFSET:
        value = RemoteInterfaceObj->getRefOffset();
        strGab.sprintf("%.2f dB",value);
//        strGab = QString::number(value) + QString(" dB");
        break;
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

/**
 * @brief  Refresh button status.
 * @author Tony
 * @since  2018-12-24
*/
void RtSa_Dialog_AmptSetup::refreshButtonDisplay()
{
    ui->pb_unitSelect->setCurrentIndex(RemoteInterfaceObj->getAmptUint());
    connect(ui->pb_unitSelect,SIGNAL(currentIndexChanged(qint32)),this,SLOT(unitSelect(qint32)));
    bool ispreampOn = RemoteInterfaceObj->IsPreAmpOn();
    if(ispreampOn)
    {
        ui->pbPreAmptOn->setChecked(true);
    }
    else
    {
        ui->pbPreAmptOn->setChecked(false);
    }
//    connect(ui->pb_AttenType,SIGNAL(currentIndexChanged(qint32)),this,SLOT(setAttenType(qint32)));
    return ;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_AmptSetup::finishEntry_ampt(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
    {
        refreshEditDisplay(RTSA_INPUT_REF_LEVEL);
        refreshEditDisplay(RTSA_INPUT_ATTEN);
        refreshEditDisplay(RTSA_INPUT_SCALEDIV);
        refreshEditDisplay(RTSA_INPUT_REF_OFFSET);
        refreshAttenAutoButton();
//        initDisplay();
    }
    if(index == RTSA_NOT_USE)
    {
        this->close();
    }
    if(index == RTSA_SHIFT_ENABLE)
    {
        RemoteInterfaceObj->setShiftKeyEnable(true);
        this->close();
    }
    return ;
}


/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void RtSa_Dialog_AmptSetup::showInputDialog(qint32 index)
{
    mSelectInputID = index;
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", rtsa_qssMode[RemoteInterfaceObj->GetDisplayMode()]);
    mInputDialog->setStyle(QApplication::style());
    if(mInputDialog->isHidden())
        mInputDialog->show();
}

void RtSa_Dialog_AmptSetup::on_pb_cancel_clicked()
{
    mInputDialog->close();
    this->close();
}

void RtSa_Dialog_AmptSetup::on_leRefLevel_clicked()
{
    showInputDialog(RTSA_INPUT_REF_LEVEL);
    return ;

}

void RtSa_Dialog_AmptSetup::on_leAtten_clicked()
{
    showInputDialog(RTSA_INPUT_ATTEN);
    return ;
}

//void RtSa_Dialog_AmptSetup::on_pbAutoAttenOn_clicked()
//{
//    mInputDialog->hide();
//    mControl->setAttenAuto(true);
//    initDisplay();
//    return;
//}


void RtSa_Dialog_AmptSetup::on_leScaleDiv_clicked()
{
    showInputDialog(RTSA_INPUT_SCALEDIV);
    return ;
}

void RtSa_Dialog_AmptSetup::on_leRefOffset_clicked()
{
    showInputDialog(RTSA_INPUT_REF_OFFSET);
    return ;
}
//void RtSa_Dialog_AmptSetup::on_pushButton_clicked()
//{
//    mInputDialog->hide();
//    mControl->setAutoScale();
//    initDisplay();
//    return;
//}

//void RtSa_Dialog_AmptSetup::on_pb_unit_dBm_clicked()
//{
//    mInputDialog->hide();
//    mControl->setAmptUnit(RTSA_DBM);
//    initDisplay();
//    return;
//}

//void RtSa_Dialog_AmptSetup::on_pb_unit_dBmV_clicked()
//{
//    mInputDialog->hide();
//    mControl->setAmptUnit(RTSA_DBMV);
//    initDisplay();
//    return;
//}

//void RtSa_Dialog_AmptSetup::on_pb_unit_dBuV_clicked()
//{
//    mInputDialog->hide();
//    mControl->setAmptUnit(RTSA_DBUV);
//    initDisplay();
//    return;
//}

//void RtSa_Dialog_AmptSetup::on_pb_unit_V_clicked()
//{
//    mInputDialog->hide();
//    mControl->setAmptUnit(RTSA_VOLT);
//    initDisplay();
//    return;
//}

//void RtSa_Dialog_AmptSetup::on_pb_unit_W_clicked()
//{
//    mInputDialog->hide();
//    mControl->setAmptUnit(RTSA_WATTS);
//    initDisplay();
//    return;
//}
void RtSa_Dialog_AmptSetup::on_Update()
{
    initDisplay();
    return;
}

void RtSa_Dialog_AmptSetup::on_pb_Scale_Auto_clicked()
{
    mInputDialog->hide();
    RemoteInterfaceObj->setAutoScale();
    initDisplay();
    return;
}

void RtSa_Dialog_AmptSetup::unitSelect(qint32 unit)
{
    mInputDialog->hide();
    RemoteInterfaceObj->setAmptUnit(unit);
    refreshEditDisplay(RTSA_INPUT_REF_LEVEL);
//    initDisplay();
    return;
}

void RtSa_Dialog_AmptSetup::setAttenType(qint32 atten)
{
    mInputDialog->hide();
    RemoteInterfaceObj->setAttenAuto(atten);
    refreshEditDisplay(RTSA_INPUT_ATTEN);
    return;
}

void RtSa_Dialog_AmptSetup::on_pbPreAmptOn_toggled(bool checked)
{
    if(checked)
    {
        ui->pbPreAmptOn->setText("On");
    }
    else
    {
        ui->pbPreAmptOn->setText("Off");
    }
    RemoteInterfaceObj->setPreAmpOn(checked);
    refreshEditDisplay(RTSA_INPUT_ATTEN);
    return;
}

void RtSa_Dialog_AmptSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

void RtSa_Dialog_AmptSetup::on_pb_Auto_clicked()
{
    RemoteInterfaceObj->setAttenAuto(true);
    refreshEditDisplay(RTSA_INPUT_ATTEN);
    return;
}

void RtSa_Dialog_AmptSetup::on_pb_Manual_clicked()
{
    RemoteInterfaceObj->setAttenAuto(false);
    refreshEditDisplay(RTSA_INPUT_ATTEN);
    return;
}


void RtSa_Dialog_AmptSetup::refreshAttenAutoButton()
{
    bool isAuto = RemoteInterfaceObj->IsAttenAuto();
    if(isAuto)
    {
        ui->pb_Auto->setChecked(true);
    }
    else
    {
        ui->pb_Manual->setChecked(true);
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*/
void RtSa_Dialog_AmptSetup::on_timeOut()
{
    timer->stop();

    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        switch (mSelectInputID)
        {
        case RTSA_INPUT_REF_LEVEL:
            RemoteInterfaceObj->setRefLevel(RemoteInterfaceObj->getRefLevel() + 1);
            initDisplay();
            break;
        case RTSA_INPUT_ATTEN:
            RemoteInterfaceObj->setAttenVal(RemoteInterfaceObj->getAttenVal() + 5);
            initDisplay();
            break;
        case RTSA_INPUT_SCALEDIV:
            RemoteInterfaceObj->setScaleDiv(RemoteInterfaceObj->getScaleDiv() + 1);
            initDisplay();
            break;
        case RTSA_INPUT_REF_OFFSET:
            RemoteInterfaceObj->setRefOffset(RemoteInterfaceObj->getRefOffset() + 1);
            initDisplay();
            break;
        default:
            break;
        }
    }
    else
    {
        switch (mSelectInputID)
         {
         case RTSA_INPUT_REF_LEVEL:
             RemoteInterfaceObj->setRefLevel(RemoteInterfaceObj->getRefLevel() - 1);
             initDisplay();
             break;
         case RTSA_INPUT_ATTEN:
             RemoteInterfaceObj->setAttenVal(RemoteInterfaceObj->getAttenVal() - 5);
             initDisplay();
             break;
         case RTSA_INPUT_SCALEDIV:
             RemoteInterfaceObj->setScaleDiv(RemoteInterfaceObj->getScaleDiv() - 1);
             initDisplay();
             break;
         case RTSA_INPUT_REF_OFFSET:
             RemoteInterfaceObj->setRefOffset(RemoteInterfaceObj->getRefOffset() - 1);
             initDisplay();
             break;
         default:
             break;
         }
    }

    return;
}
