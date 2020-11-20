#include "sa_controlwidget_spectrumemtable.h"
#include "ui_sa_controlwidget_spectrumemtable.h"

sa_ControlWidget_SpectrumEMTable::sa_ControlWidget_SpectrumEMTable(user_variable &m_user_variable, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sa_ControlWidget_SpectrumEMTable)
{
    ui->setupUi(this);
    globalUserVariable = &m_user_variable;

    setProperty("status",qssMode[m_user_variable.gDisplayMode]);
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::FramelessWindowHint /*| Qt::Dialog*/);

    ui->verticalSlider->hide();
}

sa_ControlWidget_SpectrumEMTable::~sa_ControlWidget_SpectrumEMTable()
{
    delete ui;
}
void sa_ControlWidget_SpectrumEMTable::on_pushButton_clicked()
{
    this->hide();
    emit signalHideTable(SA_SPECTRUM_EM_TABLE);
}
