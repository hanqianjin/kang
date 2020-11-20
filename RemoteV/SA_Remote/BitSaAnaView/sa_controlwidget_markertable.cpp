#include "sa_controlwidget_markertable.h"
#include "ui_sa_controlwidget_markertable.h"

sa_controlWidget_MarkerTable::sa_controlWidget_MarkerTable(user_variable &m_user_variable, QWidget *parent) :
    QWidget(parent),
    globalUserVariable(&m_user_variable),
    ui(new Ui::sa_controlWidget_MarkerTable)
{
    ui->setupUi(this);
    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);
}

sa_controlWidget_MarkerTable::~sa_controlWidget_MarkerTable()
{
    delete ui;
}

void sa_controlWidget_MarkerTable::on_pushButton_clicked()
{
    this->hide();
    emit signalHideTable(SA_MARKER_TABLE);
}
