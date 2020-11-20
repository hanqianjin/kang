#include "comset.h"
#include "ui_comset.h"
#include "shmengine.h"

comset::comset(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::comset)
{
  ui->setupUi(this);
}

comset::~comset()
{
  delete ui;
}
