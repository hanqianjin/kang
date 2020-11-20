#include "pm_dialog_error.h"
#include "ui_pm_dialog_error.h"
#include "pm_define.h"

Pm_Dialog_Error::Pm_Dialog_Error(QString title, QString warning, QWidget *parent, qint32 mDisplay) :
    QDialog(parent),
    ui(new Ui::Pm_Dialog_Error),
    mTitle(title),
    mWarning(warning)
{
    ui->setupUi(this);
    initDisplay();
    qint32 x,y;
    x = (1280 - this->width())/2;
    y = (800 - this->height())/2;
    this->move(x,y);
    setProperty("status", pm_qssMode[mDisplay]);
}

Pm_Dialog_Error::~Pm_Dialog_Error()
{
    delete ui;
}
void Pm_Dialog_Error::initDisplay()
{
    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
}

void Pm_Dialog_Error::on_pb_ok_clicked()
{
    this->close();
}
