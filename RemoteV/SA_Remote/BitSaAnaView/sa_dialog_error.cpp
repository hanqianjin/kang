#include "sa_dialog_error.h"
#include "ui_sa_dialog_error.h"

SA_Dialog_Error::SA_Dialog_Error(QString title, QString warning,QWidget *parent) :
    QDialog(parent),
    mTitle(title),
    mWarning(warning),
    ui(new Ui::SA_Dialog_Error)
{
    ui->setupUi(this);
    //setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initDisplay();
    qint32 x,y;
    x = (1280 - this->width())/2;
    y = (800 - this->height())/2;
    this->move(x,y);
}

SA_Dialog_Error::~SA_Dialog_Error()
{
    delete ui;
}
void SA_Dialog_Error::initDisplay()
{
    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
}

void SA_Dialog_Error::on_pb_ok_clicked()
{
    this->close();
}
void SA_Dialog_Error::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->close();
        return;
    }else if(event->key() == Qt::Key_PowerOff)
    {
        if(!event->isAutoRepeat())
            QApplication::sendEvent(this->parent(),event);
        return;
    }
}
