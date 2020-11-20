#include "hswinfo.h"
#include "ui_hswinfo.h"

hswinfo::hswinfo(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::hswinfo)
{
  ui->setupUi(this);
}

hswinfo::~hswinfo()
{
  delete ui;
}
