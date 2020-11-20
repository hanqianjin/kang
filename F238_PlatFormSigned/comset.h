#ifndef COMSET_H
#define COMSET_H

#include <QWidget>

namespace Ui {
  class comset;
}

class comset : public QWidget
{
  Q_OBJECT

public:
  explicit comset(QWidget *parent = 0);
  ~comset();

private:
  Ui::comset *ui;
};

#endif // COMSET_H
