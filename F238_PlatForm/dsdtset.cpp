#include "dsdtset.h"
#include "ui_dsdtset.h"

dsdtset::dsdtset(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::dsdtset)
{
  ui->setupUi(this);
}

dsdtset::~dsdtset()
{
  delete ui;
}
