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
    this->hide();
//    connect(mInputDialog,SIGNAL(finishEntry(qint32)),this,SLOT(on_finishEntry_measure(qint32)));
    initMap();
    initDisplay();
    setAttribute(Qt::WA_DeleteOnClose);
//    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
    mInputDialog = NULL;
    this->setFocus();
}

SA_Dialog_MeasureSetup::~SA_Dialog_MeasureSetup()
{
    delete ui;
    if(mInputDialog)
    {
        delete mInputDialog;
        mInputDialog = NULL;
    }
}
/**
 * @brief  Initialize map of indexes and controls.
 * @param  void
 * @author Tony
 * @since 2018-12-24
*/
void SA_Dialog_MeasureSetup::initMap()
{
//    mEditList.insert(INPUT_MANUAL_RBW,ui->RBWEdit);
//    mEditList.insert(INPUT_MANUAL_VBW,ui->VBWEdit);
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
//    refreshEditDisplay(INPUT_MANUAL_RBW);
//    refreshEditDisplay(INPUT_MANUAL_VBW);
//    refreshButtonDisplay();
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
//    case INPUT_MANUAL_RBW:
//        value = mControl->getRbwValue();
//        strGab = globalUserVariable->freqValueToQstring(value);
//        break;
//    case INPUT_MANUAL_VBW:
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
//    ui->RBWAutoPB->setChecked(mControl->getRbwStatus());
//    ui->VBWAutoPB->setChecked(mControl->getVbwStatus());
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
    this->close();
    return;
}

void SA_Dialog_MeasureSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyvalue = event->key();
    switch (keyvalue) {
    case Qt::Key_Escape:
        this->close();
        return;
    default:
        break;
    }
}
