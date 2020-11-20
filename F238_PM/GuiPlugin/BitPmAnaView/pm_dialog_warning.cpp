#include "pm_dialog_warning.h"
#include "ui_pm_dialog_warning.h"
#include <QDialogButtonBox>
#include <QAbstractButton>
#include "pm_define.h"

Pm_Dialog_Warning::Pm_Dialog_Warning(QString title, QString warning, QWidget *parent, qint32 mDisplay) :
    QDialog(parent),
    ui(new Ui::Pm_Dialog_Warning),
    mTitle(title),
    mWarning(warning)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window |Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
     this ->setWindowModality(Qt::WindowModal);
    strOK = "QPushButton{height:30px;width:80px;border-style: flat;background-image: url(:/pm/image/btn_ok_w80_nor.png);}\
    QPushButton:pressed{background-image: url(:/pm/image/btn_ok_w80_click.png);}";
    strCancel = "QPushButton{height:30px;width:80px;border-style: flat;background-image: url(:/pm/image/btn_cancel_w80_nor.png);}\
            QPushButton:pressed{background-image: url(:/pm/image/btn_cancel_w80_click.png);}";

    initDisplay();

    qint32 x,y;
    x = (1280 - this->width())/2;
    y = (800 - this->height())/2;
    this->move(x,y);
    setProperty("status",pm_qssMode[mDisplay]);
    setAttribute (Qt::WA_DeleteOnClose);
}

Pm_Dialog_Warning::~Pm_Dialog_Warning()
{
    delete ui;
}

void Pm_Dialog_Warning::initDisplay()
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

void Pm_Dialog_Warning::ShowYesButtonOnly()
{
    ui->buttonBox->hide();
    ui->buttonBox_2->show();

    ui->buttonBox_2->addButton("", QDialogButtonBox::YesRole);
//  ui->buttonBox_2->addButton("", QDialogButtonBox::NoRole);
    ui->buttonBox_2->buttons().at(0)->setStyleSheet(strOK);
//  ui->buttonBox_2->buttons().at(1)->setStyleSheet(strCancel);
    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
    connect(ui->buttonBox_2, SIGNAL(accepted()), this, SLOT(accept()));
//  connect(ui->buttonBox_2, SIGNAL(rejected()), this, SLOT(reject()));
    return;
}

void Pm_Dialog_Warning::NoShowButton()
{
    ui->buttonBox->hide();
    ui->buttonBox_2->hide();

    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
    return;
}

void Pm_Dialog_Warning::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Enter:
    case Qt::Key_Escape:
        break;
    }
}

void Pm_Dialog_Warning::closeDlg()
{
    this->close();
}

void Pm_Dialog_Warning::SerWaringText(QString strWarning)
{
    ui->Warning->setText(strWarning);
    connect(this, SIGNAL(accepted()), this, SLOT(accept()));
    return;
}
