#include "sa_dialog_specem.h"
#include "ui_sa_dialog_specem.h"
#include "sa_applicationcontrol.h"
SA_Dialog_SpecEM::SA_Dialog_SpecEM(controlInterface *interface,QWidget *parent) :
    QWidget(parent),
    mControl(interface),
    ui(new Ui::SA_Dialog_SpecEM)
{
    ui->setupUi(this);
    hide();
    setProperty("status",qssMode[mControl->GetDisplayMode()]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    initDisplay();
}

SA_Dialog_SpecEM::~SA_Dialog_SpecEM()
{
    delete ui;
}

void SA_Dialog_SpecEM::initDisplay()
{
    qint32 mDisplayType,mRefType;
    mDisplayType = mControl->getSpecEMDisplay();
    mRefType = mControl->getSpecEMRefType();
    switch (mDisplayType) {
    case SA_SPECEM_ABS:
        ui->pb_Display_Abs->setChecked(true);
        break;
    case SA_SPECEM_REL:
        ui->pb_Display_Ref->setChecked(true);
        break;
    case SA_SPECEM_INTE_PWR:
        ui->pb_Display_IntePwr->setChecked(true);
        break;
    }

    switch (mRefType) {
    case SA_SPECEM_TOTALPWR:
        ui->pb_ref_TotalPwr->setChecked(true);
        break;
    case SA_SPECEM_PSD:
        ui->pb_ref_PSD->setChecked(true);
        break;
    case SA_SPECEM_SPECPEAK:
        ui->pb_ref_SpecPk->setChecked(true);
        break;
    }

}

void SA_Dialog_SpecEM::on_pb_Display_Abs_clicked()
{
    mControl->setSpecEMDisplay(SA_SPECEM_ABS);
}

void SA_Dialog_SpecEM::on_pb_Display_Ref_clicked()
{
    mControl->setSpecEMDisplay(SA_SPECEM_REL);
}

void SA_Dialog_SpecEM::on_pb_Display_IntePwr_clicked()
{
    mControl->setSpecEMDisplay(SA_SPECEM_INTE_PWR);
}

void SA_Dialog_SpecEM::on_pb_ref_TotalPwr_clicked()
{
    mControl->setSpecEMRefType(SA_SPECEM_TOTALPWR);
}

void SA_Dialog_SpecEM::on_pb_ref_PSD_clicked()
{
    mControl->setSpecEMRefType(SA_SPECEM_PSD);
}

void SA_Dialog_SpecEM::on_pb_ref_SpecPk_clicked()
{
    mControl->setSpecEMRefType(SA_SPECEM_SPECPEAK);
}

void SA_Dialog_SpecEM::on_pb_cancel_clicked()
{
    hideWidget();
    return;
}

void SA_Dialog_SpecEM::keyPressEvent(QKeyEvent *event)
{
  qint32 keyvalue = event->key();
  if(event->key() == Qt::Key_PowerOff)
  {
      if(!event->isAutoRepeat())
          QApplication::sendEvent(this->parent(),event);
      return;
  }
  switch(keyvalue){
  case Qt::Key_Escape:
      hideWidget();
      return;
  case Qt::Key_Shift:
      if(mControl->globalUserVariable->bShiftKeyPressed)
          mControl->globalUserVariable->bShiftKeyPressed = false;
      else
          mControl->globalUserVariable->bShiftKeyPressed = true;
      hideWidget();
      return;
  }

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
      break;
  case Qt::Key_F4:
      break;
  case Qt::Key_F3:
      break;

  }
  return;
}
void SA_Dialog_SpecEM::initWidget()
{

}
void SA_Dialog_SpecEM::showWidget()
{
    initDisplay();
    show();
    return;
}
void SA_Dialog_SpecEM::hideWidget()
{
    hide();
    emit mDialogHide();
    return;
}
