#include "pm_dialog_amptsetup.h"
#include "ui_pm_dialog_amptsetup.h"
#include <QListView>
Pm_Dialog_AmptSetup::Pm_Dialog_AmptSetup(BitPm_Interface *BitPmInterface,Pm_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pm_Dialog_AmptSetup),
    PmInterfaceObj(BitPmInterface),
    mInputDialog(input),
    mSelectInputID(PM_INPUT_AMP_MAX),
    mUpDownFlag(0),
    m_UpFlg(0),
    m_DownFlg(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    ui->pb_unitSelect->setView(new  QListView());
    initMap();
    initDisplay();

    this->setAttribute(Qt::WA_NoChildEventsForParent,true);
    this->hide();

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_ampt(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",pm_qssMode[PmInterfaceObj->getSystemDisplay()]);

}

Pm_Dialog_AmptSetup::~Pm_Dialog_AmptSetup()
{
    delete ui;
}

void Pm_Dialog_AmptSetup::mousePressEvent(QMouseEvent *event)
{
    initDisplay();
    return;
}

void Pm_Dialog_AmptSetup::keyPressEvent(QKeyEvent *event)
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
        PmInterfaceObj->setShiftKeyEnable(true);
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

/**
* @brief  Slot of finish entry.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::finishEntry_ampt(qint32 index)
{
    if(this->isHidden())
        return ;
    if(mEditList.contains(index))
    {
        refreshEditDisplay(PM_INPUT_AMP_MAX);
        refreshEditDisplay(PM_INPUT_AMP_MIN);
        refreshEditDisplay(PM_INPUT_AMP_OFFSET);
        refreshEditDisplay(PM_INPUT_FORWATD_RELATIVE);
        refreshEditDisplay(PM_INPUT_REVERSE_RELATIVE);
    }
    if(index == PM_NOT_USE)
    {
        this->close();
    }
    if(index == PM_SHIFT_ENABLE)
    {
        PmInterfaceObj->setShiftKeyEnable(true);
        this->close();
    }
    return ;
}

void Pm_Dialog_AmptSetup::on_pb_cancel_clicked()
{
    mInputDialog->close();
    this->close();
}

void Pm_Dialog_AmptSetup::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

/**
* @brief
* @param
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::on_timeOut()
{
    qreal fDataUserFlg = 0;

    timer->stop();
    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        if(m_UpFlg >30)
            fDataUserFlg = 10.0;
        else if(m_UpFlg >20)
            fDataUserFlg = 1.0;
        else if(m_UpFlg >10)
            fDataUserFlg = 0.1;
        else
            fDataUserFlg = 0.01;
        m_UpFlg++;
        m_DownFlg= 0;

        switch (mSelectInputID)
        {
        case PM_INPUT_AMP_MAX:
            PmInterfaceObj->setAmptMax(PmInterfaceObj->getAmptMax() + fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_AMP_MIN:
            PmInterfaceObj->setAmptMin(PmInterfaceObj->getAmptMin() + fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_AMP_OFFSET:
            PmInterfaceObj->setAmptOffset(PmInterfaceObj->getAmptOffset() +fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_FORWATD_RELATIVE:
            PmInterfaceObj->setAmptForwardRelativeData(
                        PmInterfaceObj->getAmptForwardRelativeData() +fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_REVERSE_RELATIVE:
            PmInterfaceObj->setAmptReverseRelativeData(
                        PmInterfaceObj->getAmptReverseRelativeData() +fDataUserFlg);
            initDisplay();
            break;
            //        case PM_SELECT_UNITS:
            //           PmInterfaceObj->setAmptUnit(PmInterfaceObj->getAmptUint() + 1);
            //            initDisplay();
            break;
        default:
            break;
        }
    }
    else
    {
        if(m_DownFlg >30)
            fDataUserFlg = 10.0;
        else if(m_DownFlg >20)
            fDataUserFlg = 1.0;
        else if(m_DownFlg >10)
            fDataUserFlg = 0.1;
        else
            fDataUserFlg = 0.01;

        m_UpFlg= 0;
        m_DownFlg ++;
        switch (mSelectInputID)
        {
        case PM_INPUT_AMP_MAX:
            PmInterfaceObj->setAmptMax(PmInterfaceObj->getAmptMax() - fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_AMP_MIN:
            PmInterfaceObj->setAmptMin(PmInterfaceObj->getAmptMin() -fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_AMP_OFFSET:
            PmInterfaceObj->setAmptOffset(PmInterfaceObj->getAmptOffset() - fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_FORWATD_RELATIVE:
            PmInterfaceObj->setAmptForwardRelativeData(
                        PmInterfaceObj->getAmptForwardRelativeData() - fDataUserFlg);
            initDisplay();
            break;
        case PM_INPUT_REVERSE_RELATIVE:
            PmInterfaceObj->setAmptReverseRelativeData(
                        PmInterfaceObj->getAmptReverseRelativeData() - fDataUserFlg);
            initDisplay();
            break;
            //        case PM_SELECT_UNITS:
            //            PmInterfaceObj->setAmptUnit(PmInterfaceObj->getAmptUint() - 1);
            //            initDisplay();
        default:
            break;
        }
    }

    return;
}

/**
* @brief  Button clicked event.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::btn_clicked()
{
    qint32 index;
    Pm_LineEdit* btn = qobject_cast<Pm_LineEdit*>(sender());
    index = mEditList.key(btn,-1);
    if(index == -1)
    {
        return ;
    }
    return ;
}

void Pm_Dialog_AmptSetup::on_leMax_clicked()
{
    showInputDialog(PM_INPUT_AMP_MAX);
    return ;
}

void Pm_Dialog_AmptSetup::on_leMin_clicked()
{
    showInputDialog(PM_INPUT_AMP_MIN);
    return ;
}

void Pm_Dialog_AmptSetup::on_leEnterOffset_clicked()
{
    showInputDialog(PM_INPUT_AMP_OFFSET);
    return ;
}

void Pm_Dialog_AmptSetup::on_pb_unitSelect_highlighted(int index)
{

    return;
}

void Pm_Dialog_AmptSetup::on_pb_ForwardRelative_toggled(bool checked)
{
    PmInterfaceObj->setAmptForwardRelative(checked);
    refreshButtonDisplay();
    return;
}

void Pm_Dialog_AmptSetup::on_pb_ReverseRelative_toggled(bool checked)
{
    PmInterfaceObj->setAmptReverseRelative(checked);
    refreshButtonDisplay();
    return;
}

void Pm_Dialog_AmptSetup::on_leEnterForward_clicked()
{
    showInputDialog(PM_INPUT_FORWATD_RELATIVE);
    return ;
}

void Pm_Dialog_AmptSetup::on_leEnterReverse_clicked()
{
    showInputDialog(PM_INPUT_REVERSE_RELATIVE);
    return ;
}

void Pm_Dialog_AmptSetup::unitSelect(qint32 index)
{
    mInputDialog->hide();
    //    mSelectInputID = PM_SELECT_UNITS;
    PmInterfaceObj->setAmptUnit(index);
    refreshEditDisplay(PM_INPUT_AMP_MAX);
    refreshEditDisplay(PM_INPUT_AMP_MIN);
    refreshEditDisplay(PM_INPUT_AMP_OFFSET);
    refreshEditDisplay(PM_INPUT_FORWATD_RELATIVE);
    refreshEditDisplay(PM_INPUT_REVERSE_RELATIVE);
}

void Pm_Dialog_AmptSetup::on_pb_Scale_Auto_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setAutoScale();
    initDisplay();
    return;
}

void Pm_Dialog_AmptSetup::on_pb_SetForward_clicked()
{
    mInputDialog->hide();
    PmInterfaceObj->setForwardRelativeCurFlg(true);
    initDisplay();
}

void Pm_Dialog_AmptSetup::on_pb_SetReverse_clicked()
{
    mInputDialog->hide();
     PmInterfaceObj->setReverseRelativeCurFlg(true);
    initDisplay();
}

/**
* @brief  Init the display.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::initDisplay()
{

    if(POWER_SENSOR_V90 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->labelSetForward->setText("Relative");
        ui->labelForward->setText("Relative Level");
        ui->pb_SetForward->setText("Set To Relative");
        ui->labelSetReverse->hide();
        ui->pb_ReverseRelative->hide();
        ui->leEnterReverse->hide();
        ui->labelReverse->hide();
        ui->pb_SetReverse->hide();
        ui->lableEnterOffset->setText("Enter Offset");
    }
    else  if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
    {
        ui->labelSetForward->setText("Forward\nRelative");
        ui->labelForward->setText("Forward \nRelative Level");
        ui->pb_SetForward->setText("Set To Forward");

        ui->labelSetReverse->show();
        ui->pb_ReverseRelative->show();
        ui->leEnterReverse->show();
        ui->labelReverse->show();
        ui->pb_SetReverse->show();
    }
    refreshEditDisplay(PM_INPUT_AMP_MAX);
    refreshEditDisplay(PM_INPUT_AMP_MIN);
    refreshEditDisplay(PM_INPUT_AMP_OFFSET);
    refreshEditDisplay(PM_INPUT_FORWATD_RELATIVE);
    refreshEditDisplay(PM_INPUT_REVERSE_RELATIVE);
    refreshButtonDisplay();
    return ;
}

/**
* @brief  Initialize map of indexes and controls.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::initMap()
{
    mEditList.insert(PM_INPUT_AMP_MAX,ui->leMax);
    mEditList.insert(PM_INPUT_AMP_MIN,ui->leMin);
    mEditList.insert(PM_INPUT_AMP_OFFSET,ui->leEnterOffset);
    mEditList.insert(PM_INPUT_FORWATD_RELATIVE,ui->leEnterForward);
    mEditList.insert(PM_INPUT_REVERSE_RELATIVE,ui->leEnterReverse);
    return ;
}

/**
* @brief  Refresh the corresponding line edit according to the index.
* @param  index  The index of current editline.
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case PM_INPUT_AMP_MAX:
        value = PmInterfaceObj->getAmptMax();
        strGab = PmInterfaceObj->dBmTransformToQstring(PmInterfaceObj->getAmptUint(),value);
        break;
    case PM_INPUT_AMP_MIN:
        value = PmInterfaceObj->getAmptMin();
        strGab = PmInterfaceObj->dBmTransformToQstring(PmInterfaceObj->getAmptUint(),value);
        break;
    case PM_INPUT_AMP_OFFSET:
        value = PmInterfaceObj->getAmptOffset();
        strGab.sprintf("%.2f dB",value);
        break;
    case PM_INPUT_FORWATD_RELATIVE:
        value = PmInterfaceObj->getAmptForwardRelativeData();
        strGab.sprintf("%.2f dB",value);
        break;
    case PM_INPUT_REVERSE_RELATIVE:
        value = PmInterfaceObj->getAmptReverseRelativeData();
        strGab.sprintf("%.2f dB",value);
        break;
    default:
        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

/**
* @brief  Refresh button status.
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::refreshButtonDisplay()
{
    ui->pb_unitSelect->setCurrentIndex(PmInterfaceObj->getAmptUint());
    connect(ui->pb_unitSelect,SIGNAL(currentIndexChanged(qint32)),this,SLOT(unitSelect(qint32)));

    if(PmInterfaceObj->IsAmptForwardRelative())
    {
        ui->pb_ForwardRelative->setChecked(true);
        ui->pb_ForwardRelative->setText("On");
        if(POWER_SENSOR_V91 == PmInterfaceObj->getPowerSensorFlg())
            ui->lableEnterOffset->setText("Enter\nGain Offset");
        else
            ui->lableEnterOffset->setText("Enter Offset");

        ui->leEnterForward->show();
        ui->labelForward->show();
        ui->pb_SetForward->show();

    }
    else
    {
        ui->pb_ForwardRelative->setChecked(false);
        ui->pb_ForwardRelative->setText("Off");
        if(false == PmInterfaceObj->IsAmptReverseRelative())
            ui->lableEnterOffset->setText("Enter Offset");
        ui->leEnterForward->hide();
        ui->labelForward->hide();
        ui->pb_SetForward->hide();

    }
    if(PmInterfaceObj->IsAmptReverseRelative())
    {
        ui->pb_ReverseRelative->setChecked(true);
        ui->pb_ReverseRelative->setText("On");
        ui->lableEnterOffset->setText("Enter\nLoss Offset");

        ui->leEnterReverse->show();
        ui->labelReverse->show();
        ui->pb_SetReverse->show();
    }
    else
    {

        ui->pb_ReverseRelative->setChecked(false);
        ui->pb_ReverseRelative->setText("Off");
        if(false == PmInterfaceObj->IsAmptForwardRelative())
            ui->lableEnterOffset->setText("Enter Offset");

        ui->leEnterReverse->hide();
        ui->labelReverse->hide();
        ui->pb_SetReverse->hide();

    }

    return ;
}


/**
* @brief  show digit input dialog
* @param  void
* @author Roc
* @since  2019.11.4
*/
void Pm_Dialog_AmptSetup::showInputDialog(qint32 index)
{
    m_UpFlg = 0;
    m_DownFlg = 0;
    mSelectInputID = index;
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-PM_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),PM_DIGITAL_DIALOG_WIDTH,PM_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", pm_qssMode[PmInterfaceObj->getSystemDisplay()]);
    mInputDialog->setStyle(QApplication::style());
    if(mInputDialog->isHidden())
        mInputDialog->show();
}
