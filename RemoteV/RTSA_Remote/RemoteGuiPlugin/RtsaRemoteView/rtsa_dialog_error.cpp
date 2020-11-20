#include "rtsa_dialog_error.h"
#include "ui_rtsa_dialog_error.h"
#include "rtsa_define.h"

RtSa_Dialog_Error::RtSa_Dialog_Error(QString title, QString warning, QWidget *parent, qint32 mDisplay) :
    QDialog(parent),
    ui(new Ui::RtSa_Dialog_Error),
    mTitle(title),
    mWarning(warning)
{
    ui->setupUi(this);
    initDisplay();
    qint32 x,y;
    x = (1280 - this->width())/2;
    y = (800 - this->height())/2;
    this->move(x,y);
    setProperty("status", rtsa_qssMode[mDisplay]);
}

RtSa_Dialog_Error::~RtSa_Dialog_Error()
{
    delete ui;
}
void RtSa_Dialog_Error::initDisplay()
{
    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
}

void RtSa_Dialog_Error::on_pb_ok_clicked()
{
    this->close();
}
