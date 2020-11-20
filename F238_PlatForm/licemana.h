#ifndef LICEMANA_H
#define LICEMANA_H

#include <QWidget>

namespace Ui {
  class licemana;
}

class licemana : public QWidget
{
  Q_OBJECT

public:
  explicit licemana(QWidget *parent = 0);
  ~licemana();

private:
  Ui::licemana *ui;
};

#endif // LICEMANA_H
