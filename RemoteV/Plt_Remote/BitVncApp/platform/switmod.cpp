#include "switmod.h"
#include "ui_switmod.h"

switmod::switmod(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::switmod)
{
  ui->setupUi(this);
  this->setGeometry(mapToGlobal(parent->pos()).x() + 508,mapToGlobal(parent->pos()).y() + 360,this->width(),this->height());
}

switmod::~switmod()
{
  delete ui;
}
