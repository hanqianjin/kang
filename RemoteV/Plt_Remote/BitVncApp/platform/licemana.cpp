#include "licemana.h"
#include "ui_licemana.h"

licemana::licemana(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::licemana)
{
  ui->setupUi(this);
}

licemana::~licemana()
{
  delete ui;
}
