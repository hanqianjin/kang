#include "sa_controlwidget_occupiedxdbtable.h"
#include "ui_sa_controlwidget_occupiedxdbtable.h"

sa_controlWidget_OccupiedXdBTable::sa_controlWidget_OccupiedXdBTable(user_variable &m_user_variable, QWidget *parent) :
    QWidget(parent),
    globalUserVariable(&m_user_variable),
    ui(new Ui::sa_controlWidget_OccupiedXdBTable)
{
    ui->setupUi(this);
    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->verticalSlider->hide();
}

sa_controlWidget_OccupiedXdBTable::~sa_controlWidget_OccupiedXdBTable()
{
    delete ui;
}

void sa_controlWidget_OccupiedXdBTable::on_pushButton_clicked()
{
    this->hide();
    emit signalHideTable(SA_OCCUPIEDXDB_TABLE);
}
