#include "sa_controlwidget_multiacptable.h"
#include "ui_sa_controlwidget_multiacptable.h"

sa_ControlWidget_MultiACPTable::sa_ControlWidget_MultiACPTable(user_variable &m_user_variable,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sa_ControlWidget_MultiACPTable)
{
    ui->setupUi(this);
    globalUserVariable = &m_user_variable;

    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->verticalSlider->hide();
}

sa_ControlWidget_MultiACPTable::~sa_ControlWidget_MultiACPTable()
{
    delete ui;
}

void sa_ControlWidget_MultiACPTable::on_pushButton_clicked()
{
    this->hide();
    emit signalHideTable(SA_MULTIACP_TABLE);
}
