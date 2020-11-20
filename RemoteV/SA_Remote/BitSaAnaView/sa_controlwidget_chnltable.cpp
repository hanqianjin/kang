#include "sa_controlwidget_chnltable.h"
#include "ui_sa_controlwidget_chnltable.h"

sa_controlWidget_ChnlTable::sa_controlWidget_ChnlTable(user_variable &m_user_variable, QWidget *parent) :
    QWidget(parent),
    globalUserVariable(&m_user_variable),
    ui(new Ui::sa_controlWidget_ChnlTable)
{
    ui->setupUi(this);
    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->verticalSlider->hide();
}

sa_controlWidget_ChnlTable::~sa_controlWidget_ChnlTable()
{
    delete ui;
}

void sa_controlWidget_ChnlTable::on_pushButton_clicked()
{
    this->hide();
    emit signalHideTable(SA_CHANNELPOWER_TABLE);
}
