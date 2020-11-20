#ifndef NETWORKSET_H
#define NETWORKSET_H

#include <QWidget>

namespace Ui {
  class networkset;
}

class networkset : public QWidget
{
  Q_OBJECT

public:
  explicit networkset(QWidget *parent = 0);
  ~networkset();

private:
  Ui::networkset *ui;
};

#endif // NETWORKSET_H
