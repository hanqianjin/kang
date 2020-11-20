#ifndef DSDTSET_H
#define DSDTSET_H

#include <QWidget>

namespace Ui {
  class dsdtset;
}

class dsdtset : public QWidget
{
  Q_OBJECT

public:
  explicit dsdtset(QWidget *parent = 0);
  ~dsdtset();

private:
  Ui::dsdtset *ui;
};

#endif // DSDTSET_H
