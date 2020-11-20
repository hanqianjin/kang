#include "sysinfo.h"
#include "ui_sysinfo.h"

sysinfo::sysinfo(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::sysinfo)
{
  ui->setupUi(this);
}

sysinfo::~sysinfo()
{
  delete ui;
}
