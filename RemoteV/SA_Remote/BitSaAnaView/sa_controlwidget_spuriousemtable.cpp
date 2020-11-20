#include "sa_controlwidget_spuriousemtable.h"
#include "ui_sa_controlwidget_spuriousemtable.h"

sa_ControlWidget_SpuriousEMTable::sa_ControlWidget_SpuriousEMTable(user_variable &m_user_variable, QWidget *parent) :
    QWidget(parent),
    globalUserVariable(&m_user_variable),
    ui(new Ui::sa_ControlWidget_SpuriousEMTable)
{
    ui->setupUi(this);
    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->verticalSlider->hide();
}

sa_ControlWidget_SpuriousEMTable::~sa_ControlWidget_SpuriousEMTable()
{
    delete ui;
}

void sa_ControlWidget_SpuriousEMTable::on_pushButton_clicked()
{
    this->hide();
    emit signalHideTable(SA_SPURIOUS_EM_TABLE);
}
