#include "sa_dialog_measuresetup.h"
#include "ui_sa_dialog_measuresetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"

SA_Dialog_MeasureSetup::SA_Dialog_MeasureSetup(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    globalUserVariable(puser_variable),
    ui(new Ui::SA_Dialog_MeasureSetup)
{
    ui->setupUi(this);
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    this->setFocus();
    initMap();
//    initDisplay();
//   setAttribute(Qt::WA_DeleteOnClose);
//    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    mInputDialog = NULL;

    ui->pb_AudioDemodulation->setVisible(false);
    ui->pb_FieldStrength->setVisible(false);

    hide();
}

SA_Dialog_MeasureSetup::~SA_Dialog_MeasureSetup()
{
    delete ui;
    if(mInputDialog)
    {
        delete mInputDialog;
        mInputDialog = NULL;
    }

    if(mBtnGroup)
    {
        delete mBtnGroup;
        mBtnGroup = NULL;
    }
}

void SA_Dialog_MeasureSetup::runBtnFunction(qint32 menuID)
{
    switch(menuID)
    {
    case SA_SWEPT_SA:
        mControl->SetMeasureItems(SA_SWEPT_SA);
        break;
    case SA_CHANNEL_POWER:
        mControl->SetMeasureItems(SA_CHANNEL_POWER);
        break;
    case SA_OCCUPIED_BW:
        mControl->SetMeasureItems(SA_OCCUPIED_BW);
        break;
    case SA_SPECTRUM_EMISSION_MASK:
        mControl->SetMeasureItems(SA_SPECTRUM_EMISSION_MASK);
        break;
    case SA_ACP:
        mControl->SetMeasureItems(SA_ACP);
        break;
    case SA_MULTI_ACP:
        mControl->SetMeasureItems(SA_MULTI_ACP);
        break;
    case SA_SPURIOUS_EMISSION_MASK:
        mControl->SetMeasureItems(SA_SPURIOUS_EMISSION_MASK);
        break;
    case SA_FIELD_STRENGTH:
        mControl->SetMeasureItems(SA_FIELD_STRENGTH);
        break;
    case SA_DEMODULATION:
        mControl->SetMeasureItems(SA_DEMODULATION);
        break;
    default:
        return;
        break;
    }
    //emit signalModeChange();
}

/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MeasureSetup::initMap()
{
    mBtnGroup = new QButtonGroup();
    mBtnGroup->setExclusive(true);
    mBtnGroup->addButton(ui->pb_Spectrum,SA_SWEPT_SA);
    mBtnGroup->addButton(ui->pb_ChannelPower,SA_CHANNEL_POWER);
    mBtnGroup->addButton(ui->pb_OccupiedBW,SA_OCCUPIED_BW);
    mBtnGroup->addButton(ui->pb_SpecEmissionMask,SA_SPECTRUM_EMISSION_MASK);
    mBtnGroup->addButton(ui->pb_Adjacent,SA_ACP);
    mBtnGroup->addButton(ui->pb_Muti_Adjacent,SA_MULTI_ACP);
    mBtnGroup->addButton(ui->pb_SpuriousEmssionMask,SA_SPURIOUS_EMISSION_MASK);
    mBtnGroup->addButton(ui->pb_FieldStrength,SA_FIELD_STRENGTH);
    mBtnGroup->addButton(ui->pb_AudioDemodulation,SA_DEMODULATION);
    connect(mBtnGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(runBtnFunction(qint32)));
    return ;
}

/**
 * @brief  Init the display.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MeasureSetup::initDisplay()
{
//    refreshEditDisplay(SA_INPUT_MANUAL_RBW);
//    refreshEditDisplay(SA_INPUT_MANUAL_VBW);
    refreshButtonDisplay();
    return ;
}

/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-24
*/
void SA_Dialog_MeasureSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
//    case SA_INPUT_MANUAL_RBW:
//        value = mControl->getRbwValue();
//        strGab = globalUserVariable->freqValueToQstring(value);
//        break;
//    case SA_INPUT_MANUAL_VBW:
//        value = mControl->getVbwValue();
//        strGab = globalUserVariable->freqValueToQstring(value);
//        break;
//    default:
//        break;
    }
    mEditList.find(index).value()->setText(strGab);
    return ;
}

/**
 * @brief  Refresh button status.
 * @author Tony
 * @since  2018-12-24
*/
void SA_Dialog_MeasureSetup::refreshButtonDisplay()
{
    switch(globalUserVariable->currentMode)
    {
    case SA_SPAN_MODE:
        ui->pb_Spectrum->setChecked(true);
        break;
    case SA_CHNLPOWER_MEASURE_MODE:
        ui->pb_ChannelPower->setChecked(true);
        break;
    case SA_OCCUPIED_BW_MEASURE_MODE:
        ui->pb_OccupiedBW->setChecked(true);
        break;
    case SA_SPECTRUM_EMISSION_MASK_MODE:
        ui->pb_SpecEmissionMask->setChecked(true);
        break;
    case SA_ACP_MEASURE_MODE:
        ui->pb_Adjacent->setChecked(true);
        break;
    case SA_MULTI_ACP_MODE:
        ui->pb_Muti_Adjacent->setChecked(true);
        break;
    case SA_SPURIOUS_EMISSION_MASK_MODE:
        ui->pb_SpuriousEmssionMask->setChecked(true);
        break;
    case SA_FIELD_STRENGTH_MODE:
        ui->pb_FieldStrength->setChecked(true);
        break;
    case SA_DEMODULATION_MODE:
        ui->pb_AudioDemodulation->setChecked(true);
        break;
    }
    return ;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MeasureSetup::on_finishEntry(qint32 index)
{
    disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog = NULL;

    if(mEditList.contains(index))
        initDisplay();
    return ;
}


/**
 * @brief  show digit input dialog
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MeasureSetup::showInputDialog(qint32 index)
{
    if(mInputDialog)
    {
        qWarning()<<"Digit dialog already exist!";
        delete mInputDialog;
        mInputDialog = NULL;
    }
    mInputDialog = new SA_Dialog_DigitInput(mControl,globalUserVariable,index,this);
        mInputDialog->move(mapToGlobal(QPoint(0,0)).x()+this->x()+this->width()+2,mapToGlobal(QPoint(0,0)).y()/*+this->y()*/);

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    mInputDialog->show();
    return ;
}



void SA_Dialog_MeasureSetup::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_MeasureSetup::keyPressEvent(QKeyEvent *event)
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
        break;
        //return QWidget::keyPressEvent(event);
    default:
        break;
    }
}
void SA_Dialog_MeasureSetup::initWidget()
{

}
void SA_Dialog_MeasureSetup::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_MeasureSetup::hideWidget()
{
    hide();
    emit mDialogHide();
    return;
}
