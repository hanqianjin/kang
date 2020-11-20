#include "sa_controlwidget_acptable.h"
#include "ui_sa_controlwidget_acptable.h"

sa_ControlWidget_ACPTable::sa_ControlWidget_ACPTable(user_variable &m_user_variable,QWidget *parent) :
    QWidget(parent),
    globalUserVariable(&m_user_variable),
    ui(new Ui::sa_ControlWidget_ACPTable)
{
    ui->setupUi(this);
    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->verticalSlider->hide();
}

sa_ControlWidget_ACPTable::~sa_ControlWidget_ACPTable()
{
    delete ui;
}

void sa_ControlWidget_ACPTable::on_pushButton_clicked()
{
    this->hide();
    emit signalHideTable(SA_ACP_TABLE);
}
