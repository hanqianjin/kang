#include "sa_dialog_amptsetup.h"
#include "ui_sa_dialog_amptsetup.h"
#include "sa_applicationcontrol.h"
#include "sa_dialog_digitinput.h"
#include "sa_lineedit.h"
#include "sa_combobox.h"
#include <QListView>
SA_Dialog_AmptSetup::SA_Dialog_AmptSetup(controlInterface *interface, user_variable *puser_variable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SA_Dialog_AmptSetup)
{
    ui->setupUi(this);
    mControl = interface;
    mCurEdit = 0;
    globalUserVariable = puser_variable;

    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initMap();
    initWidget();
    initDisplay();
    //setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint /*| Qt::Dialog*/);
    mInputDialog = NULL;
    hide();
}

SA_Dialog_AmptSetup::~SA_Dialog_AmptSetup()
{
    digitInputClose();
    delete ui;
}

void SA_Dialog_AmptSetup::showWidget()
{
    initDisplay();
    show();
    return;
}

void SA_Dialog_AmptSetup::hideWidget()
{
    hide();
    digitInputClose();
    emit mDialogHide();
    return;
}

/**
 * @brief  Init widget.Set button or other control postion.
 * @param  void
 * @author Tony
 * @since 2019-05-20
 * @note   Must be placed after "initMap()";
*/
void SA_Dialog_AmptSetup::initWidget()
{
    ui->label_6->setVisible(false);
    ui->edit_ZeroRestrainPhase->setVisible(false);
    ui->label_5->setVisible(false);
    ui->edit_ZeroRestrainAtten->setVisible(false);

    qint32 mMode = mControl->getCurrentMode();
    if(SA_SPURIOUS_EMISSION_MASK_MODE == mMode ||\
            SA_SPECTRUM_EMISSION_MASK_MODE == mMode)
    {
        ui->lblAtten->setVisible(false);
        ui->pb_Auto->setVisible(false);
        ui->pb_Manual->setVisible(false);
        ui->edit_Atten->setVisible(false);

        ui->lblPreamp->move(18,222);
        ui->pb_Preamp->move(94,212);
        ui->lblOffset->move(18,262);
        ui->edit_offset->move(94,262);
        ui->lblUnit->move(18,320);
        ui->pb_unitSelect->move(94,312);

        on_getFocus(mEditList.value(SA_INPUT_REF_LEVEL));
        mCurEdit = SA_INPUT_REF_LEVEL;
    }else
    {

        ui->lblAtten->setVisible(true);
        ui->pb_Auto->setVisible(true);
        ui->pb_Manual->setVisible(true);
        ui->edit_Atten->setVisible(true);

        ui->lblPreamp->move(18,322);
        ui->pb_Preamp->move(94,312);
        ui->lblOffset->move(18,362);
        ui->edit_offset->move(94,362);
        ui->lblUnit->move(18,420);
        ui->pb_unitSelect->move(94,412);

        on_getFocus(mEditList.value(SA_INPUT_REF_LEVEL));
        mCurEdit = SA_INPUT_REF_LEVEL;
    }

    return;
}

/**
 * @brief  Close digit input dialog.
 * @param  void
 * @author Tony
 * @since 2019-01-11
*/
void SA_Dialog_AmptSetup::digitInputClose()
{
    if(mInputDialog)
    {
        disconnect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        delete mInputDialog;
        mInputDialog = NULL;
    }
    return;
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_AmptSetup::initMap()
{
    mEditList.insert(SA_INPUT_REF_LEVEL,ui->edit_level);
    mEditList.insert(SA_INPUT_REF_OFFSET,ui->edit_offset);
    mEditList.insert(SA_INPUT_SCALEDIV,ui->edit_scale);
    mEditList.insert(SA_INPUT_ATTEN,ui->edit_Atten);


#ifdef SA_F239
    //Johnson 191031
    mEditList.insert(SA_INPUT_ZERORESTRAINATTEN,ui->edit_ZeroRestrainAtten);
    mEditList.insert(SA_INPUT_ZERORESTRAINPHASE,ui->edit_ZeroRestrainPhase);
#endif

    connect(ui->edit_level,SIGNAL(clicked()),this,SLOT(edit_clicked()));
    connect(ui->edit_offset,SIGNAL(clicked()),this,SLOT(edit_clicked()));
    connect(ui->edit_scale,SIGNAL(clicked()),this,SLOT(edit_clicked()));
    connect(ui->edit_Atten,SIGNAL(clicked()),this,SLOT(edit_clicked()));


#ifdef SA_F239
    //Johnson 191031
    connect(ui->edit_ZeroRestrainAtten,SIGNAL(clicked()),this,SLOT(edit_clicked()));
    connect(ui->edit_ZeroRestrainPhase,SIGNAL(clicked()),this,SLOT(edit_clicked()));
#endif

    connect(ui->edit_level,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->edit_offset,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->edit_scale,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->edit_Atten,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));


#ifdef SA_F239
    //Johnson 191031
    connect(ui->edit_ZeroRestrainAtten,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
    connect(ui->edit_ZeroRestrainPhase,SIGNAL(mFocus(SA_LineEdit*)),this,SLOT(on_getFocus(SA_LineEdit*)));
#endif

    mBoxList.insert(SA_COMBOBOX_UNIT,ui->pb_unitSelect);
    connect(ui->pb_unitSelect,SIGNAL(clicked(SA_Combobox*)),this,SLOT(on_getComboBoxFocus(SA_Combobox*)));
    connect(ui->pb_unitSelect,SIGNAL(activated(qint32)),this,SLOT(unitSelect(qint32)));

    ui->pb_unitSelect->setView(new  QListView());
    return ;
}

//Tony 0214
void SA_Dialog_AmptSetup::on_getFocus(SA_LineEdit* mEdit)
{
    QString qss =QString("outline: none;border:2px solid rgba(162,115,0,1);padding:6px 6px 5px 8px;");
    qint32 index = mEditList.key(mEdit);
    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }else if(mCurEdit>0&& mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setStyleSheet("");
    }
    mEdit->setStyleSheet(qss);
    mCurEdit = index;
    this->repaint();
    return;
}
void SA_Dialog_AmptSetup::on_getComboBoxFocus(SA_Combobox* mBox)
{
    QString qss = "#SA_Dialog_AmptSetup[status=\"indoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_AmptSetup[status=\"outdoor\"] QComboBox{background-image: url(:/sa/image/dropdown_click.png);}\
                   #SA_Dialog_AmptSetup[status=\"night\"] QComboBox{background-image: url(:/sa/image/night/dropdown_click.png);}";
    if(mCurEdit<0 && mBoxList.contains(mCurEdit))
    {
        mBoxList.value(mCurEdit)->setStyleSheet("");
    }else if(mCurEdit>0&& mEditList.contains(mCurEdit))
    {
        mEditList.value(mCurEdit)->setStyleSheet("");
    }
    mBox->setStyleSheet(qss);
    mCurEdit = mBoxList.key(mBox);
    return;
}

/**
 * @brief  Select unit.
 * @param  unit
 * @author Tony
 * @since 2018-12-26
*/
void SA_Dialog_AmptSetup::unitSelect(qint32 unit)
{
    digitInputClose();
    mControl->setAmpUnit(unit);
    initDisplay();
    return ;
}
/**
 * @brief  Button clicked event.
 * @param  void
 * @author Tony
 * @since 2018-12-26
*/
void SA_Dialog_AmptSetup::edit_clicked()
{
    qint32 index;
    SA_LineEdit* btn = qobject_cast<SA_LineEdit*>(sender());
    index = mEditList.key(btn,-1);
    if(index == -1)
    {
        return ;
    }
    showInputDialog(index);
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
void SA_Dialog_AmptSetup::initDisplay()
{
    refreshEditDisplay(SA_INPUT_REF_LEVEL);
    refreshEditDisplay(SA_INPUT_REF_OFFSET);
    refreshEditDisplay(SA_INPUT_SCALEDIV);
    refreshEditDisplay(SA_INPUT_ATTEN);
    //Johnson 190410
    refreshEditDisplay(SA_INPUT_ZERORESTRAINATTEN);
    refreshEditDisplay(SA_INPUT_ZERORESTRAINPHASE);

    refreshButtonDisplay();
    return ;
}

/**
 * @brief  Refresh the corresponding line edit according to the index.
 * @param  index  The index of current editline.
 * @author Tony
 * @since  2018-12-24
*/
void SA_Dialog_AmptSetup::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    if(!mEditList.contains(index))
        return;
    switch (index)
    {
    case SA_INPUT_REF_LEVEL:
        value = mControl->getRefLevel();
        strGab = amptTransformToQstring(mControl->getAmpUnit(),value);
        break;
    case SA_INPUT_REF_OFFSET:
        value = mControl->getRefOffset();
        strGab = QString::number(value,'f',2)+" dB";
        break;
    case SA_INPUT_SCALEDIV:
        value = mControl->getScaleDiv();
        strGab = QString::number(value,'f',2)+" dB";
        break;
    case SA_INPUT_ATTEN:
        value = mControl->getAttenValue();
        strGab = QString::number(value)+" dB";
        break;
    case SA_INPUT_ZERORESTRAINATTEN:
        strGab = QString::number(globalUserVariable->gZeroRestrainAtten);
        break;
    case SA_INPUT_ZERORESTRAINPHASE:
        strGab = QString::number(globalUserVariable->gZeroRestrainPhase);
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
void SA_Dialog_AmptSetup::refreshButtonDisplay()
{
    qint32 status;
    ui->pb_Preamp->setChecked(mControl->getPreampStatus());
//    ui->pb_Preamp->setChecked(status);
    status = mControl->getAttenStatus();
    if(status == SA_AUTO)
    {
        ui->pb_Auto->setChecked(true);
    }
    else if(status == SA_MANUAL)
    {
        ui->pb_Manual->setChecked(true);
    }
    ui->pb_unitSelect->setCurrentIndex(mControl->getAmpUnit());
    if(mControl->getRefLevel()>0)
    {
        ui->pb_Preamp->setCheckable(false);
    }else
    {
        ui->pb_Preamp->setCheckable(true);
    }

    return ;
}
/**
 * @brief  Slot of finish entry.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_AmptSetup::on_finishEntry(qint32 index)
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
void SA_Dialog_AmptSetup::showInputDialog(qint32 index)
{
//    ui->pb_AttenType->setStyleSheet("QComboBox{background-image: url(:/sa/image/night/dropdown_click.png);}");

    if(mInputDialog)
    {
        mInputDialog->initDisplay(index);
    }else
    {
        mInputDialog = new SA_Dialog_DigitInput(mControl,globalUserVariable,index,this);
        mInputDialog->setFocusPolicy(Qt::NoFocus);
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()+this->width()-DIGITINPUT_WIDTH,mapToGlobal(QPoint(0,0)).y(),DIGITINPUT_WIDTH,DIGITINPUT_HEIGHT);
        connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
        mInputDialog->show();
    }
    return ;
}


/**
 * @brief  Auto scale button clicked.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_AmptSetup::on_pb_Scale_Auto_clicked()
{
    mControl->setAutoScale(SA_ON);
    digitInputClose();
    initDisplay();
    return;
}

QString SA_Dialog_AmptSetup::amptTransformToQstring(qint32 unit,qreal value)
{
    QString strvalue;
    char str[20];
    switch (unit) {
    case SA_DBM:
        strvalue = QString::number(value, 'f', 2) + " dBm";  // Double to String
        break;
    case SA_DBMV:
        strvalue = QString::number((value + dBmVFix), 'f', 2) + " dBmV" ;  // Double to String
        break;
    case SA_DBUV:
        strvalue = QString::number((value + dBuVFix), 'f', 2) + " dBuV";  // Double to String
        break;
    case SA_VOLT:
        globalUserVariable->dbmToVoltCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case SA_WATTS:
        globalUserVariable->dbmToWattsCalculatorAndDisplayFunc(str,value);
        strvalue = QString(str);
        break;
    case SA_DBV:
        strvalue = QString::number((value + dBVFix), 'f', 2) + " dBV" ;  // Double to String
        break;
    default:
        break;
    }
    return strvalue;
}

void SA_Dialog_AmptSetup::on_pb_Preamp_clicked()
{
    mControl->setPreampStatus(ui->pb_Preamp->isChecked());
    initDisplay();
    return ;
}

void SA_Dialog_AmptSetup::on_pb_cancel_clicked()
{
    this->hideWidget();
    return;
}

void SA_Dialog_AmptSetup::on_pb_Preamp_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_Preamp->setText("On");
    }else
    {
        ui->pb_Preamp->setText("Off");
    }
}

/**
 * @brief  Key press Event.
 * @param  event
 * @author Tony
 * @since 2019-02-14
*/
void SA_Dialog_AmptSetup::keyPressEvent(QKeyEvent *event)
{
  qint32 keyvalue = event->key();
  if(event->key() == Qt::Key_PowerOff)
  {
      if(!event->isAutoRepeat())
          QApplication::sendEvent(this->parent(),event);
      return;
  }
  switch (keyvalue) {
  case Qt::Key_F3:
  case Qt::Key_F4:
      if(mInputDialog)
          digitInputClose();
      break;
  case Qt::Key_Escape:
      if(mInputDialog)
          digitInputClose();
      else
          hideWidget();
      return;
  case Qt::Key_Shift:
      if(globalUserVariable->bShiftKeyPressed)
          globalUserVariable->bShiftKeyPressed = false;
      else
          globalUserVariable->bShiftKeyPressed = true;
      hideWidget();
      return;
  default:
      break;
  }
  if(mInputDialog)
  {
      QCoreApplication::sendEvent(mInputDialog, event);
      return;
  }

  if(!mEditList.contains(mCurEdit) || mCurEdit < 0)
      return;

  switch(keyvalue){
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
  case Qt::Key_F2:
  case Qt::Key_Minus:
  case Qt::Key_Period:
      if(!mInputDialog) mEditList.value(mCurEdit)->clicked();
      QCoreApplication::sendEvent(mInputDialog, event);
      break;
  case Qt::Key_F4:
      getKnobValue(CLOCKWISE);
      break;
  case Qt::Key_F3:
      getKnobValue(ANTICLOCKWISE);
      break;
  default:
      if(mInputDialog) QApplication::sendEvent(mInputDialog,event);
      break;
  }

  return ;
}

void SA_Dialog_AmptSetup::getKnobValue(qint32 mode)
{
    qreal mStep;
    qreal mValue;
    switch (mCurEdit)
    {
    case SA_INPUT_REF_LEVEL:
        mStep = REF_STEP;
        mValue=mControl->getRefLevel();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setRefLevel(mValue);
        break;
    case SA_INPUT_REF_OFFSET:
        mStep = REF_STEP;
        mValue=mControl->getRefOffset();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setRefOffset(mValue);
        break;
    case SA_INPUT_SCALEDIV:
        mStep = SCALE_STEP;
        mValue=mControl->getScaleDiv();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setScaleDiv(mValue);
        break;
    case SA_INPUT_ATTEN:
        if(!ui->pb_Auto->isChecked())
        {
            ui->pb_Auto->setChecked(true);
        }
        mStep = ATTEN_STEP;
        mValue=mControl->getAttenValue();
        if(mode)
            mValue += mStep;
        else
            mValue -= mStep;
        mControl->setAttenValue(mValue);
        break;
    }
    initDisplay();
    return;
}

void SA_Dialog_AmptSetup::on_pb_Auto_clicked(bool checked)
{
    quint32 status;
    if(checked)
        status= SA_AUTO;
    else
        status= SA_MANUAL;

    if(mControl->getAttenStatus() != status)
    {
         mControl->setAttenStatus(status);
         initDisplay();
    }
    return;
}

void SA_Dialog_AmptSetup::on_pb_Manual_clicked(bool checked)
{
    quint32 status;
    if(checked)
        status= SA_MANUAL;
    else
        status= SA_AUTO;

    if(mControl->getAttenStatus() != status)
    {
         mControl->setAttenStatus(status);
         initDisplay();
    }
    return;
}
