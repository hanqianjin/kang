#include "networkset.h"
#include "ui_networkset.h"
#include "shmengine.h"

networkset::networkset(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::networkset)
{
  ui->setupUi(this);
}

networkset::~networkset()
{
  delete ui;
}
