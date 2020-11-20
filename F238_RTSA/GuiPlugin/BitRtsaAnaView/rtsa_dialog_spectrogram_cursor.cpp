#include "rtsa_dialog_spectrogram_cursor.h"
#include "ui_rtsa_dialog_spectrogram_cursor.h"
#include <QListView>

RtSa_Dialog_Spectrogram_Cursor::RtSa_Dialog_Spectrogram_Cursor(RtSa_Dialog_Digitinput *mInput, RtSa_Interface *mInterface, QWidget *parent) :
    mInputDialog(mInput),
    mControl(mInterface),
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_Spectrogram_Cursor)
{
    ui->setupUi(this);
    initDisplay();
    this->hide();
    ui->combo_Cursor->setView(new  QListView());
    ui->combo_State->setView(new  QListView());

    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(finishEntry_Display(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);

}

RtSa_Dialog_Spectrogram_Cursor::~RtSa_Dialog_Spectrogram_Cursor()
{
    delete ui;
}

void RtSa_Dialog_Spectrogram_Cursor::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    qint32 Units = mInputDialog->getUnitNo();
    qreal tempTime = mControl->getPersistenceTime();
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
            return;
        }
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
    case Qt::Key_Shift:
        mControl->setShiftKeyEnable(true);
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
        }
        this->close();
        QApplication::sendEvent(this->parent(),event);
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
            mInputDialog->clearEdit();
        }
        mInputDialog->keyresponse(keyvalue);
        break;
    case Qt::Key_F3:
    case Qt::Key_Up:
    case Qt::Key_F8:
//        mUpDownFlag = 0;
//        if(timer->isActive())
//        {
//        }
//        else
//        {
//            timer->start(100);
//        }
        break;
    case Qt::Key_Down:
    case Qt::Key_F9:
    case Qt::Key_F4:
//        mUpDownFlag = 1;
//        if(timer->isActive())
//        {
//        }
//        else
//        {
//            timer->start(100);
//        }
        break;
    default:
        break;
    }
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-12-03
*/
void RtSa_Dialog_Spectrogram_Cursor::initDisplay()
{
    refreshPosition();
    refreshTime();
    refreshState();
    return;
}

void RtSa_Dialog_Spectrogram_Cursor::showInputDialog(qint32 index)
{
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", rtsa_qssMode[mControl->GetDisplayMode()]);
    mInputDialog->setStyle(QApplication::style());
    if(mInputDialog->isHidden())
        mInputDialog->show();
    return;
}
void RtSa_Dialog_Spectrogram_Cursor::on_edit_Position_clicked()
{
    showInputDialog(RTSA_SPECTROGTAM_CURSOR_INDEX);
}

void RtSa_Dialog_Spectrogram_Cursor::finishEntry_Display(qint32 index)
{
    if(this->isHidden())
        return ;
//    if(mEditList.contains(index))
//        refreshButtonDisplay();
    initDisplay();
    if(index == RTSA_NOT_USE)
    {
        this->close();
    }
    if(index == RTSA_SHIFT_ENABLE)
    {
        mControl->setShiftKeyEnable(true);
        this->close();
    }
    if(index == RTSA_SPECTROGTAM_CURSOR_INDEX)
    {
        initDisplay();
    }
    return ;
}
void RtSa_Dialog_Spectrogram_Cursor::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}
void RtSa_Dialog_Spectrogram_Cursor::refreshPosition()
{
    qint32 index = mControl->getspectrogramCursorID();
    qint32 pos = mControl->getspectrogramCursorIndex(index);
    QString str = QString::number(pos);
    ui->edit_Position->setText(str);
    return;
}

void RtSa_Dialog_Spectrogram_Cursor::refreshTime()
{
    qint32 index = mControl->getspectrogramCursorID();
    qint32 pos = mControl->getspectrogramCursorIndex(index);
    qreal acqTime = mControl->getAcqTime();
    acqTime *= pos;
    QString str = mControl->getAdjustTimeStr(acqTime);
    ui->edit_Time->setText(str);
    return;
}

void RtSa_Dialog_Spectrogram_Cursor::refreshState()
{
    qint32 index = mControl->getspectrogramCursorID();
    bool isActive = mControl->isSepectrogramDrawCursorEnable(index);
    ui->combo_State->setCurrentIndex(isActive);
    return;
}
void RtSa_Dialog_Spectrogram_Cursor::on_pb_cancel_clicked()
{
    this->close();
    return;
}

void RtSa_Dialog_Spectrogram_Cursor::on_combo_Cursor_currentIndexChanged(int index)
{
    mControl->setspectrogramCursorID(index);
    initDisplay();
    return;
}

void RtSa_Dialog_Spectrogram_Cursor::on_combo_State_currentIndexChanged(int index)
{
    qint32 id = mControl->getspectrogramCursorID();
    mControl->setSepctrogramEnableDrawCursor(id,index);
    return;
}

void RtSa_Dialog_Spectrogram_Cursor::on_pb_ClearAll_clicked()
{
    for(qint32 i = 0; i < RTSA_NUM_TRACE;i ++)
    {
        mControl->setSepctrogramEnableDrawCursor(i,false);
    }
    initDisplay();
    return;
}
