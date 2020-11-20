#include "sa_dialog_warning.h"
#include "ui_sa_dialog_warning.h"
#include <QDialogButtonBox>
#include <QAbstractButton>

SA_Dialog_Warning::SA_Dialog_Warning(QString title, QString warning, QWidget *parent) :
    QDialog(parent),
    mTitle(title),
    mWarning(warning),
    ui(new Ui::SA_Dialog_Warning)
{
    ui->setupUi(this);
    //setProperty("status",qssMode[mControl->GetDisplayMode()]);
    initDisplay();
    qint32 x,y;
    x = (1280 - this->width())/2;
    y = (800 - this->height())/2;
    this->move(x,y);
}

SA_Dialog_Warning::~SA_Dialog_Warning()
{
    delete ui;
}

void SA_Dialog_Warning::initDisplay()
{
    qint32 x,y;
//    QString strOK = "QPushButton{height:30px;width:80px;border-style: flat;background-image: url(:/sa/image/btn_ok_w80_nor.png);}\
//    QPushButton:pressed{background-image: url(:/sa/image/btn_ok_w80_click.png);}";
//    QString strCancel = "QPushButton{height:30px;width:80px;border-style: flat;background-image: url(:/sa/image/btn_cancel_w80_nor.png);}\
//            QPushButton:pressed{background-image: url(:/sa/image/btn_cancel_w80_click.png);}";
    ui->buttonBox->addButton("", QDialogButtonBox::YesRole);
    ui->buttonBox->addButton("", QDialogButtonBox::NoRole);
//    ui->buttonBox->buttons().at(0)->setStyleSheet(strOK);
//    ui->buttonBox->buttons().at(1)->setStyleSheet(strCancel);

    ui->buttonBox->buttons().at(0)->setText("OK");
    ui->buttonBox->buttons().at(1)->setText("Cancel");
    ui->buttonBox->buttons().at(0)->setObjectName(QStringLiteral("pb_ok"));
    ui->buttonBox->buttons().at(1)->setObjectName(QStringLiteral("pb_cancel"));
    ui->Title->setText(mTitle);
    ui->Warning->setText(mWarning);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}
void SA_Dialog_Warning::keyPressEvent(QKeyEvent *event)
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
