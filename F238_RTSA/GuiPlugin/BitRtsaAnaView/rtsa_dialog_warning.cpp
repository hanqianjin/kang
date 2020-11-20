#include "rtsa_dialog_warning.h"
#include "ui_rtsa_dialog_warning.h"
#include <QDialogButtonBox>
#include <QAbstractButton>
#include "rtsa_define.h"
RtSa_Dialog_Warning::RtSa_Dialog_Warning(QString title, QString warning, QWidget *parent, qint32 mDisplay) :
    QDialog(parent),
    ui(new Ui::RtSa_Dialog_Warning),
    mTitle(title),
    mWarning(warning)
{
    ui->setupUi(this);
    strOK = "QPushButton{height:30px;width:80px;border-style: flat;background-image: url(:/rtsa/image/btn_ok_w80_nor.png);}\
    QPushButton:pressed{background-image: url(:/rtsa/image/btn_ok_w80_click.png);}";
    strCancel = "QPushButton{height:30px;width:80px;border-style: flat;background-image: url(:/rtsa/image/btn_cancel_w80_nor.png);}\
            QPushButton:pressed{background-image: url(:/rtsa/image/btn_cancel_w80_click.png);}";


    initDisplay();

    qint32 x,y;
    x = (1280 - this->width())/2;
    y = (800 - this->height())/2;
    this->move(x,y);
    setProperty("status",rtsa_qssMode[mDisplay]);
}

RtSa_Dialog_Warning::~RtSa_Dialog_Warning()
{
    delete ui;
}
void RtSa_Dialog_Warning::initDisplay()
{
//    qint32 x,y;
    ui->buttonBox_2->hide();
    ui->buttonBox->show();
    ui->buttonBox->addButton("", QDialogButtonBox::YesRole);
    ui->buttonBox->addButton("", QDialogButtonBox::NoRole);
    ui->buttonBox->buttons().at(0)->setStyleSheet(strOK);
    ui->buttonBox->buttons().at(1)->setStyleSheet(strCancel);
    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    return;

}

void RtSa_Dialog_Warning::ShowYesButtonOnly()
{
    ui->buttonBox->hide();
    ui->buttonBox_2->show();

    ui->buttonBox_2->addButton("", QDialogButtonBox::YesRole);
//    ui->buttonBox_2->addButton("", QDialogButtonBox::NoRole);
    ui->buttonBox_2->buttons().at(0)->setStyleSheet(strOK);
//    ui->buttonBox_2->buttons().at(1)->setStyleSheet(strCancel);
    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
    connect(ui->buttonBox_2, SIGNAL(accepted()), this, SLOT(accept()));
//    connect(ui->buttonBox_2, SIGNAL(rejected()), this, SLOT(reject()));
    return;
}
