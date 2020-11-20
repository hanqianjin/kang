#include "f238scpi.h"
#include "ui_f238scpi.h"
#include "scpidef/scpidef.h"

F238SCPI::F238SCPI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::F238SCPI)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setGeometry(mapToGlobal(QPoint(0,0)).x(), +  mapToGlobal(QPoint(0,0)).y(),this->width(),this->height());

    SCPI_Communicate_Init();
}

F238SCPI::~F238SCPI()
{
    delete ui;
}
