#include "timesetup.h"
#include "ui_timesetup.h"
#include <QTime>
#include <QKeyEvent>

timeSetup::timeSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeSetup)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint/* | Qt::Tool | Qt::WindowDoesNotAcceptFocus*/| Qt::Dialog);
    initDisplay();
}

timeSetup::~timeSetup()
{
    delete ui;
}

qint32 timeSetup::exec()
{
    initDisplay();
    ui->Edit_hour->setFocus();
    return QDialog::exec();
}

void timeSetup::initDisplay()
{
    QTime pTime = QTime::currentTime();
    ui->Edit_hour->setText(QString::number(pTime.hour()));
    ui->Edit_minu->setText(QString::number(pTime.minute()));
    ui->edit_sec->setText(QString::number(pTime.second()));
}

void timeSetup::on_up_hour_clicked()
{
    qint32 iVal = ui->Edit_hour->text().toInt();
    iVal = (iVal + 1) % 24;
    ui->Edit_hour->setText(QString::number(iVal));
}

void timeSetup::on_down_hour_clicked()
{
    qint32 iVal = ui->Edit_hour->text().toInt();
    iVal = (iVal + 23) % 24;
    ui->Edit_hour->setText(QString::number(iVal));
}

void timeSetup::on_up_minu_clicked()
{
    qint32 iVal = ui->Edit_minu->text().toInt();
    iVal = (iVal + 1) % 60;
    ui->Edit_minu->setText(QString::number(iVal));
}

void timeSetup::on_down_minu_clicked()
{
    qint32 iVal = ui->Edit_minu->text().toInt();
    iVal = (iVal + 59) % 60;
    ui->Edit_minu->setText(QString::number(iVal));
}

void timeSetup::on_up_sec_clicked()
{
    qint32 iVal = ui->edit_sec->text().toInt();
    iVal = (iVal + 1) % 60;
    ui->edit_sec->setText(QString::number(iVal));
}

void timeSetup::on_down_sec_clicked()
{
    qint32 iVal = ui->edit_sec->text().toInt();
    iVal = (iVal + 59) % 60;
    ui->edit_sec->setText(QString::number(iVal));
}

void timeSetup::keyPressEvent(QKeyEvent *event)
{
    qint32 keyVal = event->key();
    switch (keyVal) {
    case Qt::Key_F3:
        if(ui->Edit_hour->hasFocus())
        {
            on_up_hour_clicked();
        }else if(ui->Edit_minu->hasFocus())
        {
            on_up_minu_clicked();
        }else if(ui->edit_sec->hasFocus())
        {
            on_up_sec_clicked();
        }
        break;
    case Qt::Key_F4:
        if(ui->Edit_hour->hasFocus())
        {
            on_down_hour_clicked();
        }else if(ui->Edit_minu->hasFocus())
        {
            on_down_minu_clicked();
        }else if(ui->edit_sec->hasFocus())
        {
            on_down_sec_clicked();
        }
        break;
    case Qt::Key_Escape:
        this->close();
        break;
    default:
        break;
    }
}



void timeSetup::on_pb_ok_clicked()
{
    QString tstr = QString("%1:%2:%3").arg(ui->Edit_hour->text()).arg(ui->Edit_minu->text()).arg(ui->edit_sec->text());
    QString tdstr = "date -s " + QString(" \" ") + tstr + QString(" \" ");
    system(tdstr.toStdString().c_str());
    system("hwclock -w");
    close();
    return;
}

void timeSetup::on_pb_cancel_clicked()
{
    close();
    return;
}
