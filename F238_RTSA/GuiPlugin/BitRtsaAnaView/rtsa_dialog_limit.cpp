#include "rtsa_dialog_limit.h"
#include "ui_rtsa_dialog_limitsetup.h"
#include "rtsa_define.h"

RtSa_Dialog_Limit::RtSa_Dialog_Limit(RtSa_Interface *interface, RtSa_Dialog_Digitinput *input, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RtSa_Dialog_Limit),
    mControl(interface),
    mInputDialog(input),
    mSelectInputID(RTSA_INPUT_MARGIN),
    mLimitTable(NULL),
    mUpDownFlag(0)
{
    ui->setupUi(this);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->hide();
    initMap();
    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry(qint32)));
    connect(mInputDialog,SIGNAL(ClockWiseDown(QKeyEvent*)),this,SLOT(DigitalKeyRespond(QKeyEvent*)));
    connect(mControl,SIGNAL(BitViewChanged(quint32)),this,SLOT(on_Update()));
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timeOut()));
    setProperty("status",rtsa_qssMode[mControl->GetDisplayMode()]);
}

RtSa_Dialog_Limit::~RtSa_Dialog_Limit()
{
//    if(mLimitTable != NULL)
//    {
//        delete mLimitTable;
//        mLimitTable = NULL;
//    }

    delete ui;
}
void RtSa_Dialog_Limit::keyPressEvent(QKeyEvent *event)
{
//    if(mLimitTable != NULL)
//    {
//        QCoreApplication::sendEvent(mLimitTable, event);
//        return;
//    }
    if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
        {
            QApplication::sendEvent(this->parent(),event);
        }
        return;
    }
    qint32 keyvalue = event->key();
    qint32 LimitID = mControl->getCurLimit();
    qreal tempStepFreq = 0;
    switch (keyvalue) {
    case Qt::Key_Escape:
        if(!mInputDialog->isHidden())
        {
            mInputDialog->hide();
            return;
        }
        if(mLimitTable != NULL)
        {
            mLimitTable->close();
            return;
        }
        this->close();
        QApplication::sendEvent(this->parent(),event);
        break;
    case Qt::Key_Shift:
//        QApplication::sendEvent(this->parent(),event);
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
void RtSa_Dialog_Limit::initDisplay()
{
    refreshEditDisplay(RTSA_INPUT_MARGIN);
    initButtonDisplay();
    return;
}

void RtSa_Dialog_Limit::HideTableWidget()
{
    if(mLimitTable != NULL)
    {
        delete mLimitTable;
        mLimitTable = NULL;
    }
}
/**
* @brief
* @param
* @Author Albert
* @date 2020-04-21
*/
void RtSa_Dialog_Limit::showNotice(bool isShow)
{
    if(isShow)
    {
        ui->label->setVisible(false);
        ui->label_14->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->leMargin->setVisible(false);
        ui->pb_DeleteAll->setVisible(false);
        ui->pb_Edge->setVisible(false);
        ui->pb_EditMask->setVisible(false);
        ui->pb_LM1->setVisible(false);
        ui->pb_LM2->setVisible(false);
        ui->pb_LM3->setVisible(false);
        ui->pb_LM4->setVisible(false);
        ui->pb_LM5->setVisible(false);
        ui->pb_LM6->setVisible(false);
        ui->pb_LimitTest->setVisible(false);
        ui->pb_Lower->setVisible(false);
        ui->pb_Upper->setVisible(false);
        ui->pb_toggle->setVisible(false);
        ui->label_warning->setVisible(true);
        ui->label_warning->setText("This menu is not available under\n this measurement");
    }
    else {
        ui->label->setVisible(true);
        ui->label_14->setVisible(true);
        ui->label_2->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->leMargin->setVisible(true);
        ui->pb_DeleteAll->setVisible(true);
        ui->pb_Edge->setVisible(true);
        ui->pb_EditMask->setVisible(true);
        ui->pb_LM1->setVisible(true);
        ui->pb_LM2->setVisible(true);
        ui->pb_LM3->setVisible(true);
        ui->pb_LM4->setVisible(true);
        ui->pb_LM5->setVisible(true);
        ui->pb_LM6->setVisible(true);
        ui->pb_LimitTest->setVisible(true);
        ui->pb_Lower->setVisible(true);
        ui->pb_Upper->setVisible(true);
        ui->pb_toggle->setVisible(true);
        ui->label_warning->setVisible(false);
    }
    return;
}
void RtSa_Dialog_Limit::initMap()
{
    mLimitSelectGroup = new QButtonGroup();
    mLimitSelectGroup->addButton(ui->pb_LM1,RTSA_LIMIT1);
    mLimitSelectGroup->addButton(ui->pb_LM2,RTSA_LIMIT2);
    mLimitSelectGroup->addButton(ui->pb_LM3,RTSA_LIMIT3);
    mLimitSelectGroup->addButton(ui->pb_LM4,RTSA_LIMIT4);
    mLimitSelectGroup->addButton(ui->pb_LM5,RTSA_LIMIT5);
    mLimitSelectGroup->addButton(ui->pb_LM6,RTSA_LIMIT6);
    connect(mLimitSelectGroup,SIGNAL(buttonClicked(qint32)),this,SLOT(mLimitSelectGroup_click(qint32)));

//    mLimitTable = new RtSa_Dialog_LimitTable(mControl,mInputDialog,this);
//    connect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
//    mLimitTable->hide();

    mEditList.insert(RTSA_INPUT_MARGIN,ui->leMargin);

    refreshEditDisplay(RTSA_INPUT_MARGIN);
    initButtonDisplay();

    if(mLimitTable != NULL)
    {
        mLimitTable->initTable();
    }
    return;
}
void RtSa_Dialog_Limit::initButtonDisplay()
{
    qint32 limitID = mControl->getCurLimit();
    mLimitSelectGroup->button(limitID)->setChecked(true);
    if(mControl->IsCurLimitOn(limitID))
    {
        ui->pb_toggle->setChecked(true);
        ui->pb_toggle->setText("On");
    }
    else
    {
        ui->pb_toggle->setChecked(false);
        ui->pb_toggle->setText("Off");
    }
    if(mControl->IsLimitTestOn())
    {
        ui->pb_LimitTest->setChecked(true);
        ui->pb_LimitTest->setText("On");
    }
    else
    {
        ui->pb_LimitTest->setChecked(false);
        ui->pb_LimitTest->setText("Off");
    }
    if(mControl->IsMarginOn(limitID))
    {
        ui->pb_Edge->setChecked(true);
        ui->pb_Edge->setText("On");
    }
    else
    {
        ui->pb_Edge->setChecked(false);
        ui->pb_Edge->setText("Off");
    }
    if(RTSA_UPPER == mControl->getLimitType(limitID))
    {
        ui->pb_Upper->setChecked(true);
        ui->pb_Lower->setChecked(false);
    }
    else
    {
        ui->pb_Upper->setChecked(false);
        ui->pb_Lower->setChecked(true);
    }
    return;
}
void RtSa_Dialog_Limit::refreshEditDisplay(quint32 index)
{
    QString strGab;
    qreal   value;
    switch(index)
    {
    case RTSA_INPUT_MARGIN:
        value = mControl->getMargin(mControl->getCurLimit());
        strGab = QString::number(value,'f',2) + QString(" dB");
        mEditList.find(index).value()->setText(strGab);
        break;
    }
    return;
}
void RtSa_Dialog_Limit::refreshButtonDisplay()
{
//    refreshEditDisplay(RTSA_INPUT_ACQ_TIME);
    refreshEditDisplay(RTSA_INPUT_MARGIN);
    return;
}
void RtSa_Dialog_Limit::showInputDialog(qint32 index)
{
    mSelectInputID = index;
    if(mInputDialog->isHidden())
    {
        mInputDialog->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
                                  mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
    }
    mInputDialog->initDisplay(index);
    mInputDialog->setProperty("status", rtsa_qssMode[mControl->GetDisplayMode()]);
    mInputDialog->setStyle(QApplication::style());
    mInputDialog->show();
    return ;
}
void RtSa_Dialog_Limit::on_finishEntry(qint32 index)
{
    if(index == RTSA_NOT_USE)
    {
        this->close();
        return;
    }
    if(index == RTSA_SHIFT_ENABLE)
    {
        mControl->setShiftKeyEnable(true);
        this->close();
        return;
    }
    refreshEditDisplay(index);
    initButtonDisplay();
    return;
}

void RtSa_Dialog_Limit::on_pb_cancel_clicked()
{
    mInputDialog->hide();
    this->close();
    return;
}

void RtSa_Dialog_Limit::on_leMargin_clicked()
{
    showInputDialog(RTSA_INPUT_MARGIN);
//    ui->pbLimitMarginOn->setChecked(true);
//    ui->pbLimitTestMarginOff->setChecked(false);
    return;
}

void RtSa_Dialog_Limit::mLimitSelectGroup_click(int index)
{
    mControl->setCurLimit(index);
    initButtonDisplay();
    refreshButtonDisplay();
    return;
}

//void RtSa_Dialog_Limit::on_pbInsertRow_clicked()
//{
//    mControl->InsertLimitRow();
//    return;
//}

void RtSa_Dialog_Limit::DigitalKeyRespond(QKeyEvent *event)
{
    keyPressEvent(event);
    return;
}

void RtSa_Dialog_Limit::on_pb_toggle_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_toggle->setText("On");
    }
    else
    {
        ui->pb_toggle->setText("Off");
    }
    mControl->setCurLimitOn(mControl->getCurLimit(),checked);
    return;
}

void RtSa_Dialog_Limit::on_pb_EditMask_clicked()
{
    if(mLimitTable != NULL)
    {
        delete mLimitTable;
        mLimitTable = NULL;
    }
    mLimitTable = new RtSa_Dialog_LimitTable(mControl,mInputDialog,this);
    connect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
//    if(mLimitTable->isHidden())
//    {
//        mLimitTable->setGeometry(mapToGlobal(QPoint(0,0)).x()/*+this->width()*//*-RTSA_DIGITAL_DIALOG_WIDTH*/,\
//                                  mapToGlobal(QPoint(0,0)).y(),RTSA_DIGITAL_DIALOG_WIDTH,RTSA_DIGITAL_DIALOG_HEIGHT);
//    }
    mLimitTable->show();
    mLimitTable->setFocus();
    return;
}

void RtSa_Dialog_Limit::on_limitDestroyed()
{
    mLimitTable = NULL;
    this->setFocus();
    return;
}

//void RtSa_Dialog_Limit::on_lineEdit_clicked()
//{
//    showInputDialog(RTSA_INPUT_MARGIN);
//    return;
//}

void RtSa_Dialog_Limit::on_pb_Edge_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_Edge->setText("On");
    }
    else
    {
        ui->pb_Edge->setText("Off");
    }
    mControl->setMarginOn(mControl->getCurLimit(),checked);
    return;
}

void RtSa_Dialog_Limit::on_pb_LimitTest_toggled(bool checked)
{
    if(checked)
    {
        ui->pb_LimitTest->setText("On");
    }
    else
    {
        ui->pb_LimitTest->setText("Off");
    }
    mControl->setLimitTestOn(checked);
    return;
}

void RtSa_Dialog_Limit::on_pb_Upper_clicked()
{
    mControl->setLimitType(mControl->getCurLimit(),RTSA_UPPER);
    return;
}

void RtSa_Dialog_Limit::on_pb_Lower_clicked()
{
    mControl->setLimitType(mControl->getCurLimit(),RTSA_LOWER);
    return;
}

void RtSa_Dialog_Limit::on_pb_DeleteAll_clicked()
{
    mControl->DeleteAllLimit();
    return;
}

void RtSa_Dialog_Limit::BuildLimitFromTrace()
{
    if(mLimitTable == NULL)
    {
        mLimitTable = new RtSa_Dialog_LimitTable(mControl,mInputDialog,this);
        connect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
    }
    else
    {
        connect(mLimitTable,SIGNAL(destroyed()),this,SLOT(on_limitDestroyed()));
    }
    mLimitTable->initTable();
    mLimitTable->show();
//    mLimitTable->setFocus();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-06-14
*/
void RtSa_Dialog_Limit::on_Update()
{
    initMap();
    return;
}
/**
* @brief
* @param
* @Author Albert
* @date 2019-07-30
*/
void RtSa_Dialog_Limit::on_timeOut()
{
    timer->stop();
    qint32 LimitID = mControl->getCurLimit();
    qreal tempStepFreq = 0;

    if(!mInputDialog->isHidden())
    {
        mInputDialog->hide();
    }
    if(!mUpDownFlag)
    {
        mControl->setMargin(LimitID,mControl->getMargin(LimitID) + 1);
        refreshButtonDisplay();
    }
    else
    {
        mControl->setMargin(LimitID,mControl->getMargin(LimitID) - 1);
        refreshButtonDisplay();
    }
    return;
}
